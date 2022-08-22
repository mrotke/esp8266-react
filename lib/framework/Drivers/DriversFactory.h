/*
 * DriversFactory.h
 *
 *  Created on: 7 sie 2022
 *      Author: michal
 */

#ifndef ESP8266_REACT_LIB_FRAMEWORK_DRIVERS_DRIVERSFACTORY_H_
#define ESP8266_REACT_LIB_FRAMEWORK_DRIVERS_DRIVERSFACTORY_H_

#include <memory>
#include "Driver.h"

class DriversFactory {
public:
	virtual ~DriversFactory();
	static DriversFactory& GetInstance();
	std::shared_ptr<Driver> CreateDriver(uint16_t id, const char* name);
private:
	DriversFactory();
};

#endif /* ESP8266_REACT_LIB_FRAMEWORK_DRIVERS_DRIVERSFACTORY_H_ */
