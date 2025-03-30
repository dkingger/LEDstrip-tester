// ESP32-C3 Mini Dev Board - LED-effekter med rotary encoder, ringtryk, WebSocket webinterface og EEPROM lagring

#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>
#include <EEPROM.h>

#define ENCODER_A 20
#define ENCODER_B 21
#define RING1 1
#define RING2 2
#define LED_STRIP_PIN 6
#define LED_COUNT 10
#define EEPROM_SIZE 12

const char* ssid = "ESP32-LED";
const char* password = "led12345";

WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

Adafruit_NeoPixel strip(LED_COUNT, LED_STRIP_PIN, NEO_GRB + NEO_KHZ800);

volatile int lastClkState;
volatile bool turned = false;
int brightness = 100;
int effectIndex = 0;
unsigned long lastEffectUpdate = 0;
int effectStep = 0;
int direction = 1;
unsigned long lastChangeTime = 0;

const char* effectNames[10] = {
  "Rød", "Grøn", "Blå", "Løbelys Gul", "Knight Rider Rød",
  "Blink Hvid", "Regnbue", "Løbelys Magenta", "Knight Rider Regnbue", "Orange"
};

void saveToEEPROM() {
  lastChangeTime = millis();
  EEPROM.write(0, brightness);
  EEPROM.write(1, effectIndex);
  EEPROM.put(2, lastChangeTime);
  EEPROM.commit();
  EEPROM.write(0, brightness);
  EEPROM.write(1, effectIndex);
  EEPROM.commit();
}

void loadFromEEPROM() {
  EEPROM.get(2, lastChangeTime);
  brightness = EEPROM.read(0);
  effectIndex = EEPROM.read(1);
  brightness = constrain(brightness, 0, 255);
  effectIndex = constrain(effectIndex, 0, 9);
}

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
    saveToEEPROM();
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
    case 0: effectSolidColor(strip.Color(255, 0, 0)); break;
    case 1: effectSolidColor(strip.Color(0, 255, 0)); break;
    case 2: effectSolidColor(strip.Color(0, 0, 255)); break;
    case 3: effectLøbelys(strip.Color(255, 255, 0)); break;
    case 4: effectKnightRider(strip.Color(255, 0, 0)); break;
    case 5: effectBlink(strip.Color(255, 255, 255)); break;
    case 6: effectRainbow(); break;
    case 7: effectLøbelys(strip.Color(255, 0, 255)); break;
    case 8: effectKnightRiderRainbow(); break;
    case 9: effectSolidColor(strip.Color(255, 128, 0)); break;
  }
}

void handleRoot() {
  String html = R"rawliteral(
  <html><head><title>Johannes' WS2812B LED tester</title>
  <style>
    body { font-family: sans-serif; padding: 1rem; }
    .value { font-weight: bold; font-size: 1.5rem; }
    input[type=range] {
      width: 100%;
      height: 60px;
      -webkit-appearance: none;
      background: #ddd;
      border-radius: 10px;
    }
    input[type=range]::-webkit-slider-thumb {
      -webkit-appearance: none;
      appearance: none;
      height: 60px;
      width: 30px;
      background: #333;
      border-radius: 5px;
      cursor: pointer;
    }
    button {
      font-size: 1.4rem;
      padding: 30px 25px;
      margin: 10px 0;
      width: 100%;
      height: 100px;
    }
    footer {
      margin-top: 2rem;
      font-size: 0.9rem;
      color: #777;
    }
  </style>
  </head><body>
  <h2>Johannes' WS2812B LED tester</h2>
  <p>Lysstyrke: <span id="brightness" class="value">?</span></p>
  <input type="range" id="slider" min="0" max="255" value="100">
  <p>Effekt: <span id="effect" class="value">?</span></p>
  <div style="display: flex; gap: 1rem; justify-content: center; align-items: center;">
  <button style="flex:1" onclick="send('prev')">&#8592; FORRIGE</button>
  <button style="flex:1" onclick="send('next')">NÆSTE &#8594;</button>
</div>
  <script>
  var ws = new WebSocket("ws://" + location.hostname + ":81/");
  ws.onmessage = function(event) {
    var data = JSON.parse(event.data);
    document.getElementById("brightness").innerText = data.brightness;
    document.getElementById("slider").value = data.brightness;
    document.getElementById("effect").innerText = data.effect;
  };
  document.getElementById("slider").oninput = function() {
    ws.send(JSON.stringify({type: 'brightness', value: parseInt(this.value)}));
  };
  function send(cmd) {
    ws.send(JSON.stringify({type: 'effect', value: cmd}));
  }
  </script>
  <footer>Sidst opdateret: 2025-03-29</footer>
  )rawliteral";
  server.send(200, "text/html", html);
}

void notifyClients() {
  String json = "{\"brightness\":" + String(brightness) + ",\"effect\":\"" + String(effectNames[effectIndex]) + "\"}";
  webSocket.broadcastTXT(json);
}

void setup() {
  Serial.begin(9600);
  EEPROM.begin(EEPROM_SIZE);
  loadFromEEPROM();

  pinMode(ENCODER_A, INPUT_PULLUP);
  pinMode(ENCODER_B, INPUT_PULLUP);
  pinMode(RING1, INPUT_PULLUP);
  pinMode(RING2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENCODER_A), handleEncoder, CHANGE);
  lastClkState = digitalRead(ENCODER_A);

  strip.begin();
  strip.show();
  clearStrip();

  WiFi.softAP("ESP32-LED", "led12345");
  Serial.println("ESP32 kører som Access Point!");
  Serial.print("IP adresse: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.begin();

  webSocket.begin();
  webSocket.onEvent([](uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
    if (type == WStype_TEXT) {
      String msg = String((char*)payload);
      DynamicJsonDocument doc(128);
      DeserializationError err = deserializeJson(doc, msg);
      if (!err) {
        if (doc["type"] == "brightness") {
          brightness = constrain(doc["value"], 0, 255);
          saveToEEPROM();
          notifyClients();
        } else if (doc["type"] == "effect") {
          String cmd = doc["value"];
          if (cmd == "next") effectIndex = (effectIndex + 1) % 10;
          if (cmd == "prev") effectIndex = (effectIndex - 1 + 10) % 10;
          effectStep = 0;
          direction = 1;
          saveToEEPROM();
          notifyClients();
        }
      }
    }
  });

  Serial.println("Webserver og WebSocket kører...");
  Serial.print("Sidste ændringstidspunkt (ms siden start): ");
  Serial.println(lastChangeTime);
}

void loop() {
  server.handleClient();
  webSocket.loop();

  if (turned) {
    notifyClients();
    Serial.print("Lysstyrke: ");
    Serial.println(brightness);
    turned = false;
  }

  if (digitalRead(RING1) == LOW) {
    effectIndex = (effectIndex + 1) % 10;
    effectStep = 0;
    direction = 1;
    saveToEEPROM();
    notifyClients();
    Serial.print("Næste effekt: ");
    Serial.println(effectIndex);
    delay(200);
  }

  if (digitalRead(RING2) == LOW) {
    effectIndex = (effectIndex - 1 + 10) % 10;
    effectStep = 0;
    direction = 1;
    saveToEEPROM();
    notifyClients();
    Serial.print("Forrige effekt: ");
    Serial.println(effectIndex);
    delay(200);
  }

  updateEffect();
}
