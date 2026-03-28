#define TOUCH_PIN 4
#define LED_PIN   2
#define THRESHOLD 20

bool ledState = LOW;
volatile bool touchTriggered = false;  // 中断触发标志
unsigned long lastTouchTime = 0;
unsigned long debounceDelay = 50;

// 中断服务函数（ISR）
void gotTouch() {
  touchTriggered = true;
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledState);
  // 绑定触摸中断
  touchAttachInterrupt(TOUCH_PIN, gotTouch, THRESHOLD);
}

void loop() {
  // 主循环处理中断事件（带防抖）
  if (touchTriggered) {
    unsigned long now = millis();
    if (now - lastTouchTime > debounceDelay) {
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);
      Serial.print("LED 状态翻转: ");
      Serial.println(ledState ? "亮" : "灭");
      lastTouchTime = now;
    }
    touchTriggered = false;  // 清除触发标志
  }
}
