// ===================== 双通道PWM 警车双闪灯效 =====================
const int ledPinA = 2;    // 第一个LED引脚（对应灯A）
const int ledPinB = 4;    // 第二个LED引脚（对应灯B）
const int freq = 5000;    // PWM频率 5000Hz（与实验3一致）
const int resolution = 8; // 分辨率 8位（0-255）

// 呼吸灯变量
int dutyCycle = 0;        // 公共占空比（控制A灯亮度）
int fadeAmount = 3;        // 渐变步长（越小越平滑）

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  // 初始化两个独立PWM通道
  ledcAttach(ledPinA, freq, resolution);
  ledcAttach(ledPinB, freq, resolution);
  
  // 初始状态：A灯灭，B灯最亮（反相起始）
  ledcWrite(ledPinA, 0);
  ledcWrite(ledPinB, 255);
}

void loop() {
  // ===================== 核心反相逻辑 =====================
  // 灯A：占空比 = dutyCycle（0→255 渐变）
  ledcWrite(ledPinA, dutyCycle);
  // 灯B：占空比 = 255 - dutyCycle（255→0 渐变，与A完全反相）
  ledcWrite(ledPinB, 255 - dutyCycle);

  // 更新占空比
  dutyCycle += fadeAmount;

  // 边界处理：到达极值后反向
  if (dutyCycle <= 0 || dutyCycle >= 255) {
    fadeAmount = -fadeAmount;
  }

  // 控制渐变平滑度（数值越大，变化越慢）
  delay(20);
}
