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
  myservo2.attach(11);
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

  //servo phan loai xem co phai rac ko (cho 2 if phân loại màu nóng và lạnh bên dưới vào vòng if này khi servo3 quay thì tiếp đến 2 servo còn lại)
  if(redValue >= 0){
    myservo3.write(110);
    delay(150);
    myservo3.write(0);
  }
  //mau nong
  if(200 <= redValue <= 255 &&  0 <= greenValue <= 200 && 0 <= blueValue <= 100){
    myservo1.write(110);
    delay(150);
    myservo1.write(0);
  }
  //mau lanh
  if(0 <= redValue <= 200 &&  0 <= greenValue <= 255 && 0 <= blueValue <= 255){
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