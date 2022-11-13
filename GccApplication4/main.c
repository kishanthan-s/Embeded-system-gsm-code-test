#include<avr/io.h>
#define F_CPU 16000000UL
#define BAUD 9600
#define UBRR_VALUE ((F_CPU/16/BAUD)-1)
#include<util/delay.h>
void usartinit();
unsigned char rxvalue(void);
unsigned char rxdata,a,cmd,b;
unsigned int z;
unsigned char message[15];
unsigned char cmd1[]={"AT"};
unsigned char cmd2[]={"AT+CMGF=1"};
unsigned char cmd3[]={"AT+CMGS="};
unsigned char cmd4[]={"Hi"};
unsigned char cmd5[]={"94774688266"};

int main ()
{
	DDRD|=0B00001000;
	DDRD&=0B11111011;
	
	_delay_ms(50);
	usartinit();
	
	UDR0 = ('"');
	_delay_ms(100);

	for(z=0;cmd5[z]!=' ';z++)
	{
		UDR0 = cmd5[z];
		_delay_ms(100);
	}

	UDR0 = ('"');
	_delay_ms(100);

	UDR0 = ('\r');
	_delay_ms(500);

	for(z=0;cmd4[z]!=' ';z++)
	{
		UDR0 = cmd4[z];
		_delay_ms(100);
	}

	UDR0 = (26);
	_delay_ms(100);

	while(1)
	{

		b=rxvalue();

		while (b!='+') 
		{

			b=rxvalue();

		}
		b=rxvalue();
		if(b=='C')
		{ b=rxvalue();
			if(b=='M')
			{
				b=rxvalue();
				if(b=='T')
				{
					b=rxvalue();
					if(b==':')
					{

						b=rxvalue();
						while (b!=0x0a) 
						{

							b=rxvalue();

						}
						b=rxvalue();

						message[0]=b;
						b=rxvalue();
						message[1]=b;
						b=rxvalue();
						message[2]=b;
						b=rxvalue();
						message[3]=b;
						b=rxvalue();
						message[4]=b;
						b=rxvalue();
						message[5]=b;
						

					}
				}
			}
		}

	}
}

void usartinit()
{
	UBRR0H =(unsigned char)(UBRR_VALUE>>8);
	UBRR0L =(unsigned char) (UBRR_VALUE);
	UCSR0B =(1<<RXCIE0) | (1<<RXEN0) | (1<<TXEN0);
	UCSR0C =(3<<UCSZ00);
	
}
unsigned char rxvalue(void)
{
	while(!(UCSR0A & (1<<RXC0)));
	{
		rxdata=UDR0;
		return rxdata;
	}
}