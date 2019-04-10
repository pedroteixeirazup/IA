/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package genetic;

/**
 *
 * @author pedro.teixeira
 */
public class Genetic {

    public static final int QUEENS_QTD = 8;
    public static final int POPULACAO = 30;
    
    public static void main(String[] args) {
       Populacao p = new Populacao();
        
        while(!p.getFim()) {
            p.calculaFitness();
            p.printaMelhor();
            p.selecaoNatural();
            p.novaGeracao();
        }
    }
}
