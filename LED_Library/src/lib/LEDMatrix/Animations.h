/*
 * Animations.h
 *
 *  Created on: 04.03.2018
 *      Author: Felix
 */

#ifndef SRC_LIB_LEDMATRIX_ANIMATIONS_H_
#define SRC_LIB_LEDMATRIX_ANIMATIONS_H_

#include <LEDMatrix.h>

void blink_anim(LEDMatrix &matrix, int delay_ms, int count, uint8_t r1, uint8_t g1,
		uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2);


#endif /* SRC_LIB_LEDMATRIX_ANIMATIONS_H_ */
