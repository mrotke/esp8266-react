/*
 * DriverGpio.cpp
 *
 *  Created on: 7 sie 2022
 *      Author: michal
 */

#include "DriverGpio.h"

DriverGpio::DriverGpio(AsyncWebServer* server, FS* fs, SecurityManager* sm,uint16_t id):
Driver(id),
_httpEndpoint(DriverGpioSettings::read,
			  DriverGpioSettings::update,
			  this,
			  server,
			  Driver::GetHttpPath(),
			  sm,
			  AuthenticationPredicates::IS_AUTHENTICATED),
_FSPersistance(DriverGpioSettings::read,
		       DriverGpioSettings::update,
			   this,
			   fs,
			   Driver::GetFSJSON().c_str())
{

}

DriverGpio::~DriverGpio() {
	// TODO Auto-generated destructor stub
}

DriverGpio::eDriverType DriverGpio::GetType() const {
	return eDriverType::eDriverGpio;
}

void DriverGpio::onConfigUpdated() {
#ifndef LINUX
	pinMode(_state.m_gpioNum, OUTPUT);
	digitalWrite(_state.m_gpioNum, _state.state);
#endif
}
