package genetic;

import java.util.Random;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author pedro.teixeira
 */
public class DNA {
    
    private int [] gene;
    
    public DNA(){
        this.gene = randomize();
    }
    
    public DNA(int [] gene){
        this.gene = gene;
    }
    
    
    private int[] randomize() {
        int g[] = new int[Genetic.QUEENS_QTD];
        
        Random rand = new Random();
        for(int i = 0; i < g.length; i++) {
            g[i] = rand.nextInt(g.length);
        }
        
        return g;
    }
    
    public DNA crossOver(DNA mae){
        int [] filho = new int[this.gene.length];
        int mid = this.gene.length/2; //Pode ser randomizado para melhorar ou piorar.
        
        for(int i = 0 ; i < this.gene.length; i++){
            filho[i] = mid < i ? this.geneAt(i) : mae.geneAt(i);
        }
        return new DNA(filho);
    }
    
    public void mutate (){
        float rate = 0.05f;
        
        Random rand = new Random();
        
        for(int i = 0; i < this.gene.length; i++){
            if(rate > rand.nextFloat()){
                this.gene[i] =  rand.nextInt(this.gene.length);
            }
        }
    }
    
     public void print() {
        for(int i = 0; i < this.gene.length; i++) {
            System.out.print(this.gene[i] + " ");
        }
    }
    
    public int geneAt(int pos) {
        return this.gene[pos];
    }
}
