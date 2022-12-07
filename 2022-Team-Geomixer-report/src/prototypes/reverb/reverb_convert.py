import soundfile as sf
from numpy.fft import ifft2, fft2
from scipy.io import loadmat
from scipy.stats import norm
from pylab import figure, show
from numpy import (
    asarray, zeros, int16, log, ceil, sort, linspace, asfarray, exp, sqrt,
    int32, abs, convolve, any, sin, pi, sum, arange, ones, mean, std
)
__all__= ['bitSize','bits','unq','fpBest','fpq','fpconv','fpconv_UNSAFE']
import csv

def bitSize(dtype):
  """
  Return number of bits in an integer datatype
  """
  # Note: signed ints have one fewer bits to use
  return asarray([0],dtype).nbytes * 8 + min((dtype(-1),0))

def bits(m):
  """
  Return number of bits needed shift to bring 0.5<m<=1
  """
  if not any(m):
    return 0
  return int(ceil(log(m)/log(2)))

def unq(q,qn):
  """
  Unquantize data from q, given quantization notation qn
  """
  s = qn[1]
  if s>0:
    return asfarray(q)*(1<<s)
  return asfarray(q)/(1<<-s)
def fpBest(x,b):
  """
  Find the best quantization for floats x with with a budget of b bits.
  returns s, such that x / 2**s is ready for integer quantization
  """
  ax = abs(asarray(x))
  m = ax.max()
  # Special case -- array might be all zeros
  if m == 0:
    return 0
  # maximal mag bits
  mx = bits(m)
  return mx-b+1

def fpq(x,s=None,extra=0,dtype=int16):
  """
  Quantize into selected data type as fixed point
  INPUT:
    x -- any -- array of floating point numbers
    s -- shift -- (optional) default auto-scale
    extra -- int -- number of extra bits to reserve
    dtype -- numpy dtype -- (optional) storage type; default int16
  OUTPUT: q,(b,s)
    q -- same as x -- array of dtype numbers
    (b,s) -- (int,int) -- bits and shift
  """
  # Make sure x is a float array
  x = asfarray(x)
  b = bitSize(dtype)
  s = fpBest( x, b-extra )
  # Rescale and quantize
  if s>0:
    return asarray(x / (1<<s), dtype), (b,s)
  return asarray(x * (1<<-s), dtype), (b,s)

data, sr = sf.read('smalldrumroom.wav')
data = data[:,0]
out = fpq(data)

file = open('reverb_ir.csv','w')
writer = csv.writer(file)
out = out[0]
writer.writerow(out)
file.close()
