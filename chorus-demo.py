import sounddevice as sd
import soundfile as sf
import csv
import numpy
import scipy
from scipy import signal

data, samplingRate = sf.read('mixed_sound.wav')
data1 = numpy.zeros(len(data))
data2 = numpy.zeros(len(data))
data3 = numpy.zeros(len(data))
data4 = numpy.zeros(len(data))
for i in range(len(data)):
    data1[i] = data[i-1024]
    data2[i] = data[i-2048]
    data3[i] = data[i-256]
    data4[i] = data[i-512]
newData = data1+2*data2+data3+data4
sd.play(newData, samplingRate)
sd.wait()
