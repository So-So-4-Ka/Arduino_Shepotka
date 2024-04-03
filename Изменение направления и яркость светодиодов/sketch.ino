// Определение портов для светодиодов и кнопки
#define LED_1 PD2
#define LED_2 PD3
#define LED_3 PD4
#define LED_4 PD5
#define LED_5 PD6
#define LED_6 PD7
#define BUT_1 PB0
#define BUT_2 PB1

// #define inc 10

uint32_t volatile buffer;
bool volatile direction = 1;
bool volatile buttonPressed = false;
uint8_t volatile brightnessLevel = 10; // Начальный уровень яркости (от 0 до 255)
int inc=10;
// Прерывание по совпадению таймера 1 (TIMER1_COMPA_vect)
ISR(TIMER1_COMPA_vect)
{
  if ((PINB & (1 << BUT_1)) == 0)
  {
    while ((PINB & (1 << BUT_1)) == 0)
    {
      PORTC = 1;
    }
    direction = !direction;
  }

  if (direction)
  {
    PORTD = buffer;
    PORTD = (PORTD >> 1) | (PORTD << 6);
    buffer = PORTD;
  }
  else
  {
    PORTD = buffer;
    PORTD = (PORTD << 1) | (PORTD >> 6);
    buffer = PORTD;
  }
}

// Прерывание по совпадению таймера 0 (TIMER0_COMPA_vect)
ISR(TIMER0_COMPA_vect)
{
  PORTC = 0;
  buffer = PORTD;
  PORTD = 0;

}

// Прерывание по переполнению таймера 0 (TIMER0_OVF_vect)
ISR(TIMER0_OVF_vect)
{
  PORTD = buffer;
  PORTC = 1;
  //OCR0A = brightnessLevel; // Применяем текущий уровень яркости
}

int main(void)
{
  // Настройка последовательной связи (предполагается, что Serial.begin(1152000) устанавливает скорость передачи данных)
  Serial.begin(115200);
  PORTD |= (1 << PD2);
  DDRC=1;
  // Настройка таймера 1
  TCCR1B |= (1 << CS12) | (0 << CS11) | (1 << CS10) | (1 << WGM12);  // Установка предделителя и режима
  TIMSK1 = (1 << TOIE1) | (1 << OCIE1A);  // Разрешение прерываний
  OCR1A = 2000;  // Задание значения для сравнения
  // Настройка второго таймера
  TCCR0A = (1 << WGM00) | (1 << WGM01);
  OCR0A = 250;
  TIMSK0 = (1 << TOIE0) | (1 << OCIE0A);  // Разрешение прерываний
  TCCR0B |= (1 << CS00) | (1<< CS01) /*| (0 << CS11) | (1 << CS10) | (1 << WGM12)*/;
  sei();  // Разрешение прерываний

  while (1) {
    // _delay_ms(100);
     Serial.println(OCR0A);

    
  if ((PINB & (1 << BUT_2)) == 0)
  {
    if (!buttonPressed)
    {
      buttonPressed = true;
      while ((PINB & (1 << BUT_2)) == 0)
      {_delay_ms(100);
        // brightnessLevel += inc;
        //else if (brightnessLevel >= 250) brightnessLevel = 10;
        OCR0A += inc;
      }
    }
  }
  else
  {
    buttonPressed = false;
  }
  }
}