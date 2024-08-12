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
#define time_axis   (8)  //20ms
#define graph_current (1)


#define Resolver (1)
#define OTHER   (1)
#define Encoder (0)
#define NANOTEC (0)
#define Calibration (1)

#define K_MOT_DIR_CCW     (1)
#define K_MOT_DIR_CW      (0)

#define eMotorBoardVoltageMax	(0.86)	//0.9	// Duty cycle PWM
#define eMotorBoardCurrentMax   (180.0)		// Max Current
#define VDC 					(48.0)		//DC Link Voltage
#define BANDWITH				(1000.0)	//Bandwith of the PI Controller [Hz]

#if (Motor == NANOTEC)					//NANOTEC DB42S02

#define CFG_ENCODER_OFFSET  (-842)
#define CFG_M0_POLPAIR		(5)			//NANOTEC DB42S02
#define CFG_M0_RESISTANCE	(0.174)//(0.028)		//NANOTEC DB42S02 (Stator Impendanz)@r   (0.01704)?
#define CFG_M0_INDUCTANCE	(0.131e-3)//(0.28)	//NANOTEC DB42S02 (Stator Inductivity)@l     (0.1254e-3)?

#define kpd_multi           (0.085)   //0.5   //NANOTEC (without) Load   //0.1
#define kid_multi           (0.11) //(0.06)    //NANOTEC (without) Load

#define kpq_multi           (0.1)//(0.5)      //NANOTEC (without) Load
#define kiq_multi           (0.09)//(0.06)   //NANOTEC (without) Load


#define amplitude_openLoop	(0.16)
#define got_topzero			(3)

#define min_speed			(100)		//Min. rotation speed of motor
#define fails				(2)			//Number of fails befor motor ist stopped
#define delta_speed         (1000.0)	//delta between ref. speed and nominal speed

#endif


#if (Motor == OTHER)

#define CFG_M0_POLPAIR		(1)			//Other
#define CFG_M0_RESISTANCE	(0.190)		//Other
#define CFG_M0_INDUCTANCE	(40e-6)		//Other
#define kpd_multi 			(0.01)	   	//Other (without) Load
#define kid_multi 			(0.002)		//Other (without) Load
#define kpq_multi 			(0.01)	   	//Other (without) Load
#define kiq_multi 			(0.002)		//Other (without) Load
//#define kpd_multi 			(0.2)	//Other (with) Load
//#define kid_multi 			(0.1)	//Other (with) Load
//#define kpq_multi 			(0.2)	//Other (with) Load
//#define kiq_multi 			(0.1)	//Other (with) Load
#endif


#define FOC_CALC_TSTATOR    (CFG_M0_INDUCTANCE)/(CFG_M0_RESISTANCE)//l/r
#define FOC_K_FACTOR		(1/(VDC*(2/PI)))//0.032725
#define FOC_CALC_KP         (FOC_CALC_KI*FOC_CALC_TSTATOR)//205.61724*l=0.030534   205.61724*0.28 =57.5728
#define FOC_CALC_KI			(CFG_M0_RESISTANCE)/(1/(2*PI*BANDWITH))*FOC_K_FACTOR//205.61724*r=35.7774    205.61724*0.028 = 5.75728

#define CFG_M0_PI_ID_KP 	(kpd_multi*(FOC_CALC_KP)) 	//    0.575728    brief Define the Kp parameter value.@0.00030534
#define CFG_M0_PI_ID_KI 	(kid_multi*(FOC_CALC_KI))  	//    0.00575728  brief Define the Ki parameter value.@0.0357774

#define CFG_M0_PI_IQ_KP 	(kpq_multi*(FOC_CALC_KP))  	//brief Define the Kp parameter value.
#define CFG_M0_PI_IQ_KI 	(kiq_multi*(FOC_CALC_KI))   //brief Define the Ki parameter value.

#define CFG_M0_PI_ID_LIMIT_MAX (0.86)        //0.85    		//brief Define the max limit value.
#define CFG_M0_PI_IQ_LIMIT_MAX (0.86)             		//brief Define the max limit value.*/

#define CFG_M0_IQ_LIMIT		(5.0)
#define CFG_M0_ID_LIMIT		(4.0)



#endif /* CFG_FOCCONTROL_H_ */
