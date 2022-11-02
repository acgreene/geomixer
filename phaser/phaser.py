import soundfile as sf
import sounddevice as sd
import scipy as sp
import numpy as np

def fpq(x, s):
    for i in range(0, len(x)):
        x[i] = x[i] / (2**-s)
    fixedpoint = np.zeros(len(x), dtype=np.int16)
    for i in range (0, len(x)):
        fixedpoint[i] = np.int16(x[i])
    #fixedpoint = np.uint16(floatval) if x >= 0 else np.int16(floatval)
    #bitnum = 16 if x>= 0 else 15 # This code is for 1.1, for 1.2 we want all the values stored in ints
    bitnum = 15
    return (fixedpoint, (bitnum, s))

data, fs = sf.read('guitarSound.wav')
datafp = fpq(data[:, 0], 14)[0]
datacpy3 = np.zeros(len(datafp))
for i in range(0, len(datafp)):
    datacpy3[i] = datafp[(i-10000) % len(datafp)]
output = data[:,0] + datacpy3
output = np.asarray(output / (2**14), dtype = np.float32)
sd.play(output, fs)
sd.wait()