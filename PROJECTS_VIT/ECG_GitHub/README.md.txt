# Design and Implementation of a Rudimentary Electrocardiogram using Operational Amplifier LM741

This repository contains the design, implementation, and analysis of a rudimentary Electrocardiogram (ECG) circuit built using the LM741 operational amplifier. The project demonstrates the use of analog circuit design techniques to capture and amplify bioelectric signals from the human body.

## Objective
To design a cost-effective ECG circuit that captures and amplifies cardiac signals, serving as an introduction to biomedical instrumentation and analog electronics.

# How It Works
1. Signal Detection: Electrodes detect weak electrical signals from the heart.
2. Amplification: Signals are amplified using the LM741 operational amplifier and a resistor network.
3. Visualization: The amplified signal is processed and displayed using a Python-based visualization tool.

# Components Used
# Analog Components:
-> LM741 Operational Amplifier
-> Resistors:
-> 1.8 kΩ (voltage divider network)
-> 100 kΩ (feedback resistor)
-> 10 MΩ (weak signal detection)
-> 9V Battery
-> ECG Pads and Connectors
-> TRS Auxiliary Cable
-> Solderless Breadboard

# Digital Components:
-> Computer (MacBook Pro used in this project)
-> PyCharm Professional IDE
-> Python Libraries: `numpy`, `matplotlib`, `sounddevice`

# Design Process
1. Assemble the circuit on a solderless breadboard using the LM741 and resistor network.
2. Connect the circuit output to a TRS auxiliary cable for signal transmission.
3. Process the signal using a Python script to generate the ECG waveform.

# Features
-> Gain: Approx. 56.56 (suitable for basic signal detection).
-> Visualizes a 2-second capture of ECG signals.
-> Demonstrates the basics of analog signal processing.

# Limitations
-> Limited signal gain for raw ECG signals.
-> High noise levels due to lack of advanced filtering.
-> Non-real-time data capture (only 2 seconds).

# Results
-> The circuit successfully captured ECG signals with identifiable peaks (systole phase).
-> Noise and low gain affected signal clarity.

# Future Improvements
-> Add digital and analog filtering for noise reduction.
-> Increase gain using advanced operational amplifiers (e.g., AD620).
-> Implement real-time signal acquisition and wireless data transmission.
-> Develop a GUI for live ECG visualization.