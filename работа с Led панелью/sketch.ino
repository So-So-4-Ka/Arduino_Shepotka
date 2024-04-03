#define DDR_SPI DDRB
#define DD_MOSI PB2
#define DD_SCK PB1
#define DD_CS1 PB4
#define DD_CS PB0
 
void Transmit(char adr, char dt) { 
  PORTB &= ~1<<DD_CS;  
 // PORTC &= ~1<<DD_CS;  
  SPI_MasterTransmit(adr); 
  SPI_MasterTransmit(dt);  
  PORTB |= 1<<DD_CS;
 // PORTC |= 1<<DD_CS; 
}
 
void Transmit7219(char adr, char dt) { 
  PORTB &= ~1<<DD_CS1;  
 // PORTC &= ~1<<DD_CS;  
  SPI_MasterTransmit(adr); 
  SPI_MasterTransmit(dt);  
  PORTB |= 1<<DD_CS1;
 // PORTC |= 1<<DD_CS; 
}
void SPI_MasterTransmit(char cData)
{
// PORTB&= ~1<<PB0;
/* Start transmission */
SPDR = cData;
/* Wait for transmission complete */
while(!(SPSR & (1<<SPIF)))
{
}
} 

void SPI_MasterInit(void)
{
/* Set MOSI and SCK output, all others input */
DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_CS);
/* Enable SPI, Master, set clock rate fck/16 */
DDRB|= (1<<DD_CS1);
SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
PORTB|=1<<PB0; 
}






int main()
{
SPI_MasterInit();
  // put your setup code here, to run once:

while(1)
{ 
  for (int i = 0; i < 9; i++){ 
    for (int j = 0; j < 129; j++){ 
      Transmit(i,j);
      Transmit7219(i,j);
    } 
  }
  // Transmit(1,1); 
  // _delay_ms(100);
  // Transmit(1,2); 
  // _delay_ms(100);
  // Transmit(1,4);
  // _delay_ms(100);
  // Transmit(1,8);
  // _delay_ms(100);
  // Transmit(1,16); 
  // _delay_ms(100);
  // Transmit(1,32);
  // _delay_ms(100);
  // Transmit(1,64);
  // _delay_ms(100);
  // Transmit(1,128);
  // _delay_ms(100);
  // Transmit(2,64);
  // _delay_ms(100);
  // Transmit(3,32); 
  // _delay_ms(100);
  // Transmit(4,16);
  // _delay_ms(100);
  // Transmit(5,8);
  // _delay_ms(100);
  // Transmit(6,4);
  // _delay_ms(100);
  // Transmit(7,2);
  // _delay_ms(100);
  // Transmit(8,1);
  // _delay_ms(100);
  // Transmit(8,2);
  // _delay_ms(100);
  // Transmit(8,4);
  // _delay_ms(100);
  // Transmit(8,8);
  // _delay_ms(100);
  // Transmit(8,16);
  // _delay_ms(100);
  // Transmit(8,32);
  // _delay_ms(100); 
  // Transmit(8,64);
  // _delay_ms(100); 
  // Transmit(8,128); 
  // _delay_ms(100); 

// PORTB&= ~1<<PB0;
// SPI_MasterTransmit(0x01);
// SPI_MasterTransmit(0x01);
// PORTB|=1<<PB0;
//   _delay_ms(100);
//   PORTB=0xFF;
//  _delay_ms(100);
//     PORTB=0x00;
//   _delay_ms(100);
}
  // put your main code here, to run repeatedly:

}