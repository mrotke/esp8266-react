/*
 * DriverMacro.h
 *
 *  Created on: 10 sie 2022
 *      Author: michal
 */

//			eDriverType,    ,className,         ,name
#ifdef DEF_DRIVER
DEF_DRIVER(eDriverGpio, 	DriverGpio,			"DriverGpio")
#else
#include "DriverGpio/DriverGpio.h"
#endif
