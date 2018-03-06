/*
 * LEDMatrix.h
 *
 *  Created on: 04.03.2018
 *      Author: Felix
 */

#ifndef SRC_LEDMATRIX_H_
#define SRC_LEDMATRIX_H_

#include <Arduino.h>
#include "FastLED.h"

class LEDMatrix {
public:
	LEDMatrix();
	LEDMatrix(uint16_t columns, uint16_t rows, bool background);
	virtual ~LEDMatrix();

	// sets the rgb value of an led
	void set_led(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b);

	// sets all led's to a color
	void set_all(uint8_t r, uint8_t g, uint8_t b);

	// updates the led's to show new states
	void flip();

	// allocates memory for the background
	void init_background();

	// calculates a logarithmic interpolation between c_min and c_max with respect to the (step) distance to the center
	// c_min CANNOT be 0
	void log_background(uint8_t c_min, uint8_t c_max);

	// draws the background
	void draw_background();

	// for debugging
	void print_background();

private:
	// stores the size of the LED Matrix
	uint16_t columns;
	uint16_t rows;
	uint16_t num_leds;

	CRGB *leds;

	// is able to store a background if wanted
	CRGB *background;

	// maps an x (column), y (row) coordinate to index in leds array
	uint16_t map_snake(uint16_t x, uint16_t y);
};

#endif /* SRC_LEDMATRIX_H_ */
