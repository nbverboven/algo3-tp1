import numpy as np
import matplotlib.pyplot as plt
import sys

inputfile = sys.argv[1]

datos = np.loadtxt(inputfile, delimiter=',')

plt.plot(datos[:,0], datos[:,1], label='Backtracking', linewidth=2)
plt.xlabel('Cantidad de elementos', color='black')
plt.ylabel('Tiempo de ejecucion (ms)', color= 'black')
plt.legend(loc=2)
plt.show()