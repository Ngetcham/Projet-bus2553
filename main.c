#include <msp430.h> 



void demarrer();
void avancer();
void reculer();
void tournerGauche();
void tournerDroite();
void stop();
int aDemarre = 0;

//fonction avancer
void avancer(){

        P2OUT |= BIT5;
        P2OUT &= ~BIT1;
        TA1CCR2 = 100;
        TA1CCR1 = 100;
}

//fonction reculer
void reculer(){

        P2OUT&=~BIT5;
        P2OUT|=BIT1;
        TA1CCR2 = 100;
        TA1CCR1 = 100;

}



//fonction tourner gauche
void tournerGauche(){
        P2OUT|=BIT5;
        P2OUT&=~BIT1;
        TA1CCR2 = 60;
        TA1CCR1 = 100;

}

//fonction tourner droite
void tournerDroite(){
        P2OUT|=BIT5;
        P2OUT&=~BIT1;
        TA1CCR1 = 60;
        TA1CCR2 = 100;
}

void demarrer(){

    WDTCTL = WDTPW + WDTHOLD;
    BCSCTL1= CALBC1_1MHZ;
    DCOCTL= CALDCO_1MHZ;

    P2DIR |= BIT2; // P2.2 en sortie
    P2SEL |= BIT2; // selection fonction TA1.1
    P2SEL2 &= ~BIT2; // selection fonction TA1.1

    TA1CTL = TASSEL_2 | MC_1; // source SMCLK pour TimerA (no 2), mode comptage Up
    TA1CCTL1 |= OUTMOD_7; // activation mode de sortie n°7

    TA1CCR0 = 100; // determine la periode du signal
                    // determine le rapport cyclique du signal

    P2DIR |= BIT4; // P2.4 en sortie
    P2SEL |= BIT4; // selection fonction TA1.2
    P2SEL2 &= ~BIT4; // selection fonction TA1.2

    TA1CCTL2 |= OUTMOD_7; // activation mode de sortie n°7
                    // determine le rapport cyclique du signal




    P1DIR|=BIT1;
    P1SEL |= BIT1;
    P1SEL2 &= ~BIT1;
    TA0CTL = (TASSEL_2 | ID_3| MC_3|TAIE);
    TA0CCR0 = 63000;

    P2DIR |= (BIT1 | BIT2 | BIT4 | BIT5);
    aDemarre = 1;
    P1DIR&=~(BIT2|BIT0|BIT4);
}

void stop(){
        TA1CCR1 = 0;
        TA1CCR2 = 0;
        aDemarre=0;
}

/**
 * main.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	   demarrer(aDemarre);
	   avancer();
	   // reculer();
	    //tournerGauche();

	   // tournerDroite();
	
}
