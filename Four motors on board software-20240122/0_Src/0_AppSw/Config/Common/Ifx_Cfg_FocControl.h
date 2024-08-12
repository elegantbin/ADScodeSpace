/*
 * Cfg_FocControl.h
 *
 *  Created on: 22.10.2012
 *
 */

#ifndef CFG_FOCCONTROL_H_
#define CFG_FOCCONTROL_H_


/** @name Current Id PI controller configuration
 *
 * @see control_pi
 */

#define trace_memory (512)

#define scale_angle (0.20f)
//#define time_axis (2)  //5ms
//#define time_axis (4)  //10ms
#define time_axis (8)  //20ms
#define graph_current (1)

#define Resolver (1)
#define Encoder (0)

#define OTHER   (1)
#define NANOTEC (0)
#define Calibration (1)


#define SensorMode  (Encoder)

#define eMotorBoardVoltageMax	(0.9)		// Duty cycle PWM
#define eMotorBoardCurrentMax   (4.0)		// Max Current
#define VDC 					(12.0)		//DC Link Voltage
#define BANDWITH				(1000.0)	//Bandwith of the PI Controller [Hz]


#define CFG_M0_RESISTANCE	(0.19)		//NANOTEC DB42S02 (Stator Impendanz)
#define CFG_M0_INDUCTANCE	(0.245e-3)	//NANOTEC DB42S02 (Stator Inductivity)
#define kpd_multi 			(0.01)	   	//NANOTEC (without) Load
#define kid_multi 			(0.001)		//NANOTEC (without) Load
#define kpq_multi 			(0.01)	   	//NANOTEC (without) Load
#define kiq_multi 			(0.001)		//NANOTEC (without) Load

#define speed_openLoop		(45000)		//NANOTEC with Encoder
#define amplitude_openLoop	(0.1)
#define got_topzero			(3)

#define min_speed			(50)		//Min. rotation speed of motor
#define fails				(20)			//Number of fails befor motor ist stopped
#define delta_speed         (1000.0)	//delta between ref. speed and nominal speed



#define CFG_ENCODER_OFFSET  (-842)
#define CFG_M0_POLPAIR      (4)

#define FOC_CALC_TSTATOR    (CFG_M0_INDUCTANCE)/(CFG_M0_RESISTANCE)
#define FOC_K_FACTOR		(1/(VDC*(2/PI)))
#define FOC_CALC_KI			(CFG_M0_RESISTANCE)/(1/(2*PI*BANDWITH))*FOC_K_FACTOR
#define FOC_CALC_KP			(FOC_CALC_KI*FOC_CALC_TSTATOR)

#define CFG_M0_PI_ID_KP 	(kpd_multi*(FOC_CALC_KP)) 	//brief Define the Kp parameter value.
#define CFG_M0_PI_ID_KI 	(kid_multi*(FOC_CALC_KI))  	// brief Define the Ki parameter value.

#define CFG_M0_PI_IQ_KP 	(kpq_multi*(FOC_CALC_KP))  	//brief Define the Kp parameter value.
#define CFG_M0_PI_IQ_KI 	(kiq_multi*(FOC_CALC_KI))   //brief Define the Ki parameter value.

#define CFG_M0_PI_ID_LIMIT_MAX (0.85)            		//brief Define the max limit value.
#define CFG_M0_PI_IQ_LIMIT_MAX (0.85)             		//brief Define the max limit value.*/

#define CFG_M0_IQ_LIMIT		(5.0)
#define CFG_M0_ID_LIMIT		(4.0)



#endif /* CFG_FOCCONTROL_H_ */
