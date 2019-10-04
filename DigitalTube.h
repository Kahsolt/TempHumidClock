/*
  八段数码管
  Author: kahsolt
  Create Date: ?
  Update Date: 2019/10/04
*/

/* 针脚定义 */
#define W1 A5
#define W2 A2
#define W3 A1
#define W4 12
#define a A4
#define b A0
#define c 10
#define d 8
#define e 7
#define f A3
#define g 11
#define dp 9
#define TUBE_REFRESH_INTERVAL 5
#define TUBE_CONTROL_PIN_NUM 4
#define TUBE_LED_PIN_NUM 8

int Tube_Control_Pins[] = { W1, W2, W3, W4 };
int Tube_LED_Pins[] = { a, b, c, d, e, f, g, dp };
char Tube_LookTable[] = {
  0x3F, 0x06, 0x5B, 0x4F, 0x66, 
  0x6D, 0x7D, 0x07, 0x7F, 0x6F, // '0' ~ '9'
  0x80, // '.' (10)
  0x39, // 'C' (11)
  0x76, // 'H' (12)
  0x40, // '-' (13)
};

void Tube_Off() {
  for (int i = 0; i < TUBE_CONTROL_PIN_NUM; i++)
    digitalWrite(Tube_Control_Pins[i], LOW);
  for (int i = 0; i < TUBE_LED_PIN_NUM; i++)
    digitalWrite(Tube_LED_Pins[i], HIGH);
}

void Tube_Init() {
  for (int i = 0; i < TUBE_CONTROL_PIN_NUM; i++)
    pinMode(Tube_Control_Pins[i], OUTPUT);
  for (int i = 0; i < TUBE_LED_PIN_NUM; i++)
    pinMode(Tube_LED_Pins[i], OUTPUT);
  Tube_Off();
}

void Tube_Write(int idx, int n) {
  Tube_Off();
  digitalWrite(Tube_Control_Pins[idx], HIGH);

  char val = ~Tube_LookTable[n];  // binary reverse
  for (int i = 0; i < TUBE_LED_PIN_NUM; i++) {
    digitalWrite(Tube_LED_Pins[i], val & 0x01);
    val >>= 1;
  }
}

void Tube_Display(int data[], float seconds) {
  long minisec = int(seconds * 1000);
  while (minisec > 0)
    for (int i = 0; i < TUBE_CONTROL_PIN_NUM && minisec > 0; i++) {
      Tube_Write(i, data[i]);
      delay(TUBE_REFRESH_INTERVAL);
      minisec -= TUBE_REFRESH_INTERVAL;
    }
}

void Tube_Test() {
  int temp[4] = { 3, 7, 10, 11 };
  Tube_Display(temp, 2.5);
  Tube_Off();

  int hum[4] = { 5, 6, 10, 12 };
  Tube_Display(hum, 2.5);
  Tube_Off();
}
