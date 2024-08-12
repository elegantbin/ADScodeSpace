/**
 * @file app_VelocityControl.c
 * @brief Application implementation: Control.
 *
 */

//---------------------------------------------------------------------------
#include "DoorSys.h"
#include <DoorSys_VelocityControl.h>
#include "DoorSysCfg_Velocity.h"
#include <MotAct.h>
#include "IMU.h"
#include <Roll_Pitch_Parameter.h>
//---------------------------------------------------------------------------


uint16_t assistdutyflag=1;

VelocityControl g_velocityControl;

int16_t g_i16DoorDutyPercent = K_VELOCITY_DUTY_PERCENT;
int16_t g_i16DoorDutyPercent_1;
int8_t OPEN_ADJUST[5]= {0,0,0,0,0};
/** @brief Execute the speed PI controller
 *
 * @param VelocityControl Specifies the velocity control object.
 * @param Speed Specifies the current speed.
 *
 * @return the speed controller output.
 * @see Pic()
 * @ingroup app_velocity_control
 */
float32 VelocityControl_Do(VelocityControl *velocityControl, float32 speed)
{
	float32 result;
    if (velocityControl->enabled != FALSE)
    {
        result = Pic_Do(&velocityControl->pi, velocityControl->ref - speed);
    }
    else
    {
        result = velocityControl->pi.uk;
    }
    return result;
}

/** @brief Initialize the velocity control object
 *
 * @param VelocityControl Specifies the velocity control object.
 *
 * @return None.
 * @see Pic_Init()
 * @ingroup app_velocity_control
 */
void VelocityControl_Init(void)
{
	VelocityControl* velocityControl = &g_velocityControl;

	DoorControl_t *door = &g_door;

    Pic_Init(&velocityControl->pi);

    if(door->b_dir_open_fbk != 0)
    {
    	 // VelocityControl_SetKpKi(velocityControl, OPEN_VELOCITY_CONTROL_KP, OPEN_VELOCITY_CONTROL_KI, VELOCITY_CONTROL_PERIOD,0, 0);

    	  VelocityControl_SetKpKi(velocityControl, (gOpen_Roll_Pitch_ParaSet.Kp*VELOCITY_Kp_FACTOR)
    			  ,(gOpen_Roll_Pitch_ParaSet.Ki*VELOCITY_Ki_FACTOR), VELOCITY_CONTROL_PERIOD,0, 0);  //!!
    }else
    {
    	//VelocityControl_SetKpKi(velocityControl, CLOSE_VELOCITY_CONTROL_KP, CLOSE_VELOCITY_CONTROL_KI, VELOCITY_CONTROL_PERIOD,0, 0);
    	VelocityControl_SetKpKi(velocityControl,
    			(gClose_Roll_Pitch_ParaSet.Kp*VELOCITY_Kp_FACTOR),(gClose_Roll_Pitch_ParaSet.Ki*VELOCITY_Ki_FACTOR),
				VELOCITY_CONTROL_PERIOD,0, 0);  //!

    }



    VelocityControl_SetLimit(velocityControl, VELOCITY_CONTROL_MIN, VELOCITY_CONTROL_MAX);
    VelocityControl_SetMaxSpeed(velocityControl, VELOCITY_CONTROL_MAX_RPM);

    VelocityControl_SetRefSpeed(velocityControl, VELOCITY_CONTROL_REF_NORM);

    VelocityControl_Enable(velocityControl);
}


void VelocityControl_open_adjust_curve(void)
{

	int8_t OPEN_ADJUST[5]= {2,1,-2,-3,-2};
	DoorControl_t *door = &g_door;

	if((door->u16Realtime_Pos>2100)&&(door->u16Realtime_Pos<2600)&&(assistdutyflag==1))
	{

					g_i16DoorDutyPercent+=OPEN_ADJUST[0];
					assistdutyflag=2;

	}
	if((door->u16Realtime_Pos>2600)&&(door->u16Realtime_Pos<3000)&&(assistdutyflag==2))
	{
					g_i16DoorDutyPercent+=OPEN_ADJUST[1];
					assistdutyflag=3;

	}
	if((door->u16Realtime_Pos>3000)&&(door->u16Realtime_Pos<3060)&&(assistdutyflag==3))
	{

		g_i16DoorDutyPercent+=OPEN_ADJUST[2];
					assistdutyflag=4;
	}
	if((door->u16Realtime_Pos>3060)&&(door->u16Realtime_Pos<3135)&&(assistdutyflag==4))
	{

		g_i16DoorDutyPercent+=OPEN_ADJUST[3];
					assistdutyflag=5;
	}
				if((door->u16Realtime_Pos>3135)&&(door->u16Realtime_Pos<3250)&&(assistdutyflag==5))
	{

					g_i16DoorDutyPercent+=OPEN_ADJUST[4];
					assistdutyflag=1;
	}

}

void VelocityControl_open_adjust_curve1(void)

{

/*	int8_t OPEN_ADJUST[5]= {2,1,-2,-3,-2};*/
	DoorControl_t *door = &g_door;

	if((door->u16Realtime_Pos>gOpen_Roll_Pitch_ParaSet.DutyOffsetPos[0])&&(door->u16Realtime_Pos<gOpen_Roll_Pitch_ParaSet.DutyOffsetPos[1])&&(assistdutyflag==1))
	{

					g_i16DoorDutyPercent+=gOpen_Roll_Pitch_ParaSet.DutyOffset[0];
					assistdutyflag=2;

	}
	if((door->u16Realtime_Pos>gOpen_Roll_Pitch_ParaSet.DutyOffsetPos[1])&&(door->u16Realtime_Pos<gOpen_Roll_Pitch_ParaSet.DutyOffsetPos[2])&&(assistdutyflag==2))
	{
					g_i16DoorDutyPercent+=gOpen_Roll_Pitch_ParaSet.DutyOffset[1];
					assistdutyflag=3;

	}
	if((door->u16Realtime_Pos>gOpen_Roll_Pitch_ParaSet.DutyOffsetPos[2])&&(door->u16Realtime_Pos<gOpen_Roll_Pitch_ParaSet.DutyOffsetPos[3])&&(assistdutyflag==3))
	{

		g_i16DoorDutyPercent+=gOpen_Roll_Pitch_ParaSet.DutyOffset[2];
					assistdutyflag=4;
	}
	if((door->u16Realtime_Pos>gOpen_Roll_Pitch_ParaSet.DutyOffsetPos[3])&&(door->u16Realtime_Pos<gOpen_Roll_Pitch_ParaSet.DutyOffsetPos[4])&&(assistdutyflag==4))
	{

		g_i16DoorDutyPercent+=gOpen_Roll_Pitch_ParaSet.DutyOffset[3];
					assistdutyflag=5;
	}
	if((door->u16Realtime_Pos>gOpen_Roll_Pitch_ParaSet.DutyOffsetPos[4])&&(door->u16Realtime_Pos<gOpen_Roll_Pitch_ParaSet.DutyOffsetPos[5])&&(assistdutyflag==5))
	{

					g_i16DoorDutyPercent+=gOpen_Roll_Pitch_ParaSet.DutyOffset[4];
					assistdutyflag=1;
	}

}

void VelocityControl_close_adjust_curve(void)

{

	DoorControl_t *door = &g_door;
	int8_t CLOSE_ADJUST[6]= {5,3,3,2,3,4};


	if((door->u16Realtime_Pos<3450)&&(door->u16Realtime_Pos>3300)&&(assistdutyflag==1))
		{
					g_i16DoorDutyPercent+=CLOSE_ADJUST[0];
					assistdutyflag=2;
		}


	if((door->u16Realtime_Pos<3300)&&(door->u16Realtime_Pos>3100)&&(assistdutyflag==2))
		{
			g_i16DoorDutyPercent+=CLOSE_ADJUST[1];
			assistdutyflag=3;
		}

	if((door->u16Realtime_Pos<3100)&&(door->u16Realtime_Pos>3050)&&(assistdutyflag==3))
		{
					g_i16DoorDutyPercent+=CLOSE_ADJUST[2];
					assistdutyflag=4;
		}
	if((door->u16Realtime_Pos<3050)&&(door->u16Realtime_Pos>3000)&&(assistdutyflag==4))
		{

							g_i16DoorDutyPercent+=CLOSE_ADJUST[3];
							assistdutyflag=5;
		}

	if((door->u16Realtime_Pos<3000)&&(door->u16Realtime_Pos>2400)&&(assistdutyflag==5))
		{
				g_i16DoorDutyPercent+=CLOSE_ADJUST[4];
				assistdutyflag=6;

		}
	if((door->u16Realtime_Pos<2400)&&(door->u16Realtime_Pos>2100)&&(assistdutyflag==6))
		{
			g_i16DoorDutyPercent+=CLOSE_ADJUST[5];
			assistdutyflag=1;

		}

}


void VelocityControl_close_adjust_curve1(void)

{

	DoorControl_t *door = &g_door;
	int8_t CLOSE_ADJUST[6]= {5,3,3,2,3,4};


	if((door->u16Realtime_Pos<gClose_Roll_Pitch_ParaSet.DutyOffsetPos[0])&&(door->u16Realtime_Pos>gClose_Roll_Pitch_ParaSet.DutyOffsetPos[1])&&(assistdutyflag==1))
		{
					g_i16DoorDutyPercent+=gClose_Roll_Pitch_ParaSet.DutyOffset[0];
					assistdutyflag=2;
		}


	if((door->u16Realtime_Pos<gClose_Roll_Pitch_ParaSet.DutyOffsetPos[1])&&(door->u16Realtime_Pos>gClose_Roll_Pitch_ParaSet.DutyOffsetPos[2])&&(assistdutyflag==2))
		{
			g_i16DoorDutyPercent+=gClose_Roll_Pitch_ParaSet.DutyOffset[1];
			assistdutyflag=3;
		}

	if((door->u16Realtime_Pos<gClose_Roll_Pitch_ParaSet.DutyOffsetPos[2])&&(door->u16Realtime_Pos>gClose_Roll_Pitch_ParaSet.DutyOffsetPos[3])&&(assistdutyflag==3))
		{
					g_i16DoorDutyPercent+=gClose_Roll_Pitch_ParaSet.DutyOffset[2];
					assistdutyflag=4;
		}
	if((door->u16Realtime_Pos<gClose_Roll_Pitch_ParaSet.DutyOffsetPos[3])&&(door->u16Realtime_Pos>gClose_Roll_Pitch_ParaSet.DutyOffsetPos[4])&&(assistdutyflag==4))
		{

							g_i16DoorDutyPercent+=gClose_Roll_Pitch_ParaSet.DutyOffset[3];
							assistdutyflag=5;
		}

	if((door->u16Realtime_Pos<gClose_Roll_Pitch_ParaSet.DutyOffsetPos[4])&&(door->u16Realtime_Pos>gClose_Roll_Pitch_ParaSet.DutyOffsetPos[5])&&(assistdutyflag==5))
		{
				g_i16DoorDutyPercent+=gClose_Roll_Pitch_ParaSet.DutyOffset[4];
				assistdutyflag=6;

		}
	if((door->u16Realtime_Pos<gClose_Roll_Pitch_ParaSet.DutyOffsetPos[5])&&(door->u16Realtime_Pos>gClose_Roll_Pitch_ParaSet.DutyOffsetPos[6])&&(assistdutyflag==6))
		{
			g_i16DoorDutyPercent+=gClose_Roll_Pitch_ParaSet.DutyOffset[5];
			assistdutyflag=1;

		}

}


void VelocityControl_Task(void)      /* 1ms task*/
{
	static uint16_t u16VelocityCtrlCount=0;
	DoorControl_t *door = &g_door;
	VelocityControl* velocityControl = &g_velocityControl;


	if(u16VelocityCtrlCount > K_VELOCITY_CTRL_COUNT)
	{
		u16VelocityCtrlCount = 0;
		if(VelocityControl_IsEnabled(velocityControl))
		{
			// set reference Speed
			velocityControl->speed =(float)(door->u16Velocity);

			float32 result = VelocityControl_Do(velocityControl, velocityControl->speed);

			g_i16DoorDutyPercent_1 = (int16_t)(result * 100);

			if(g_i16DoorDutyPercent_1 > K_VELOCITY_DUTY_MAX)
			{
				g_i16DoorDutyPercent_1 = K_VELOCITY_DUTY_MAX;

			}
			else if(g_i16DoorDutyPercent_1 < K_VELOCITY_DUTY_MIN)
			{
				g_i16DoorDutyPercent_1 = K_VELOCITY_DUTY_MIN;

			}

			if(g_i16DoorDutyPercent_1 >g_i16DoorDutyPercent)
			{
				g_i16DoorDutyPercent+=1;

			}
			else
			{
				g_i16DoorDutyPercent-=1;
			}

			/*g_i16DoorDutyPercent = g_i16DoorDutyPercent_1;*/

			if(door->b_dir_open_fbk == 1) //door->b_dir_open
			{
				VelocityControl_open_adjust_curve1();


			}

			if(door->b_dir_close_fbk == 1) //door->b_dir_close
            {
				VelocityControl_close_adjust_curve1();
            }

		}
		else
		{
			/* Velocity Control disable */
		}
	}
	else
	{
		u16VelocityCtrlCount++;
	}
}
