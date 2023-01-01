
#define FASTLED_INTERNAL
#include <FastLED.h>

FASTLED_USING_NAMESPACE

#define NUM_LEDS 50 // 53

#define LED_PIN1 2
#define LED_PIN2 3
#define LED_PIN3 4
#define LED_PIN4 5
#define LED_PIN5 6
#define LED_PIN6 7
#define LED_PIN7 8
#define LED_PIN8 9
#define LED_PIN9 10
#define LED_PIN10 11
#define LED_PIN11 12
#define LED_PIN12 13

#define STRAND_COUNT 12

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

// interrupt pins
const byte interruptPinA1 = 15; // A1
const byte interruptPinA2 = 16; // A2
const byte interruptPinA3 = 17; // A3
const byte interruptPinA4 = 18; // A4

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
  
  // Setup interrupt pins
  pinMode(interruptPinA1, INPUT_PULLUP);
  pinMode(interruptPinA2, INPUT_PULLUP);
  pinMode(interruptPinA3, INPUT_PULLUP);
  pinMode(interruptPinA4, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(interruptPinA1), doPhase1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPinA2), doPhase2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPinA3), doPhase3, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPinA4), doPhase4, CHANGE);
  // TODO phase 5, launch the sparkle ponies
  // attachInterrupt(digitalPinToInterrupt(interruptPin19), doPhase5, CHANGE);

  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear(); // clears all LEDs to reset the stage
  FastLED.show();
}

typedef void (*SimpleStrandList[])();
// these are functions!
//SimpleStrandList strands = { strand1, strand2, strand3, strand4, strand5, strand6, strand7, strand8, strand9, strand10, strand11, strand12 };

uint8_t currentStrand = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
unsigned long previousMillis = 0;  // will store last time LED was updated
int ledstrips [STRAND_COUNT] = { pin1leds, pin2leds, pin3leds, pin4leds, pin5leds, pin6leds, pin7leds, pin8leds, pin9leds, pin10leds, pin11leds, pin12leds};

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
  currentStrand = (currentStrand + 1) % STRAND_COUNT;
  //strands[currentStrand](); 
  allStrands(currentStrand); 
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

// returns the requested strand less the subtractor
int getStrand(int strand, int subtract) {
  int newStrand = strand - subtract;
  if (newStrand < 0) {
    newStrand += STRAND_COUNT;
  } 
  return newStrand;
}

void allStrands(int strand) {
  // what is this strand and the two before it
  int currentStrandM0 = getStrand(strand,0); //   pin1
  int currentStrandM1 = getStrand(strand,1); //   pin2
  int currentStrandM2 = getStrand(strand,2); //   pin3
  int currentStrandM3 = getStrand(strand,3); //   pin4
  int currentStrandM4 = getStrand(strand,4); //   pin5
  int currentStrandM5 = getStrand(strand,5); //   pin6
  int currentStrandM6 = getStrand(strand,6); //   pin7
  int currentStrandM7 = getStrand(strand,7); //   pin8
  int currentStrandM8 = getStrand(strand,8); //   pin9
  int currentStrandM9 = getStrand(strand,9); //   pin10
  int currentStrandM10 = getStrand(strand,10); // pin11
  int currentStrandM11 = getStrand(strand,11); // pin12

  fill_solid(ledstrips[currentStrandM0],NUM_LEDS, CHSV(0, 255, full)); 
  fill_solid(ledstrips[currentStrandM11],NUM_LEDS, CHSV(0, 255, first)); 
  fill_solid(ledstrips[currentStrandM10],NUM_LEDS, CHSV(0, 255, second)); 
  if (phase2 == true || phase3 == true || phase4 == true) {
    fill_solid(ledstrips[currentStrandM6],NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(ledstrips[currentStrandM5],NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(ledstrips[currentStrandM4],NUM_LEDS, CHSV(0, 255, second)); 
  }
  if (phase3 == true) {
    fill_solid(ledstrips[currentStrandM3],NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(ledstrips[currentStrandM2],NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(ledstrips[currentStrandM1],NUM_LEDS, CHSV(0, 255, second)); 

    fill_solid(ledstrips[currentStrandM9],NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(ledstrips[currentStrandM8],NUM_LEDS, CHSV(0, 255, first)); 
    fill_solid(ledstrips[currentStrandM7],NUM_LEDS, CHSV(0, 255, second));
  }
  if (phase4 == true) {
    fill_solid(ledstrips[currentStrandM2],NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(ledstrips[currentStrandM1],NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(ledstrips[currentStrandM4],NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(ledstrips[currentStrandM3],NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(ledstrips[currentStrandM8],NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(ledstrips[currentStrandM7],NUM_LEDS, CHSV(0, 255, first)); 

    fill_solid(ledstrips[currentStrandM10],NUM_LEDS, CHSV(0, 255, full)); 
    fill_solid(ledstrips[currentStrandM9],NUM_LEDS, CHSV(0, 255, first)); 
  }
  FastLED.show(); 
  for (int value = 0; value < spread; value+=multiplier) {
    fill_solid(ledstrips[currentStrandM0],NUM_LEDS, CHSV(0, 255, full-value)); 
    fill_solid(ledstrips[currentStrandM11],NUM_LEDS, CHSV(0, 255, first-value)); 
    fill_solid(ledstrips[currentStrandM10],NUM_LEDS, CHSV(0, 255, second-value)); 
    if (phase2 == true || phase3 == true || phase4 == true) {
      fill_solid(ledstrips[currentStrandM6],NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(ledstrips[currentStrandM5],NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(ledstrips[currentStrandM4],NUM_LEDS, CHSV(0, 255, second-value)); 
    }
    if (phase3 == true) {
      fill_solid(ledstrips[currentStrandM3],NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(ledstrips[currentStrandM2],NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(ledstrips[currentStrandM1],NUM_LEDS, CHSV(0, 255, second-value)); 

      fill_solid(ledstrips[currentStrandM9],NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(ledstrips[currentStrandM8],NUM_LEDS, CHSV(0, 255, first-value)); 
      fill_solid(ledstrips[currentStrandM7],NUM_LEDS, CHSV(0, 255, second-value));
    }
    if (phase4 == true) {
      fill_solid(ledstrips[currentStrandM2],NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(ledstrips[currentStrandM1],NUM_LEDS, CHSV(0, 255, first-value)); 

      fill_solid(ledstrips[currentStrandM4],NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(ledstrips[currentStrandM3],NUM_LEDS, CHSV(0, 255, first-value)); 

      fill_solid(ledstrips[currentStrandM8],NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(ledstrips[currentStrandM7],NUM_LEDS, CHSV(0, 255, first-value)); 

      fill_solid(ledstrips[currentStrandM10],NUM_LEDS, CHSV(0, 255, full-value)); 
      fill_solid(ledstrips[currentStrandM9],NUM_LEDS, CHSV(0, 255, first-value)); 
    }
    FastLED.show();
  }
}