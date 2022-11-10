#include <msp430.h>

#define BASE_PWM 1000 /* Valeur pour le TA1CCR0 */
#define BASE_PWM_WHEEL 800 /* Valeur nominal pour les roues */
#define TURN_PWM_WHEEL 300 /* Valeur virage pour les roues */
#define STOP_PWM_WHEEL 0 /* V9aleur arrêt pour les roues */

void engine_init(){

    // Frequence d’horloge 1MHz
    BCSCTL1= CALBC1_1MHZ;
    DCOCTL= CALDCO_1MHZ;

    // Entrée/Sortie
    P2DIR |= (BIT1|BIT2|BIT4|BIT5);
    P2DIR &= ~(BIT0|BIT3);

    // Sens avant des roues
    P2OUT &= ~(BIT1);
    P2OUT |= BIT5;

    // Selection fonction TA
    P2SEL |= (BIT2|BIT4);
    P2SEL2 &= ~(BIT2|BIT4);

    // Source SMCLK pour TimerA , mode comptage Up
    TA1CTL = TASSEL_2 | MC_1;

    // Activation mode de sortie n°7
    TA1CCTL1 |= OUTMOD_7;
    TA1CCTL2 |= OUTMOD_7;

    // Rapport Cyclique Arrêt
    TA1CCR0 = BASE_PWM;
    TA1CCR1 = STOP_PWM_WHEEL;
    TA1CCR2 = STOP_PWM_WHEEL;

}

void engine_forward(){

    // Sens Avant des Roues
    P2OUT &= ~(BIT1);
    P2OUT |= BIT5;

    // Rapport Cyclique Nominal
    TA1CCR1 = BASE_PWM_WHEEL;
    TA1CCR2 = BASE_PWM_WHEEL;

}

void engine_backward(){

    // Sens Arrière des Roues
    P2OUT &= ~(BIT5);
    P2OUT |= BIT1;

    // Rapport Cyclique Nominal
    TA1CCR1 = BASE_PWM_WHEEL;
    TA1CCR2 = BASE_PWM_WHEEL;

}

void engine_turn_left(){

    // Sens Avant des Roues
    P2OUT &= ~(BIT1);
    P2OUT |= BIT5;

    // Rapport Cyclique Virage Left
    TA1CCR1 = TURN_PWM_WHEEL;
    TA1CCR2 = BASE_PWM_WHEEL;

}

void engine_turn_right(){

    // Sens Avant des Roues
    P2OUT &= ~(BIT1);
    P2OUT |= BIT5;

    // Rapport Cyclique Virage Right
    TA1CCR1 = BASE_PWM_WHEEL;
    TA1CCR2 = TURN_PWM_WHEEL;

}

void engine_rotate_left(){

    // Sens Rotation Gauche des Roues
    P2OUT &= ~(BIT5|BIT1);

    // Rapport Cyclique Nominal
    TA1CCR1 = BASE_PWM_WHEEL;
    TA1CCR2 = BASE_PWM_WHEEL;

}

void engine_rotate_right(){

    // Sens Rotation Droite des Roues
    P2OUT |= (BIT5|BIT1);

    // Rapport Cyclique Nominal
    TA1CCR1 = BASE_PWM_WHEEL;
    TA1CCR2 = BASE_PWM_WHEEL;

}

void engine_stop(){

    // Sens Avant des Roues
    P2OUT &= ~(BIT1);
    P2OUT |= BIT5;

    // Rapport Cyclique Stop
    TA1CCR1 = STOP_PWM_WHEEL;
    TA1CCR2 = STOP_PWM_WHEEL;

}
