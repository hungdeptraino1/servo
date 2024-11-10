#include <Servo.h>

// Khai báo các chân kết nối của cảm biến màu
const int S0 = 4;
const int S1 = 5;
const int S2 = 6;
const int S3 = 7;
const int sensorOut = 8;

// Biến để lưu giá trị tần số RGB
unsigned long redFrequency = 0;
unsigned long greenFrequency = 0;
unsigned long blueFrequency = 0;

// Tạo đối tượng servo
Servo myservo1;  
Servo myservo2;  
Servo myservo3;

// Khai báo hàm normalize
int normalize(int value, int maxValue);

void setup() {
  // Thiết lập các chân S0, S1, S2, S3 là OUTPUT
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Thiết lập chân sensorOut là INPUT
  pinMode(sensorOut, INPUT);

  // Thiết lập tần số xung ra 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  // Gắn servo 1 vào chân 9, servo 2 vào chân 10 và servo 3 vào chân 11
  myservo1.attach(9); 
  myservo2.attach(10); 
  myservo3.attach(11);

  // Khởi động Serial Monitor với tốc độ 9600 bps
  Serial.begin(9600);
}

void loop() {
  // Đọc giá trị màu đỏ
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  redFrequency = pulseIn(sensorOut, LOW);

  // Đọc giá trị màu xanh lá
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  greenFrequency = pulseIn(sensorOut, LOW);

  // Đọc giá trị màu xanh dương
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  blueFrequency = pulseIn(sensorOut, LOW);

  // Xác định giá trị tần số lớn nhất để chuẩn hóa
  unsigned long maxFrequency = max(redFrequency, max(greenFrequency, blueFrequency));

  // Kiểm tra tránh chia cho 0
  if (maxFrequency == 0) {
    maxFrequency = 1; // Đặt giá trị lớn nhất là 1 để tránh lỗi chia
  }

  // Chuẩn hóa các giá trị RGB về thang 0-255
  int redValue = normalize(redFrequency, maxFrequency);
  int greenValue = normalize(greenFrequency, maxFrequency);
  int blueValue = normalize(blueFrequency, maxFrequency);

  // Hiển thị giá trị RGB chuẩn hóa
  Serial.print("Red: ");
  Serial.print(redValue);
  Serial.print(" | Green: ");
  Serial.print(greenValue);
  Serial.print(" | Blue: ");
  Serial.println(blueValue);

  // Kiểm tra lệnh từ Python để điều khiển servo3
  if (Serial.available() > 0) {
    int command = Serial.read();  // Đọc lệnh từ Python
    if (command == '1') {
      myservo3.write(110);  // Quay servo3 tới 110 độ
      delay(150);
      myservo3.write(0);    // Quay về 0 độ
    }
  }

  // Phân loại màu nóng
  if (redValue >= 200 && redValue <= 255 && greenValue >= 0 && greenValue <= 200 && blueValue >= 0 && blueValue <= 100) {
    myservo1.write(110);
    delay(150);
    myservo1.write(0);
  }

  // Phân loại màu lạnh
  if (redValue >= 0 && redValue <= 200 && greenValue >= 0 && greenValue <= 255 && blueValue >= 0 && blueValue <= 255) {
    myservo2.write(110);
    delay(150);
    myservo2.write(0);
  }
// Tạm dừng trước lần đọc tiếp theo
  delay(1000);
}

// Định nghĩa hàm normalize
int normalize(int value, int maxValue) {
  return map(value, 0, maxValue, 0, 255);
}