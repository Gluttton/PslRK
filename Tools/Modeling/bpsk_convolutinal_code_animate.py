import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation


class BPSK (object):
    def __init__ (self, ax):
        self.sample_rate     = 5e3
        self.code            = "+++---+++-------+++-+++--++-+++-++-+-+-++-++-++-+--"
        self.bit_width       = 5e-3
        self.time_of_view    = self.bit_width * len (self.code) * 2.
        self.shift           = self.time_of_view / 2.
        self.shifts          = [self.time_of_view / 6., self.time_of_view / 3., self.time_of_view / 2.]
        self.magnitudes      = [1, 0.75, 1.5]
        self.time            = np.linspace (0, self.time_of_view, self.time_of_view * self.sample_rate)
        self.carrier         = 1e2
        self.noise           = 1.

        self.noncompressed,  = ax.plot ([], [], 'b-')
        self.compressed,     = ax.plot ([], [], 'r-')

        self.ax = ax

        self.ax.set_xlim (0, self.time_of_view)
        self.ax.set_ylim (0, len (self.code) * 2)
        self.ax.grid (False)

        np.random.seed (42)

    def __call__ (self, i):
        signal = np.zeros (self.time.size)
        signal = np.random.normal (0, self.noise, self.time.size)

        for i in range (len (self.shifts) ):
            for j in range (self.time.size):
                if self.time [j] >= self.shifts [i] and self.time [j] < self.shifts [i] + self.bit_width * len (self.code):
                    k = int ( (self.time [j] - self.shifts [i]) / self.bit_width)
                    phase = 0 if self.code [k] == '+' else np.pi
                    signal [j] += self.magnitudes [i] * np.sin (2 * np.pi * self.carrier * self.time [j] + phase)

        signal_i = +signal * np.cos (2 * np.pi * self.carrier * self.time);
        signal_q = -signal * np.sin (2 * np.pi * self.carrier * self.time);

        noncompressed = np.sqrt (signal_i ** 2 + signal_q ** 2);
        
        sample_per_bit  = int (self.bit_width * self.sample_rate)
        for i in range (self.time.size):
            sum_i = 0.
            sum_q = 0.
            for j in range (len (self.code) ):
                if i + j * sample_per_bit < self.time.size:
                    m = 1. if self.code [j] == '+' else -1.
                    sum_i += m * signal_i [i + j * sample_per_bit]
                    sum_q += m * signal_q [i + j * sample_per_bit]
            signal_i [i] = sum_i
            signal_q [i] = sum_q

        compressed = np.sqrt (signal_i ** 2 + signal_q ** 2);        

        self.noncompressed.set_data (self.time, noncompressed)
        self.compressed.set_data    (self.time, compressed)
        return self.noncompressed, self.compressed,


fig, ax = plt.subplots ()
bpsk = BPSK (ax)
anim = FuncAnimation (fig, bpsk, interval = 25, blit = False)
#anim.save ('/home/gluttton/compressed.gif', writer = 'imagemagick', fps = 25)
plt.show ()
