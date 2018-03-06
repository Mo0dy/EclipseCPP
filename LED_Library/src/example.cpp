/*
 * main.cpp
 *
 *  Created on: 04.03.2018
 *      Author: Felix
 */

#include <Arduino.h>
#include "Animations.h"
#include "LEDMatrix.h"
#include <EEPROM.h>
#include <LiquidCrystal.h>

// size of the matrix
#define ROWS 10
#define COLUMNS 10

// LiquidCrystal ==========================================
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

// the eprom adresse the highscore is saved to
#define HIGH_SCORE_ADRESS 0

// stores a 2d position
struct position {
	uint16_t x;
	uint16_t y;
};

// the direction the snake is moving to
enum Direction {
	up, down, left, right
};
Direction dir;

LEDMatrix led_matrix;

bool paused = false;

// stores the length of the snake
int snake_length;
// stores the initial shape of the snake
position init_snake[] = { { 4, 4 }, { 5, 4 }, { 6, 4 }, { 4, 5 } };

// the snake is an ordered list of coordinates
// only the positions up until snake_length - 1 are displayed
position snake[ROWS * COLUMNS];

// the apple the snake chases after
position apple;

// the delay between frames
int delay_ms = (100);

// moves the goal to a new position
void new_apple() {
	bool on_snake = true;

	// chose new position if the chosen position alignes with the snake body
	while (on_snake) {
		apple.x = random8(COLUMNS - 1);
		apple.y = random8(ROWS - 1);

		// checks for collision with snake
		on_snake = false;
		for (int i = 0; i < snake_length; i++) {
			// checks if it is on snake part
			if (snake[i].x == apple.x && snake[i].y == apple.y) {
				on_snake = true;
				break;
			}
		}
	}
}

void draw_score() {
	lcd.clear();

	lcd.setCursor(0, 0);
	lcd.print("score:     ");
	lcd.print(snake_length);

	lcd.setCursor(0, 1);
	lcd.print("highscore: ");
	lcd.print(EEPROM.read(HIGH_SCORE_ADRESS));
}

// resets the playing field
void reset() {
	snake_length = 4;
	dir = up;
	// sets the beginning of the snake to init_snake
	memcpy(&snake, &init_snake, sizeof(init_snake));

	new_apple();
	paused = true;
}

void update_hightscore() {
	if (snake_length <= 256) {
		Serial.println("============================");

		uint8_t score = snake_length;
		Serial.print("Score: ");
		Serial.println(score);

		uint8_t old_highscore = EEPROM.read(HIGH_SCORE_ADRESS);
		Serial.print("old highscore: ");
		Serial.println(old_highscore);
		if (score > old_highscore) {
			Serial.println("NEW HIGHSCORE!!!");
			lcd.setCursor(0, 0);
			lcd.print("HIGHSCORE!!!");
			lcd.setCursor(0, 1);
			lcd.print("score = ");
			lcd.print(score);

			// save new hightscore
			EEPROM.write(HIGH_SCORE_ADRESS, score);
		}
		Serial.println("============================");
		Serial.println("");
	} else {
		Serial.print("ERROR COULD NOT SAVE SCORE. SCORE IS GREATER THEN 256");
	}
}

// triggered failure state
void game_over() {
	update_hightscore();
	blink_anim(led_matrix, 100, 2, 5, 0, 0, 0, 0, 0);
	reset();
}

void handle_input() {
	// Serial input form python controller mapper this should be its own library
	// Serial input
	while (Serial.available()) {
		char c = Serial.read();
		paused = false;
		if (char(c) == 'B') {
			dir = right;
		} else if (char(c) == 'X') {
			dir = left;
		} else if (char(c) == 'A') {
			dir = down;
		} else if (char(c) == 'Y') {
			dir = up;
		}
	}
}

// this delay function handles input while waiting
void my_delay(unsigned int ms) {
	unsigned long end_time = millis() + ms;
	while (end_time > millis()) {
		handle_input();
		delay(5);
	}
}

void draw_snake() {
	for (int i = 0; i < snake_length; i++) {
		position s = snake[i];
		// linear color interpolation over the body of the snake between 50 (tail) and 255 (head)
		uint8_t g = 205 * (snake_length - i - 1) / snake_length + 50;

		led_matrix.set_led(s.x, s.y, 0, g, 0);
	}
}

void draw_goal() {
	led_matrix.set_led(apple.x, apple.y, 255, 0, 0);
}

void draw() {
	led_matrix.draw_background();

	draw_snake();
	draw_goal();
	led_matrix.flip();
}

void setup() {
	// set up the LCD's number of columns and rows:
	lcd.begin(16, 2);

	Serial.begin(115200);

	// create new led_matrix object and sets background to true
	// the port is defined in the led_matrix library
	led_matrix = LEDMatrix(COLUMNS, ROWS, true);
	// creates logarithmic interpolation as background image
	led_matrix.log_background(1, 10);
	// init game
	reset();

	draw_score();
}

void loop() {
	if (!paused) {

		// move the snake
		position curr_pos = snake[0];

		position new_pos;
		new_pos.x = curr_pos.x;
		new_pos.y = curr_pos.y;

		// the actual movement into the direction of dir
		switch (dir) {
		case up:
			new_pos.y -= 1;
			break;
		case down:
			new_pos.y += 1;
			break;
		case right:
			new_pos.x += 1;
			break;
		case left:
			new_pos.x -= 1;
			break;
		}

		// ate the apple
		if (new_pos.x == apple.x and new_pos.y == apple.y) {
			// elongate snake
			snake_length += 1;
			for (int i = snake_length - 1; i >= 0; i--) {
				snake[i].x = snake[i - 1].x;
				snake[i].y = snake[i - 1].y;
			}
			new_apple();

			// displays score on lcd;
			draw_score();
		} else {
			// move snake body except head back in array
			// copy from back to front so the new one is not overwritten to soon
			for (int i = snake_length - 1; i > 0; i--) {
				snake[i].x = snake[i - 1].x;
				snake[i].y = snake[i - 1].y;
			}
		}

		snake[0].x = new_pos.x;
		snake[0].y = new_pos.y;

		// check for self intersection
		bool intersection = false;
		// exclude the head
		for (int i = 1; i < snake_length; i++) {
			if (snake[i].x == new_pos.x && snake[i].y == new_pos.y) {
				intersection = true;
				break;
			}
		}
		// also check out of bounds
		if (intersection
				|| new_pos.x
						< 0|| new_pos.x >= COLUMNS || new_pos.y < 0 || new_pos.y >= ROWS) {
			game_over();
		}

		draw();

	}
	my_delay(delay_ms);
}
