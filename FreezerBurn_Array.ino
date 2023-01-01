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

#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gCurrentStrandNumber = 0; // Index number of which light strand is the current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

const int brightness = 255;

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

}

void loop() {

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


}
