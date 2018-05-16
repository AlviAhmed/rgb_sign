/*WORKING RGB PWM WITH ATTINY 85*/
    #define F_CPU 1000000UL
    
    #include <avr/io.h>
    #include <stdio.h>
    #include <util/delay.h>
    #include <avr/interrupt.h>
	#define numcolour 3

	
 	
	unsigned volatile int colourarray[numcolour][3] =  
	{ 
	{250,0,0}, 
	{0,250,0}, 
	{0,0,250}
	}; 		
	
    unsigned volatile int redduty = 0;  

    unsigned volatile int greenduty = 0;  

    unsigned volatile int blueduty = 0; 
    

    unsigned volatile int i = 0; 

    int main (void) { 
		init();  
	
		unsigned int tempred; 
    	unsigned int tempgreen; 
 		unsigned int tempblue;
    
		
		while (1)  
	    { 	  
	    	_delay_ms(15);  
	    	
	    	tempred = ( colourarray[i][0]); 
	    	tempgreen = ( colourarray[i][1]); 
	    	tempblue = ( colourarray[i][2]);   

	    	if(redduty < tempred) {redduty ++ ;} 
			if(redduty > tempred){redduty --;}  
			

			if (greenduty < tempgreen){greenduty ++;} 
			if(greenduty > tempgreen) {greenduty --;} 

			if (blueduty < tempblue){blueduty ++;} 
			if(blueduty > tempblue){blueduty --;}

	    	
	    	if ((redduty == tempred) && (greenduty == tempgreen) && (blueduty == tempblue)){ 
	    		i++;
	    		if (i > numcolour){ 
	    			i = 0;  
	    		}
	    	} 

	    	
	    
		}
	 }
	    	
		
     

  

    void init(){  
    	DDRB |= ( (1 << PB0) | (1 << PB1) | (1 << PB4)); //enabling all output pins with pwm 
		TCCR0A |= ( (1 << WGM01) | (1 << WGM00) | (1 << COM0A1) | (1 << COM0B1)); /* 
		enabling pwm mode for OC0A & OC0B, clearing on match*/  
		GTCCR |= ((1 << PWM1B) | (1 << COM1B1) ); //enabling pwm for pin PB4
		TIMSK |= ((1 << TOIE0) | (1 << TOIE1)); //enabling overflow timer 0 and 1 
		sei();  
		
		TCCR1 |= (1 << CS12); // prescaler of 8 for timer 1
		TCCR0B |=  ((1 << CS01)); // prescaler of 8 at input freq of 1000000 with 42 ticks gives about 3 khz
		//PORTB &= ~ _BV(PB0);
		 
		

    } 


 
	 ISR(TIMER0_OVF_vect){ /* The Timer/Counter Overflow Flag (TOV0) is set each time counter reaches TOP 
	 this means interrupt can be used to update compare value*/
    	OCR0A = redduty;
		OCR0B = greenduty;
		
	} 

	ISR(TIMER1_OVF_vect){  
		OCR1B = blueduty;

	}
  
