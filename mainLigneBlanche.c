#include <msp430.h> 
#include <ADC.h>
#include <Afficheur.h>
#include <engine.h>

unsigned int val=0;

//#define BASE_PWM_WHEEL 200 /* Valeur nominal pour les roues */
//#define TURN_PWM_WHEEL 100 /* Valeur virage pour les roues */

/**
 * main.c
 */
   void init()
    {
        P2DIR|=BIT1;//ligne P2.2 en entr�e
        P2DIR|=BIT2;
        P2DIR|=BIT4;
        P2DIR|=BIT5;
        P2DIR|=BIT0;//Mettre la led rouge en sortie

        P1DIR &=~BIT2;//ligne P2.2 en entree Capteur A
        P1DIR &=~BIT1;//ligne P2.2 en entree Capteur B

        P2SEL|= BIT2;
        P2SEL|= BIT4;

        P2SEL2 &=~ BIT2;
        P2SEL2 &=~ BIT4;

        TA1CTL= TASSEL_2 | MC_1;
        TA1CCTL1 |= OUTMOD_7;
        TA1CCTL2 |= OUTMOD_7;

        TA1CCR0=5000;
        TA1CCR1=2000;
        TA1CCR2=2000;


    }
 void pivoter_gauche_avant()
      {
     TA1CCR1=1000;
            TA1CCR2=500;
      }

 void pivoter_droite_avant()
      {
     TA1CCR1=500;
            TA1CCR2=1000;
      }
  
  void avancer()
      {
      TA1CCR1=1000;
             TA1CCR2=1000;
      }
  
  void stop()
      {
      TA1CCR1=000;
             TA1CCR2=000;
      }

      void test()
      {

        //avancer();//le robot avance
        while(1)
        {


         if(((P1IN & BIT1) !=0) && ((P1IN & BIT2) !=0)  ) //les capteurs A et B captent la ligne noir
            {
                P1OUT|=BIT0;//On allume la LED rouge
                engine_forward();//le robot avance
            }
        else if(((P1IN & BIT1) ==0) && ((P1IN & BIT2) ==0)  ) //les capteurs A et B captent la ligne blanche
        {
            P1OUT&=~BIT0;//On allume la LED rouge
            engine_stop();
           //SI LE CAPTEUR GAUCHE EST DANS LE BLANC,pivoter à gauche
       }
        else if(((P1IN & BIT1) !=0) && ((P1IN & BIT2) ==0)  ) //le capteur A  capte la ligne blanche et le B capte la ligne noire
               {
                  // P1OUT&=~BIT0;//On allume la LED rouge

            engine_rotate_right();
                   //SI LE CAPTEUR GAUCHE EST DANS LE BLANC,pivoter à gauche
               }
       else if(((P1IN & BIT1) ==0) && ((P1IN & BIT2) !=0)  ) //le capteur B  capte la ligne blanche et le A capte la ligne noire
               {
                   //P1OUT&=~BIT0;//On allume la LED rouge
           engine_rotate_left();
                   //SI LE CAPTEUR GAUCHE EST DANS LE BLANC,pivoter à gauche
               }

      }
      }

int main(void)
{
//	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
//
//   ADC_init();
//   init();
//
//   P2OUT|=BIT1;
//          P2OUT&=~BIT5;
//
//
//          P1OUT |= BIT0;
//
    P1DIR &=~BIT2;//ligne P2.2 en entree Capteur A
          P1DIR &=~BIT1;//ligne P2.2 en entree Capteur B
    engine_init();
	while(1){

          test();

	        }

}
