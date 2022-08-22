/*
 * Driver.h
 *
 *  Created on: 7 sie 2022
 *      Author: michal
 */

#ifndef ESP8266_REACT_LIB_FRAMEWORK_DRIVERS_DRIVER_H_
#define ESP8266_REACT_LIB_FRAMEWORK_DRIVERS_DRIVER_H_
#include <Arduino.h>
#include <ArduinoJson.h>
#include <string>

using namespace std;

class Driver {
public:
	enum class eDriverType
	{
#define DEF_DRIVER(etype, className, name) etype,
#include "DriverMacro.h"
#undef DEF_DRIVER
	};
	Driver(uint16_t id);
	virtual ~Driver();

	virtual eDriverType GetType() const = 0;

	const char* GetTypeName();

	string GetName() const;

	uint16_t getId() const {
		return m_id;
	}

	const String& GetHttpPath();
	const String& GetFSJSON();

private:
	uint16_t m_id;
	String _httpPath;
	String _FSPath;
};

#endif /* ESP8266_REACT_LIB_FRAMEWORK_DRIVERS_DRIVER_H_ */
