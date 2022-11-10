#include <msp430.h>
#include "ADC.h"
#include "engine.h"


unsigned int lum;
unsigned int var;



int detecte_lumiere()
{


    ADC_Demarrer_conversion(5); // le port P1.5 correspond au capteur de lumière
    lum = ADC_Lire_resultat();

    return lum;
}

void lumiere()

{
    while (detecte_lumiere() > 20)
        {
            engine_rotate_right();
        }
    engine_stop();
    __delay_cycles(10000);
}

/**
 * main.c
 */

int main(void)
{


    ADC_init();
    engine_init();
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog time
    P1DIR &= ~BIT5; // capteur de lumière

        lumiere();

}
