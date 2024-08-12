/**
 * \file Ifx_cfg_VelocityControl.h
 * \brief Driver configuration.
 *
 * \license
 * You can use this file under the terms of the IFX License.
 *
 * This file is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the IFX License for more details (IFX_License.txt).
 *
 * This file may be used, copied, and distributed, with or without modification, provided
 * that all copyright notices are retained; that all modifications to this file are
 * prominently noted in the modified file; and that this paragraph is not modified.
 *
 * \copyright Copyright (C) 2012 Infineon Technologies AG
 *
 *
 * $Revision:  $
 * $Date:  $
 *
 * \defgroup velocity_control		Speed Controller
 * \defgroup cfg_velocity_control	Configuration of Speed Controller
 * \ingroup velocity_control
 */

#include "Ifx_Cfg_FocControl.h"

#ifndef IFX_CFG_VELOCITYCONTROL_H_
#define IFX_CFG_VELOCITYCONTROL_H_

#define VELOCITY_kp_multi (0.5)
#define VELOCITY_ki_multi (1.0)


#define VELOCITY_CONTROL_KP			(VELOCITY_kp_multi*(FOC_CALC_KP))    	/**< @brief Define the Kp parameter value. */
#define VELOCITY_CONTROL_KI			(VELOCITY_ki_multi*(FOC_CALC_KI))			/**< @brief Define the Ki parameter value. */
#define VELOCITY_CONTROL_MIN		(0.0)								/**< @brief Define the Pi Controller Out minimum value. */
#define VELOCITY_CONTROL_MAX		(1.0)								/**< @brief Define the Pi Controller Out maximum value. */
#define VELOCITY_CONTROL_MAX_RPM	(5000.0)							/**< @brief Define the Max rpm in 1/min value. */
#define VELOCITY_CONTROL_PERIOD		(1e-3)								/**< @brief Define the Controller period in seconds value. */
#define VELOCITY_CONTROL_REF		(0.0)							   /**< @brief Define the Motor REF rpm in 1/min value. */

#endif /* IFX_CFG_VELOCITYCONTROL_H_ */


