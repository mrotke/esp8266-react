/*
 * Driver.cpp
 *
 *  Created on: 7 sie 2022
 *      Author: michal
 */

#include "Driver.h"

Driver::Driver(uint16_t id):
m_id(id)
{
	_httpPath = "/rest/driver/" + id;
	_FSPath = _httpPath + ".json";
}

Driver::~Driver() {
}

string Driver::GetName() const
{
	string result;
	switch (GetType()) {
#define DEF_DRIVER(etype, className, name) case eDriverType::etype: \
	result = name; \
	break;
#include "DriverMacro.h"
#undef DEF_DRIVER
		default:
			break;
	}

	return result;
}

const String& Driver::GetHttpPath() {
	return _httpPath;
}

const String& Driver::GetFSJSON() {
	return _FSPath;
}
