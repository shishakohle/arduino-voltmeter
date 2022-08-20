#define PIN_ADC_INPUT   A0
#define VREF            5.0

void setup()
{
  pinMode(PIN_ADC_INPUT, INPUT);
  init_display();
}

void loop()
{
  int conversion_result = analogRead(PIN_ADC_INPUT);
  float voltage = conversion_result * (VREF / 1023);
  flash_number(voltage);
  int percentage = 100*(voltage / VREF);
  flash_LED_bar(percentage);
}
