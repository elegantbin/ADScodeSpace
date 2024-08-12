/**
 * \file DoorSysfg_VelocityControl.h
 * \brief Driver configuration.
 *
 * \defgroup velocity_control		Speed Controller
 * \defgroup cfg_velocity_control	Configuration of Speed Controller
 * \ingroup velocity_control
 */



#ifndef DOORSYS_CFG_VELOCITYCONTROL_H_
#define DOORSYS_CFG_VELOCITYCONTROL_H_

/*

#define OPEN_VELOCITY_kp  (8.0)
#define OPEN_VELOCITY_ki  (3.0)

#define CLOSE_VELOCITY_kp    (10.0)
#define CLOSE_VELOCITY_ki    (2.0)
*/


#define OPEN_VELOCITY_kp  (8)
#define OPEN_VELOCITY_ki   (3)
#define CLOSE_VELOCITY_kp  (10)
#define CLOSE_VELOCITY_ki  (2)
#define OPEN_VELOCITY_CONTROL_REF_NORM		(1400)							    /**< @brief Define the Motor REF rpm in 1/min value. */
#define CLOSE_VELOCITY_CONTROL_REF_NORM    (2600)


#define VELOCITY_Kp_FACTOR DOORSYS_CFG_VELOCITYCONTROL_H_    (1e-4)
#define VELOCITY_Ki_FACTOR     (1e-3)
#define CLOSE_VELOCITY_CONTROL_KP               ((CLOSE_VELOCITY_kp)*(VELOCITY_Kp_FACTOR))
#define CLOSE_VELOCITY_CONTROL_KI	            ((CLOSE_VELOCITY_ki)*(VELOCITY_Ki_FACTOR))


#define OPEN_VELOCITY_CONTROL_KP			((OPEN_VELOCITY_kp )*(VELOCITY_Kp_FACTOR))                   	/**< @brief Define the Kp parameter value. */
#define OPEN_VELOCITY_CONTROL_KI			((OPEN_VELOCITY_ki)*(VELOCITY_Ki_FACTOR))		           	    /**< @brief Define the Ki parameter value. */
#define VELOCITY_CONTROL_MIN		(0.05)								/**< @brief Define the Pi Controller Out minimum value. */
#define VELOCITY_CONTROL_MAX		(0.90)								/**< @brief Define the Pi Controller Out maximum value. */
#define VELOCITY_CONTROL_MAX_RPM	(4000.0)							/**< @brief Define the Max rpm in 1/min value. */

#define VELOCITY_CONTROL_PERIOD		(1e-4)								/**< @brief Define the Controller period in seconds value. */



#define VELOCITY_CONTROL_REF_NORM      (2100)
#define VELOCITY_CONTROL_REF_LOW		(1000.0)
#define VELOCITY_CONTROL_REF_HIGH		(3000.0)
#endif /* DOORSYS_CFG_VELOCITYCONTROL_H_ */


