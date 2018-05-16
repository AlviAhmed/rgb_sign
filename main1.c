/*PWM BY USING CTC MODE*/
    #define F_CPU 8000000UL
    
    #include <avr/io.h>
    #include <stdio.h>
    #include <util/delay.h>
    #include <avr/interrupt.h>

   
	#define numcolour 3

	
 	
	unsigned volatile int colourarray[numcolour][3] =  
	{ 
	{255,0,0}, 
	{0,0,255}, 
	{0,255,0} 
	}; 		
	/* 
    unsigned volatile int redduty = 0;  

    unsigned volatile int greenduty = 0;  

    unsigned volatile int blueduty = 0; 
    */
    //unsigned volatile int timekeeper; 
    unsigned volatile int boolduty = 0; 
    unsigned volatile int i = 0; 

    int main (void) { 
			 
		//OCR0A = redduty; /*The Output compare register (OC0x) is cleared on compare match between TCNT0 and OCR0x,*/ 
		//OCR0B = greenduty; 
		
		init();  
	
		unsigned int tempred; 
    	unsigned int tempgreen; 
 
    	
		
		while (1)  
	    { 	  

	    	 //_delay_ms(10); 
	    	 if (boolduty == i){ 
	    	 	PORTB |= _BV(PB0);
	    	 }  
	    	   if (boolduty == 255){ 
	    	 	PORTB &= ~ _BV(PB0); 
	    	 	boolduty = 0; 
	    	  	i += 5;
	 		} 
	 		
	    	 if (i >= 255){ 
	    	 	i = 0;
	    	 }
	    	
	    
		}
	 }
	    	
		
     

  

    void init(){  
    	DDRB |= ( (1 << PB0) | (1 << PB1) | (1 << PB4)); //enabling all output pins with pwm 
		TCCR0A |= ( (1 << WGM01) ); //enabling ctc mode
		TIMSK |= ((1 << TOIE0) | (1 << OCIE0A)); //overflow interrupt now enabled for timer 0
		sei();  
		OCR0A = 10;
		TCCR0B |=  ((1 << CS01)); // prescaler of 8 at input freq of 1000000 with 42 ticks gives about 3 khz
		PORTB &= ~ _BV(PB0);
		 
		

    } 


    ISR(TIMER0_COMPA_vect){ //when ever ctc hits the compare value, maybe can use this with the hardware pins  

    boolduty ++;

    }
 
	 ISR(TIMER0_OVF_vect){ /* The Timer/Counter Overflow Flag (TOV0) is set each time counter reaches TOP 
	 this means interrupt can be used to update compare value*/
    // PORTB |= (1 << PB0);
		
	}
  
