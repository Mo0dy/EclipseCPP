/*
 *  Small.cpp
 *
 *  Copyright (C) 2015  Armin Joachimsmeyer
 *  armin.joachimsmeyer@gmail.com
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/gpl.html>.
 *
 */

#include <Arduino.h>

#include <stdlib.h> // for dtostrf


// Pin 13 has an LED connected on most Arduino boards.
const int LED_PIN = 13;

void setup() {
	// initialize the digital pin as an output.
    pinMode(LED_PIN, OUTPUT);

}

void loop() {

}
