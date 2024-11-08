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

  // Gắn servo 1 vào chân 9 và servo 2 vào chân 10
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

  // // Điều khiển servo 1 dựa trên màu xanh lá
  // if (greenValue > 200) { // Nếu màu xanh lá vượt quá ngưỡng
  //   myservo2.write(100);    // Servo 1 quay về vị trí 90 độ
  //   delay(200);
  //   myservo2.write(0);     // Sau đó quay lại vị trí 0 độ
  // }
  // // Điều khiển servo 2 dựa trên màu xanh dương
  // if (blueValue > 200) {   // Nếu màu xanh dương vượt quá ngưỡng
  //   myservo2.write(100);   // Servo 2 quay về vị trí 180 độ
  //   delay(200);
  //   myservo2.write(0);    // Sau đó quay lại vị trí 90 độ
  // }
  // //mau cam
  // if(redValue >= 250 && greenValue >= 130){
  //   myservo1.write(100);
  //   delay(200);
  //   myservo1.write(0);
  // }
  // // mau kaki
  // if(redValue >= 240 && greenValue >= 220 && blueValue >= 130){
  //   myservo1.write(100);
  //   delay(200);
  //   myservo1.write(0);
  // }
  // // mau do
  // if(redValue >= 250){
  //   myservo1.write(100);
  //   delay(200);
  //   myservo1.write(0);
  // }
  // //mau xanh ngoc
  // if(redValue >= 60 && greenValue >= 220 && blueValue >= 200){
  //   myservo2.write(100);
  //   delay(200);
  //   myservo2.write(0);
  // }

  
  //xanh la
  if (redValue <= 150, greenValue > 200, blueValue <= 150) {
  myservo1.write(100);
  delay(200);
  myservo1.write(0);
  }
  //xanh duong
  if (redValue <= 170, greenValue <= 200, blueValue >= 200) {
  myservo1.write(100);
  delay(200);
  myservo1.write(0);
  }
  //do
  if (redValue >= 200, greenValue <= 170, blueValue <= 140) {
  myservo2.write(100);
  delay(200);
  myservo2.write(0);
  }
  // Tạm dừng trước lần đọc tiếp theo
  delay(1000);
}




// Định nghĩa hàm normalize
int normalize(int value, int maxValue) {
  return map(value, 0, maxValue, 0, 255);
}