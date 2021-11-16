#include <FastLED.h>

#define LED_PIN     10
#define NUM_LEDS    31
#define BRIGHTNESS  64
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

unsigned long previousMillis = 0;
const long interval = 1000;

uint8_t brightness = 0;
int fade = 0;
int a = 0;

const int SENSOR_PIN = A1;
//const int ledPin1 = 2;
//const int ledPin2 = 4;
//const int ledPin3 = 7;

int h = 0;
int r = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay( 3000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;

  pinMode(SENSOR_PIN, INPUT);
  //  pinMode(ledPin1, OUTPUT);
  //  pinMode(ledPin2, OUTPUT);
  //  pinMode(ledPin3, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  FastLED.setBrightness(  BRIGHTNESS );
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */

  FillLEDsFromPaletteColors( startIndex);

  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);


  // put your main code here, to run repeatedly:
  h = analogRead(SENSOR_PIN);
  if (currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
  
  if (h <= 0) {
    Serial.println("--");
  }
  else {
    r = map(h, 1000, 1, 0, 160);
    if (r < 40) {
      Serial.println("hold still");
      //      digitalWrite(ledPin1, LOW);
      //      digitalWrite(ledPin2, LOW);
      //      digitalWrite(ledPin3, LOW);
      a = 0;
    }
    if (r >= 40 && r < 90) {
      Serial.println(r);
      //      digitalWrite(ledPin1, HIGH);
      SetupBlackAndBlueStripedPalette();
      currentBlending = LINEARBLEND;
      a = 1;
//      delay(500);
    }
    if (r >= 90 && r < 120) {
      Serial.println(r);
      //      digitalWrite(ledPin2, HIGH);
      SetupBlackAndGreenStripedPalette();
      currentBlending = LINEARBLEND;
      a = 2;
//      delay(500);
    }
    if (r >= 120) {
      Serial.println(r);
      //      digitalWrite(ledPin3, HIGH);
      SetupBlackAndRedStripedPalette();
      currentBlending = LINEARBLEND;
      a = 3;
//      delay(500);
    }
  }
  delay(5);
  a = a;
  }

}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
  if (a == 0){
    fade = 0;
  }
  if (a == 1){
    fade = 2;
  }
  if (a == 2){
    fade = 5;
  }
  if (a == 3){
    fade = 20;
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

void SetupBlackAndBlueStripedPalette()
{
  // 'black out' all 16 palette entries...
  fill_solid( currentPalette, 16, CRGB::Blue);
  // and set every fourth one to white.
  currentPalette[0] = CRGB::Blue;
  currentPalette[4] = CRGB::Blue;
  currentPalette[8] = CRGB::Blue;
  currentPalette[12] = CRGB::Blue;

}

void SetupBlackAndGreenStripedPalette()
{
  // 'black out' all 16 palette entries...
  fill_solid( currentPalette, 16, CRGB::Green);
  // and set every fourth one to white.
  currentPalette[0] = CRGB::Green;
  currentPalette[4] = CRGB::Green;
  currentPalette[8] = CRGB::Green;
  currentPalette[12] = CRGB::Green;

}

void SetupBlackAndRedStripedPalette()
{
  // 'black out' all 16 palette entries...
  fill_solid( currentPalette, 16, CRGB::Red);
  // and set every fourth one to white.
  currentPalette[0] = CRGB::Red;
  currentPalette[4] = CRGB::Red;
  currentPalette[8] = CRGB::Red;
  currentPalette[12] = CRGB::Red;

}
