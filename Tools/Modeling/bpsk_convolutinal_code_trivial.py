import numpy as np
import matplotlib.pyplot as plt

sample_rate     = 1e4
code            = "+++++--++-+-+"
bit_width       = 1e-2
time_of_view    = bit_width * len (code) * 2.
shift           = time_of_view / 2.
time            = np.linspace (0, time_of_view, time_of_view * sample_rate)
carrier         = 5e1

signal          = np.zeros (time.size)

for i in range (time.size):
    if time [i] >= shift and time [i] < shift + bit_width * len (code):
        j = int ( (time [i] - shift) / bit_width)
        phase = 0 if code [j] == '+' else np.pi
        signal [i] += np.sin (2 * np.pi * carrier * time [i] + phase)

signal_i = +signal * np.cos (2 * np.pi * carrier * time);
signal_q = -signal * np.sin (2 * np.pi * carrier * time);

sample_per_bit  = int (bit_width * sample_rate)
for i in range (time.size):
    sum_i = 0.
    sum_q = 0.
    for j in range (len (code) ):
        if i + j * sample_per_bit < time.size:
            m = 1. if code [j] == '+' else -1.
            sum_i += m * signal_i [i + j * sample_per_bit]
            sum_q += m * signal_q [i + j * sample_per_bit]
    signal_i [i] = sum_i
    signal_q [i] = sum_q

magnitude   = np.sqrt (signal_i ** 2 + signal_q ** 2);


fig = plt.figure ()

plt.subplot (2, 1, 1)
plt.plot (time,  signal);
plt.title ("Input signal.")
plt.xlabel ("Time")
plt.ylabel ("Amplitude")

plt.subplot (2, 1, 2)
plt.plot (time, magnitude);
plt.title ("Magnitude of compressed signal.")
plt.xlabel ("Time")
plt.ylabel ("Amplitude")

plt.show()
