import soundfile as sf
import sounddevice as sd
import scipy as sp
import numpy as np
import math

def fpq(x, s):
    for i in range(0, len(x)):
        x[i] = x[i] / (2**-s)
    fixedpoint = np.zeros(len(x), dtype=np.int16)
    for i in range (0, len(x)):
        fixedpoint[i] = np.int16(x[i])
    bitnum = 15
    return (fixedpoint, (bitnum, s))

x_in, fs = sf.read('guitarSound.wav')
x = fpq(x_in[0:500000, 0], 14)[0]
print(fs)
print(len(x_in))

# all-pass filter: y[n] = (−g·x[n]) + x[n−M] + (g·y[n−M])
apf_g = 0.7
apf_M1 = 441 #1051
apf_M2 = 341 #337
apf_M3 = 225 #113

# frame size
frame_size = 128

def apf(x,M,g,frame_size):
    out = np.zeros(len(x))
    out = np.pad(out, M)
    for fn in range(M, len(x)-frame_size-M, frame_size):
        frame = x[fn:fn+frame_size]
        for i in range(fn, fn+frame_size):
            out[i+M] = (-g*x[i]) + x[i-M] + g*out[i-M]
            #print(f'out loc set: {i+M}')
    return out[M:len(x)+M]

if 1:
    apf1 = apf(x,apf_M1,apf_g,frame_size)
    apf2 = apf(apf1,apf_M2,apf_g,frame_size)
    apf3 = apf(apf2,apf_M3,apf_g,frame_size)

    apf = apf3

# comb filter: y[n] = x[n] + g·y[n−M]
comb_g1 = 0.742
comb_g2 = 0.733
comb_g3 = 0.715
comb_g4 = 0.697
comb_M1 = 1116 #4799
comb_M2 = 1356 #4999
comb_M3 = 1422 #5399
comb_M4 = 1617 #5801

def comb(x,M,g,frame_size):
    out = np.zeros(len(x))
    out = np.pad(out, M)
    for fn in range(M, len(x)-frame_size-M, frame_size):
        for i in range(fn, fn+frame_size):
            out[i+M] = x[i] + g*out[i-M]
            #print(f'out loc set: {i+M}')
    return out[M:len(x)+M]

if 1:
    comb1 = comb(apf,comb_M1,comb_g1,frame_size)
    comb2 = comb(apf,comb_M2,comb_g2,frame_size)
    comb3 = comb(apf,comb_M3,comb_g3,frame_size)
    comb4 = comb(apf,comb_M4,comb_g4,frame_size)

    output = comb1 + comb2 + comb3 + comb4

    print(len(output))
    output = np.asarray(output / (2**18), dtype = np.float32)

    if 1:
        sd.play(output, fs)
        sd.wait()

#lp_b = [5.106995766137598e-05,0.0005106995766137599,0.0022981480947619195,0.006128394919365118,0.010724691108888957,0.012869629330666748,0.010724691108888958,0.0061283949193651184,0.002298148094761919,0.0005106995766137599,5.106995766137598e-05]
#lp_a = [1.0,-4.784004693332918,12.44863681096088,-21.827407539066158,28.036051315161046,-27.256251176350986,20.20268135871092,-11.252325130451128,4.513997359943759,-1.1843277549541773,0.15631234391473633]
lp_b = [2.0760315722441468e-07,2.076031572244147e-06,9.342142075098661e-06,2.491237886692976e-05,4.359666301712708e-05,5.23159956205525e-05,4.359666301712709e-05,2.4912378866929763e-05,9.342142075098661e-06,2.076031572244147e-06,2.0760315722441468e-07]
lp_a = [1.0,-7.77932533337796,28.263301263700697,-62.965617487315086,95.06300798330224,-101.48553351598798,77.51041193419627,-41.79594267181992,15.224669140107599,-3.3831775537411057,0.34842316505056536]


def lpfcomb(x,M,g,frame_size):
    out = np.zeros(len(x))
    out = np.pad(out, M)
    for fn in range(M, len(x)-frame_size-M, frame_size):
        frame = g*out[fn-M:fn+frame_size-M]
        lp = sp.signal.lfilter(lp_b,lp_a,frame)
        out[fn+M:fn+frame_size+M] = np.add(x[fn:fn+frame_size],lp)
    return out[M:len(x)+M]

if 0:
    comb1 = lpfcomb(apf,comb_M1,comb_g1,frame_size)
    comb2 = lpfcomb(apf,comb_M2,comb_g2,frame_size)
    comb3 = lpfcomb(apf,comb_M3,comb_g3,frame_size)
    comb4 = lpfcomb(apf,comb_M4,comb_g4,frame_size)

    output = comb1 + comb2 + comb3 + comb4

    print(len(output))
    output = np.asarray(output / (2**18), dtype = np.float32)

    if 1:
        sd.play(output, fs)
        sd.wait()
