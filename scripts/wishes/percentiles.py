import matplotlib
import matplotlib.pyplot as plt
import numpy
import time

matplotlib.use('TkAgg')

if __name__ == "__main__":
    start = time.time()
    freqs = numpy.loadtxt("rolls_freq_standard_5.bin", dtype=numpy.int64)
    print("Loaded file in", time.time() - start, "seconds")

    start = time.time()
    xs = numpy.arange(1001) / 10.0
    pcts = [numpy.percentile(freqs, i) for i in xs]
    print("Computed percentiles in", time.time() - start, "seconds")

    plt.bar(xs, pcts, align='center')
    plt.show()
