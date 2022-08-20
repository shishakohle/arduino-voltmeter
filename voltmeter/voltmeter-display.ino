#define PIN_20                A5
#define PIN_40                A4
#define PIN_60                A3
#define PIN_80                A2
#define PIN_100               A1
#define PIN_NORTH              7
#define PIN_SOUTH              1
#define PIN_NORTHEAST          8
#define PIN_SOUTHEAST         10
#define PIN_SOUTHWEST          0
#define PIN_NORTHWEST          2
#define PIN_CENTER             3
#define PIN_DOT                9
#define PIN_LED_BAR_SEL        5
#define PIN_DIGIT_LEFT_SEL     4
#define PIN_DIGIT_RIGHT_SEL    6

#define PERIPHERAL_SELECT      LOW
#define PERIPHERAL_DESELECT    HIGH
#define PERIPHERAL_FLASH       HIGH
#define PERIPHERAL_UNFLASH     LOW

#define ZERO    {1, 1, 1, 1, 1, 1, 0}
#define ONE     {0, 0, 1, 1, 0, 0, 0}
#define TWO     {1, 1, 1, 0, 1, 0, 1}
#define THREE   {1, 1, 1, 1, 0, 0, 1}
#define FOUR    {0, 0, 1, 1, 0, 1, 1}
#define FIVE    {1, 1, 0, 1, 0, 1, 1}
#define SIX     {1, 1, 0, 1, 1, 1, 1}
#define SEVEN   {1, 0, 1, 1, 0, 0, 0}
#define EIGHT   {1, 1, 1, 1, 1, 1, 1}
#define NINE    {1, 1, 1, 1, 0, 1, 1}

struct digit
{
  bool north, south, northeast, southeast, southwest, northwest, center;
};

struct digit digits[10] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};

void init_display()
{
  pinMode(PIN_20             , OUTPUT);
  pinMode(PIN_40             , OUTPUT);
  pinMode(PIN_60             , OUTPUT);
  pinMode(PIN_80             , OUTPUT);
  pinMode(PIN_100            , OUTPUT);
  pinMode(PIN_NORTH          , OUTPUT);
  pinMode(PIN_SOUTH          , OUTPUT);
  pinMode(PIN_NORTHEAST      , OUTPUT);
  pinMode(PIN_SOUTHEAST      , OUTPUT);
  pinMode(PIN_SOUTHWEST      , OUTPUT);
  pinMode(PIN_NORTHWEST      , OUTPUT);
  pinMode(PIN_CENTER         , OUTPUT);
  pinMode(PIN_DOT            , OUTPUT);
  pinMode(PIN_LED_BAR_SEL    , OUTPUT);
  pinMode(PIN_DIGIT_LEFT_SEL , OUTPUT);
  pinMode(PIN_DIGIT_RIGHT_SEL, OUTPUT);

  digitalWrite(PIN_LED_BAR_SEL    , PERIPHERAL_DESELECT);
  digitalWrite(PIN_DIGIT_LEFT_SEL , PERIPHERAL_DESELECT);
  digitalWrite(PIN_DIGIT_RIGHT_SEL, PERIPHERAL_DESELECT);
}

void flash_LED_bar(int percentage)
{
  digitalWrite(PIN_LED_BAR_SEL, PERIPHERAL_SELECT);
  
  digitalWrite(PIN_20 , PERIPHERAL_UNFLASH);
  digitalWrite(PIN_40 , PERIPHERAL_UNFLASH);
  digitalWrite(PIN_60 , PERIPHERAL_UNFLASH);
  digitalWrite(PIN_80 , PERIPHERAL_UNFLASH);
  digitalWrite(PIN_100, PERIPHERAL_UNFLASH);

  switch(percentage/20)
  {
    case 5: digitalWrite(PIN_100, PERIPHERAL_FLASH);
    case 4: digitalWrite(PIN_80 , PERIPHERAL_FLASH);
    case 3: digitalWrite(PIN_60 , PERIPHERAL_FLASH);
    case 2: digitalWrite(PIN_40 , PERIPHERAL_FLASH);
    case 1: digitalWrite(PIN_20 , PERIPHERAL_FLASH);
  }
}

void flash_digit(int digit)
{
  digit = abs(digit) % 10;
  
  digitalWrite(PIN_NORTH    , digits[digit].north     ? PERIPHERAL_FLASH : PERIPHERAL_UNFLASH);
  digitalWrite(PIN_SOUTH    , digits[digit].south     ? PERIPHERAL_FLASH : PERIPHERAL_UNFLASH);
  digitalWrite(PIN_NORTHEAST, digits[digit].northeast ? PERIPHERAL_FLASH : PERIPHERAL_UNFLASH);
  digitalWrite(PIN_SOUTHEAST, digits[digit].southeast ? PERIPHERAL_FLASH : PERIPHERAL_UNFLASH);
  digitalWrite(PIN_SOUTHWEST, digits[digit].southwest ? PERIPHERAL_FLASH : PERIPHERAL_UNFLASH);
  digitalWrite(PIN_NORTHWEST, digits[digit].northwest ? PERIPHERAL_FLASH : PERIPHERAL_UNFLASH);
  digitalWrite(PIN_CENTER   , digits[digit].center    ? PERIPHERAL_FLASH : PERIPHERAL_UNFLASH);
}

void flash_number(float number)
{
  // seperate float into digits before and after the decimal point
  int after = round( abs(number*10) );
  int before = after / 10;
  after -= before*10;

  // flash left digit (including decimal point) for 10ms
  digitalWrite(PIN_DIGIT_LEFT_SEL, PERIPHERAL_SELECT); // TODO write a select_left() and select_right()
  flash_digit(before);
  digitalWrite(PIN_DOT, PERIPHERAL_FLASH);
  delay(10);
  digitalWrite(PIN_DIGIT_LEFT_SEL, PERIPHERAL_DESELECT);

  // flash right digit for 10ms
  digitalWrite(PIN_DIGIT_RIGHT_SEL, PERIPHERAL_SELECT);
  flash_digit(after);
  digitalWrite(PIN_DOT, PERIPHERAL_UNFLASH);
  delay(10);
  digitalWrite(PIN_DIGIT_RIGHT_SEL, PERIPHERAL_DESELECT);
}
