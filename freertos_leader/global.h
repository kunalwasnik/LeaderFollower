/*
 * global.h
 *
 *  Created on: 07-Apr-2024
 *      Author: karti
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123GH6pm.h"
#include "gpio_pins.h"

/*
 * MACROS
 */

#define COLOR_GREEN_ON 0x08
#define COLOR_BLUE_ON 0x04
#define COLOR_CYAN_ON 0x0C
#define COLOR_RED_ON 0x02
#define COLOR_YELLOW_ON 0x0A
#define COLOR_MAGENTA_ON 0x06
#define COLOR_WHITE_ON 0x0E

#define LED_OFF 0x00


/*
 * Varibables
 */


//IR SENSOR
extern int ir_turn_read_only_value;




#endif /* GLOBAL_H_ */
