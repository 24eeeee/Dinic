import time
import matplotlib.pyplot as plt
import sys

if __name__ == "__main__":
    DenseG_V_E = list(map(lambda x: int(x), sys.argv[1:]))
    plt.plot([n for n in range(1, len(sys.argv))], DenseG_V_E)
    plt.grid()
    plt.xlabel("Vecrtices")
    plt.ylabel("Time (mcs.)")
    #plt.legend()
    plt.show()