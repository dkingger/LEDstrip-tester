# SuperMini LED Tester 🔦✨

Et ESP32-C3-baseret projekt der styrer en WS2812B LED-strip via rotary encoder, fysiske knapper og et trådløst webinterface med live opdatering.

## Funktioner
- 🎚️ Rotary encoder til justering af lysstyrke
- 🔘 To fysiske knapper til at skifte mellem 10 forskellige lys-effekter
- 🌐 Webinterface med WebSocket real-time kontrol
- 💾 EEPROM-lagring af sidste effekt og lysstyrke
- 📱 Mobilvenligt interface – fungerer også i Captive Portal-mode
- 🖼️ SPIFFS-hostede billeder og HTML

---

## Versioner i dette repository

| Filnavn                      | Beskrivelse |
|-----------------------------|-------------|
| `Encode_LED.ino`            | Basal version med fysiske knapper og encoder – uden webinterface |
| `Encode_LED_Web.ino`        | Version med simpelt webinterface (ingen live opdatering) |
| `Encode_LED_WebSocket.ino`  | Tilføjer WebSocket så webinterfacet opdateres live |
| `Encode_LED_WebSocket_SPIFFS.ino` | Fuldt webinterface via SPIFFS – nu mobilvenlig og med logo, pile og Captive Portal |

---

## 📚 Nødvendige biblioteker

Disse biblioteker installeres automatisk via PlatformIO, eller manuelt i Arduino IDE:

- [Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)
- [ArduinoJson](https://arduinojson.org/)
- [WebSockets by Links2004](https://github.com/Links2004/arduinoWebSockets)
- WiFi, EEPROM, SPIFFS (indbygget i ESP32 Arduino core)

---

## 🧰 Hardware

- ESP32-C3 Mini Dev Board
- 2x momentary trykknapper
- 1x Rotary encoder (uden indbygget LED)
- WS2812B LED-strip (10 LED'er)

---

## 🕒 Sidst ændret

**29. marts 2025** – implementeret stabil rotary encoder, fixet WebSocket-synkronisering og flyttet EEPROM-lagring ud af interrupt.

---

## 🧪 Testet med

- PlatformIO på Visual Studio Code
- Arduino IDE 2 (uden SPIFFS upload plugin)
- Chrome & Safari på mobil og desktop

---

## 📸 Interface

<img src="logo.png" width="100%">

---

Du er velkommen til at foreslå ændringer eller lave en fork af projektet!
