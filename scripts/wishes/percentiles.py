import matplotlib
import matplotlib.pyplot as plt
import numpy
import sys
import time

matplotlib.use('TkAgg')

if __name__ == "__main__":
    if len(sys.argv) < 2:
        pass

    start = time.time()
    freqs = numpy.fromfile("rolls_freq_event_5_standard.bin", dtype=numpy.uint64)
    print("Loaded file in", time.time() - start, "seconds")

    start = time.time()
    uniques, counts = numpy.unique(freqs, return_counts=True)
    print("Computed distribution in", time.time() - start, "seconds")

    plt.bar(uniques, counts)
    plt.show()
