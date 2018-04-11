import numpy as np
import matplotlib.pyplot as plt
import sys

inputfile = sys.argv[1]

datos = np.loadtxt(inputfile, delimiter=',')

plt.plot(datos[:,0], datos[:,1], label='Fuerza bruta', linewidth=2)
plt.plot(datos[:,0], datos[:,2], label='Backtracking', linewidth=2)
plt.plot(datos[:,0], datos[:,3], label='Programación dinámica', linewidth=2)
plt.plot(datos[:,0], datos[:,4], label='Fuerza bruta2', linewidth=2)
plt.plot(datos[:,0], datos[:,5], label='Backtracking2', linewidth=2)
plt.plot(datos[:,0], datos[:,6], label='Programación dinámica2', linewidth=2)
plt.yscale('log')
plt.xlabel('Cantidad de elementos', color='black')
plt.ylabel('Tiempo de ejecucion (ms)', color= 'black')
plt.legend(loc=2)
plt.show()