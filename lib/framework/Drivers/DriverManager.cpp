/*
 * DriverManager.cpp
 *
 *  Created on: 7 sie 2022
 *      Author: michal
 */

#include "DriverManager.h"
#include <algorithm>

using namespace std;

DriverManager DriverManager::m_instance = DriverManager();

DriverManager& DriverManager::GetInstance() {
	return m_instance;
}

void DriverManager::AddDriver(Driver* drv) {
	m_drivers.push_back(drv);
}

void DriverManager::RemoveDriver(uint16_t driver_id) {
//	m_drivers.erase(
//			remove_if(m_drivers.begin(), m_drivers.end(),
//			[driver_id](const unique_ptr<Driver>& drv) {return drv->getId() == driver_id;}),
//			m_drivers.end());
}

DriverManager::DriverManager() {
	// TODO Auto-generated constructor stub

}

DriverManager::~DriverManager() {
	// TODO Auto-generated destructor stub
}

