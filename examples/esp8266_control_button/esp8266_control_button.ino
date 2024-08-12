#include <SimpleTBDevice.h>
#include <ESP8266WiFi.h>

// Tên và mật khẩu wifi.
#define SSID "Tên WiFi"
#define PASSWORD "Mật khẩu"

// Địa chỉ máy chủ thingsboard
#define SERVER_ADDR "địa chỉ(:port)" //ví dụ example.com:8080
// Access token của device
#define ACCESS_TOKEN ""

// Chân gắn đèn, ví dụ : 
#define LED D0

TBDevice device(ACCESS_TOKEN);

void setup() {
  pinMode(LED, OUTPUT);

  Serial.begin(115200);

  WiFi.begin(SSID, PASSWORD);
  Serial.println("Bắt đầu kết nối wifi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Đã kết nối wifi.");
  
  WiFiClient client;
  device.begin(SERVER_ADDR, client);
}

void loop() {
  if(device.read("nut1").asBoolean()) {
    digitalWrite(LED, HIGH);
    Serial.println("Đèn bật.");
  } else {
    digitalWrite(LED, LOW);
    Serial.println("Đèn tắt.");
  }
  delay(200);
}