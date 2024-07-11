/*
 * ir_sensor.h
 *
 *  Created on: 07-Apr-2024
 *      Author: karti
 */

#ifndef IR_SENSOR_H_
#define IR_SENSOR_H_

/*
 * HEADER FILES
 */
#include "global.h"

/*
 * MACROS
 */
#define IR_SEN_PIN1 PA2
#define IR_SEN_PIN2 PA3
#define IR_SEN_PIN3 PA4
#define IR_SEN_PIN4 PA5
#define IR_SEN_PIN5 PA6

#define SENSOR_READ (IR_SEN_PIN1 | IR_SEN_PIN2 |IR_SEN_PIN3 |IR_SEN_PIN4|IR_SEN_PIN5)

#endif /* IR_SENSOR_H_ */
