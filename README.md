# Johannes' WS2812B LED Tester

![Johannes Super Mini LED Tester](https://raw.githubusercontent.com/dkingger/LEDstrip-tester/7f5f77b4aae9404add1b30063f668b28c3c08b79/Super_mini_tester.png)

Et LED-controller-projekt baseret på **ESP32-C3 Super Mini**, designet til at teste og styre WS2812B LED-strips med forskellige effekter, justerbar lysstyrke og et trådløst webinterface.

## 🔧 Hardware

- ESP32-C3 Mini Dev Board
- WS2812B LED strip (10 pixels)
- Rotary Encoder (med trykknap og RGB-lys)
- 2 Push buttons
- Strømforsyning (5V)

## 💡 Funktioner

- 10 forskellige lys-effekter (løbelys, Knight Rider, regnbue mm.)
- Lysstyrke kan justeres med rotary encoder eller via webinterface
- Webinterface med realtid WebSocket-opdatering
- Kan bruges helt uden webinterface også

---

## 🧪 Kodeversioner

### `Encode_LED_noWeb.ino`
- Ren fysisk styring via knapper og encoder
- Velegnet til test af hardware og grundfunktionalitet

---

### `Encode_LED_Web.ino`
- Tilføjer et simpelt webinterface
- Viser lysstyrke og valgt effekt
- ESP32 fungerer som WiFi Access Point

---

### `Encode_LED_WebSocket.ino` ✅ *(mest avancerede version)*
- Realtime styring via webinterface med WebSocket
- Slider til justering af lysstyrke
- Knapper til valg af effekter
- Responsivt interface – også til mobil

---

## 🌐 Brug

1. Upload `.ino`-filen til din ESP32-C3 Mini
2. Forbind til WiFi-netværket `ESP32-LED` (kode: `led12345`)
3. Åbn browser og gå til `http://192.168.4.1`

---

## 📦 Krævede biblioteker

Installér disse via **Sketch → Include Library → Manage Libraries** i Arduino IDE:

- [Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)
- [WebSockets by Markus Sattler](https://github.com/Links2004/arduinoWebSockets)
- [ArduinoJson by Benoît Blanchon](https://arduinojson.org/)
- `WiFi` og `WebServer` følger med ESP32 board support

---

## 🚀 Idéer til udvidelse

- Dropdown-menu til at vælge specifik effekt
- Gemme lysstyrke og effekt i EEPROM
- Overgang til station-mode og MQTT-integration
- Musik-reaktiv LED-effekt (med mikrofon)

---

🛠️ Projektet er perfekt til undervisning, makerspaces og hobbybrug – og helt open source.
