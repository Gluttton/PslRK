import numpy as np
import matplotlib.pyplot as plt
import scipy.signal as sig

time_of_view            = 7e-5;
dynamic_range           = 1.;
carrier_frequency       = 30e6;
sampling_rate           = 120e6;
sample_number           = time_of_view * sampling_rate;
sampling_time           = np.linspace (0, time_of_view, sample_number);

pulse_code              = "+++++--++-+-+"
pulse_code_length       = len (pulse_code);
pulse_width             = 2e-6;
pulse_amplitude         = 1.;
pulse_partial_length    = 1; # bit duration
pulse_shift             = pulse_width * (0.5 + pulse_code_length * pulse_partial_length);
pulse_period            = pulse_width * pulse_code_length * pulse_partial_length * 3;

quantizing_bits         = 8;
quantizing_levels       = 2 ** quantizing_bits / 2;
quantizing_step         = dynamic_range / quantizing_levels;


sampling_signal         = np.zeros (sampling_time.size);
sampling_signal         = np.random.normal (0, 0.1, sampling_time.size);

for i in range (sampling_time.size):
    t = sampling_time [i] % pulse_period
    if t >= pulse_shift and t < pulse_shift + pulse_width * pulse_partial_length * pulse_code_length:
        s = int (np.trunc ( (t - pulse_shift) / (pulse_width * pulse_partial_length) ) )
        phase = 0. if pulse_code [s] == '+' else np.pi
        sampling_signal [i] += pulse_amplitude * np.cos (2 * np.pi * (carrier_frequency) * sampling_time [i] + phase)


quantizing_signal       = np.round (sampling_signal / quantizing_step) * quantizing_step;

signal_i = +quantizing_signal * np.cos (2 * np.pi * carrier_frequency * sampling_time);
signal_q = -quantizing_signal * np.sin (2 * np.pi * carrier_frequency * sampling_time);


decimation_factor       = [3, 4, 4, 5]
decimation_rate         = np.prod (np.array (decimation_factor) )
decimated_time          = sampling_time
decimated_signal_i      = signal_i
decimated_signal_q      = signal_q

for i in range (len (decimation_factor) ):
    decimated_time      = decimated_time [0::decimation_factor [i] ];
    decimated_signal_i  = sig.decimate (decimated_signal_i, decimation_factor [i], 1, ftype="fir", axis=-1);
    decimated_signal_q  = sig.decimate (decimated_signal_q, decimation_factor [i], 1, ftype="fir", axis=-1);


sample_per_bit          = int (pulse_width * sampling_rate / decimation_rate)
for i in range (decimated_time.size):
    s_i = 0.
    s_q = 0.
    for j in range (pulse_code_length):
        if i + j * sample_per_bit < decimated_time.size:
            m = 1. if pulse_code [j] == '+' else -1.
            s_i += m * decimated_signal_i [i + j * sample_per_bit]
            s_q += m * decimated_signal_q [i + j * sample_per_bit]
    decimated_signal_i [i] = s_i
    decimated_signal_q [i] = s_q


signal_magnitude        = np.sqrt (decimated_signal_i ** 2 + decimated_signal_q ** 2);


fig = plt.figure ()

plt.subplot (2, 1, 1)
plt.plot (sampling_time,  quantizing_signal);
plt.title ("Input signal.")
plt.xlabel ("Time")
plt.ylabel ("Amplitude")

plt.subplot (2, 1, 2)
plt.plot (decimated_time, signal_magnitude);
plt.title ("Magnitude of compressed signal.")
plt.xlabel ("Time")
plt.ylabel ("Amplitude")

plt.show()
