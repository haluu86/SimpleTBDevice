#include "TBData.h"

// Json string received from Thingsboard server
// won't be invalid!
TBData::TBData(String data, String key) : _key(key) {
	deserializeJson(_data, data);
}

// Assumed using shared attribute only.
int TBData::asInt() {
	return _data["shared"][_key].as<int>();
}

float TBData::asFloat() {
	return _data["shared"][_key].as<float>();
}

bool TBData::asBoolean() {
	return _data["shared"][_key].as<bool>();
}

String TBData::asString() {
	return _data["shared"][_key].as<String>();
}

