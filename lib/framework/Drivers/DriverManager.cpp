/*
 * DriverManager.cpp
 *
 *  Created on: 7 sie 2022
 *      Author: michal
 */

#include "DriverManager.h"
#include "DriversFactory.h"
#include <algorithm>

using namespace std;

std::shared_ptr<DriverManager> DriverManager::m_instance = nullptr;

std::shared_ptr<DriverManager> DriverManager::GetInstance() {
	return m_instance;
}

void DriverManager::AddDriver(std::shared_ptr<Driver> drv) {
	if (drv)
		m_drivers.push_back(drv);
}

void DriverManager::RemoveDriver(uint16_t driver_id) {
	m_drivers.erase(
			remove_if(m_drivers.begin(), m_drivers.end(),
			[driver_id](const shared_ptr<Driver> drv) {return drv->getId() == driver_id;}),
			m_drivers.end());
}

DriverManager::DriverManager(AsyncWebServer* server, FS* fs, SecurityManager* sm):
m_server(server),
m_FS(fs),
m_securityManager(sm),
_httpEndpoint(DriverManagerSettings::read,
		      DriverManagerSettings::update,
			  this,
			  server,
			  "/rest/driverManager",
			  sm,
			  AuthenticationPredicates::IS_AUTHENTICATED),
_FSPersistance(DriverManagerSettings::read, DriverManagerSettings::updateFromFS, this, fs, "drivermanager.json")
{

}

DriverManager::~DriverManager() {
	// TODO Auto-generated destructor stub
}

void DriverManager::CreateInstance(std::shared_ptr<DriverManager> ptr)
{
	m_instance = ptr;
}

void DriverManager::Begin() {
	_FSPersistance.readFromFS();
}

void DriverManagerSettings::read(DriverManagerSettings &settings,JsonObject &root) {
	// allocate the memory for the document
	DynamicJsonDocument doc(128);

	JsonArray drivers = root.createNestedArray("drivers");
	// create an object
	JsonObject driver = doc.to<JsonObject>();

	std::shared_ptr<DriverManager> manager = DriverManager::GetInstance();
	if(manager)
	{
		for (auto drv : manager->m_drivers)
		{
			driver["id"] = drv->getId();
			driver["type"] = drv->GetName();
			drivers.add(driver);
		}
	}
}

StateUpdateResult DriverManagerSettings::update(JsonObject &root,DriverManagerSettings &State) {
	if (root.containsKey("drivers"))
	{
		JsonArray drivers = root["drivers"].as<JsonArray>();
		for(auto v : drivers)
		{
			JsonObject driver = v.as<JsonObject>();
			uint16_t id = driver["id"];
			std::shared_ptr<DriverManager> manager = DriverManager::GetInstance();
			if(manager)
			{
				manager->RemoveDriver(id);
				String name = driver["type"];
				std::shared_ptr<Driver> drv = DriversFactory::GetInstance().CreateDriver(id, name.c_str());
				manager->AddDriver(drv);
			}
		}
	}
	return StateUpdateResult::CHANGED;
}

StateUpdateResult DriverManagerSettings::updateFromFS(JsonObject &root,DriverManagerSettings &State) {
	if (root.containsKey("drivers"))
	{
		JsonArray drivers = root["drivers"].to<JsonArray>();
		for(JsonVariant v : drivers)
		{
			JsonObject driver = v.to<JsonObject>();
			uint16_t id = driver["id"];
			std::shared_ptr<DriverManager> manager = DriverManager::GetInstance();
			if(manager)
			{
				manager->RemoveDriver(id);
				String name = driver["type"];
				std::shared_ptr<Driver> drv = DriversFactory::GetInstance().CreateDriver(id, name.c_str());
				manager->AddDriver(drv);
			}
		}
	}
	return StateUpdateResult::CHANGED;
}
