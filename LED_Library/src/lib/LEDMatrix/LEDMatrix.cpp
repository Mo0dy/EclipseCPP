/*
 * LEDMatrix.cpp
 *
 *  Created on: 04.03.2018
 *      Author: Felix
 */

#include <LEDMatrix.h>

#define DATA_PIN 10

LEDMatrix::LEDMatrix() {
	// TODO Auto-generated constructor stub
	this->rows = 0;
	this->columns = 0;
	this->num_leds = 0;
	this->leds = nullptr;
	this->background = nullptr;
}

LEDMatrix::LEDMatrix(uint16_t columns, uint16_t rows, bool background) {
	// saves the size of the matrix
	this->rows = rows;
	this->columns = columns;
	this->num_leds = rows * columns;

	if (background) {
		// allocates memory for background.
		this->background = (CRGB*) malloc(this->num_leds * sizeof(CRGB));
		memset(this->background, CRGB(), this->num_leds);
	}

	// makes memory available to store the state of the led's
	this->leds = (CRGB*) malloc(num_leds * sizeof(CRGB));
	memset(this->leds, CRGB(), num_leds);

	this->set_all(0, 0, 0);

	FastLED.addLeds<WS2812B, DATA_PIN, GRB>(this->leds, this->num_leds);


}

LEDMatrix::~LEDMatrix() {
	// TODO Auto-generated destructor stub
	free(leds);
	free(background);
}

uint16_t LEDMatrix::map_snake(uint16_t x, uint16_t y) {
	if (y % 2) {
		// second, fourth, sixth . . . row
		return (this->rows - y - 1) * this->columns + (this->columns - x - 1);
	} else {
		// first, third, fith . . . row
		return (this->rows - y - 1) * this->columns + x;
	}
}

void LEDMatrix::set_led(uint16_t x, uint16_t y, uint8_t r, uint8_t g,
		uint8_t b) {
	this->leds[this->map_snake(x, y)].setRGB(r, g, b);
}

void LEDMatrix::flip() {
	FastLED.show();
}

void LEDMatrix::set_all(uint8_t r, uint8_t g, uint8_t b) {
	for (uint16_t i = 0; i < this->num_leds; i++) {
		this->leds[i].setRGB(r, g, b);
	}
}

void LEDMatrix::log_background(uint8_t c_min, uint8_t c_max) {
	// calculate background
	// calculate the center coordinates i.e. for a 10x10 matrix they would be 5.5, 5.5 respectively
	float center_x = (this->columns - 1) / 2.0;
	float center_y = (this->rows - 1) / 2.0;

	// maximum possible distance any point can have
	float max_dist = center_x + center_y;

	// logarithmic interpolation c(v) = a * e^(b * i)
	float a = c_min;
	float b = log(c_max / float(c_min)) / max_dist;

	// for every coordinate
	for (uint8_t x = 0; x < this->columns; x++) {
		for (uint8_t y = 0; y < this->rows; y++) {
			// calculate distance (not eucle  adian)
			float d = abs(center_x - x) + abs(center_y - y);
			// logarithmic interpolation over distance between c_min and c_max for a yellow (red and green) color
			// int c = (max_dist - d) / max_dist * (c_max - c_min) + c_min;
			uint8_t c = a * exp(b * d);

			// only maps blue and green
			this->background[this->map_snake(x, y)].setRGB(0, c, c);
		}
	}
}

void LEDMatrix::draw_background() {
	memcpy(this->leds, this->background, this->num_leds * sizeof(CRGB));
}

void LEDMatrix::print_background() {
	for (uint16_t i = 0; i < this->num_leds; i++) {
		Serial.print("LED: ");
		Serial.print(i);
		Serial.print(": r = ");
		Serial.print(this->background[i].r);
		Serial.print(" | g = ");
		Serial.print(this->background[i].g);
		Serial.print(" | b = ");
		Serial.println(this->background[i].b);
	}
}
