#include <settingscommands.h>

void SettingsCommands_Init()
{
	CLI_AddCmd("bright", BrightnessCmd, 1, TMC_None, "set brightness values - [type] <-c channel_no> <-b brightness_value>");
	CLI_AddCmd("getextbright", GetExtBrightCmd, 0, TMC_PrintStartTime | TMC_PrintStopTime, "getextbright");
	CLI_AddCmd("remote", RemoteControlCmd, 0, TMC_None, "set infrared remote parameters - <-a address> <-rm receiver mode> <-sm sender mode> <-sa send address> <-sd send data>");
	CLI_AddCmd("alarmsetting", AlarmSettingsCmd, 0, TMC_None, "set alarm parameters - <-f time to fade-in light>");
	CLI_AddCmd("alarm", AlarmCmd, 0, TMC_None, "trigger, reset, set alarm skip count - <-a 1 | 0> <-s alarm skip count>");
	CLI_AddCmd("power", PowerCmd, 0, TMC_None, "switch light set min external power and battery voltage and calibration- <-l 1 | 0>");
	CLI_AddCmd("reset", ResetSettingsCmd, 0, TMC_None, "reset settings to factory defaults");
	CLI_AddCmd("statusled", StatusLEDCmd, 1, TMC_None, "flash status led  - [flash count]");
}

void printValueArray(unsigned char(*values)[])
{
	int i;
	for (i = 0; i < maxChannel;	i++)
	{
		CLI_Printf("\r\nchannel: %d value: %d", i, (int)*(*values+i));
	};
}

void printIntValueArray(unsigned int(*values)[])
{
	int i;
	for (i = 0; i < maxChannel;	i++)
	{
		CLI_Printf("\r\nchannel: %d value: %d", i, (int)*(*values+i));
	};
}


char* printMinuteOff(char* str, unsigned char Value)
{
	if (0==Value)
		{
		strcpy(str, "off");
		}
	else if (1==Value)
		{
		strcpy(str, "instantly");
		}
	else if (2==Value)
		{
		strcpy(str, "1 min.");
		}
	else
		{
		sprintf(str, "%2d min.", Value-1);
		}
	return &(str[0]);
}


// ***************** implementation commands ****************

uint8_t BrightnessCmd()
{
	uint32_t channel_no = 0;
	uint32_t brightness_value = 0;

	// be sure arguments
	uint32_t type = CLI_GetArgHex(0);

	// optional arguments
	bool cflag = CLI_GetArgDecByFlag("-c", &channel_no) & (channel_no < maxChannel);
	bool bflag = CLI_GetArgDecByFlag("-b", &brightness_value) & (brightness_value <= maxBrightnessLimit);

	switch (type)
	{
		case 0:
			CLI_Printf("\r\nBrightness last used before lights were switched off.");
			if (cflag & bflag)
			{
				GLOBAL_settings_ptr->Brightness_start[channel_no]=brightness_value;
			}
			printValueArray(&(GLOBAL_settings_ptr->Brightness_start));
			break;
		case 1:
			CLI_Printf("\r\nMinimum brightness when switched on:");
			if (cflag & bflag)
			{
				GLOBAL_settings_ptr->minBrightness[channel_no]=brightness_value;
			}
			printValueArray(&(GLOBAL_settings_ptr->minBrightness));
			break;
		case 2:
			CLI_Printf("\r\nMaximum brightness any time:");
			if (cflag & bflag)
			{
				GLOBAL_settings_ptr->maxBrightness[channel_no]=brightness_value;
			}
			printValueArray(&(GLOBAL_settings_ptr->maxBrightness));
			break;
		case 3:
			CLI_Printf("\r\nMaximum brightness when an alarm is triggered:");
			if (cflag & bflag)
			{
				GLOBAL_settings_ptr->AlarmBrightness[channel_no]=brightness_value;
			}
			printValueArray(&(GLOBAL_settings_ptr->AlarmBrightness));
			break;
		case 4:
			CLI_Printf("\r\nPWM offset for brightness:");
			if (cflag & bflag)
			{
				GLOBAL_settings_ptr->PWM_Offset[channel_no]=brightness_value;
				PWM_SetupDim(channel_no, fadetime, 0, 0);
			}
			printIntValueArray(&(GLOBAL_settings_ptr->PWM_Offset));
			break;
		case 5:
			CLI_Printf("\r\nCurrent brightness:");
			if (cflag & bflag)
			{
				Brightness[channel_no]=brightness_value;
				PWM_SetupDim(channel_no, fadetime, 0, 0);
			}
			printValueArray(&Brightness);
			break;
		default:
			return TE_ArgErr;
			break;
	}

	SettingsWrite();

	return TE_OK;
}

uint8_t GetExtBrightCmd()
{
	CLI_Printf("\r\nExternal brightness: %10d", (int) (extBrightness >> 6));
	return TE_OK;
}

uint8_t RemoteControlCmd()
{
	uint32_t address = 0;
	uint32_t receiverMode = 0;
	uint32_t senderMode = 0;
	uint32_t sendData = 0;
	uint32_t sendAddress = 0;

	// optional arguments
	if (CLI_GetArgDecByFlag("-a", &address) & (address <= maxRC5Addr))
	{
		GLOBAL_settings_ptr->RC5Addr = (uint8_t)address;
	}
	if (CLI_GetArgDecByFlag("-rm", &receiverMode) & (receiverMode <= maxComMode))
	{
		GLOBAL_settings_ptr->ReceiverMode = (uint8_t)receiverMode;
	}
	if (CLI_GetArgDecByFlag("-sm", &senderMode) & (senderMode <= maxComMode))
	{
		GLOBAL_settings_ptr->SenderMode = (uint8_t)senderMode;
	}
	if (CLI_GetArgDecByFlag("-sa", &sendAddress) & CLI_GetArgDecByFlag("-sd", &sendData))
	{
		SendRC5(sendAddress, sendData, 1, ComModeOff, RC5Cmd_Repeats);
	}

	CLI_Printf("\r\nRC5 receiver address: %d\r\nreceiver mode: %d %s\r\nsender mode: %d %s",
			(int)GLOBAL_settings_ptr->RC5Addr,
			(int)GLOBAL_settings_ptr->ReceiverMode,
			ComModetext[GLOBAL_settings_ptr->ReceiverMode],
			(int)GLOBAL_settings_ptr->SenderMode,
			ComModetext[GLOBAL_settings_ptr->SenderMode]);

	SettingsWrite();

	return TE_OK;
}

uint8_t AlarmSettingsCmd()
{
	uint32_t fading = 0;
	char strf[12];

	// optional arguments
	if (CLI_GetArgDecByFlag("-f", &fading))
	{
		GLOBAL_settings_ptr->LightFading = (uint8_t)fading;
	}

	SettingsWrite();

	CLI_Printf("\r\ntime to fade-in light: %s", printMinuteOff(strf, GLOBAL_settings_ptr->LightFading));

	return TE_OK;
}

uint8_t AlarmCmd()
{
	uint32_t set = 0;

	// optional arguments

	if (CLI_GetArgDecByFlag("-a", &set) & (set <=1))
	{
		AlarmTrigger = (set == 1);
	}

	return TE_OK;
}


uint8_t PowerCmd()
{
	uint32_t light = 0;

	if (CLI_GetArgDecByFlag("-l", &light))
	{
		if (light == 0)
		{
			SwAllLightOff();
		}
		else
		{
			SwAllLightOn();
		}
	}

	return TE_OK;
}

uint8_t ResetSettingsCmd()
{
	CLI_Printf("\r\nReset settings to factory defaults.");
	SettingsReset2Defaults();

	return TE_OK;
}

uint8_t StatusLEDCmd()
{
	// be sure arguments
	uint32_t flashCount = CLI_GetArgDec(0);
	if (flashCount <= LEDFlashMaxSeq)
	{
		LEDSetupOptions(flashCount);
		return TE_OK;
	}
	else
	{
		return TE_ArgErr;
	}
}
