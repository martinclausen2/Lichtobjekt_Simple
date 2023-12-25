# Lichtobjekt Simple

The "Lichtobjekt Simple" projects allows to create simple lighting appliances.

## Features

- One LED driver channels
  - Flicker free brightness control through current adjustment
- Status LED to indicate power on and standby
- Brightness measurement to adjust brightness at power on
- IR remote control receiver
- Single rotational encoder and switch needed to control

## Technical Features
- ARM Cortex M3 based STM32L151 microcontroller
  - EEPROM for permanent storage of settings
- RC5 based communication receiver
- TPS61165DBVT step-up LED driver with PWM adjustment of LED driving current up to 350mA
- High dynamic brightness measurement with low cost phototransistor SFH320

# Design description

## Hardware

### MCU
The STM32L1 series features for this application relevant features like a large number of timers and an embedded EEPROM.

The MCU can be programmed and debugged via SWD accessable through a custom pin header, that also exposes the serial port.

There is not terminal available to adjust the configuration due to a lack of program memory with the selected MCU FLASH size.

### LED Driver
To drive a sufficient number of LEDs for edge illumination without efficiency reducing current balancing resistors, a LED driver with a step-up topology was selected.

### RC5 receiver and sender

To receive RC5 commands the output of the IR receiver is sampled at a rate of about 4.5kHz by the MCU. The power supply of the IR receiver is cut in standby mode to prevent the battery to be drained prematurely.

### Brightness Sensor

The ambient brightness is sensed via an in expensive a broadly available phototransistor SFA 320. To enhance the dynamic range, the MCU can switch the bias current between two different levels.
The precision is fully sufficient to adjust the brightness of the power LEDs at power on and dim the status LED in standby.

## Software

TBA

## Known Limitations
- The ioc file currently targets the STM32L151 which is not available anymore. The setup can easily be changed to the STM32L151A.

# User Manual

The user interface is rather simplistic.

Turning the encoder increases or decreases the brightness.
The integrated push button is used to select functionality and change between on and off.

Coming from standby a short button press switches the light on.

When the button is pressed, the status led previews a for a short time the next selected functionality.

Standby can be reached via a long button pressed from power on mode.

| LED Color 	| Condition | Status   | 
| :------------ | :------ | :------- |
| red			|         | standby  |
| white			|         | power on |
| green flash	| while adjusting brightness | maximum brightness reached |
| red flash		| while adjusting brightness | minimum brightness reached |
| green flash	| pressing the button very long | cancel button pressed |

The user can reset to default settings by pressing the button on power on.