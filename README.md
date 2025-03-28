# Johannes' WS2812B LED Tester

![Johannes Super Mini LED Tester](https://raw.githubusercontent.com/dkingger/LEDstrip-tester/7f5f77b4aae9404add1b30063f668b28c3c08b79/Super_mini_tester.png)

Dette projekt er en LED-tester baseret på en ESP32-C3 Super Mini med følgende komponenter:

- Rotary encoder med trykknap og RGB lys
- To trykknapper
- En WS2812B LED strip (10 pixels)
- Webinterface til visning og styring

## 🧪 Kodeversioner

### `Encode_LED_noWeb.ino`
Enkel version uden webinterface.  
Styring sker udelukkende via knapper og rotary encoder.  
God som test af hardware og grundlæggende funktionalitet.

---

### `Encode_LED_Web.ino`
Tilføjer simpelt webinterface via Access Point.  
Du kan se lysstyrke og aktiv effekt i browseren.  
God til introduktion af netværk og HTML.

---

### `Encode_LED_WebSocket.ino` ✅ *(Seneste og mest avancerede)*
Fuld version med:
- Webinterface via Access Point
- Realtime opdatering via WebSocket
- Slider til lysstyrke
- Knapper til at skifte effekt

---

## 🌐 Brug

1. Upload `Encode_LED_WebSocket.ino` til din ESP32-C3
2. Forbind til WiFi: `ESP32-LED`, kode: `led12345`
3. Gå til: [http://192.168.4.1](http://192.168.4.1)

---

## 🔦 Funktioner

- 10 forskellige LED-effekter (herunder Knight Rider og regnbue)
- Justerbar lysstyrke via encoder eller webinterface
- Visuel feedback i browser og Serial Monitor

---

📦 Projektet er let at udvide – fx med EEPROM, MQTT eller animationsvalg via dropdown.

