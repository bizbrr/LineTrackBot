#include <msp430.h>
#include "ADC.h"

unsigned int mesure = 0;

void obstacle_init(){


    // Entr�e/Sortie
    P1DIR &= ~BIT4;

    // Valeur mesur�e
    mesure = 0;

}

//Retourne une valeur de seuil suivant la proximit� de l'obstacle
int detect_obstacle(){

    ADC_Demarrer_conversion(4);
    mesure = ADC_Lire_resultat();
    if(mesure < 600){
        return 1; //Pas d'obstacle
    }
    else if(mesure < 700){
        return 2; //Danger
    }
    else{
        return 3; //Critique
    }


}

