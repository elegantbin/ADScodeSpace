/*
 * General_Defines.h
 *
 *  Created on: 16.04.2014
 */

#ifndef GENERAL_DEFINES_H_
#define GENERAL_DEFINES_H_


#define USE_TFT
#define TFT_OVER_DAS


#define REFRESH_TFT 50		// Refresh rate [ms]; 1x refresh ~0,8 % CPU load; for graphic-out: 4 colors ~ 1.2 % CPU load, 16 colors ~ 0.8 % CPU load
							// Max refresh rate ~ 40 ms due to QSPI-load

#endif /* GENERAL_DEFINES_H_ */
