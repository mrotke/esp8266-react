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
#include "../StatefulService.h"
#include "../HttpEndpoint.h"
#include "../FSPersistence.h"

class DriverManagerSettings{
public:
	static void read(DriverManagerSettings& settings, JsonObject& root);

	static StateUpdateResult update(JsonObject& root, DriverManagerSettings& State);
};

class DriverManager:public StatefulService<DriverManagerSettings>{
friend class DriverManagerSettings;
public:
	~DriverManager();
	static void CreateInstance(std::shared_ptr<DriverManager> ptr);
	static std::shared_ptr<DriverManager> GetInstance();
	void AddDriver(std::shared_ptr<Driver> drv);
	void RemoveDriver(uint16_t driver_id);
	DriverManager(AsyncWebServer* server, FS* fs);
	void Begin();

	FS* getFS() {
		return m_FS;
	}

	AsyncWebServer* getServer() {
		return m_server;
	}

private:
	//static constexpr char URL[] = "/rest/DriverManager";
	//static constexpr char FILE[] = "DriverManager.json";

	AsyncWebServer* m_server = nullptr;
	FS* m_FS = nullptr;
	static std::shared_ptr<DriverManager> m_instance;
	std::vector<std::shared_ptr<Driver>> m_drivers;
	HttpEndpoint<DriverManagerSettings> _httpEndpoint;
	FSPersistence<DriverManagerSettings> _FSPersistance;
};

#endif /* ESP8266_REACT_LIB_FRAMEWORK_DRIVERS_DRIVERMANAGER_H_ */
