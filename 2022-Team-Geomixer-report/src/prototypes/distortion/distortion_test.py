import numpy as np
import sounddevice as sd
import matplotlib.pyplot as plt
from scipy.io import wavfile


samplerate, data = wavfile.read('mixed_sound.wav')
max_ = max(abs(data))
data = data/max_
new_data = []

for x in range (len(data)):
    if abs(data[x])<(1/3):
        new_val = data[x]*2
        new_data.append(new_val*max_)
    elif abs(data[x])>1/3 and abs(data[x])<2/3:
        if np.sign(data[x]) > 0:
            new_val = (3-((2-3*data[x])**2))/3
            new_data.append(new_val*max_)
        elif np.sign(data[x]) < 0:
            new_val = -(3-((2+3*data[x])**2))/3
            new_data.append(new_val*max_)
    else:
        new_val = np.sign(data[x])*1
        new_data.append(new_val*max_)

data = data*max_
plt.plot(data)
plt.title("original data")
plt.xlabel("Sample index")
plt.ylabel("Amplitude")
plt.show()

plt.plot(new_data)
plt.title("new data")
plt.xlabel("Sample index")
plt.ylabel("Amplitude")
plt.show()


sd.play(np.int16(new_data), samplerate)
wavfile.write("file.wav", samplerate, np.int16(new_data))
