/**
 * @brief my configuration file for an ATMega 2560-based OAT.
 * 
 * This configuration includes NEMA17 steppers on RA & DEC axes with TMC2209_UART drivers, 
 * GPS. Display is Arduino LCD shield with keypad. 
 * USB serial port is set for direct connection to Stellarium.
 * Wifi is not available on ATmega, so is disabled.
 */

#pragma once

// Used RA wheel version. Unless you printed your OAT before March 2020, you're using
// a version 2 or higher (software only differentiates between 1 and more than 1)
#define RA_WHEEL_VERSION 4

// We are using the RAMPS c/w ATMega 2560 (or clone) board
#if defined(BOARD) && BOARD != BOARD_AVR_MEGA2560
    //#error Selected PIO environment does not match this configuration
#else
    #define BOARD BOARD_AVR_MEGA2560
#endif

// Track immediately after boot
#define TRACK_ON_BOOT 0

/**
 * @brief Stepper motor type in use on RA and DEC axes.
 * See Constants.hpp for supported options.
 */
#define RA_STEPPER_TYPE  STEPPER_TYPE_NEMA17
#define DEC_STEPPER_TYPE STEPPER_TYPE_NEMA17

/**
 * @brief Stepper driver type in use on RA and DEC axes, with associated pin assignments
 * See Constants.hpp for supported DRIVER_TYPE options.
 */
#define RA_DRIVER_TYPE           DRIVER_TYPE_TMC2209_UART
#define DEC_DRIVER_TYPE          DRIVER_TYPE_TMC2209_UART

// TMC2209 UART settings

// Define some RA stepper motor settings
#define RA_MOTOR_CURRENT_RATING       450 // mA
#define RA_OPERATING_CURRENT_SETTING  90 // %
#define RA_SLEW_MICROSTEPPING         16
#define RA_TRACKING_MICROSTEPPING     256


// Define some DEC stepper motor settings
#define DEC_MOTOR_CURRENT_RATING       450 // mA 
#define DEC_OPERATING_CURRENT_SETTING  90 // %
#define DEC_SLEW_MICROSTEPPING         16
#define DEC_GUIDE_MICROSTEPPING        256


#define RA_STEPPER_SPEED         400  // Max. Speed = 600 for 28BYJ-48 and 3000 for NEMA17. Defaults = 400 for 28BYJ-48 and 1200 for NEMA17
#define RA_STEPPER_ACCELERATION  600  // Defaults: 600 for 28BYJ-48, 6000 for NEMA17
#define DEC_STEPPER_SPEED        600  // Max. Speed = 600 for 28BYJ-48 and 3000 for NEMA17. Defaults = 600 for 28BYJ-48 and 1300 for NEMA17
#define DEC_STEPPER_ACCELERATION 600  // Defaults: 600 for 28BYJ-48, 6000 for NEMA17
#define BACKLASH_STEPS           0    //Number of steps of backlash for RA motor. Defaults: 16 for 28BYJ, 0 for NEMA

#define USE_VREF 0  //By default Vref is ignored when using UART to specify rms current. Only enable if you know what you are doing.

// Define limits for RA... 
#define RA_LIMIT_LEFT     5.5f
#define RA_LIMIT_RIGHT    6.5f
#define RA_TRACKING_LIMIT 6.75f // can't quite get to 7h...

// TMC2209 Stealth Mode (spreadCycle)
// More precise tracking when not in stealth mode, but steppers will sound
#define RA_UART_STEALTH_MODE  1
#define DEC_UART_STEALTH_MODE 1

// Set the tooth gear for DEC & RA belt
#define DEC_PULLEY_TEETH 16
#define RA_PULLEY_TEETH 20

// Is it going the wrong way?
#define RA_INVERT_DIR  0
#define DEC_INVERT_DIR  0

/**
 * @brief GPS receiver configuration.
 * Set USE_GPS to 1 to enable, 0 or #undef to exclude GPS from configuration.
 */
#define USE_GPS 1

/**
 * @brief Gyro-based tilt/roll levelling configuration.
 * Set USE_GYRO_LEVEL to 1 to enable, 0 or #undef to exclude gyro from configuration.
 */
#define USE_GYRO_LEVEL 0

/**
 * @brief Display & keypad configuration.
 * See Constants.hpp for supported DISPLAY_TYPE options.
 * Pin assignments vary based on display & keypad selection.
 */
#define DISPLAY_TYPE DISPLAY_TYPE_LCD_KEYPAD

/**
 * @brief External (USB) serial port configuration.
 * See Constants.hpp for predefined SERIAL_BAUDRATE options, or customize as required.
 */
#define SERIAL_BAUDRATE SERIAL_BAUDRATE_ASCOM

///////////////////////
// Debug settings
#define DEBUG_LEVEL (DEBUG_NONE)
// DEBUG_COORD_CALC|DEBUG_MOUNT_VERBOSE


//////////////////////////////////////
// Extra Settings here.

// MOTOR & DRIVER SETTINGS    ////////

#define RA_STEPPER_SPR 400  // NEMA 0.9° = 400  |  NEMA 1.8° = 200
#define DEC_STEPPER_SPR 400  // NEMA 0.9° = 400  |  NEMA 1.8° = 200
