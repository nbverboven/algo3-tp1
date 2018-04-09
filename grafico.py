import numpy as np
import matplotlib.pyplot as plt
import sys

inputfile = sys.argv[1]

datos = np.loadtxt(inputfile, delimiter=',')

plt.plot(datos[:,0], datos[:,1], 'bo', label='Fuerza bruta', linewidth=2)
plt.plot(datos[:,0], datos[:,1], 'g^', label='Fuerza bruta2', linewidth=2)
#plt.yscale('log')
plt.xlabel('Cantidad de elementos', color='black')
plt.ylabel('Tiempo de ejecucion (ms)', color= 'black')
plt.legend(loc=2)
plt.show()