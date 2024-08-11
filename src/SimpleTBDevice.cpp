#include "SimpleTBDevice.h"

TBDevice::TBDevice(String accessToken)
	: _token(accessToken) {

	// Telementry cần authentication token trong profile của người dùng
	// để đọc. Để tăng sự tiện dụng, có thể cân nhắc một số giải pháp
	// sau, để tránh việc dùng JWT token (vì token là một string rất
	// dài):
	// 1. Gửi dữ liệu dưới dạng cả attribute và telemetry.
	// 2. Chỉ gửi dưới dạng telemetry.
	// Telemetry có thể được timeseries widget vẽ.
	// Attribute được gửi từ thiết bị sẽ là client attribute, dùng
	// rule chain của thingsboard để chuyển thành shared attribute,
	// có thể đọc được/thay đổi được bởi widget.
	this->_JWT_token = "";
}

void TBDevice::begin(String address, WiFiClient& client){
	this->_client = client;
	this->_common = "http://" + address + "/api";
	this->_commonv1 = "http://" + address + "/api/v1/" + this->_token;
}

// TODO: Ack response status.
void TBDevice::write(String key, String value) {
	// send data pair both as telemetry and (shared) attribute.
	int wteleStatus = _writeTele(key, value);
	int wattrStatus = _writeAttr(key, value);
	// if wteleStatus != 200 | wattrStatus != 200 then you should be panic!
}

void TBDevice::write(String key, int value) {
	write(key, String(value));
}

void TBDevice::write(String key, float value) {
	write(key, String(value));
}

void TBDevice::write(String key, bool value) {
	String _value = (value) ? "true" : "false";
	write(key, _value); 
}

// TODO: Ack response status.
TBData TBDevice::read(String key) {
	int rattrStatus = _readAttr(key);
	// if rattrStatus != 200 then you should be panic!
	return TBData(this->_response, key);
}

// All elementary read/write function will return http status.
// Http response string will be stored in _repsonse
int TBDevice::_writeTele(String key, String value){
	this->_http.begin(this->_client, this->_commonv1 + "/telemetry");
	this->_http.addHeader("Content-Type", "application/json");
	String jsonString = "{" + key + ":" + value + "}";
	int ret = this->_http.POST(jsonString);
	this->_http.end();
	return ret;
}

// UNUSED
int TBDevice::_readTele(String key){
	this->_http.begin(this->_client, this->_common + 
		"/plugins/telemetry/DEVICE/" +
		this->_id +
		"/values/timeseries?keys=" +
		key);
	this->_http.addHeader("Content-Type", "application/json");
	this->_http.addHeader("X-Authorization", this->_JWT_token);
	int ret = this->_http.GET();
	this->_response = this->_http.getString();
	this->_http.end();
	return ret;
}

int TBDevice::_writeAttr(String key, String value){
	this->_http.begin(this->_client, this->_commonv1 + "/attributes");
	this->_http.addHeader("Content-Type", "application/json");
	String jsonString = "{" + key + ":" + value + "}";
	int ret = this->_http.POST(jsonString);
	this->_http.end();
	return ret;
}

int TBDevice::_readAttr(String value){
	this->_http.begin(this->_client, this->_commonv1 + "/attributes?sharedKeys=" + value);
	this->_http.addHeader("Content-Type", "application/json");
	int ret = this->_http.GET();
	this->_response = this->_http.getString();
	this->_http.end();
	return ret;
}
