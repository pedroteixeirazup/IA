# Programa feito por: Pedro Henrique Faria Teixeira,
#                     João Daniel de Aquino Rufino.

# Predição de emails usando Naive Bayes, transformando as mensagens em inteiros,
# e treinando-as em arrays com classificadores de  Naive Bayes.
# Este programa possui um DATASET com mais de 5000 linhas de emails, classificandos como
# HAM e SPAM, o programa os utiliza para treinar e dar uma predição sobre mensagens spams e hams encontradas.
# Essa predição e a output final do programa.

import nltk
nltk.download('stopwords')
from nltk.corpus import stopwords
import string
import pandas as pd

from sklearn.model_selection import train_test_split
from sklearn.pipeline import Pipeline
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.feature_extraction.text import TfidfTransformer
from sklearn.naive_bayes import MultinomialNB
from sklearn.metrics import classification_report,confusion_matrix

messages = pd.read_csv('spam.csv', encoding='latin-1')
messages.drop(['Unnamed: 2','Unnamed: 3','Unnamed: 4'],axis=1,inplace=True)
messages = messages.rename(columns={'v1': 'class','v2': 'text'})

messages.head()

messages.groupby('class').describe()

messages['length'] = messages['text'].apply(len)

messages.hist(column='length',by='class',bins=50, figsize=(15,6))

messages['length'] = messages['text'].apply(len)

messages.hist(column='length',by='class',bins=50, figsize=(15,6))

def process_text(text):
    # '''
    # O que será coberto:
    # 1. Remover pontuação
    # 2. Remover palavras irrelevantes
    # 3. Lista de retorno de palavras de texto limpas
    # '''
    
    #1
    nopunc = [char for char in text if char not in string.punctuation]
    nopunc = ''.join(nopunc)
    
    #2
    clean_words = [word for word in nopunc.split() if word.lower() not in stopwords.words('english')]
    
    #3
    return clean_words


messages['text'].apply(process_text).head()

msg_train, msg_test, class_train, class_test = train_test_split(messages['text'],messages['class'],test_size=0.2)

pipeline = Pipeline([
    ('bow',CountVectorizer(analyzer=process_text)), # converte strings em contagens inteiras
    ('tfidf',TfidfTransformer()), # converte contagens inteiras para pontuações ponderadas do TF-IDF
    ('classifier',MultinomialNB()) # treina os numeros em vetores TF-IDF com classificador Naive Bayes
])

pipeline.fit(msg_train,class_train)

predictions = pipeline.predict(msg_test)

print(classification_report(class_test,predictions))
