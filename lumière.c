int detecte_lumi�re()
{
    P1DIR &= ~BIT4; // capteur de lumi�re


    ADC_Demarrer_conversion(0x04); // le port P1.4 correspond au capteur de lumi�re
    lum = ADC_Lire_resultat();

    return lum;
}

void lumiere()

{
    P1DIR &= ~BIT4; // capteur de lumi�re


    ADC_Demarrer_conversion(0x04); // le port P1.4 correspond au capteur de lumi�re
    lum = ADC_Lire_resultat();

    while (detecte_lumi�re < 200)
        {
            tourner_droite();
        }

    __delay_cycles(10000);
}
