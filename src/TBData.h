#include <ArduinoJson.h>

#ifndef _TBData_
#define _TBData_

// Warp around json string received from thingsboard
class TBData {
	JsonDocument _data;
	String _key;
public:
	TBData(String, String);
	int asInt();
	float asFloat();
	String asString();
	bool asBoolean();
};

#endif // _TBData_
