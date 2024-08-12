/*
 * AppPositionAquisition.h
 *
 *  Created on: 20.09.2012
 *
 */

#ifndef APPPOSITIONAQUISITION_H_
#define APPPOSITIONAQUISITION_H_

#include "math/LowPass_PT1.h"

#include "GPT12/IncrEnc/IfxGpt12_IncrEnc.h"


/** @brief Position acquisition mode
 */
typedef enum
{
    PositionAcquisition_Hall = 0,              	 /**< @brief Hall sensor is used */
    PositionAcquisition_Encoder = 1,           	 /**< @brief Encoder & Hall sensors are used */
    PositionAcquisition_Resolver = 2,            /**< @brief Resolver	sensor is used */
    PositionAcquisition_Sensorless = 3
} PositionAcquisition_Mode;

/** @brief Position acquisition object
 */
typedef struct
{
    IfxGpt12_IncrEnc 			encoder;        /**< \brief GPT12-based encoder object */
    PositionAcquisition_Mode   	mode;           /**< @brief Position sensor used */
    boolean                     statusOk;       /**< @brief Position sensor used is ok*/
    LowPass_PT1                	speedFilter;    /**< @brief Speed filter */
} PositionAcquisition;

void AppPositionAcquisition_init(PositionAcquisition *sensors, uint8 motorPolPairs);
sint32 AppPositionAcquisition_updatePosition(PositionAcquisition *sensors);
float32 AppPositionAcquisition_updateSpeed(PositionAcquisition *sensors);

#endif /* APPPOSITIONAQUISITION_H_ */
