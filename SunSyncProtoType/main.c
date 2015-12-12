/*
 * SunSyncProtoType.c
 *
 * Created: 12/8/2015 12:09:43 PM
 * Author : josh
 */ 

#include <avr/io.h>

#define F_CPU 1000000UL // 4Mhz
#include <util/delay.h>


void setup() {
	
	// Set pins to output so timer outputs will show up on them
	DDRB |= _BV(0);			// Cold		
	DDRB |= _BV(1);			// Warm	
	
	// Timer in Fast PWM mode
	// Output A clears on match
	// Output B sets on match
	
	TCCR0A = _BV(COM0A1) | _BV( COM0B1 ) |  _BV( COM0B0 ) | _BV( WGM01 ) | _BV( WGM00 );
	
	// No prescaler
	
	TCCR0B = _BV( CS00 ) ;
	
}

inline void setCold( int x ) {
	
	OCR0A= x;
	
}

inline void set( int x ) {
	
	OCR0A= x;
	
}



int main(void)
{
	
	setup();
	
	DDRB |= _BV(2);
	
	/*
	
	OCR0A = (20*255)/100;
	OCR0B = (30*255)/100;
	while(1);
	
	*/
	
	
	
    /* Replace with your application code */
    while (1) 
    {
		/*
		for(int x=128;x>=1;x--) {
			OCR0A = x;
			OCR0B = x;
			_delay_ms(100);
		}
		*/
		
		
		//Trigger scope
		PORTB |= _BV(2);
		_delay_ms(1);
		PORTB &= ~_BV(2);
		
		
		// Give 'em two quick 5 second cycles just so they know it is working
		for(int c=0; c<2;c++) {
		
			for(int x=0;x<254;x++) {
				OCR0A = x;
				OCR0B = x;
				_delay_ms( (5*1000) / 254 );
			}
			
		}
		
		
		// Now do an infinte series of 1 minute cycles
		
		while (1) {
			
			
			// Flash off for 1/2 second to sugnalo new day 
			OCR0A = 0;
			OCR0B = 255;
			_delay_ms(500);
			
			
			// ramp up to full blue for first 1/3 of day
			
			for(int x=128;x>0;x--) {
				OCR0A = x;
				OCR0B = x;
				_delay_ms( (60*1000UL)/ (254+128) );
			}
			
			
			// spend last 2/3s of day ramping from full blue to full red
			
			for(int x=0;x<254;x++) {
				OCR0A = x;
				OCR0B = x;
				_delay_ms( (60*1000UL)/ (254+128) );
			}
			
			
		}
		
		/*
		// blink 3 times to indicate switchover
		
		for(int x=0; x<1 ; x++) {
			
			OCR0A = 255;
			OCR0B = 0; 
			
			_delay_ms(500);

			OCR0A = 0;
			OCR0B = 255;
			
			_delay_ms(500);
			
			
		}
		*/

		
    }
}

