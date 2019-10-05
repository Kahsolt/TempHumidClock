/*
  DHT11 温湿度传感器
  Author: kahsolt
  Create Date: 2016-10-15
  Update Date: 2019/10/04
*/

/* 针脚定义 
#define DHT11_PIN 13        // 数字脚:IN+OUT
*/

int DHT11_Temperature;      // 温度
int DHT11_Humidity;         // 湿度
int DHT11_Checksum;         // 校验码
int DHT11_Data[40] = { 0 }; // 存放40个bit数据

void DHT11_Init() {
  pinMode(DHT11_PIN, INPUT_PULLUP);
}

boolean DHT11_Wakeup() {
  unsigned int timeout;
  unsigned long timestamp;

  pinMode(DHT11_PIN, OUTPUT);    // 设置接口模式为：输出
  digitalWrite(DHT11_PIN, LOW);  // 输出低电平20ms（>18ms）
  delay(20);
  digitalWrite(DHT11_PIN, HIGH); // 输出高电平40μs
  delayMicroseconds(40);
  digitalWrite(DHT11_PIN, LOW);

  pinMode(DHT11_PIN, INPUT);     // 设置接口模式：输入
  timeout = 10000;
  while (digitalRead(DHT11_PIN) != HIGH) // 越过80us低电平应答信号
    if (timeout-- == 0)          // 长时间不返回高电平，则失败
      return false;
  timeout = 30000;
  while (digitalRead(DHT11_PIN) != LOW) // 越过80us高电平数据接收通知信号
    if (timeout-- == 0)          // 长时间不返回低电平，则失败
      return false;
  return true;                   // 出现低电平，开始读数
}

void DHT11_Read() {
  if (!DHT11_Wakeup()) {
    if (SERIAL_ENABLE) Serial.println("[DHT11] fail to wakeup");
    return;
  }

  for (int i = 0; i < 40; i++) {
    while (digitalRead(DHT11_PIN) == LOW) { }
    // 当出现高电平时，记下时间time
    long timestamp = micros();
    while (digitalRead(DHT11_PIN) == HIGH) { }
    // 当出现低电平，记下时间，再减去刚才储存的time
    // 值若大于50μs，则为‘1’(70μs)，否则为‘0’(26~28μs)
    if (micros() - timestamp > 50)
      DHT11_Data[i] = 1;
    else
      DHT11_Data[i] = 0;
  }

  DHT11_Humidity = DHT11_Temperature = DHT11_Checksum = 0;
  for (int i = 0, j = 7; i < 8 && j >= 0; i++, j--) {
    DHT11_Humidity += DHT11_Data[i] << j;
    DHT11_Temperature += DHT11_Data[16 + i] << j;
    DHT11_Checksum += DHT11_Data[32 + i] << j;
  }

  if (DHT11_Humidity + DHT11_Temperature != DHT11_Checksum)
    if (SERIAL_ENABLE) Serial.print("[DHT11] data checksum mismatch");
}

void DHT11_Print() {
  if (!SERIAL_ENABLE) return;
  Serial.print("[DHT11] Temperature: ");
  Serial.print(DHT11_Temperature);
  Serial.print("°C    ");
  Serial.print("Humidity: ");
  Serial.print(DHT11_Humidity);
  Serial.println("%");
}
