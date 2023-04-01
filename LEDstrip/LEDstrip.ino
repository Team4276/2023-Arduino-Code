const int DIO_PIN_0 = 5;
const int DIO_PIN_1 = 4;
const int DIO_PIN_2 = 3;

const int MODE_OFF = 0;
const int MODE_AUTO = 1;
const int MODE_TELEOP_NORMAL = 2;
const int MODE_TELEOP_BALANCING = 3;
const int MODE_TELEOP_HOLD_POSITION = 4;
const int MODE_PURPLE_FOR_CUBE = 5;
const int MODE_YELLOW_FOR_CONE = 6;
const int MODE_UNUSED_7 = 7;

#include <Adafruit_NeoPixel.h>

#define LED_PIN 7
#define LED_COUNT 128

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  pinMode(DIO_PIN_0, INPUT_PULLUP);
  pinMode(DIO_PIN_1, INPUT_PULLUP);
  pinMode(DIO_PIN_2, INPUT_PULLUP);

  strip.begin();
  strip.show();  // Initialize all pixels to off
}
int getMode() {
  int result = 0;
  int value = 0;

  result = digitalRead(DIO_PIN_2);
  value = digitalRead(DIO_PIN_1);
  result *= 2;
  result |= value;
  value = digitalRead(DIO_PIN_0);
  result *= 2;
  result |= value;

  return result;
}

void rainbowSequence(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void yellowblueSequence(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}


void loop() {

  int mode = getMode();
  Serial.print("mode = ");
  Serial.println(mode);

  switch (mode) {
    case MODE_OFF:
      break;

    case MODE_AUTO:
      rainbowSequence(10);
      break;

    case MODE_TELEOP_NORMAL:  //it would just be smarter to have one color actually since the shoulder is broken
      yellowblueSequence(10);
      break;

    case MODE_TELEOP_BALANCING:
      rainbowSequence(10);
      break;

    case MODE_TELEOP_HOLD_POSITION:
      rainbowSequence(10);
      break;

    case MODE_PURPLE_FOR_CUBE:
      // Set all LEDS to purple
      for (int i = 0; i < LED_COUNT; i++) {
        strip.setPixelColor(i, 128, 0, 128);
      }

      strip.show();  // Display the purple color on all LEDs
      delay(500);    // Wait for 500 milliseconds (0.5 seconds)

      // Turn all LEDs off
      for (int i = 0; i < LED_COUNT; i++) {
        strip.setPixelColor(i, 0, 0, 0);
      }
      strip.show();  // Turn off all LEDs
      delay(500);    // Wait for 500 milliseconds (0.5 seconds)
      break;

    case MODE_YELLOW_FOR_CONE:
      // Set all LEDS to yellow
      for (int i = 0; i < LED_COUNT; i++) {
        strip.setPixelColor(i, 255, 255, 0);
      }

      strip.show();  // Display the purple color on all LEDs
      delay(500);    // Wait for 500 milliseconds (0.5 seconds)

      // Turn all LEDs off
      for (int i = 0; i < LED_COUNT; i++) {
        strip.setPixelColor(i, 0, 0, 0);
      }

      strip.show();  // Turn off all LEDs
      delay(500);    // Wait for 500 milliseconds (0.5 seconds)
      break;

    case MODE_UNUSED_7:
    default:
      break;
  }
}
