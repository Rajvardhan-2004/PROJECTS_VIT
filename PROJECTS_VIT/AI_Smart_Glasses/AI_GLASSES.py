import speech_recognition as sr
import requests

# Step 1: Initialize recognizer
recognizer = sr.Recognizer()

# Step 2: Ask user to speak
print("🎤 Please speak now...")

with sr.Microphone() as source:
    recognizer.adjust_for_ambient_noise(source)
    audio_data = recognizer.listen(source)
    print("🔊 Got your voice, transcribing...")

    try:
        # Step 3: Transcribe using Google's recognizer (offline option also available)
        text = recognizer.recognize_google(audio_data)
        print("✅ Transcribed Text:", text)

        # Step 4: Send to ESP32 over WiFi using GET request
        esp32_ip = "http://172.20.10.3"  # Replace with your ESP32's IP
        endpoint = f"{esp32_ip}/send_text_to_esp32?text={text}"
        response = requests.get(endpoint)

        if response.status_code == 200:
            print("📡 Successfully sent to ESP32.")
        else:
            print("⚠️ Failed to send to ESP32. Status Code:", response.status_code)

    except sr.UnknownValueError:
        print("❌ Could not understand the audio.")
    except sr.RequestError as e:
        print(f"❌ Speech Recognition service error: {e}")

