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
#define LED_PIN7 37
#define LED_PIN8 38
#define LED_PIN9 39
#define LED_PIN10 40
#define LED_PIN11 41
#define LED_PIN12 42

const byte interruptPinPhase1 = 18; // white
const byte interruptPinPhase2 = 19; // grey
const byte interruptPinPhase3 = 20; // black
const byte interruptPinPhase4 = 21; // green

#define COLOR_ORDER BRG
#define LED_TYPE WS2811  
#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120

CRGB pin1leds[NUM_LEDS];
CRGB pin2leds[NUM_LEDS];
CRGB pin3leds[NUM_LEDS];
CRGB pin4leds[NUM_LEDS];
CRGB pin5leds[NUM_LEDS];
CRGB pin6leds[NUM_LEDS];
CRGB pin7leds[NUM_LEDS];
CRGB pin8leds[NUM_LEDS];
CRGB pin9leds[NUM_LEDS];
CRGB pin10leds[NUM_LEDS];
CRGB pin11leds[NUM_LEDS];
CRGB pin12leds[NUM_LEDS];

// reset all to false
// then set the correct phase based on the input interrupt pin to the correct phase
bool phase0 = true; // idle animation sequence
bool phase1 = false;
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

void strand1();
void strand2();
void strand3();
void strand4();
void strand5();
void strand6();
void strand7();
void strand8();
void strand9();
void strand10();
void strand11();
void strand12();

// these are functions!
typedef void (*SimpleStrandList[])();
SimpleStrandList strands = { strand1, strand2, strand3, strand4, strand5, strand6, strand7, strand8, strand9, strand10, strand11, strand12 };
uint8_t currentStrand = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
unsigned long previousMillis = 0;  // will store last time LED was updated
int ledstrips [12] = { pin1leds, pin2leds, pin3leds, pin4leds, pin5leds, pin6leds, pin7leds, pin8leds, pin9leds, pin10leds, pin11leds, pin12leds};
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gCurrentStrandNumber = 0; // Index number of which light strand is the current

void nextPattern();
void rainbowWithGlitter();
void bpm();
void rainbow();
void confetti();
void sinelon();
void juggle();

// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm };


void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void rainbow()
{
  // FastLED's built-in rainbow generator
  //fill_rainbow( leds, NUM_LEDS, gHue, 7);
  fill_rainbow(pin1leds, NUM_LEDS, gHue, 7); // not plugged in
  fill_rainbow(pin2leds, NUM_LEDS, gHue, 7); // not plugged in
  fill_rainbow(pin3leds, NUM_LEDS, gHue, 7);
  fill_rainbow(pin4leds, NUM_LEDS, gHue, 7);
  fill_rainbow(pin5leds, NUM_LEDS, gHue, 7);
  fill_rainbow(pin6leds, NUM_LEDS, gHue, 7);
  fill_rainbow(pin7leds, NUM_LEDS, gHue, 7);
  fill_rainbow(pin8leds, NUM_LEDS, gHue, 7);
  fill_rainbow(pin9leds, NUM_LEDS, gHue, 7);
  fill_rainbow(pin10leds, NUM_LEDS, gHue, 7);
  fill_rainbow(pin11leds, NUM_LEDS, gHue, 7);
  fill_rainbow(pin12leds, NUM_LEDS, gHue, 7);
}


void addGlitter( fract8 chanceOfGlitter)
{
  if( random8() < chanceOfGlitter) {
    //leds[ random16(NUM_LEDS) ] += CRGB::White;
    pin1leds[random16(NUM_LEDS) ] += CRGB::White;
    pin2leds[random16(NUM_LEDS) ] += CRGB::White;
    pin3leds[random16(NUM_LEDS) ] += CRGB::White;
    pin4leds[random16(NUM_LEDS) ] += CRGB::White;
    pin5leds[random16(NUM_LEDS) ] += CRGB::White;
    pin6leds[random16(NUM_LEDS) ] += CRGB::White;
    pin7leds[random16(NUM_LEDS) ] += CRGB::White;
    pin8leds[random16(NUM_LEDS) ] += CRGB::White;
    pin9leds[random16(NUM_LEDS) ] += CRGB::White;
    pin10leds[random16(NUM_LEDS) ] += CRGB::White;
    pin11leds[random16(NUM_LEDS) ] += CRGB::White;
    pin12leds[random16(NUM_LEDS) ] += CRGB::White;
  }
}

void confetti()
{
  // random colored speckles that blink in and fade smoothly
  //fadeToBlackBy( leds, NUM_LEDS, 10);
  fadeToBlackBy( pin1leds, NUM_LEDS, 10);
  fadeToBlackBy( pin2leds, NUM_LEDS, 10);
  fadeToBlackBy( pin3leds, NUM_LEDS, 10);
  fadeToBlackBy( pin4leds, NUM_LEDS, 10);
  fadeToBlackBy( pin5leds, NUM_LEDS, 10);
  fadeToBlackBy( pin6leds, NUM_LEDS, 10);
  fadeToBlackBy( pin7leds, NUM_LEDS, 10);
  fadeToBlackBy( pin8leds, NUM_LEDS, 10);
  fadeToBlackBy( pin9leds, NUM_LEDS, 10);
  fadeToBlackBy( pin10leds, NUM_LEDS, 10);
  fadeToBlackBy( pin11leds, NUM_LEDS, 10);
  fadeToBlackBy( pin12leds, NUM_LEDS, 10);
  
  pin1leds[random16(NUM_LEDS)] += CHSV( gHue + random8(64), 200, 255);
  pin2leds[random16(NUM_LEDS)] += CHSV( gHue + random8(64), 200, 255);
  pin3leds[random16(NUM_LEDS)] += CHSV( gHue + random8(64), 200, 255);
  pin4leds[random16(NUM_LEDS)] += CHSV( gHue + random8(64), 200, 255);
  pin5leds[random16(NUM_LEDS)] += CHSV( gHue + random8(64), 200, 255);
  pin6leds[random16(NUM_LEDS)] += CHSV( gHue + random8(64), 200, 255);
  pin7leds[random16(NUM_LEDS)] += CHSV( gHue + random8(64), 200, 255);
  pin8leds[random16(NUM_LEDS)] += CHSV( gHue + random8(64), 200, 255);
  pin9leds[random16(NUM_LEDS)] += CHSV( gHue + random8(64), 200, 255);
  pin10leds[random16(NUM_LEDS)] += CHSV( gHue + random8(64), 200, 255);
  pin11leds[random16(NUM_LEDS)] += CHSV( gHue + random8(64), 200, 255);
  pin12leds[random16(NUM_LEDS)] += CHSV( gHue + random8(64), 200, 255);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( pin1leds, NUM_LEDS, 20);
  fadeToBlackBy( pin2leds, NUM_LEDS, 20);
  fadeToBlackBy( pin3leds, NUM_LEDS, 20);
  fadeToBlackBy( pin4leds, NUM_LEDS, 20);
  fadeToBlackBy( pin5leds, NUM_LEDS, 20);
  fadeToBlackBy( pin6leds, NUM_LEDS, 20);
  fadeToBlackBy( pin7leds, NUM_LEDS, 20);
  fadeToBlackBy( pin8leds, NUM_LEDS, 20);
  fadeToBlackBy( pin9leds, NUM_LEDS, 20);
  fadeToBlackBy( pin10leds, NUM_LEDS, 20);
  fadeToBlackBy( pin11leds, NUM_LEDS, 20);
  fadeToBlackBy( pin12leds, NUM_LEDS, 20);

  pin1leds[beatsin16( 13, 0, NUM_LEDS-1 )] += CHSV( gHue, 255, 192);
  pin2leds[beatsin16( 13, 0, NUM_LEDS-1 )] += CHSV( gHue, 255, 192);
  pin3leds[beatsin16( 13, 0, NUM_LEDS-1 )] += CHSV( gHue, 255, 192);
  pin4leds[beatsin16( 13, 0, NUM_LEDS-1 )] += CHSV( gHue, 255, 192);
  pin5leds[beatsin16( 13, 0, NUM_LEDS-1 )] += CHSV( gHue, 255, 192);
  pin6leds[beatsin16( 13, 0, NUM_LEDS-1 )] += CHSV( gHue, 255, 192);
  pin7leds[beatsin16( 13, 0, NUM_LEDS-1 )] += CHSV( gHue, 255, 192);
  pin8leds[beatsin16( 13, 0, NUM_LEDS-1 )] += CHSV( gHue, 255, 192);
  pin9leds[beatsin16( 13, 0, NUM_LEDS-1 )] += CHSV( gHue, 255, 192);
  pin10leds[beatsin16( 13, 0, NUM_LEDS-1 )] += CHSV( gHue, 255, 192);
  pin11leds[beatsin16( 13, 0, NUM_LEDS-1 )] += CHSV( gHue, 255, 192);
  pin12leds[beatsin16( 13, 0, NUM_LEDS-1 )] += CHSV( gHue, 255, 192);
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    pin1leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
    pin2leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
    pin3leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
    pin4leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
    pin5leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
    pin6leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
    pin7leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
    pin8leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
    pin9leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
    pin10leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
    pin11leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
    pin12leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( pin1leds, NUM_LEDS, 20);
  fadeToBlackBy( pin2leds, NUM_LEDS, 20);
  fadeToBlackBy( pin3leds, NUM_LEDS, 20);
  fadeToBlackBy( pin4leds, NUM_LEDS, 20);
  fadeToBlackBy( pin5leds, NUM_LEDS, 20);
  fadeToBlackBy( pin6leds, NUM_LEDS, 20);
  fadeToBlackBy( pin7leds, NUM_LEDS, 20);
  fadeToBlackBy( pin8leds, NUM_LEDS, 20);
  fadeToBlackBy( pin9leds, NUM_LEDS, 20);
  fadeToBlackBy( pin10leds, NUM_LEDS, 20);
  fadeToBlackBy( pin11leds, NUM_LEDS, 20);
  fadeToBlackBy( pin12leds, NUM_LEDS, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    pin1leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    pin2leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    pin3leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    pin4leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    pin5leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    pin6leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    pin7leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    pin8leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    pin9leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    pin10leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    pin11leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    pin12leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}

void rainbowWithGlitter()
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void setup() {

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
  
  pinMode(interruptPinPhase1, INPUT_PULLUP);
  pinMode(interruptPinPhase2, INPUT_PULLUP);
  pinMode(interruptPinPhase3, INPUT_PULLUP);
  pinMode(interruptPinPhase4, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPinPhase1), doPhase1, RISING);  
  attachInterrupt(digitalPinToInterrupt(interruptPinPhase2), doPhase2, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptPinPhase3), doPhase3, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptPinPhase4), doPhase4, RISING);
  // TODO phase 5, launch the sparkle ponies
  // attachInterrupt(digitalPinToInterrupt(interruptPinPhase5), doPhase5, CHANGE);
  
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear(); // clears all LEDs to reset the stage
  FastLED.show();

  doPhase0();
}

void doPhase0 () {
  phase0 = true;
  phase1 = false;
  phase2 = false;
  phase3 = false;
  phase4 = false;
  phase5 = false;
  interval = 1000; // these won't matter
  multiplier = 1;  // these won't matter  
}

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
 
   // any button is pushed 
  if (digitalRead(interruptPinPhase1) == LOW || 
      digitalRead(interruptPinPhase2) == LOW ||
      digitalRead(interruptPinPhase3) == LOW ||
      digitalRead(interruptPinPhase4) == LOW) {
      phase0 = false;
  } else {
      phase0 = true;
  }


 // idle sequence
  if (phase0) {
    /* new code */
    // Call the current pattern function once, updating the 'leds' array
    gPatterns[gCurrentPatternNumber]();

    // send the 'leds' array out to the actual LED strip
    FastLED.show();  
    // insert a delay to keep the framerate modest
    FastLED.delay(1000/FRAMES_PER_SECOND); 

    // do some periodic updates
    EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
    EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically
  } else {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;
      nextStrand();
    }
  }

}

void nextStrand() {
  currentStrand = (currentStrand + 1) % ARRAY_SIZE( strands);
  strands[currentStrand]();  
}

void fillStrand(int strand, int value) {
  fill_solid(ledstrips[strand-1],NUM_LEDS, CHSV(0, 255, value)); 
  FastLED.show(); 
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