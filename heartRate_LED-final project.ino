#include <FastLED.h>

#define LED_PIN1     9
#define LED_PIN2    10
#define LED_PIN3    11
#define NUM_LEDS    30
#define BRIGHTNESS  64
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

uint8_t brightness = 0;
int fade = 0;
int a = 0;


unsigned long previousMillis = 0;
const long interval = 5000;

const int SENSOR_PIN = A1;

int h = 0;
int r = 0;


void setup() {
  Serial.begin(9600);
  delay( 3000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN1, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED_PIN2, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED_PIN3, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;

  pinMode(SENSOR_PIN, INPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  FastLED.setBrightness(  BRIGHTNESS );
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */

  FillLEDsFromPaletteColors( startIndex);

  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);


  h = analogRead(SENSOR_PIN);
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (h <= 0) {
      Serial.println("--");
    }

    else {
      r = map(h, 1000, 1, 0, 160);
      if (r < 40) {
        Serial.println("hold still");
        a = 0;
      }
      if (r >= 40 && r < 60) {
        Serial.println(r);
        Blue();
        currentBlending = LINEARBLEND;
        //        tone(buzzer, NOTE_G6, 8); /////////////////////////////////////////////
        a = 1;
      }
      if (r >= 60 && r < 80) {
        Serial.println(r);
        Green();
        currentBlending = LINEARBLEND;
        //        tone(buzzer, NOTE_A6, 8); /////////////////////////////////////////////
        a = 2;
      }
      if (r >= 80 && r < 100) {
        Serial.println(r);
        Yellow();
        currentBlending = LINEARBLEND;
        //        tone(buzzer, NOTE_B6, 8); /////////////////////////////////////////////
        a = 3;
      }
      if (r >= 100 && r < 120) {
        Serial.println(r);
        Purple();
        currentBlending = LINEARBLEND;
        //        tone(buzzer, NOTE_C7, 8); /////////////////////////////////////////////
        a = 4;
      }
      if (r >= 120) {
        Serial.println(r);
        Serial.println(r);
        Red();
        currentBlending = LINEARBLEND;
        //        tone(buzzer, NOTE_D7, 8); /////////////////////////////////////////////
        a = 5;
      }
    }
    delay(5);
    a = a;
  }

}


void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
  if (a == 0) {
    fade = 0;
  }
  if (a == 1) {
    fade = 2;
  }
  if (a == 2) {
    fade = 3;
  }
  if (a == 3) {
    fade = 4;
  }
  if (a == 4) {
    fade = 5;
  }
  if (a == 5) {
    fade = 6;
  }


  brightness = brightness + fade;
  
  if (brightness <= 0 || brightness >= 255) {
    fade = -fade;
  }

  for ( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
    colorIndex += 3;
  }
}

void Purple()
{
  // 'black out' all 16 palette entries...
  fill_solid( currentPalette, 16, CRGB::Purple);
  // and set every fourth one to white.
  currentPalette[0] = CRGB::Purple;
  currentPalette[4] = CRGB::Purple;
  currentPalette[8] = CRGB::Purple;
  currentPalette[12] = CRGB::Red;

}

void Blue()
{
  // 'black out' all 16 palette entries...
  fill_solid( currentPalette, 16, CRGB::Blue);
  // and set every fourth one to white.
  currentPalette[0] = CRGB::Blue;
  currentPalette[4] = CRGB::Blue;
  currentPalette[8] = CRGB::Blue;
  currentPalette[12] = CRGB::Cyan;

}

void Green()
{
  // 'black out' all 16 palette entries...
  fill_solid( currentPalette, 16, CRGB::Green);
  // and set every fourth one to white.
  currentPalette[0] = CRGB::Green;
  currentPalette[4] = CRGB::Green;
  currentPalette[8] = CRGB::Green;
  currentPalette[12] = CRGB::Yellow;

}

void Yellow()
{
  // 'black out' all 16 palette entries...
  fill_solid( currentPalette, 16, CRGB::Yellow);
  // and set every fourth one to white.
  currentPalette[0] = CRGB::Yellow;
  currentPalette[4] = CRGB::Yellow;
  currentPalette[8] = CRGB::Yellow;
  currentPalette[12] = CRGB::Purple;

}

void Red()
{
  // 'black out' all 16 palette entries...
  fill_solid( currentPalette, 16, CRGB::Red);
  // and set every fourth one to white.
  currentPalette[0] = CRGB::Red;
  currentPalette[4] = CRGB::Red;
  currentPalette[8] = CRGB::Red;
  currentPalette[12] = CRGB::White;

}


const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
  CRGB::Red,
  CRGB::Yellow, // 'white' is too bright compared to red and blue
  CRGB::Blue,
  CRGB::Purple,

  CRGB::Red,
  CRGB::Yellow,
  CRGB::Blue,
  CRGB::Purple,

  CRGB::Red,
  CRGB::Red,
  CRGB::Yellow,
  CRGB::Yellow,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Purple,
  CRGB::Purple
};
