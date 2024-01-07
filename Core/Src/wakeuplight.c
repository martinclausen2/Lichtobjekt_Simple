/*
 * wakeuplight.c
 *
 *  Created on: 14.04.2023
 *      Author: Martin
 */

#include "wakeuplight.h"

unsigned int AlarmDim_Cnt[maxChannel] = {0};
unsigned int AlarmDim_Cnt_Reload[maxChannel] = {0};

//stays on as long as the light fades in
bool AlarmFlag = false;
bool AlarmTrigger = false;

void CheckAlarm()
{
	if (AlarmTrigger)
	{
		AlarmTrigger = false;

		//execute a new alarm, but only if none is already running
		if (!AlarmFlag)
		{
			for (int i = 0; i < maxChannel;	i++)
			{
				// fade in to required brightness in on or off,
				// no fade in if already brighter, Alarm_StepDim() takes care of this behavior
				AlarmDim_Cnt_Reload[i]=(GLOBAL_settings_ptr->LightFading*callsinminute)/GLOBAL_settings_ptr->AlarmBrightness[i];
				AlarmDim_Cnt[i]=AlarmDim_Cnt_Reload[i];
			}
			LightOn=1;
			AlarmFlag=1;
			SendRC5(RC5Addr_com, RC5Cmd_AlarmStart, 1, ComModeAlarm, RC5Cmd_Repeats);
		}
	}

	//wake-up light dimming all channels
	if (AlarmFlag)
	{
		for (int i = 0; i < maxChannel;	i++)
		{
			Alarm_StepDim(i);
		}
	}
}

//stop any brightness increase, count down to acoustic alarm, or acoustic alarm
void AlarmEnd()
{
	if (AlarmFlag)
	{
		SendRC5(RC5Addr_com, RC5Cmd_AlarmEnd, 1, ComModeAlarm, RC5Cmd_Repeats);
		AlarmFlag=0;
		LEDOn();
	}
}

//wake-up light dimming
void Alarm_StepDim(unsigned char i)
{
	if (AlarmDim_Cnt[i])
	{
		--AlarmDim_Cnt[i];				//count down step
	}
	else								//dimming step
	{
		if (Brightness[i] < GLOBAL_settings_ptr->AlarmBrightness[i])
		{
			int dimsteps = Brightness[i] + AlarmBrightnessStep;
			dimsteps = dimsteps * dimsteps - Brightness[i] * Brightness[i];

			AlarmDim_Cnt[i]=AlarmDim_Cnt_Reload[i];		//reload count down
			PWM_SetupDim(i, dimsteps, AlarmBrightnessStep, AlarmDim_Cnt_Reload[i]*cases/dimsteps);	//setup brightness
		}
		else
		{
			AlarmFlag=0;				//we reached target brightness!
		}
	}
}
