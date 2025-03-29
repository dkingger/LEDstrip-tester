# SuperMini LED Tester 💡🔧

Et ESP32-C3 Mini Dev Board projekt der styrer en WS2812B LED-strip via fysisk rotary encoder, to trykknapper og et mobilvenligt webinterface med live opdatering via WebSocket.

---

## 📸 Fotos

### Hardwareopsætning
![Hardware](Hardware.jpg)

### Webinterface på mobil
![Interface](Interface.PNG)

### Projektets logo
![Logo](logo.png)

---

## Funktioner

- 🔄 Rotary encoder: Justér lysstyrken (0–255)
- 🔘 To fysiske ringtryk: Skift mellem 10 effekter
- 🌈 LED-strip: WS2812B med 10 dioder
- 🌐 Webinterface med live opdatering via WebSocket
- 📁 SPIFFS: Webside og grafik hostes direkte på ESP32
- 📶 AP-mode + Captive Portal
- 💾 EEPROM-lagring af sidste indstilling (effekt og lysstyrke)

---

## Versioner i dette repository

| Filnavn                      | Beskrivelse |
|-----------------------------|-------------|
| `Encode_LED.ino`            | Fysisk styring via knapper og encoder – uden WiFi/web |
| `Encode_LED_Web.ino`        | Simpelt webinterface uden live opdatering |
| `Encode_LED_WebSocket.ino`  | Live WebSocket-baseret interface |
| `Encode_LED_WebSocket_SPIFFS.ino` | Komplet version med SPIFFS og mobilvenligt design |

---

## 📚 Krævede biblioteker

Installeres automatisk via PlatformIO eller manuelt i Arduino IDE:

- [Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)
- [ArduinoJson](https://arduinojson.org/)
- [WebSockets (Links2004)](https://github.com/Links2004/arduinoWebSockets)
- SPIFFS, EEPROM og WiFi (indbygget i ESP32 Arduino core)

---

## 🔩 Hardware

- ESP32-C3 Mini Dev Board
- 2x ringtryk (momentary)
- 1x rotary encoder (uden RGB-lys)
- 10x WS2812B RGB LED (LED-strip)
- Modstand og modstrømsbeskyttelse anbefales

---

## 🕓 Sidst ændret

**29. marts 2025**  
- Debounce på rotary encoder
- EEPROM flyttet ud af interrupt
- Forbedret WebSocket-opdatering og Captive Portal

---

## 🧪 Udviklet og testet med

- PlatformIO (VS Code)
- Arduino IDE 2.3 (begrænset SPIFFS-understøttelse)
- Chrome & Safari på mobil og desktop

---

> 💬 Kontakt: Johannes • Projektstatus: ✅ Fuldt fungerende og udbygget
