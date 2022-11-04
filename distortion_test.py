import numpy as np
import sounddevice as sd
import matplotlib.pyplot as plt
from scipy.io import wavfile


samplerate, data = wavfile.read('mixed_sound.wav')

print("Argmax is = ",np.argmax(data),"\n")
max_ = np.argmax(data)
data = data/max_
plt.plot(data)
plt.title("original data")
plt.xlabel("Sample index")
plt.ylabel("Amplitude")
plt.show()

saw = -(data%2)+1
saw = saw*max_
plt.plot(saw)
plt.title("sawtooth data")
plt.xlabel("Sample index")
plt.ylabel("Amplitude")
plt.show()

#data = np.abs((data)%2-1)*2-1
data = np.where((data)%2<1,-1,1)
data = data*max_


plt.plot(data)
plt.title("distorted data")
plt.xlabel("Sample index")
plt.ylabel("Amplitude")
plt.show()

sd.play(np.int16(saw), samplerate)
wavfile.write("file.wav", samplerate, np.int16(saw))


#%%
