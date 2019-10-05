/*
  MG45 光敏电阻
  Author: kahsolt
  Create Date: 2016-11-28
  Update Date: 2019/10/04
*/

/* 针脚定义 
#define MG45_PIN A7     // 模拟脚:IN
*/

float MG45_Analog_Value;

void MG45_Init() {
  pinMode(MG45_PIN, INPUT_PULLUP);
}

void MG45_Read() {
  MG45_Analog_Value = analogRead(MG45_PIN);
}

void MG45_Print() {
  if (!SERIAL_ENABLE) return;
  Serial.print("[MG45] Analog Value: ");
  Serial.println(MG45_Analog_Value);
}
