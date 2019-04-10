/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package genetic;

import java.util.ArrayList;
import java.util.Random;

/**
 *
 * @author pedro.teixeira
 */
public class Populacao {
    
    private Tabuleiro [] tabuleiros;
    private ArrayList<Tabuleiro> matingPool;
    private int geracao;
    private boolean fim;
    
   public Populacao() {
        int popSize = Genetic.POPULACAO;
        this.tabuleiros = new Tabuleiro[popSize];
        for(int i = 0; i < popSize; i++) {
            this.tabuleiros[i] = new Tabuleiro(new DNA());
        }
        this.matingPool = new ArrayList<>();       
        this.geracao = 0;
        this.fim = false;
    }
    
    public void calculaFitness(){
        for(Tabuleiro tabulero : this.tabuleiros){
            tabulero.calculaFitness();
        }
    }
    
   public int getMaxFitness() {
        int max = 0;
        for(Tabuleiro t : this.tabuleiros) {
            int fitness = t.getFitness();
            max = fitness > max ? fitness : max;
        }
        return max;
    }
   
   public void selecaoNatural(){
       int maxFit = getMaxFitness();
       
       this.matingPool.clear();
       for(Tabuleiro tabuleiro : this.tabuleiros){
           int porcentagem = (tabuleiro.getFitness()/maxFit) * 100;
           
           for(int i = 0; i < porcentagem; i++){
               this.matingPool.add(tabuleiro);
           }
       }
   }
   
   public void novaGeracao(){
       Tabuleiro [] novaGeracao = new Tabuleiro[Genetic.POPULACAO];
       
       Random rand = new Random();
       for(int i = 0; i < this.tabuleiros.length; i++){
           int a = rand.nextInt(this.matingPool.size());
           int b = rand.nextInt(this.matingPool.size());
           
           DNA pai = this.matingPool.get(a).getDNA();
           DNA mae = this.matingPool.get(b).getDNA();
           
           DNA filho = pai.crossOver(mae);
           filho.mutate();
           
           novaGeracao[i]= new Tabuleiro(filho);
       }
       
       this.tabuleiros = novaGeracao;
       this.geracao++;
   }
   
       public void printaMelhor() {
        int maxFitness = 0;
        Tabuleiro best = null;
        
        for(Tabuleiro t : this.tabuleiros) {
            int fitness = t.getFitness();
            if(maxFitness < fitness) {
                maxFitness = fitness;
                best = t;
            }
        }
        
        if(maxFitness == (Genetic.QUEENS_QTD * (Genetic.QUEENS_QTD - 1)) / 2) {
            this.fim = true;
        }
               
        if(best != null) {
            best.getDNA().print();
            System.out.println("\nFitness: " + best.getFitness());
            System.out.println("Geracao: " + this.geracao);
        }      
    }
    
    public boolean getFim() {
        return this.fim;
    }
}
