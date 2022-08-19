/*
 * DriverManager.h
 *
 *  Created on: 7 sie 2022
 *      Author: michal
 */

#ifndef ESP8266_REACT_LIB_FRAMEWORK_DRIVERS_DRIVERMANAGER_H_
#define ESP8266_REACT_LIB_FRAMEWORK_DRIVERS_DRIVERMANAGER_H_
#include <vector>
#include <memory>
#include "Driver.h"


class DriverManager {
public:
	~DriverManager();
	static DriverManager& GetInstance();
	void AddDriver(std::shared_ptr<Driver> drv);
	void RemoveDriver(uint16_t driver_id);
private:
	DriverManager();

	static DriverManager m_instance;
	std::vector<std::shared_ptr<Driver>> m_drivers;
};

#endif /* ESP8266_REACT_LIB_FRAMEWORK_DRIVERS_DRIVERMANAGER_H_ */
