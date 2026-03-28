// ===================== 实验3：呼吸灯 PWM 定义 =====================
const int ledPin = 2;
const int freq = 5000;
const int resolution = 8;

// ===================== 实验4：触摸引脚定义 =====================
#define TOUCH_PIN 4
int threshold = 25;
int touchValue;

// ===================== 3档位速度 =====================
int speedLevel = 1;
int delayTime = 6;

// ===================== 触摸防抖 =====================
bool lastTouch = false;
unsigned long lastDebounce = 0;
const long debounceDelay = 80;

// ===================== 呼吸灯平滑变量 =====================
int brightness = 0;
int fadeAmount = 5;

void setup() {
  Serial.begin(115200);
  delay(1000);
  ledcAttach(ledPin, freq, resolution);
}

void loop() {
  // ========================== 触摸检测 ==========================
  touchValue = touchRead(TOUCH_PIN);
  unsigned long now = millis();
  bool currentTouch = (touchValue < threshold);

  if (currentTouch != lastTouch) {
    lastDebounce = now;
  }

  if (now - lastDebounce > debounceDelay) {
    if (currentTouch == true && lastTouch == false) {
      speedLevel++;
      if (speedLevel > 3) speedLevel = 1;

      // ====================== 三档差距非常明显 ======================
      if (speedLevel == 1) delayTime = 40;   // 超慢  肉眼看得很清楚
      if (speedLevel == 2) delayTime = 15;   // 中等  节奏舒服
      if (speedLevel == 3) delayTime = 4;    // 较快  依然可见呼吸

      Serial.print("当前档位：");
      Serial.println(speedLevel);
    }
    lastTouch = currentTouch;
  }

  // ========================== 呼吸灯（不停） ==========================
  ledcWrite(ledPin, brightness);
  brightness += fadeAmount;

  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }

  delay(delayTime);
}
