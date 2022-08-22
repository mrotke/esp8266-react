/*
 * DriversFactory.cpp
 *
 *  Created on: 7 sie 2022
 *      Author: michal
 */

#include "DriversFactory.h"
#include <string>
#include "DriverMacro.h"
#include "DriverManager.h"
#include <iostream>

DriversFactory& DriversFactory::GetInstance() {
	static DriversFactory instance;
	return instance;
}

std::shared_ptr<Driver> DriversFactory::CreateDriver(uint16_t id, const char *name)
{
	std::shared_ptr<DriverManager> manager = DriverManager::GetInstance();

	if (manager)
	{
		AsyncWebServer* server = manager->getServer();
		FS* fs = manager->getFS();
	#define DEF_DRIVER(etype, className, Typename) if ( strcmp(name, Typename) == 0 ) \
		 return(std::shared_ptr<Driver>(new className(server, fs, id)));
	#include "DriverMacro.h"
	#undef DEF_DRIVER
	}

	return nullptr;
}

DriversFactory::DriversFactory() {
	// TODO Auto-generated constructor stub

}

DriversFactory::~DriversFactory() {
	// TODO Auto-generated destructor stub
}

