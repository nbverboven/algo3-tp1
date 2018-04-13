import numpy as np
import matplotlib.pyplot as plt

datosFB = [ np.loadtxt("exp_fb_"+str(i)+".csv", delimiter=',') for i in range(1,7) ]
datosBT = [ np.loadtxt("exp_bt_"+str(i)+".csv", delimiter=',') for i in range(1,7) ]
datosBTCrec = [ np.loadtxt("exp_BTO_"+str(i)+".csv", delimiter=',') for i in range(1,7) ]
datosPD = [ np.loadtxt("exp_pd_"+str(i)+".csv", delimiter=',') for i in range(1,7) ]

plt.plot(datos[:,0], datos[:,1], 'r', label='Fuerza bruta', linewidth=1)
# plt.plot(datos[:,0], datos[:,2], 'g', label='Backtracking', linewidth=1)
# plt.plot(datos[:,0], datos[:,3], label='BacktrackingCopado', linewidth=1)
# plt.plot(datos[:,0], datos[:,4], 'b', label='Programación dinámica', linewidth=1)
plt.plot(datos[:,0], datos[:,2], 'r--', label='Fuerza bruta2', linewidth=1)
# plt.plot(datos[:,0], datos[:,6], 'g--', label='Backtracking2', linewidth=1)
# plt.plot(datos[:,0], datos[:,7],  label='BacktrackingCopado2', linewidth=1)
# plt.plot(datos[:,0], datos[:,8], 'b--', label='Programación dinámica2', linewidth=1)
plt.yscale('log')
plt.xlabel('Cantidad de elementos', color='black')
plt.ylabel('Tiempo de ejecucion (ms)', color= 'black')
# plt.legend(loc=2)
plt.show()