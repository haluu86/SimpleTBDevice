#include <ArduinoJson.h>

#ifdef ESP8266
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#else
#include <HTTPClient.h>
#include <WiFi.h>
#endif // ESP8266

#include "TBData.h"

#ifndef _SimpleTBDevice_
#define _SimpleTBDevice_

class TBDevice{
  String _payload;
  String _token;
  String _id;
  String _common;
  String _commonv1;
  WiFiClient _client;
  HTTPClient _http;
  String _response;
  String _JWT_token;

  int _writeTele(String, String);
  int _readTele(String);
  int _writeAttr(String, String);
  int _readAttr(String);
public:
  TBDevice(String);

  void begin(String, WiFiClient&);

  void write(String, int);
  void write(String, float);
  void write(String, bool);
  void write(String, String);
  TBData read(String);
};

#endif //_SimpleTBDevice_
