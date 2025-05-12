import sounddevice as sd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
# Parameters
SAMPLING_RATE = 44100 # Audio sampling rate (Hz)
DURATION = 2 # Duration for capturing (seconds)
BUFFER_SIZE = 1024 # Size of each buffer for live plotting AMPLIFICATION_FACTOR = 100 # Increase to amplify weak signals further AUDIO_DEVICE_INDEX = None # Default input device
# Create figure and axis for plotting
fig, ax = plt.subplots()
x_data = np.arange(0, BUFFER_SIZE) / SAMPLING_RATE # Time axis (seconds) y_data = np.zeros(BUFFER_SIZE)
line, = ax.plot(x_data, y_data)
# Initialize plot settings
ax.set_xlim(0, BUFFER_SIZE / SAMPLING_RATE) ax.set_ylim(-1, 1) # Initial Y-axis limits; will auto-adjust ax.set_title("Real-Time ECG Signal (Amplified)") ax.set_xlabel("Time (s)")
ax.set_ylabel("Amplitude")
# Function to update the plot
def update_plot(frame):
global y_data
# Capture audio data from input device
audio_chunk = sd.rec(BUFFER_SIZE, samplerate=SAMPLING_RATE,
channels=1, dtype='float32', device=AUDIO_DEVICE_INDEX) sd.wait() # Wait until recording is complete
# Amplify the signal
y_data = audio_chunk.flatten() * AMPLIFICATION_FACTOR line.set_ydata(y_data) # Update line with new data
# Dynamically adjust the y-limits based on data
ax.set_ylim(np.min(y_data) - 0.1, np.max(y_data) + 0.1)
# Debug: print a small portion of the data to confirm signal
print("Audio chunk data (first 10 samples):", y_data[:10]) return line,
# Run animation with frame caching turned off
ani = FuncAnimation(fig, update_plot, blit=True, interval=50, cache_frame_data=False)
plt.show()
