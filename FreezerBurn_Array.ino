#define FASTLED_INTERNAL
#include <FastLED.h>

#define NUM_LEDS 50

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

#define COLOR_ORDER BRG

#define LED_TYPE WS2811

//const byte ledPin = 13;

/* 2, 3, 18, 19, 20, 21 */
const byte interruptPin1 = 2;
const byte interruptPin2 = 3;
const byte interruptPin3 = 18;
const byte interruptPin4 = 19;
const byte interruptPin5 = 20;
const byte interruptPin6 = 21;
volatile byte state = LOW;

int currentTime = 0;
int lastTime = 0;

// speeds
#define SLOW 1000
#define WALK 600
#define JOG 300
#define RUN 150
#define BALLS 50

#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gCurrentStrandNumber = 0; // Index number of which light strand is the current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

const int brightness = 255;
int phase1Color = CRGB::Red;

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
  fill_rainbow(pin1leds, NUM_LEDS, gHue, 7);// not plugged in
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

// strip 1
void fillStrip_01() {
  CRGB phase1color = CRGB::Blue;
  fill_solid(pin1leds,NUM_LEDS, phase1color);
  FastLED.show();
  fadeToBlackBy( pin1leds, NUM_LEDS, 1);
}

// strip 2
void fillStrip_02() {
  CRGB phase1color = CRGB::Red;
  fill_solid(pin2leds,NUM_LEDS, phase1color);
  FastLED.show();
}

// strip 3
void fillStrip_03() {
  CRGB phase1color = CRGB::Green;
  fill_solid(pin3leds,NUM_LEDS, phase1color);
  FastLED.show();
}

// strip 4
void fillStrip_04() {
  CRGB phase1color = CRGB::Yellow;
  fill_solid(pin4leds,NUM_LEDS, phase1color);
  FastLED.show();
}

// strip 5
void fillStrip_05() {
  CRGB phase1color = CRGB::Orange;
  fill_solid(pin5leds,NUM_LEDS, phase1color);
  FastLED.show();
}

// strip 6
void fillStrip_06() {
  CRGB phase1color = CRGB::Pink;
  fill_solid(pin6leds,NUM_LEDS, phase1color);
  FastLED.show();
}

// strip 7
void fillStrip_07() {
  CRGB phase1color = CRGB::Brown;
  fill_solid(pin7leds,NUM_LEDS, phase1color);
  FastLED.show();
}

// strip 8
void fillStrip_08() {
  CRGB phase1color = CRGB::Purple;
  fill_solid(pin8leds,NUM_LEDS, phase1color);
    FastLED.show();
}

// strip 9
void fillStrip_09() {
  CRGB phase1color = CRGB::RoyalBlue;
  fill_solid(pin9leds,NUM_LEDS, phase1color);
  FastLED.show();
}

// strip 10
void fillStrip_10() {
  CRGB phase1color = CRGB::White;
  fill_solid(pin10leds,NUM_LEDS, phase1color);
  FastLED.show();
}

// strip 11
void fillStrip_11() {
  CRGB phase1color = CRGB::Chocolate;
  fill_solid(pin11leds,NUM_LEDS, phase1color);
  FastLED.show();
}

// strip 12
void fillStrip_12() {
  CRGB phase1color = CRGB::DarkOliveGreen;
  fill_solid(pin12leds,NUM_LEDS, phase1color);
  FastLED.show();
}

SimplePatternList lightStrands = { fillStrip_01, fillStrip_02, fillStrip_03, fillStrip_04, fillStrip_05, fillStrip_06, fillStrip_07, fillStrip_08, fillStrip_09, fillStrip_10, fillStrip_11, fillStrip_12 };
void nextStrand() {
  // add one to the current strand number, and wrap around at the end
  gCurrentStrandNumber = (gCurrentStrandNumber + 1) % ARRAY_SIZE( lightStrands );
}
// 
void chasePattern(CRGB color, int delay) {
  currentTime = millis();
  int ellapsed = currentTime - lastTime;
  if (ellapsed > delay) {
    Serial.println(ellapsed);
    nextStrand();
    lastTime = currentTime;
  }

  //fadeAllToBlack();
}



void fillAllToBlack() {

  fillStrip_01();
  fillStrip_02();
  fillStrip_03();
  fillStrip_04();
  fillStrip_05();
  fillStrip_06();
  fillStrip_07();
  fillStrip_08();
  fillStrip_08();
  fillStrip_10();
  fillStrip_11();
  fillStrip_12();
}

// turns all wires all to black
void fadeAllToBlack() {
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
}

void setStringColor(int ledStrip, CRGB color) {
  int localBrightness = brightness;
  int ledstrips [13] = { pin1leds, pin2leds, pin3leds, pin4leds, pin5leds, pin6leds, pin7leds, pin8leds, pin9leds, pin10leds, pin11leds, pin12leds};
  fill_solid(ledstrips[ledStrip],NUM_LEDS, color);
  FastLED.show();
  while(localBrightness > 0) {
    unsetStringColor(ledStrip, color, localBrightness);
    localBrightness = localBrightness - 1;
  }

}

void unsetStringColor(int ledStrip, CRGB color, int brightness) {
  int ledstrips [13] = { pin1leds, pin2leds, pin3leds, pin4leds, pin5leds, pin6leds, pin7leds, pin8leds, pin9leds, pin10leds, pin11leds, pin12leds};
  fill_solid(ledstrips[ledStrip],NUM_LEDS, color);
  FastLED.setBrightness(brightness);
  FastLED.show();
}


// Inputs: Time between each string, Time to fade to Black
// Half a second or more between the pulses
// start at Red
void phase1() {
  int ledstrips [13] = { pin1leds, pin2leds, pin3leds, pin4leds, pin5leds, pin6leds, pin7leds, pin8leds, pin9leds, pin10leds, pin11leds, pin12leds};
  for (int x = 0; x < sizeof(ledstrips)/2; x++) {
    // fill_solid(ledstrips[x],NUM_LEDS, CRGB::Red); // up to 4 colors
    // fadeToBlackBy( ledstrips[x], NUM_LEDS, 10);
    // FastLED.show();

    fadeToBlackBy( ledstrips[x], NUM_LEDS, 20);

    
    delay(SLOW);
  }

  /* 
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
  fadeToBlackBy( pin12leds, NUM_LEDS, 10);*/

}

// yellow
void phase2() {
  
}

// green
void phase3() {

}

// end on blue
void phase4() {

}

// every color go nuts chaos, like a rotor (HSV) and then change Hue step by 30 points, prime numbers until it completes several rotors
void phase5() {


}

void setup() {

  FastLED.addLeds<LED_TYPE, LED_PIN1, COLOR_ORDER>(pin1leds, NUM_LEDS);
  FastLED.addLeds<LED_TYPE, LED_PIN2, COLOR_ORDER>(pin2leds, NUM_LEDS);
  FastLED.addLeds<LED_TYPE, LED_PIN3, COLOR_ORDER>(pin3leds, NUM_LEDS);
  FastLED.addLeds<LED_TYPE, LED_PIN4, COLOR_ORDER>(pin4leds, NUM_LEDS);
  FastLED.addLeds<LED_TYPE, LED_PIN5, COLOR_ORDER>(pin5leds, NUM_LEDS);
  FastLED.addLeds<LED_TYPE, LED_PIN6, COLOR_ORDER>(pin6leds, NUM_LEDS);
  FastLED.addLeds<LED_TYPE, LED_PIN7, COLOR_ORDER>(pin7leds, NUM_LEDS);
  FastLED.addLeds<LED_TYPE, LED_PIN8, COLOR_ORDER>(pin8leds, NUM_LEDS);
  FastLED.addLeds<LED_TYPE, LED_PIN9, COLOR_ORDER>(pin9leds, NUM_LEDS);
  FastLED.addLeds<LED_TYPE, LED_PIN10, COLOR_ORDER>(pin10leds, NUM_LEDS);
  FastLED.addLeds<LED_TYPE, LED_PIN11, COLOR_ORDER>(pin11leds, NUM_LEDS);
  FastLED.addLeds<LED_TYPE, LED_PIN12, COLOR_ORDER>(pin12leds, NUM_LEDS);

  FastLED.setBrightness(BRIGHTNESS);

  int ledstrips [13] = { pin1leds, pin2leds, pin3leds, pin4leds, pin5leds, pin6leds, pin7leds, pin8leds, pin9leds, pin10leds, pin11leds, pin12leds};
 
  for (int x = 0; x < 13; x++) {
    fill_solid(ledstrips[x],NUM_LEDS, CRGB::Black);
      FastLED.show();
  }



  


  //
  Serial.begin(9600);


  //bootsequence();

  // pinMode(ledPin, OUTPUT);
  // pinMode(interruptPin, INPUT_PULLUP);
  // attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);

}

// one strand with trails 

void bootsequence() {
   int ledstrips [13] = { pin1leds, pin2leds, pin3leds, pin4leds, pin5leds, pin6leds, pin7leds, pin8leds, pin9leds, pin10leds, pin11leds, pin12leds};
   int speed = BALLS;
   for (int x = 0; x < 12; x++) {
    fill_solid(ledstrips[x],NUM_LEDS, CRGB::Red); // up to 4 colors
    FastLED.show();
    delay(speed);
    fill_solid(ledstrips[x],NUM_LEDS, CRGB::Black); // up to 4 colors
    FastLED.show();
    delay(speed);
   }   

  
  fill_solid(pin1leds, NUM_LEDS, CRGB::Red);// not plugged in
  fill_solid(pin2leds, NUM_LEDS, CRGB::Red); // not plugged in fill_rainbow(pin3leds, NUM_LEDS, 0, 255 / NUM_LEDS);
  fill_solid(pin4leds, NUM_LEDS, CRGB::Red);
  fill_solid(pin5leds, NUM_LEDS, CRGB::Red);
  fill_solid(pin6leds, NUM_LEDS, CRGB::Red);
  fill_solid(pin7leds, NUM_LEDS, CRGB::Red);
  fill_solid(pin8leds, NUM_LEDS, CRGB::Red);
  fill_solid(pin9leds, NUM_LEDS, CRGB::Red);
  fill_solid(pin10leds, NUM_LEDS, CRGB::Red);
  fill_solid(pin11leds, NUM_LEDS, CRGB::Red);
  fill_solid(pin12leds, NUM_LEDS, CRGB::Red);
  FastLED.show();
  delay(SLOW);

  fill_solid(pin1leds, NUM_LEDS, CRGB::Green);// not plugged in
  fill_solid(pin2leds, NUM_LEDS, CRGB::Green); // not plugged in fill_rainbow(pin3leds, NUM_LEDS, 0, 255 / NUM_LEDS);
  fill_solid(pin4leds, NUM_LEDS, CRGB::Green);
  fill_solid(pin5leds, NUM_LEDS, CRGB::Green);
  fill_solid(pin6leds, NUM_LEDS, CRGB::Green);
  fill_solid(pin7leds, NUM_LEDS, CRGB::Green);
  fill_solid(pin8leds, NUM_LEDS, CRGB::Green);
  fill_solid(pin9leds, NUM_LEDS, CRGB::Green);
  fill_solid(pin10leds, NUM_LEDS, CRGB::Green);
  fill_solid(pin11leds, NUM_LEDS, CRGB::Green);
  fill_solid(pin12leds, NUM_LEDS, CRGB::Green);
  FastLED.show();
  delay(SLOW);

  fill_solid(pin1leds, NUM_LEDS, CRGB::Blue);// not plugged in
  fill_solid(pin2leds, NUM_LEDS, CRGB::Blue); // not plugged in fill_rainbow(pin3leds, NUM_LEDS, 0, 255 / NUM_LEDS);
  fill_solid(pin4leds, NUM_LEDS, CRGB::Blue);
  fill_solid(pin5leds, NUM_LEDS, CRGB::Blue);
  fill_solid(pin6leds, NUM_LEDS, CRGB::Blue);
  fill_solid(pin7leds, NUM_LEDS, CRGB::Blue);
  fill_solid(pin8leds, NUM_LEDS, CRGB::Blue);
  fill_solid(pin9leds, NUM_LEDS, CRGB::Blue);
  fill_solid(pin10leds, NUM_LEDS, CRGB::Blue);
  fill_solid(pin11leds, NUM_LEDS, CRGB::Blue);
  fill_solid(pin12leds, NUM_LEDS, CRGB::Blue);
  FastLED.show();
  delay(SLOW);

  fill_solid(pin1leds, NUM_LEDS, CRGB::Black);// not plugged in
  fill_solid(pin2leds, NUM_LEDS, CRGB::Black); // not plugged in fill_rainbow(pin3leds, NUM_LEDS, 0, 255 / NUM_LEDS);
  fill_solid(pin4leds, NUM_LEDS, CRGB::Black);
  fill_solid(pin5leds, NUM_LEDS, CRGB::Black);
  fill_solid(pin6leds, NUM_LEDS, CRGB::Black);
  fill_solid(pin7leds, NUM_LEDS, CRGB::Black);
  fill_solid(pin8leds, NUM_LEDS, CRGB::Black);
  fill_solid(pin9leds, NUM_LEDS, CRGB::Black);
  fill_solid(pin10leds, NUM_LEDS, CRGB::Black);
  fill_solid(pin11leds, NUM_LEDS, CRGB::Black);
  fill_solid(pin12leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
  delay(SLOW);
}

void idle() {
  int ledstrips [13] = { pin1leds, pin2leds, pin3leds, pin4leds, pin5leds, pin6leds, pin7leds, pin8leds, pin9leds, pin10leds, pin11leds, pin12leds};
   
  int speed = WALK;
   for (int x = 0; x < 12; x++) {
    fill_solid(ledstrips[x],NUM_LEDS, CRGB::Red); // up to 4 colors
    if (x - 1 > 0) {
      fill_solid(ledstrips[x-1],NUM_LEDS, CRGB::FireBrick); // up to 4 colors
    }
    if (x - 2 > 0) {
      fill_solid(ledstrips[x-2],NUM_LEDS, CRGB::Maroon); // up to 4 colors
    }
    FastLED.show();
    delay(speed);
     if (x - 1 > 0) {
      fill_solid(ledstrips[x-1],NUM_LEDS, CRGB::Black); // up to 4 colors
    }
    if (x - 2 > 0) {
      fill_solid(ledstrips[x-2],NUM_LEDS, CRGB::Black); // up to 4 colors
    }

    if (x - 3 > 0) {
      fill_solid(ledstrips[x-3],NUM_LEDS, CRGB::Black); // up to 4 colors
    }
    FastLED.show();
    delay(speed);
   }   
}

void loop() {



  chasePattern(CRGB::Red, 1000);

  //int ledstrips [13] = { pin1leds, pin2leds, pin3leds, pin4leds, pin5leds, pin6leds, pin7leds, pin8leds, pin9leds, pin10leds, pin11leds, pin12leds};

  //setStringColor(5,phase1Color);
  //fadeAllToBlack();

  //idle();
  
  // state 0;

  /* new code */
  // Call the current pattern function once, updating the 'leds' array
  //gPatterns[gCurrentPatternNumber]();
  lightStrands[gCurrentStrandNumber]();

  // // send the 'leds' array out to the actual LED strip
  FastLED.show();
  // insert a delay to keep the framerate modest
  //FastLED.delay(1000/FRAMES_PER_SECOND);

  // do some periodic updates
  //EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  //EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically
  //EVERY_N_SECONDS( 10 ) { nextStrand(); }
  
  /* old code */

  // check for signal interupt

  // put your main code here, to run repeatedly:
  //for (int x = 0; x < sizeof(ledstrips); x++) {

  // fill_rainbow(pin1leds, NUM_LEDS, 0, 255 / NUM_LEDS);// not plugged in
  // fill_rainbow(pin2leds, NUM_LEDS, 0, 255 / NUM_LEDS); // not plugged in
  // fill_rainbow(pin3leds, NUM_LEDS, 0, 255 / NUM_LEDS);
  // fill_rainbow(pin4leds, NUM_LEDS, 0, 255 / NUM_LEDS);
  // fill_rainbow(pin5leds, NUM_LEDS, 0, 255 / NUM_LEDS);
  // fill_rainbow(pin6leds, NUM_LEDS, 0, 255 / NUM_LEDS);
  // fill_rainbow(pin7leds, NUM_LEDS, 0, 255 / NUM_LEDS);
  // fill_rainbow(pin8leds, NUM_LEDS, 0, 255 / NUM_LEDS);
  // fill_rainbow(pin9leds, NUM_LEDS, 0, 255 / NUM_LEDS);
  // fill_rainbow(pin10leds, NUM_LEDS, 0, 255 / NUM_LEDS);
  // fill_rainbow(pin11leds, NUM_LEDS, 0, 255 / NUM_LEDS);
  // fill_rainbow(pin12leds, NUM_LEDS, 0, 255 / NUM_LEDS);
  // FastLED.show();
  // delay(1000);

  //for (int x = 0; x < sizeof(ledstrips); x++) {
    
    // fill_solid(pin4leds,NUM_LEDS, CRGB::Red); // up to 4 colors
    // FastLED.show();
    // delay(1000);
    // fill_solid(pin4leds,NUM_LEDS, CRGB::Black); // up to 4 colors
    // FastLED.show();
    // delay(1000);

    // fill_solid(pin4leds,NUM_LEDS, CRGB::Red); // up to 4 colors
    // FastLED.show();
    // delay(800);
    // fill_solid(pin4leds,NUM_LEDS, CRGB::Black); // up to 4 colors
    // FastLED.show();
    // delay(800);

    // fill_solid(pin4leds,NUM_LEDS, CRGB::Red); // up to 4 colors
    // FastLED.show();
    // delay(600);
    // fill_solid(pin4leds,NUM_LEDS, CRGB::Black); // up to 4 colors
    // FastLED.show();
    // delay(600);

    // fill_solid(pin4leds,NUM_LEDS, CRGB::Red); // up to 4 colors
    // FastLED.show();
    // delay(400);
    // fill_solid(pin4leds,NUM_LEDS, CRGB::Black); // up to 4 colors
    // FastLED.show();
    // delay(400);

    // fill_solid(pin4leds,NUM_LEDS, CRGB::Red); // up to 4 colors
    // FastLED.show();
    // delay(200);
    // fill_solid(pin4leds,NUM_LEDS, CRGB::Black); // up to 4 colors
    // FastLED.show();
    // delay(200);

    // fill_solid(pin4leds,NUM_LEDS, CRGB::Red); // up to 4 colors
    // FastLED.show();
    // delay(100);
    // fill_solid(pin4leds,NUM_LEDS, CRGB::Black); // up to 4 colors
    // FastLED.show();
    // delay(100);

    // fill_solid(pin4leds,NUM_LEDS, CRGB::Red); // up to 4 colors
    // FastLED.show();
    // delay(50);
    // fill_solid(pin4leds,NUM_LEDS, CRGB::Black); // up to 4 colors
    // FastLED.show();
    // delay(50);

    // fill_solid(pin4leds,NUM_LEDS, CRGB::Red); // up to 4 colors
    // FastLED.show();
    // delay(50);
    // fill_solid(pin4leds,NUM_LEDS, CRGB::Black); // up to 4 colors
    // FastLED.show();
    // delay(50);

    // fill_solid(pin4leds,NUM_LEDS, CRGB::Red); // up to 4 colors
    // FastLED.show();
    // delay(50);
    // fill_solid(pin4leds,NUM_LEDS, CRGB::Black); // up to 4 colors
    // FastLED.show();
    // delay(50);

    // fill_solid(pin4leds,NUM_LEDS, CRGB::Red); // up to 4 colors
    // FastLED.show();
    // delay(50);
    // fill_solid(pin4leds,NUM_LEDS, CRGB::Black); // up to 4 colors
    // FastLED.show();
    // delay(50);
  //}

  //   fill_solid(pin4leds, NUM_LEDS, CRGB::Green);
  //   FastLED.show();


  //   fill_solid(pin5leds, NUM_LEDS, CRGB::Blue);
  //   FastLED.show();

  //   for (int i = 0; i < NUM_LEDS; i++) {
  //     pin6leds[i] = CRGB::Blue;
  //     pin7leds[i] = CRGB::Blue;
  //     pin8leds[i] = CRGB::Blue;
  //     FastLED.show();
  //     delay(100);
  //     pin6leds[i] = CRGB::Red;
  //     pin7leds[i] = CRGB::Red;
  //     pin8leds[i] = CRGB::Red;
  //     FastLED.show();

  //     delay(100);
  // }


    // fill_solid(leds, NUM_LEDS, CRGB::Blue);
    // FastLED.show();
    // delay(500);
  //}
}
