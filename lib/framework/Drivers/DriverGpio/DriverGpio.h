/*
 * DriverGpio.h
 *
 *  Created on: 7 sie 2022
 *      Author: michal
 */

#ifndef ESP8266_REACT_LIB_FRAMEWORK_DRIVERS_DRIVERGPIO_H_
#define ESP8266_REACT_LIB_FRAMEWORK_DRIVERS_DRIVERGPIO_H_

#include "../Driver.h"
#include "../../StatefulService.h"
#include "../../HttpEndpoint.h"
#include "../../FSPersistence.h"

class DriverGpioSettings{
public:
	static void read(DriverGpioSettings& settings, JsonObject& root) {
		  root["gpio_num"] = settings.m_gpioNum;
		  root["state"] = settings.state;
	}

	static StateUpdateResult update(JsonObject& root, DriverGpioSettings& State) {
		bool newState = State.state;
		uint16_t newGpio = State.m_gpioNum;

		if (root.containsKey("state"))
			newState = root["state"];
		if (root.containsKey("gpio_num"))
			newGpio = root["gpio_num"];

	    if (newState != State.state || newGpio != State.m_gpioNum)
	    {
	      State.state = newState;
	      State.m_gpioNum = newGpio;
	      return StateUpdateResult::CHANGED;
	    }
	    return StateUpdateResult::UNCHANGED;
	}

	uint16_t m_gpioNum = 0;
	bool state = false;
};

class DriverGpio:public StatefulService<DriverGpioSettings>, public Driver {
public:
	DriverGpio(AsyncWebServer* server, FS* fs,SecurityManager* sm, uint16_t id);
	virtual ~DriverGpio();
	eDriverType GetType() const override;
private:
	void onConfigUpdated();

	HttpEndpoint<DriverGpioSettings> _httpEndpoint;
	FSPersistence<DriverGpioSettings> _FSPersistance;
};

#endif /* ESP8266_REACT_LIB_FRAMEWORK_DRIVERS_DRIVERGPIO_H_ */
