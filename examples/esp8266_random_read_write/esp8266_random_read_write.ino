#include <SimpleTBDevice.h>
#include <ESP8266WiFi.h>

// Tên và mật khẩu wifi.
#define SSID "Tên WiFi"
#define PASSWORD "Mật khẩu"

// Địa chỉ máy chủ thingsboard
#define SERVER_ADDR "địa chỉ(:port)" //ví dụ example.com:8080
// Access token của device
#define ACCESS_TOKEN ""

TBDevice device(ACCESS_TOKEN);

void setup() {
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

  randomSeed(analogRead(A0));
}

void loop() {
  device.write("random", (int)random(100));
  Serial.printf("Đã gửi: %d.\n", device.read("random").asInt());
  delay(1000);
}
