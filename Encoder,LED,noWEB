// ESP32-C3 Mini Dev Board - LED-effekter med rotary encoder og ringtryk

#include <Adafruit_NeoPixel.h>

#define ENCODER_A 20
#define ENCODER_B 21
#define RING1 1
#define RING2 2
#define LED_STRIP_PIN 6
#define LED_COUNT 10

Adafruit_NeoPixel strip(LED_COUNT, LED_STRIP_PIN, NEO_GRB + NEO_KHZ800);

volatile int lastClkState;
volatile bool turned = false;
int brightness = 100;
int effectIndex = 0;
unsigned long lastEffectUpdate = 0;
int effectStep = 0;
int direction = 1; // Flyttet globalt for Knight Rider

void IRAM_ATTR handleEncoder() {
  int clkState = digitalRead(ENCODER_A);
  int dtState = digitalRead(ENCODER_B);
  if (clkState != lastClkState) {
    if (dtState != clkState) {
      brightness += 10;
      if (brightness > 255) brightness = 255;
    } else {
      brightness -= 10;
      if (brightness < 0) brightness = 0;
    }
    turned = true;
  }
  lastClkState = clkState;
}

void clearStrip() {
  for (int i = 0; i < LED_COUNT; i++) {
    strip.setPixelColor(i, 0);
  }
  strip.show();
}

void effectSolidColor(uint32_t color) {
  strip.setBrightness(brightness);
  for (int i = 0; i < LED_COUNT; i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
}

void effectLøbelys(uint32_t color) {
  if (millis() - lastEffectUpdate > 100) {
    clearStrip();
    strip.setPixelColor(effectStep % LED_COUNT, color);
    strip.show();
    effectStep++;
    lastEffectUpdate = millis();
  }
}

void effectKnightRider(uint32_t color) {
  if (millis() - lastEffectUpdate > 80) {
    clearStrip();
    strip.setPixelColor(effectStep, color);
    strip.show();
    effectStep += direction;
    if (effectStep == LED_COUNT - 1 || effectStep == 0) direction = -direction;
    lastEffectUpdate = millis();
  }
}

void effectBlink(uint32_t color) {
  if (millis() - lastEffectUpdate > 250) {
    for (int i = 0; i < LED_COUNT; i++) {
      strip.setPixelColor(i, (effectStep % 2 == 0) ? color : 0);
    }
    strip.show();
    effectStep++;
    lastEffectUpdate = millis();
  }
}

void effectRainbow() {
  if (millis() - lastEffectUpdate > 50) {
    strip.setBrightness(brightness);
    for (int i = 0; i < LED_COUNT; i++) {
      int hue = (i * 256 / LED_COUNT + effectStep * 5) % 256;
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(hue * 256)));
    }
    strip.show();
    effectStep++;
    lastEffectUpdate = millis();
  }
}

void effectKnightRiderRainbow() {
  static uint32_t rainbowColors[LED_COUNT];
  if (effectStep == 0) {
    for (int i = 0; i < LED_COUNT; i++) {
      int hue = (i * 256 / LED_COUNT);
      rainbowColors[i] = strip.gamma32(strip.ColorHSV(hue * 256));
    }
  }
  if (millis() - lastEffectUpdate > 80) {
    clearStrip();
    strip.setPixelColor(effectStep, rainbowColors[effectStep]);
    strip.show();
    effectStep += direction;
    if (effectStep == LED_COUNT - 1 || effectStep == 0) direction = -direction;
    lastEffectUpdate = millis();
  }
}

void updateEffect() {
  strip.setBrightness(brightness);
  switch (effectIndex) {
    case 0: effectSolidColor(strip.Color(255, 0, 0)); break;         // Rød
    case 1: effectSolidColor(strip.Color(0, 255, 0)); break;         // Grøn
    case 2: effectSolidColor(strip.Color(0, 0, 255)); break;         // Blå
    case 3: effectLøbelys(strip.Color(255, 255, 0)); break;          // Gul Løbelys
    case 4: effectKnightRider(strip.Color(255, 0, 0)); break;        // Knight Rider rød
    case 5: effectBlink(strip.Color(255, 255, 255)); break;          // Hvid blink
    case 6: effectRainbow(); break;                                  // Regnbue farver
    case 7: effectLøbelys(strip.Color(255, 0, 255)); break;          // Magenta løbelys
    case 8: effectKnightRiderRainbow(); break;                       // Knight Rider regnbue
    case 9: effectSolidColor(strip.Color(255, 128, 0)); break;       // Orange
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(ENCODER_A, INPUT_PULLUP);
  pinMode(ENCODER_B, INPUT_PULLUP);
  pinMode(RING1, INPUT_PULLUP);
  pinMode(RING2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENCODER_A), handleEncoder, CHANGE);
  lastClkState = digitalRead(ENCODER_A);

  strip.begin();
  strip.show();
  clearStrip();

  Serial.println("Test af LED-effekter starter...");
}

void loop() {
  if (turned) {
    Serial.print("Lysstyrke: ");
    Serial.println(brightness);
    turned = false;
  }

  if (digitalRead(RING1) == LOW) {
    effectIndex = (effectIndex + 1) % 10;
    effectStep = 0;
    direction = 1;
    Serial.print("Næste effekt: ");
    Serial.println(effectIndex);
    delay(200);
  }

  if (digitalRead(RING2) == LOW) {
    effectIndex = (effectIndex - 1 + 10) % 10;
    effectStep = 0;
    direction = 1;
    Serial.print("Forrige effekt: ");
    Serial.println(effectIndex);
    delay(200);
  }

  updateEffect();
}
