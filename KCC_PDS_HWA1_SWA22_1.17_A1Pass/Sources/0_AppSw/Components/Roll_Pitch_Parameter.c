/*
 * MotAct_AdjustCurve.c
 *
 *  Created on: 2024Äê1ÔÂ3ÈÕ
 *      Author: Administrator
 */
#include <MotAct.h>
#include "DoorSys.h"
#include "IMU.h"
#include "DoorSys.h"
#include <DoorSys_VelocityControl.h>
#include "DoorSysCfg_Velocity.h"
#include <MotAct.h>
#include <Roll_Pitch_Parameter.h>

Roll_Pitch_ParaSet_t gOpen_Roll_Pitch_ParaSet;
Roll_Pitch_ParaSet_t gClose_Roll_Pitch_ParaSet;


 const Roll_Pitch_ParaSet_t  OpenRollPitch_Cfg[25] =
{
/*		***************************************************/
		{ 			/* roll (-6~-3) pitch( 12~8)*/
				.DutyOffset = {2,1,0,0,1,0},
				.DutyOffsetPos = {3250,3135,3060,2900,2600,2400,2100},
				.Ki = 2,
				.Kp = 8,
				.StartCurve= {2,2,3,2,2,2,1},
				.StartUpDuty =20,
				.Referspeed = 2200,
				.ApPosOffset = {-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000},
				.EbrakEnable = 1,
				.ApSumStartup =-2000,
				.ApStartupCout = 80,
				.TiprunStartCout = 120,
		},
		{ 			/* roll (-6~-3) pitch (8~3)*/
				.DutyOffset = {2,1,0,0,1,0},
				.DutyOffsetPos = {3250,3135,3060,2900,2600,2400,2100},
				.Ki = 2,
				.Kp = 8,
				.StartCurve= {2,2,3,2,2,2,1},
				.StartUpDuty =20,
				.Referspeed = 2200,
				.ApPosOffset = {-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000},
				.EbrakEnable = 1,
				.ApSumStartup =-2000,
				.ApStartupCout = 80,
				.TiprunStartCout = 120,
		},
		{ 			/* roll (-6~-3) pitch (3~-3)*/
				.DutyOffset = {2,1,0,0,1,0},
				.DutyOffsetPos = {3250,3135,3060,2900,2600,2400,2100},
				.Ki = 2,
				.Kp = 8,
				.StartCurve= {2,2,3,2,2,2,1},
				.StartUpDuty =20,
				.Referspeed = 2200,
				.ApPosOffset = {-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000},
				.EbrakEnable = 1,
				.ApSumStartup =-2000,
				.ApStartupCout = 80,
				.TiprunStartCout = 120,
		},
		{ 			/* roll (-6~-3) pitch (-3~-8)*/
				.DutyOffset = {2,1,-2,-3,-2},
			    .DutyOffsetPos = {2100,2600,3000,3060,3135,3250,3400},
				.Ki = 3,
				.Kp = 8,
				.StartCurve = {2,3,3,2,2,1,1},
				.StartUpDuty = 20,
				.Referspeed = 1400,
				.ApPosOffset = {-1000,-1000,-1000,-1000,-1000,-1000,-1000},
				.EbrakEnable = 1,
				.ApSumStartup =-2000,
				.ApStartupCout = 120,
				.TiprunStartCout = 120,
		},
		{ 			/* roll (-6~-3) pitch (-8~-12)*/
				.DutyOffset = {2,1,-2,-3,-2},
			    .DutyOffsetPos = {2100,2600,3000,3060,3135,3250,3400},
				.Ki = 3,
				.Kp = 8,
				.StartCurve = {2,3,3,2,2,1,1},
				.StartUpDuty = 20,
				.Referspeed = 1400,
				.ApPosOffset = {-1000,-1000,-1000,-1000,-1000,-1000,-1000},
				.EbrakEnable = 1,
				.ApSumStartup =-2000,
				.ApStartupCout = 120,
				.TiprunStartCout = 120,


		},
/*		***************************************************/
		{ 			/* roll (-3~--1) pitch( 12~8)*/
				.DutyOffset = {0,0,0,0,0,0},
				.DutyOffsetPos = {2100,2300,2600,3060,3135,3250,3400},
				.Ki = 5,
				.Kp = 6,
				.StartCurve = {2,2,2,2,2,2,1},
				.StartUpDuty = 20,
				.Referspeed = 2100,
				.ApPosOffset = {-1900,-1900,-1900,-1900,-1900,-1900,-1900,-1900},
				.EbrakEnable = 1,
				.TiprunStartCout = 120,
				.ApSumStartup =-2000,
				.ApStartupCout = 140,
		},
		{ 			/* roll (-3~--1)pitch (8~3)*/
				.DutyOffset = {0,0,0,0,0,0},
				.DutyOffsetPos = {2100,2600,3000,3060,3135,3250,3400},
				.Ki = 3,
				.Kp = 6,
				.StartCurve = {2,2,2,3,2,2,2},
				.StartUpDuty = 20,
				.Referspeed = 2100,
				.ApPosOffset = {-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000},
				.EbrakEnable = 1,
				.TiprunStartCout = 120,
				.ApSumStartup =-1800,
				.ApStartupCout = 120,
		},
		{ 			/*roll (-3~--1) pitch (3~-3)*/
				.DutyOffset = {0,0,0,0,0,0},
				.DutyOffsetPos = {2100,2600,3000,3060,3135,3250,3400},
				.Ki = 3,
				.Kp = 6,
				.StartCurve = {2,2,2,3,2,2,2},
				.StartUpDuty = 20,
				.Referspeed = 2100,
				.ApPosOffset = {-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000},
				.EbrakEnable = 1,
				.TiprunStartCout = 120,
				.ApSumStartup =-2000,
				.ApStartupCout = 120,
		},
		{ 			/* roll (-3~--1)) pitch (-3~-8)*/
				.DutyOffset = {0,0,0,0,0,0},
				.DutyOffsetPos = {2100,2600,3000,3060,3135,3250,3400},
				.Ki = 8.0,
				.Kp = 2.5,
				.StartCurve = {2,1,2,3,2,1,2},
				.StartUpDuty = 20,
				.Referspeed = 1200,
				.EbrakEnable = 1,
				.ApPosOffset = {-1400,-1400,-1400,-1400,-1400,-1400,-1400,-1400},
				.ApSumStartup =-1200,
				.ApStartupCout = 120,
				.TiprunStartCout = 60,
		},
		{ 			/* roll (-3~--1) pitch (-8~-12)*/
				.DutyOffset = {0,0,0,0,0,0},
				.DutyOffsetPos = {2100,2600,3000,3060,3135,3250,3400},
				.Ki = 8.0,
				.Kp = 2.5,
				.StartCurve = {2,1,2,3,2,1,2},
				.StartUpDuty = 20,
				.Referspeed = 1200,
				.EbrakEnable = 1,
				.ApPosOffset = {-1400,-1400,-1400,-1400,-1400,-1400,-1400,-1400},
				.ApSumStartup =-1200,
				.ApStartupCout = 120,
				.TiprunStartCout = 60,
		},
/*		***************************************************/
		{ 			/* roll (-1~-1) pitch( 12~8)*/
				.DutyOffset = {2,2,1,1,2,1},
				.DutyOffsetPos = {2100,2600,3000,3060,3135,3250,3400},
				.Ki = 10,
				.Kp = 25,
				.StartCurve = {2,2,2,3,2,1,2},
				.StartUpDuty = 20,
				.Referspeed = 2750,
				.ApPosOffset = {-1500,-1500,-1500,-1500,-1500,-1500,-1500,-1500},
				.EbrakEnable = 1,
				.ApSumStartup =-1400,
				.ApStartupCout = 160,
		},
		{ 			/* roll (-1~-1) pitch (8~3)*/
				.DutyOffset = {1,2,1,1,2,1},
				.DutyOffsetPos = {2100,2600,3000,3060,3135,3250,3400},
				.Ki = 10,
				.Kp = 23,
				.StartCurve = {2,2,2,1,2,2,2},
				.StartUpDuty = 20,
				.Referspeed = 2650,
				.ApPosOffset = {0,0,0,0,0,0,0,0},
				.EbrakEnable = 1,
				.TiprunStartCout = 60,
				.ApSumStartup =0,
				.ApStartupCout = 0,


		},
		{ 			/* roll (-1~-1) pitch (3~-3)*/
				.DutyOffset = {0,0,0,0,0,0},
				.DutyOffsetPos = {2100,2600,3000,3060,3135,3250,3400},
				.Ki = 22,
				.Kp = 2.5,
				.StartCurve = {2,1,2,3,2,1,2},
				.StartUpDuty = 20,
				.Referspeed = 2100,
				.ApPosOffset = {0,0,0,0,0,0,0,0},
				.EbrakEnable = 0,
				.TiprunStartCout = 60,
				.ApSumStartup =0,
				.ApStartupCout = 0,

		},
		{ 			/* roll (-1~-1) pitch (-3~-8)*/
				.DutyOffset = {0,0,0,0,0,0},
				.DutyOffsetPos = {2100,2600,3000,3060,3135,3250,3400},
				.Ki = 8.0,
				.Kp = 3.0,
				.StartCurve = {2,1,2,3,2,1,2},
				.StartUpDuty = 20,
				.Referspeed = 1400,
				.ApPosOffset = {0,0,0,0,0,0,0,0},
				.EbrakEnable = 1,
				.ApSumStartup =0,
				.ApStartupCout = 0,
				.TiprunStartCout = 60,

		},
		{ 			/* roll (-1~-1) pitch (-8~-12)*/
				.DutyOffset = {0,0,-1,-1,-1,-1},
				.DutyOffsetPos = {2100,2600,3000,3060,3135,3250,3400},
				.Ki = 8.0,
				.Kp = 2.5,
				.StartCurve = {2,1,2,3,2,1,2},
				.StartUpDuty = 20,
				.Referspeed = 1200,
				.ApPosOffset = {0,0,0,0,0,0,0,0},
				.EbrakEnable = 1,
				.ApSumStartup = 0,
				.ApStartupCout = 0,

		},
	/*		***************************************************/
		{ 			/* roll (1~3) pitch( 12~8)*/
				.DutyOffset = {2,2,4,3,4,4},
				.DutyOffsetPos = {2100,2600,3000,3060,3135,3250,3400},
				.Ki = 50,
				.Kp = 6,
				.StartCurve = {2,2,3,3,2,2,2},
				.StartUpDuty = 20,
				.Referspeed = 2500,
				.ApPosOffset = {-800,-800,-800,-800,-800,-800,-800},
				.EbrakEnable = 1,
				.ApSumStartup =-1600,
				.ApStartupCout = 150,
		},
		{ 			/* roll (1~3) pitch (8~3)*/
				.DutyOffset = {1,2,2,1,1,2},
				.DutyOffsetPos = {2100,2600,3000,3060,3135,3250,3400},
				.Ki = 25,
				.Kp = 4,
				.StartCurve = {2,2,3,3,2,2,2},
				.StartUpDuty = 20,
				.Referspeed = 2500,
				.ApPosOffset = {-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000},
				.EbrakEnable = 1,
				.ApSumStartup =-1000,
				.ApStartupCout = 130,
		},
		{ 			/* roll (1~3) pitch (3~-3)*/
				.DutyOffset = {2,3,2,3,2,2},
				.DutyOffsetPos = {2100,2600,3000,3060,3135,3250,3400},
				.Ki = 22,
				.Kp = 2.5,
				.StartCurve = {2,1,2,3,2,1,2},
				.StartUpDuty = 20,
				.Referspeed = 2100,
				.ApPosOffset = {0,0,0,0,0,0,0,0},
				.EbrakEnable = 1,
				.ApSumStartup = 0,
				.ApStartupCout = 0,
		},
		{ 			/* roll (1~3) pitch (-3~-8)*/
				.DutyOffset = {0,0,0,0,0,0},
				.DutyOffsetPos = {2100,2600,3000,3060,3135,3250,3400},
				.Ki = 8.0,
				.Kp = 3.0,
				.StartCurve = {2,2,2,3,2,2,2},
				.StartUpDuty = 20,
				.Referspeed = 1800,
				.ApPosOffset = {0,0,0,0,0,0,0,0},
				.EbrakEnable = 1,
				.ApSumStartup = 0,
				.ApStartupCout = 0,



		},
		{ 			/* roll (1~3) pitch (-8~-12)*/
				.DutyOffset = {2,1,0,0,0,0},
				.DutyOffsetPos = {2100,2600,3000,3060,3135,3250,3400},
				.Ki = 3.0,
				.Kp = 4,
				.StartCurve = {2,2,2,3,2,2,2},
				.StartUpDuty = 20,
				.Referspeed = 2100,
				.ApPosOffset = {0,0,0,0,0,0,0,0},
				.EbrakEnable = 1,
				.ApSumStartup = 0,
				.ApStartupCout = 0,
		},
		/*		***************************************************/

		{ 			/* roll (3~6) pitch( 12~8)*/
				.DutyOffset = {0,1,3,4,2,0},
				.DutyOffsetPos = {3450,3300,3100,3050,3000,2400,2100},
				.Ki = 15,
				.Kp = 30,
				.StartCurve= {2,3,2,3,3,4,3},
				.StartUpDuty = 30,
				.Referspeed = 2600,
				.ApPosOffset = {-1900,-1900,-1900,-1900,-1900,-1900,-1900,-1900},
				.EbrakEnable = 1,
				.ApSumStartup = -900,
				.ApStartupCout = 100,
		},
		{ 			/* roll (3~6) pitch (8~3)*/
				.DutyOffset = {0,1,3,4,5,0},
				.DutyOffsetPos = {3450,3300,3100,3050,3000,2400,2100},
				.Ki = 15,
				.Kp = 30,
				.StartCurve= {2,3,2,3,3,4,3},
				.StartUpDuty = 30,
				.Referspeed = 2600,
				.ApPosOffset = {-1900,-1900,-1900,-1900,-1900,-1900,-1900,-1900},
				.EbrakEnable = 1,
				.ApSumStartup = -900,
				.ApStartupCout = 100,
		},
		{ 			/* roll (3~6) pitch (3~-3)*/
				.DutyOffset = {0,1,3,3,0,0},
				.DutyOffsetPos = {3450,3300,3100,3050,3000,2400,2100},
				.Ki = 15,
				.Kp = 30,
				.StartCurve= {2,3,2,3,3,4,3},
				.StartUpDuty = 30,
				.Referspeed = 2600,
				.ApPosOffset = {-1200,-1200,-1200,-1200,-1200,-1200,-1200,-1200},
				.EbrakEnable = 1,
				.ApSumStartup = -900,
				.ApStartupCout = 100,
		},
		{ 			/* roll (3~6) pitch (-3~-8)*/
				.DutyOffset = {0,3,3,3,0,0},
				.DutyOffsetPos = {3250,3135,3060,2900,2600,2400,2100},
				.Ki = 5,
				.Kp = 6,
				.StartCurve= {2,3,2,3,3,4,3},
				.StartUpDuty =30,
				.Referspeed = 2600,
				.ApPosOffset = {-1800,-1800,-1800,-1800,-1800,-1800,-1800,-1800},
				.EbrakEnable = 1,
				.ApSumStartup = -1200,
				.ApStartupCout = 140,
		},
		{ 			/* roll (3~-6) pitch (-8~-12)*/
				.DutyOffset = {0,3,4,5,3,2},
				.DutyOffsetPos = {3250,3135,3060,2900,2600,2400,2100},
				.Ki = 5,
				.Kp = 6,
				.StartCurve= {2,3,2,3,3,4,3},
				.StartUpDuty =25,
				.Referspeed = 2600,
				.ApPosOffset = {-1800,-1800,-1800,-1800,-1800,-1800,-1800,-1800},
				.EbrakEnable = 1,
				.ApSumStartup = -1200,
				.ApStartupCout = 100,
		},


};

 const Roll_Pitch_ParaSet_t  CloseRollPitch_Cfg[25] =
{
		/*		***************************************************/
				{ 			/* roll (-6~-3) pitch( 12~8)*/
						.DutyOffset = {0,1,2,1,2,2},
						.DutyOffsetPos = {3250,3135,3060,2900,2600,2400,2100},
						.Ki = 10,
						.Kp = 3,
						.StartCurve= {2,1,1,1,1,1,1},
						.StartUpDuty =15,
						.Referspeed = 2000,
						.ApPosOffset = {-1200,-1200,-1200,-1200,-1200,-1200,-1200},
						.EbrakEnable = 1,
						.ApSumStartup =-1200,
						.ApStartupCout = 100,
						.TiprunStartCout = 200,
				},
				{ 			/* roll (-6~-3) pitch (8~3)*/
						.DutyOffset = {0,1,2,1,2,2},
						.DutyOffsetPos = {3250,3135,3060,2900,2600,2400,2100},
						.Ki = 10,
						.Kp = 3,
						.StartCurve= {2,1,1,1,1,1,1},
						.StartUpDuty =15,
						.Referspeed = 2000,
						.ApPosOffset = {-1200,-1200,-1200,-1200,-1200,-1200,-1200},
						.EbrakEnable = 1,
						.ApSumStartup =-1200,
						.ApStartupCout = 100,
						.TiprunStartCout = 200,
				},
				{ 			/* roll (-6~-3) pitch (3~-3)*/
						.DutyOffset = {0,1,2,1,2,2},
						.DutyOffsetPos = {3250,3135,3060,2900,2600,2400,2100},
						.Ki = 10,
						.Kp = 3,
						.StartCurve= {2,1,1,1,1,1,1},
						.StartUpDuty =20,
						.Referspeed = 2000,
						.ApPosOffset = {-1200,-1200,-1200,-1200,-1200,-1200,-1200},
						.EbrakEnable = 1,
						.ApSumStartup =-1200,
						.ApStartupCout = 100,
						.TiprunStartCout = 200,
				},
				{ 			/* roll (-6~-3) pitch (-3~-8)*/
						.DutyOffset = {0,1,3,2,3,4},
						.DutyOffsetPos= {3450,3300,3100,3050,3000,2400,2100},
						.Ki = 2,
						.Kp = 10,
						.StartCurve = {3,3,4,5,4,3,2},
						.StartUpDuty = 30,
						.Referspeed = 2600,
						.ApPosOffset = {-1000,-1000,-1000,-1300,-1000,-1000,-1000},
						.EbrakEnable = 1,
						.ApSumStartup =-2000,
						.ApStartupCout = 140,
						.TiprunStartCout = 200,

				},
				{ 			/* roll (-6~-3) pitch (-8~-12)*/
						.DutyOffset = {0,1,3,2,3,3},
						.DutyOffsetPos= {3450,3300,3100,3050,3000,2400,2100},
						.Ki = 2,
						.Kp = 10,
						.StartCurve = {3,3,4,5,4,3,2},
						.StartUpDuty = 30,
						.Referspeed = 2600,
						.ApPosOffset = {-1000,-1000,-1000,-1000,-1000,-1000,-1000},
						.EbrakEnable = 1,
						.ApSumStartup =-2000,
						.ApStartupCout = 140,
						.TiprunStartCout = 200,


				},
		/*		***************************************************/
				{ 			/* roll (-3~--1) pitch( 12~8)*/

						.DutyOffset = {0,0,0,0,0,0},
						.DutyOffsetPos = {3250,3135,3060,2900,2600,2400,2100},
						.Ki = 2,
						.Kp = 3,
						.StartCurve = {2,1,1,0,0,1,1},
						.StartUpDuty =20,
						.Referspeed = 1300,
						.ApPosOffset = {-2000,-2000,-2000,-2000,-2000,-2000,-2000,-2000},
						.EbrakEnable = 1,
						.ApSumStartup =-2000,
						.ApStartupCout = 140,
						.TiprunStartCout = 200,
				},
				{ 			/* roll (-3~--1)pitch (8~3)*/
						.DutyOffset = {0,0,0,0,0,0},
						.DutyOffsetPos = {3250,3135,3060,2900,2600,2400,2100},
						.Ki = 22,
						.Kp = 2.5,
						.StartCurve = {2,1,2,3,2,1,2},
						.StartUpDuty = 20,
						.Referspeed = 2100,
						.ApPosOffset = {-1800,-1800,-1800,-1800,-1800,-1800,-1800,-1800},
						.ApSumStartup =-1800,
						.ApStartupCout = 130,
						.TiprunStartCout = 120,
						.EbrakEnable = 1,
				},
				{ 			/*roll (-3~--1) pitch (3~-3)*/
						.DutyOffset = {0,0,0,0,0,0},
						.DutyOffsetPos = {3250,3135,3060,2900,2600,2400,2100},
						.Ki = 22,
						.Kp = 2.5,
						.StartCurve = {2,1,2,3,2,1,2},
						.StartUpDuty = 20,
						.Referspeed = 2100,
						.ApPosOffset = {-1800,-1800,-1800,-1800,-1800,-1800,-1800,-1800},
						.ApSumStartup =-1800,
						.ApStartupCout = 130,
						.TiprunStartCout = 120,
						.EbrakEnable = 1,
				},
				{ 			/* roll (-3~--1)) pitch (-3~-8)*/
						.DutyOffset = {3,4,5,3,3,2},
						.DutyOffsetPos = {3250,3135,3060,2900,2600,2400,2100},
						.Ki = 10,
						.Kp = 6,
						.StartCurve= {2,2,3,4,3,2,0},
						.StartUpDuty =20,
						.Referspeed = 2600,
						.ApPosOffset = {-1800,-1800,-1800,-1800,-1800,-1800,-1800,-1800},
						.ApSumStartup =-1800,
						.ApStartupCout = 130,
						.TiprunStartCout = 120,
						.EbrakEnable = 1,
				},
				{ 			/* roll (-3~--1) pitch (-8~-12)*/

						.DutyOffset = {2,2,2,1,0,0},
						.DutyOffsetPos = {3250,3135,3060,2900,2600,2400,2100},
						.Ki = 2.5,
						.Kp = 8,
						.StartCurve = {2,3,3,4,3,3,2},
						.StartUpDuty = 25,
						.Referspeed = 2600,
						.ApPosOffset = {-1800,-1800,-1800,-1800,-1800,-1800,-1800,-1800},
						.ApSumStartup =-1800,
						.ApStartupCout = 130,
						.TiprunStartCout = 120,
						.EbrakEnable = 1,
				},
		/*		***************************************************/
				{ 			/* roll (-1~1) pitch( 12~8)*/
						.DutyOffset = {-1,-2,-1,-2,-2,-1},
						.DutyOffsetPos = {3250,3135,3060,2900,2600,2400,2100},
						.Ki = 1,
						.Kp = 3,
						.StartCurve = {2,1,1,2,1,0,1},
						.StartUpDuty = 20,
						.Referspeed = 1300,
						.ApPosOffset = {0,0,0,0,0,0,0,0},
						.EbrakEnable = 1,
						.TiprunStartCout = 80,
						.ApSumStartup =0,
						.ApStartupCout = 0,
				},
				{ 			/* roll (-1~1) pitch (8~3)*/
						.DutyOffset = {0,-1,-1,-2,-2,0},
						.DutyOffsetPos = {3250,3135,3060,2900,2600,2400,2100},
						.Ki = 1,
						.Kp = 3,
						.StartCurve = {2,1,1,2,1,0,1},
						.StartUpDuty = 20,
						.Referspeed = 1400,
						.ApPosOffset = {0,0,0,0,0,0,0,0},
						.EbrakEnable = 1,
						.TiprunStartCout = 60,
						.ApSumStartup =0,
						.ApStartupCout = 0,
				},
				{ 			/* roll (-1~1) pitch (3~-3)*/
						.DutyOffset = {0,0,0,0,0,0},
						.DutyOffsetPos = {3250,3135,3060,2900,2600,2400,2100},
						.Ki = 22,
						.Kp = 2.5,
						.StartCurve = {2,1,2,3,2,1,2},
						.StartUpDuty = 20,
						.Referspeed = 2100,
						.ApPosOffset = {0,0,0,0,0,0,0,0},
						.EbrakEnable = 0,
						.TiprunStartCout = 60,
						.ApSumStartup =0,
						.ApStartupCout = 0,
				},
				{ 			/* roll (-1~1) pitch (-3~-8)*/
						.DutyOffset = {0,0,0,0,0,0},
						.DutyOffsetPos = {3250,3135,3060,2900,2600,2400,2100},
						.Ki = 22,
						.Kp = 3.0,
						.StartCurve = {2,1,2,3,2,1,2},
						.StartUpDuty = 20,
						.Referspeed = 2100,
						.ApPosOffset = {0,0,0,0,0,0,0,0},
						.EbrakEnable = 1,
						.ApSumStartup =0,
						.ApStartupCout = 0,
						.TiprunStartCout = 60,
				},
			   { 			/* roll (-1~1) pitch (-8~-12)*/
						.DutyOffset = {1,2,0,0,0,0},
						.DutyOffsetPos = {3250,3135,3060,2900,2600,2400,2100},
						.Ki = 4,
						.Kp = 3.5,
						.StartCurve = {2,1,2,1,2,2,1},
						.StartUpDuty = 20,
						.Referspeed = 2600,
						.ApPosOffset = {0,0,0,0,0,0,0,0},
						.ApSumStartup =0,
						.ApStartupCout = 0,
						.TiprunStartCout = 60,
						.EbrakEnable = 1,
				},
			/*		***************************************************/
				{ 			/* roll (1~3) pitch( 12~8)*/
						.DutyOffset = {-1,-2,-1,-2,-2,-1},
						.DutyOffsetPos = {3250,3135,3060,2900,2600,2400,2100},
						.Ki = 1,
						.Kp = 3,
						.StartCurve = {2,1,1,2,1,0,1},
						.StartUpDuty = 20,
						.Referspeed = 1300,
						.ApPosOffset = {-1200,-1200,-1200,-1200,-1200,-1200,-1200,-1200},
						.EbrakEnable = 1,
						.TiprunStartCout = 60,
						.ApSumStartup =-1500,
						.ApStartupCout = 100,
				},
				{ 			/* roll (1~3) pitch (8~3)*/

						.DutyOffset = {0,-1,-1,-2,-2,0},
						.DutyOffsetPos = {3250,3135,3060,2900,2600,2400,2100},
						.Ki = 1,
						.Kp = 3,
						.StartCurve = {2,1,1,2,1,0,1},
						.StartUpDuty = 20,
						.Referspeed = 1400,
						.ApPosOffset = {0,0,0,0,0,0,0,0},
						.EbrakEnable = 1,
						.TiprunStartCout = 60,
						.ApSumStartup =0,
						.ApStartupCout = 0,
				},
				{ 			/* roll (1~3) pitch (3~-3)*/

						.DutyOffset = {0,0,0,0,0,0},
						.DutyOffsetPos = {3250,3135,3060,2900,2600,2400,2100},
						.Ki = 22,
						.Kp = 2.5,
						.StartCurve = {2,1,2,3,2,1,2},
						.StartUpDuty = 20,
						.Referspeed = 2100,
						.ApPosOffset = {0,0,0,0,0,0,0,0},
						.EbrakEnable = 1,
						.TiprunStartCout = 60,
						.ApSumStartup =0,
						.ApStartupCout = 0,

				},
				{ 			/* roll (1~3) pitch (-3~-8)*/
						.DutyOffset = {2,2,2,1,3,2},
						.DutyOffsetPos = {3250,3135,3060,2900,2600,2400,2100},
						.Ki = 8,
						.Kp = 6,
						.StartCurve= {2,2,3,3,1,1,2},
						.StartUpDuty =20,
						.Referspeed = 2400,
						.ApPosOffset = {-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000},
						.ApSumStartup =-1400,
						.ApStartupCout = 120,
						.TiprunStartCout = 120,
						.EbrakEnable = 1,
				},
				{ 			/* roll (1~3) pitch (-8~ -12)*/
						.DutyOffset = {0,0,0,0,0,0},
						.DutyOffsetPos = {3250,3135,3060,2900,2600,2400,2100},
						.Ki = 4,
						.Kp = 3.5,
						.StartCurve = {2,1,2,1,2,2,1},
						.StartUpDuty = 20,
						.Referspeed = 2400,
						.ApPosOffset = {-600,-600,-600,-600,-600,-600,-600,-600},
						.ApSumStartup =-1400,
						.ApStartupCout = 120,
						.TiprunStartCout = 100,
						.EbrakEnable = 1,
				},
				/*		***************************************************/

				{ 			/* roll (3~6) pitch( 12~8)*/
						.DutyOffset = {1,0,0,0,0,0},
						.DutyOffsetPos = {3450,3300,3100,3050,3000,2400,2100},
						.Ki = 5,
						.Kp = 3.0,
						.StartCurve= {1,1,1,1,1,1,1},
						.StartUpDuty = 10,
						.Referspeed = 1300,
						.ApPosOffset = {-600,-600,-600,-600,-600,-600,-600,-600},
						.ApSumStartup =-1200,
						.ApStartupCout = 100,
						.TiprunStartCout = 100,
						.EbrakEnable = 1,
				},
				{ 			/* roll (3~6) pitch (8~3)*/
						.DutyOffset = {1,0,0,0,0,0},
						.DutyOffsetPos = {3450,3300,3100,3050,3000,2400,2100},
						.Ki = 5,
						.Kp = 3.0,
						.StartCurve= {1,1,1,1,1,1,1},
						.StartUpDuty = 10,
						.Referspeed = 1600,
						.ApPosOffset = {-600,-600,-600,-600,-600,-600,-600,-600},
						.ApSumStartup =-1200,
						.ApStartupCout = 80,
						.TiprunStartCout = 100,
						.EbrakEnable = 1,
				},
				{ 			/* roll (3~6) pitch (3~-3)*/
						.DutyOffset = {1,0,0,0,0,0},
						.DutyOffsetPos = {3450,3300,3100,3050,3000,2400,2100},
						.Ki = 5,
						.Kp = 3.0,
						.StartCurve= {1,1,1,1,1,1,1},
						.StartUpDuty = 10,
						.Referspeed = 1800,
						.ApPosOffset = {-600,-600,-600,-600,-600,-600,-600,-600},
						.ApSumStartup =-1200,
						.ApStartupCout = 80,
						.TiprunStartCout = 100,
						.EbrakEnable = 1,
				},
				{ 			/* roll (3~-6) pitch (-3~-8)*/
						.DutyOffset = {1,3,4,3,3,0},
						.DutyOffsetPos = {3250,3135,3060,2900,2600,2400,2100},
						.Ki = 6,
						.Kp = 4.5,
						.StartCurve= {2,3,3,3,2,2,2},
						.StartUpDuty =20,
						.Referspeed = 1900,
						.ApPosOffset = {-1600,-1600,-1600,-1600,-1600,-1600,-1600,-1600},
						.ApSumStartup =-1200,
						.ApStartupCout = 80,
						.TiprunStartCout = 100,
						.EbrakEnable = 1,
				},
				{ 			/* roll (3~-6) pitch (-8~-12)*/
						.DutyOffset = {4,6,5,3,0,0},
						.DutyOffsetPos = {3250,3135,3060,2900,2600,2400,2100},
						.Ki = 5,
						.Kp = 3,
						.StartCurve= {2,3,3,3,3,3,2},
						.StartUpDuty =20,
						.Referspeed = 2200,
						.ApPosOffset = {-2000,-2000,-2000,-2000,-2000,-2000,-2000,-2000},
						.ApSumStartup =-2000,
						.ApStartupCout = 170,
						.TiprunStartCout = 100,
						.EbrakEnable = 1,
				},



};

/*
	up_pitch_high,		//[12,8)
	up_pitch_light,		//[8, 3)
	no_pitch,			//[3,-3)
	low_pitch_light,   	//[-3,8)
	low_pitch_high,    //[-8,-12]
*/
void Roll_Pitch_Adjust(void)
{
/***********************************left_roll_high[-6,-3)  Group1*************************************************/

	if((g_Roll_level==left_roll_high)&&(g_Pitch_level==up_pitch_high))
	{
		gOpen_Roll_Pitch_ParaSet =  OpenRollPitch_Cfg[0];
		gClose_Roll_Pitch_ParaSet = CloseRollPitch_Cfg[0];
	}
	if((g_Roll_level==left_roll_high)&&(g_Pitch_level==up_pitch_light))
	{
		gOpen_Roll_Pitch_ParaSet =  OpenRollPitch_Cfg[1];
		gClose_Roll_Pitch_ParaSet = CloseRollPitch_Cfg[1];
	}
	if((g_Roll_level==left_roll_high)&&(g_Pitch_level==no_pitch))
	{
		gOpen_Roll_Pitch_ParaSet =  OpenRollPitch_Cfg[2];
		gClose_Roll_Pitch_ParaSet = CloseRollPitch_Cfg[2];
	}
	if((g_Roll_level==left_roll_high)&&(g_Pitch_level==low_pitch_light))
	{
		gOpen_Roll_Pitch_ParaSet =  OpenRollPitch_Cfg[3];
		gClose_Roll_Pitch_ParaSet = CloseRollPitch_Cfg[3];
	}
	if((g_Roll_level==left_roll_high)&&(g_Pitch_level==low_pitch_high))
	{
		gOpen_Roll_Pitch_ParaSet =  OpenRollPitch_Cfg[4];
		gClose_Roll_Pitch_ParaSet = CloseRollPitch_Cfg[4];
	}
/*********************************left_roll_light[-3,-1) Group2*******************************************/
	if((g_Roll_level==left_roll_light)&&(g_Pitch_level==up_pitch_high))
	{
		gOpen_Roll_Pitch_ParaSet =  OpenRollPitch_Cfg[5];
		gClose_Roll_Pitch_ParaSet = CloseRollPitch_Cfg[5];
	}
	if((g_Roll_level==left_roll_light)&&(g_Pitch_level==up_pitch_light))
	{
		gOpen_Roll_Pitch_ParaSet =  OpenRollPitch_Cfg[6];
		gClose_Roll_Pitch_ParaSet = CloseRollPitch_Cfg[6];
	}
	if((g_Roll_level==left_roll_light)&&(g_Pitch_level==no_pitch))
	{
		gOpen_Roll_Pitch_ParaSet =  OpenRollPitch_Cfg[7];
		gClose_Roll_Pitch_ParaSet = CloseRollPitch_Cfg[7];
	}
	if((g_Roll_level==left_roll_light)&&(g_Pitch_level==low_pitch_light))
	{
		gOpen_Roll_Pitch_ParaSet =  OpenRollPitch_Cfg[8];
		gClose_Roll_Pitch_ParaSet = CloseRollPitch_Cfg[8];
	}
	if((g_Roll_level==left_roll_light)&&(g_Pitch_level==low_pitch_high))
	{
		gOpen_Roll_Pitch_ParaSet =  OpenRollPitch_Cfg[9];
		gClose_Roll_Pitch_ParaSet = CloseRollPitch_Cfg[9];
	}
/*****************************no_roll [-1,1)   Group3   0K!******************************************/
	if((g_Roll_level==no_roll)&&(g_Pitch_level==up_pitch_high))
	{
		gOpen_Roll_Pitch_ParaSet =  OpenRollPitch_Cfg[10];
		gClose_Roll_Pitch_ParaSet = CloseRollPitch_Cfg[10];
	}
	if((g_Roll_level==no_roll)&&(g_Pitch_level==up_pitch_light))
	{
		gOpen_Roll_Pitch_ParaSet =  OpenRollPitch_Cfg[11];
		gClose_Roll_Pitch_ParaSet = CloseRollPitch_Cfg[11];
	}
	if((g_Roll_level==no_roll)&&(g_Pitch_level==no_pitch))
	{
		gOpen_Roll_Pitch_ParaSet =  OpenRollPitch_Cfg[12];
		gClose_Roll_Pitch_ParaSet = CloseRollPitch_Cfg[12];
	}

	if((g_Roll_level==no_roll)&&(g_Pitch_level==low_pitch_light))
	{
		gOpen_Roll_Pitch_ParaSet =  OpenRollPitch_Cfg[13];
		gClose_Roll_Pitch_ParaSet = CloseRollPitch_Cfg[13];
	}
	if((g_Roll_level==no_roll)&&(g_Pitch_level==low_pitch_high))
	{
		gOpen_Roll_Pitch_ParaSet =  OpenRollPitch_Cfg[14];
		gClose_Roll_Pitch_ParaSet = CloseRollPitch_Cfg[14];
	}
/**************************right_roll_light[1,3) Group4  ok!********************************************/
	if((g_Roll_level==right_roll_light)&&(g_Pitch_level==up_pitch_high))
	{
		gOpen_Roll_Pitch_ParaSet =  OpenRollPitch_Cfg[15];
		gClose_Roll_Pitch_ParaSet = CloseRollPitch_Cfg[15];
	}
	if((g_Roll_level==right_roll_light)&&(g_Pitch_level==up_pitch_light))
	{
		gOpen_Roll_Pitch_ParaSet =  OpenRollPitch_Cfg[16];
		gClose_Roll_Pitch_ParaSet = CloseRollPitch_Cfg[16];
	}
	if((g_Roll_level==right_roll_light)&&(g_Pitch_level==no_pitch))
	{
		gOpen_Roll_Pitch_ParaSet =  OpenRollPitch_Cfg[17];
		gClose_Roll_Pitch_ParaSet = CloseRollPitch_Cfg[17];
	}

	if((g_Roll_level==right_roll_light)&&(g_Pitch_level==low_pitch_light))
	{
		gOpen_Roll_Pitch_ParaSet =  OpenRollPitch_Cfg[18];
		gClose_Roll_Pitch_ParaSet = CloseRollPitch_Cfg[18];
	}
	if((g_Roll_level==right_roll_light)&&(g_Pitch_level==low_pitch_high))
	{
		gOpen_Roll_Pitch_ParaSet =  OpenRollPitch_Cfg[19];
		gClose_Roll_Pitch_ParaSet = CloseRollPitch_Cfg[19];
	}
/*************************right_roll_high[3,6] Group5  ok!******************************************/
	if((g_Roll_level==right_roll_high)&&(g_Pitch_level==up_pitch_high))
	{
		gOpen_Roll_Pitch_ParaSet =  OpenRollPitch_Cfg[20];
		gClose_Roll_Pitch_ParaSet = CloseRollPitch_Cfg[20];
	}
	if((g_Roll_level==right_roll_high)&&(g_Pitch_level==up_pitch_light))
	{
		gOpen_Roll_Pitch_ParaSet =  OpenRollPitch_Cfg[21];
		gClose_Roll_Pitch_ParaSet = CloseRollPitch_Cfg[21];
	}
	if((g_Roll_level==right_roll_high)&&(g_Pitch_level==no_pitch))
	{
		gOpen_Roll_Pitch_ParaSet =  OpenRollPitch_Cfg[22];
		gClose_Roll_Pitch_ParaSet = CloseRollPitch_Cfg[22];
	}

	if((g_Roll_level==right_roll_high)&&(g_Pitch_level==low_pitch_light))
	{
		gOpen_Roll_Pitch_ParaSet =  OpenRollPitch_Cfg[23];
		gClose_Roll_Pitch_ParaSet = CloseRollPitch_Cfg[23];
	}
	if((g_Roll_level==right_roll_high)&&(g_Pitch_level==low_pitch_high))
	{
		gOpen_Roll_Pitch_ParaSet =  OpenRollPitch_Cfg[24];
		gClose_Roll_Pitch_ParaSet = CloseRollPitch_Cfg[24];
	}


}




