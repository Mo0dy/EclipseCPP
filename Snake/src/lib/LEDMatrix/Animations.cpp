#include "Animations.h"

// flashes the screen between two colors
void blink_anim(LEDMatrix &matrix, int delay_ms, int count, uint8_t r1, uint8_t g1,
		uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2) {
	for (int i = 0; i < count; i++) {
		matrix.set_all(r1, g1, b1);
		matrix.flip();
		delay(delay_ms);
		matrix.set_all(r2, g2, b2);
		matrix.flip();
		delay(delay_ms);
	}
}


