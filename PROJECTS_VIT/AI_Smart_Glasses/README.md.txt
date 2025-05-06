# AI-Powered Smart Glasses for the Deaf 

These smart glasses assist people with hearing disabilities by detecting speech and converting it into visual alerts and text on a display.

1) Components Used

-> ESP32 OLED Module (with AMS1117 regulator)
-> MAX9814 Microphone Module
-> Arduino Nano
-> LED bulb
-> External OLED Display
-> MT3608 Boost Converter (3.7V → 5V)
-> Li-Po Battery
-> OLED Display

2) Working Principle

1. Audio Capture: MAX9814 captures sound → ESP32 receives audio via GPIO39
2. Speech Detection: ESP32 sends data to laptop
3. Transcription: Laptop uses Google Speech-to-Text API
4. Visual Output:
   - LED glows if speech is detected
   - Transcribed text is shown on OLED via Arduino Nano

3) Highlights

-> Works offline after speech-to-text
-> Visual alert + textual display
-> Battery-powered prototype (no need for recharge)


