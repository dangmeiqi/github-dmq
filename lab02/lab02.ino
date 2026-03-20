// 定义板载LED引脚，避免使用"魔法数字"
#define LED_PIN 2
#define LED_R 4
#define LED_B 22

void setup() {
  // 初始化串口通信
  Serial.begin(115200);
  // 初始化板载LED引脚为输出模式
  pinMode(LED_PIN, OUTPUT); 
  pinMode(LED_R, OUTPUT);
  pinMode(LED_B, OUTPUT);
}

void loop() {
  Serial.println("Hello ESP32!");
  digitalWrite(LED_PIN, HIGH);   // 点亮LED红
  digitalWrite(LED_R, HIGH);   // 点亮LED绿
  digitalWrite(LED_B, HIGH);   // 点亮LED黄
  delay(1000);                   // 等待1秒
  digitalWrite(LED_PIN, LOW);    // 熄灭LED红
  digitalWrite(LED_R, LOW);    // 熄灭LED绿
  digitalWrite(LED_B, LOW);    // 熄灭LED黄
  delay(1000);              // 等待1秒
}