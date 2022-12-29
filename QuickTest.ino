
#define FASTLED_INTERNAL
#include <FastLED.h>

FASTLED_USING_NAMESPACE

#define NUM_LEDS 50 // 53

#define LED_PIN1 31
#define LED_PIN2 32
#define LED_PIN3 33
#define LED_PIN4 34
#define LED_PIN5 35
#define LED_PIN6 36
#define LED_PIN7 43
#define LED_PIN8 38
#define LED_PIN9 39
#define LED_PIN10 40
#define LED_PIN11 41
#define LED_PIN12 42

#define COLOR_ORDER BRG
#define LED_TYPE WS2811
#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120

CRGBArray<NUM_LEDS> pin1leds;
CRGBArray<NUM_LEDS> pin2leds;
CRGBArray<NUM_LEDS> pin3leds;
CRGBArray<NUM_LEDS> pin4leds;
CRGBArray<NUM_LEDS> pin5leds;
CRGBArray<NUM_LEDS> pin6leds;
CRGBArray<NUM_LEDS> pin7leds;
CRGBArray<NUM_LEDS> pin8leds;
CRGBArray<NUM_LEDS> pin9leds;
CRGBArray<NUM_LEDS> pin10leds;
CRGBArray<NUM_LEDS> pin11leds;
CRGBArray<NUM_LEDS> pin12leds;

// interupt pins 2, 3, 18, 19, 20, 21
const byte interruptPin2 = 2;
const byte interruptPin3 = 3;
const byte interruptPin18 = 18;
const byte interruptPin19 = 19;
const byte interruptPin20 = 20;
const byte interruptPin21 = 21;

volatile byte statelow = LOW; // trigger the interrupt whenever the pin is low
volatile byte statechange = CHANGE; // trigger the interrupt whenever the pin changes value
volatile byte staterising = RISING; // trigger when the pin goes from low to high
volatile byte statefalling = FALLING; // trigger when the pin goes from high to low

// these will change when the state changes voltage
// reset all to false
// then set the correct phase based on the input interrupt pin to the correct phase
bool phase0 = false; // idle animation sequence
bool phase1 = true;
bool phase2 = false;
bool phase3 = false;
bool phase4 = false;
bool phase5 = false;

// constants won't change:
const int full = 255;
const int first = 153;
const int second = 76;

// thereexist a marriage between these values to make it go faster
long interval = 1000;  // interval at which to blink (milliseconds)
int spread = 76;
int multiplier = 1;

void setup() {
  fill_solid(pin1leds,NUM_LEDS, CRGB::Black);
  fill_solid(pin2leds,NUM_LEDS, CRGB::Black);
  fill_solid(pin3leds,NUM_LEDS, CRGB::Black);
  fill_solid(pin4leds,NUM_LEDS, CRGB::Black);
  fill_solid(pin5leds,NUM_LEDS, CRGB::Black);
  fill_solid(pin6leds,NUM_LEDS, CRGB::Black);
  FastLED.show();

  delay(1); // 2 second delay for recovery

  // put your setup code here, to run once:
  FastLED.addLeds<LED_TYPE, LED_PIN1, COLOR_ORDER>(pin1leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, LED_PIN2, COLOR_ORDER>(pin2leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, LED_PIN3, COLOR_ORDER>(pin3leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, LED_PIN4, COLOR_ORDER>(pin4leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, LED_PIN5, COLOR_ORDER>(pin5leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, LED_PIN6, COLOR_ORDER>(pin6leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, LED_PIN7, COLOR_ORDER>(pin7leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, LED_PIN8, COLOR_ORDER>(pin8leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, LED_PIN9, COLOR_ORDER>(pin9leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, LED_PIN10, COLOR_ORDER>(pin10leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, LED_PIN11, COLOR_ORDER>(pin11leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, LED_PIN12, COLOR_ORDER>(pin12leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  
  // experimental for now
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  pinMode(LED_PIN3, OUTPUT);
  pinMode(LED_PIN4, OUTPUT);
  pinMode(LED_PIN5, OUTPUT);
  pinMode(LED_PIN6, OUTPUT);
  pinMode(LED_PIN7, OUTPUT);
  pinMode(LED_PIN8, OUTPUT);
  pinMode(LED_PIN9, OUTPUT);
  pinMode(LED_PIN10, OUTPUT);
  pinMode(LED_PIN11, OUTPUT);
  pinMode(LED_PIN12, OUTPUT);
  
  // interupt pins 2, 3, 18, 19, 20, 21
  pinMode(interruptPin2, INPUT_PULLUP);
  pinMode(interruptPin3, INPUT_PULLUP);
  pinMode(interruptPin18, INPUT_PULLUP);
  pinMode(interruptPin19, INPUT_PULLUP);
  pinMode(interruptPin20, INPUT_PULLUP);
  pinMode(interruptPin21, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(interruptPin2), doPhase1, CHANGE);  // pin 2 to phase 1  
  attachInterrupt(digitalPinToInterrupt(interruptPin3), doPhase2, CHANGE);  // pin 2 to phase 1
  attachInterrupt(digitalPinToInterrupt(interruptPin18), doPhase3, CHANGE);  // pin 2 to phase 1
  attachInterrupt(digitalPinToInterrupt(interruptPin19), doPhase4, CHANGE);  // pin 2 to phase 1
  // TODO phase 5, launch the sparkle ponies
  // attachInterrupt(digitalPinToInterrupt(interruptPin19), doPhase5, CHANGE);  // pin 2 to phase 1


  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear(); // clears all LEDs to reset the stage
  FastLED.show();
}

typedef void (*SimpleStrandList[])();
// these are functions!
SimpleStrandList strands = { strand1, strand2, strand3, strand4, strand5, strand6, strand7, strand8, strand9, strand10, strand11, strand12 };

uint8_t currentStrand = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
unsigned long previousMillis = 0;  // will store last time LED was updated
int ledstrips [12] = { pin1leds, pin2leds, pin3leds, pin4leds, pin5leds, pin6leds, pin7leds, pin8leds, pin9leds, pin10leds, pin11leds, pin12leds};

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void doPhase1 () {
  phase0 = false;
  phase1 = true;
  phase2 = false;
  phase3 = false;
  phase4 = false;
  phase5 = false;
  interval = 1000;
  multiplier = 1;  
}

void doPhase2 () {
  phase0 = false;
  phase1 = false;
  phase2 = true;
  phase3 = false;
  phase4 = false;
  phase5 = false;
  interval = 600;
  multiplier = 3;
}

void doPhase3 () {
  phase0 = false;
  phase1 = false;
  phase2 = false;
  phase3 = true;
  phase4 = false;
  phase5 = false;
  interval = 300;
  multiplier = 7;
}

void doPhase4 () {
  phase0 = false;
  phase1 = false;
  phase2 = false;
  phase3 = false;
  phase4 = true;
  phase5 = false;
  interval = 100;
  multiplier = 10;
}

// sparkle pony shit
void doPhase5 () {}

void loop() {
 
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    nextStrand();
  }
  // fill_solid(pin1leds,NUM_LEDS, CRGB::Red);
  // fill_solid(pin2leds,NUM_LEDS, CRGB::Orange);
  // fill_solid(pin3leds,NUM_LEDS, CRGB::Yellow);
  // fill_solid(pin4leds,NUM_LEDS, CRGB::Green);
  // fill_solid(pin5leds,NUM_LEDS, CRGB::Blue);
  // fill_solid(pin6leds,NUM_LEDS, CRGB::Brown);
  // fill_solid(pin7leds,NUM_LEDS, CRGB::Red);
  // fill_solid(pin8leds,NUM_LEDS, CRGB::Orange);
  // fill_solid(pin9leds,NUM_LEDS, CRGB::Yellow);
  // fill_solid(pin10leds,NUM_LEDS, CRGB::Green);
  // fill_solid(pin11leds,NUM_LEDS, CRGB::Blue);
  // fill_solid(pin12leds,NUM_LEDS, CRGB::Brown);
  // FastLED.show();
}


void nextStrand() {
  currentStrand = (currentStrand + 1) % ARRAY_SIZE( strands);
  strands[currentStrand]();  
}

void fillStrand(int strand, int value) {
  fill_solid(ledstrips[strand-1],NUM_LEDS, CHSV(0, 255, value)); 
  FastLED.show(); 
}

// prototype
void strand(int strand) {
  fill_solid(ledstrips[strand-1],NUM_LEDS, CHSV(0, 255, full)); 
  fill_solid(ledstrips[strand-2],NUM_LEDS, CHSV(0, 255, first)); 
  fill_solid(ledstrips[strand-3],NUM_LEDS, CHSV(0, 255, second)); 
  FastLED.show(); 
  for (int value = 0; value < spread; value+=multiplier) {
    fill_solid(ledstrips[strand-1],NUM_LEDS, CHSV(0, 255, full-value)); 
    fill_solid(ledstrips[strand-2],NUM_LEDS, CHSV(0, 255, first-value)); 
    fill_solid(ledstrips[strand-3],NUM_LEDS, CHSV(0, 255, second-value)); 
    FastLED.show();
  }
}

void strand1() {
  fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, full)); 
  fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, first)); 
  fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, second)); 
  if (phase2 == true || phase3 == true || phase4 == true) {
    fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, second)); 
  }
  if (phase3 == true) {
    fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, second)); 

    fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, second));
  }
  if (phase4 == true) {
    fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, first)); 
  }
  FastLED.show(); 
  for (int value = 0; value < spread; value+=multiplier) {
    fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, full-value)); 
    fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, first-value)); 
    fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, second-value)); 
    if (phase2 == true || phase3 == true || phase4 == true) {
      fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, second-value)); 
    }
    if (phase3 == true) {
      fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, second-value)); 

      fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, second-value));
    }
    if (phase4 == true) {
      fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, first-value)); 

      fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, first-value)); 

      fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, first-value)); 

      fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, first-value)); 
    }
    FastLED.show();
  }
}

void strand2() {
  fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, full)); 
  fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, first)); 
  fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, second)); 
  if (phase2 == true || phase3 == true || phase4 == true) {
    fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, second)); 
  }
  if (phase3 == true) {
    fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, second)); 

    fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, second));
  }
  if (phase4 == true) {
    fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, first)); 
  }
  FastLED.show(); 
  for (int value = 0; value < spread; value+=multiplier) {
    fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, full-value)); 
    fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, first-value)); 
    fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, second-value)); 
    if (phase2 == true || phase3 == true || phase4 == true) {
      fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, second-value)); 
    }
    if (phase3 == true) {
      fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, full-value));  
      fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, first-value));
      fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, second-value)); 

      fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, full-value));  
      fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, first-value));
      fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, second-value)); 
    }
    if (phase4 == true) {
      fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, full-value));  
      fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, first-value));

      fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, first-value));

      fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, first-value));

      fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, first-value));
    }
    FastLED.show();
  }
}

void strand3() {
  fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, full)); 
  fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, first)); 
  fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, second)); 
  if (phase2 == true || phase3 == true || phase4 == true) {
    fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, second)); 
  }
  if (phase3 == true) {
    fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, second)); 

    fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, second));
  }
  if (phase4 == true) {
    fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, first)); 
  }
  FastLED.show(); 
  for (int value = 0; value < spread; value+=multiplier) {
    fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, full-value)); 
    fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, first-value)); 
    fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, second-value)); 
    if (phase2 == true || phase3 == true || phase4 == true) {
      fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, second-value)); 
    }
    if (phase3 == true) {
      fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, second-value)); 

      fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, second-value));
    }
    if (phase4 == true) {
      fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, first-value)); 

      fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, first-value)); 

      fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, first-value)); 

      fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, first-value)); 
    }
    FastLED.show();
  }

}

void strand4() {
  fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, full)); 
  fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, first)); 
  fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, second)); 
  if (phase2 == true || phase3 == true || phase4 == true) {
    fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, second)); 
  }
  if (phase3 == true) {
    fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, second)); 

    fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, second));
  }
  if (phase4 == true) {
    fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, first)); 
  }
  FastLED.show(); 
  for (int value = 0; value < spread; value+=multiplier) {
    fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, full-value)); 
    fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, first-value)); 
    fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, second-value)); 
    if (phase2 == true || phase3 == true || phase4 == true) {
      fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, second-value)); 
    }
    if (phase3 == true) {
      fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, second-value)); 

      fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, second-value));
    }
    if (phase4 == true) {
      fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, first-value)); 

      fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, first-value)); 

      fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, first-value)); 

      fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, first-value)); 
    }
    FastLED.show();
  }
}

void strand5() {
  fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, full)); 
  fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, first)); 
  fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, second)); 
  if (phase2 == true || phase3 == true || phase4 == true) {
    fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, second)); 
  }
  if (phase3 == true) {
    fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, second)); 

    fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, second));
  }
  if (phase4 == true) {
    fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, first)); 
  }
  FastLED.show(); 
  for (int value = 0; value < spread; value+=multiplier) {
    fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, full-value)); 
    fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, first-value)); 
    fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, second-value)); 
    if (phase2 == true || phase3 == true || phase4 == true) {
      fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, second-value)); 
    }
    if (phase3 == true) {
      fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, second-value)); 

      fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, second-value));
    }
    if (phase4 == true) {
      fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, first-value)); 

      fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, first-value)); 

      fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, first-value)); 

      fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, first-value)); 
    }
    FastLED.show();
  }
}


void strand6() {
  fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, full)); 
  fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, first)); 
  fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, second)); 
  if (phase2 == true || phase3 == true || phase4 == true) {
    fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, second)); 
  }
  if (phase3 == true) {
    fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, second)); 

    fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, second));
  }
  if (phase4 == true) {
    fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, first)); 
  }
  FastLED.show(); 
  for (int value = 0; value < spread; value+=multiplier) {
    fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, full-value)); 
    fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, first-value)); 
    fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, second-value)); 
    if (phase2 == true || phase3 == true || phase4 == true) {
      fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, second-value)); 
    }
    if (phase3 == true) {
      fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, second-value)); 

      fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, second-value));
    }
    if (phase4 == true) {
      fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, first-value)); 

      fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, first-value)); 

      fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, first-value)); 

      fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, first-value)); 
    }
    FastLED.show();
  }
}
void strand7() {
  fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, full)); 
  fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, first)); 
  fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, second)); 
  if (phase2 == true || phase3 == true || phase4 == true) {
    fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, second)); 
  }
  if (phase3 == true) {
    fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, second)); 

    fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, second));
  }
  if (phase4 == true) {
    fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, first)); 
  }
  FastLED.show(); 
  for (int value = 0; value < spread; value+=multiplier) {
    fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, full-value)); 
    fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, first-value)); 
    fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, second-value));
    if (phase2 == true || phase3 == true || phase4 == true) {
      fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, second-value)); 
    }
    if (phase3 == true) {
      fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, second-value)); 

      fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, second-value));
    }
    if (phase4 == true) {
      fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, first-value)); 

      fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, first-value)); 

      fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, first-value)); 

      fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, full)); 
      fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, full)); 
    }
    FastLED.show();
  }
}
void strand8() {
  fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, full)); 
  fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, first)); 
  fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, second)); 
  if (phase2 == true || phase3 == true || phase4 == true) {
    fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, second)); 
  }
  if (phase3 == true) {
    fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, second)); 

    fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, second));
  }
  if (phase4 == true) {
    fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, first)); 
  }
  FastLED.show(); 
  for (int value = 0; value < spread; value+=multiplier) {
    fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, full-value)); 
    fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, first-value)); 
    fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, second-value)); 
    if (phase2 == true || phase3 == true || phase4 == true) {
      fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, second-value)); 
    }
    if (phase3 == true) {
      fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, second-value)); 

      fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, second-value));
    }
    if (phase4 == true) {
      fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, first-value)); 

      fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, first-value)); 

      fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, first-value)); 

      fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, first-value)); 
    }
    FastLED.show();
  }
}
void strand9() {
  fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, full)); 
  fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, first)); 
  fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, second)); 
  if (phase2 == true || phase3 == true || phase4 == true) {
    fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, second)); 
  }
  if (phase3 == true) {
    fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, second)); 

    fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, second));
  }
  if (phase4 == true) {
    fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, first)); 
  }
  FastLED.show(); 
  for (int value = 0; value < spread; value+=multiplier) {
    fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, full-value)); 
    fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, first-value)); 
    fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, second-value)); 
    if (phase2 == true || phase3 == true || phase4 == true) {
      fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, second-value)); 
    }
    if (phase3 == true) {
      fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, second-value)); 

      fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, second-value));
    }
    if (phase4 == true) {
      fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, first-value)); 

      fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, first-value)); 

      fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, first-value)); 

      fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, first-value)); 
    }
    FastLED.show();
  }

}
void strand10() {
  fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, full)); 
  fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, first)); 
  fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, second)); 
  if (phase2 == true || phase3 == true || phase4 == true) {
    fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, second)); 
  }
  if (phase3 == true) {
    fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, second)); 

    fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, second));
  }
  if (phase4 == true) {
    fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, first)); 
  }
  FastLED.show(); 
  for (int value = 0; value < spread; value+=multiplier) {
    fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, full-value)); 
    fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, first-value)); 
    fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, second-value)); 
    if (phase2 == true || phase3 == true || phase4 == true) {
      fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, second-value)); 
    }
    if (phase3 == true) {
      fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, second-value)); 

      fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, second-value));
    }
    if (phase4 == true) {
      fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, first-value)); 

      fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, first-value)); 

      fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, first-value)); 

      fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, first-value)); 
    }
    FastLED.show();
  }
}
void strand11() {
  fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, full)); 
  fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, first)); 
  fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, second)); 
  if (phase2 == true || phase3 == true || phase4 == true) {
    fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, second)); 
  }
  if (phase3 == true) {
    fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, second)); 

    fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, second));
  }
  if (phase4 == true) {
    fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, first)); 
  }
  FastLED.show(); 
  for (int value = 0; value < spread; value+=multiplier) {
    fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, full-value)); 
    fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, first-value)); 
    fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, second-value)); 
    if (phase2 == true || phase3 == true || phase4 == true) {
      fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, second-value)); 
    }
    if (phase3 == true) {
      fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, second-value)); 

      fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, second-value));
    }
    if (phase4 == true) {
      fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, first-value)); 

      fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, first-value)); 

      fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, first-value)); 

      fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, first-value)); 
    }
    FastLED.show();
  }
}
void strand12() {
  fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, full)); 
  fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, first)); 
  fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, second)); 
  if (phase2 == true || phase3 == true || phase4 == true) {
    fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, second)); 
  }
  if (phase3 == true) {
    fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, second)); 

    fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, second));
  }
  if (phase4 == true) {
    fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, first)); 
  }
  FastLED.show(); 
  for (int value = 0; value < spread; value+=multiplier) {
    fill_solid(pin12leds,NUM_LEDS, CHSV(0, 255, full-value)); 
    fill_solid(pin11leds,NUM_LEDS, CHSV(0, 255, first-value)); 
    fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, second-value)); 
    if (phase2 == true || phase3 == true || phase4 == true) {
      fill_solid(pin6leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin5leds,NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, second-value)); 
    }
    if (phase3 == true) {
      fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, second-value)); 

      fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, second-value));
    }
    if (phase4 == true) {
      fill_solid(pin2leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin1leds,NUM_LEDS, CHSV(0, 255, first-value)); 

      fill_solid(pin4leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin3leds,NUM_LEDS, CHSV(0, 255, first-value)); 

      fill_solid(pin8leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin7leds,NUM_LEDS, CHSV(0, 255, first-value)); 

      fill_solid(pin10leds,NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(pin9leds,NUM_LEDS, CHSV(0, 255, first-value)); 
    }
    FastLED.show();
  }
}
