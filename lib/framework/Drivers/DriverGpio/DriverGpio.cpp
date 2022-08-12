/*
 * DriverGpio.cpp
 *
 *  Created on: 7 sie 2022
 *      Author: michal
 */

#include "DriverGpio.h"

DriverGpio::DriverGpio(AsyncWebServer* server, FS* fs,uint16_t id):
Driver(id),
_httpEndpoint(DriverGpioSettings::read, DriverGpioSettings::update, this, server, Driver::GetHttpPath(), this),
_FSPersistance(DriverGpioSettings::read, DriverGpioSettings::update, this, fs, Driver::GetFSJSON())
{

}

DriverGpio::~DriverGpio() {
	// TODO Auto-generated destructor stub
}

void DriverGpio::onConfigUpdated() {
#ifndef LINUX
	pinMode(_state.m_gpioNum, OUTPUT);
	digitalWrite(_state.m_gpioNum, _state.state);
#endif
}
