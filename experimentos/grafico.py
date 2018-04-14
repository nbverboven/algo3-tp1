import numpy as np
import matplotlib.pyplot as plt

datosFB = [ np.loadtxt("exp_fb_"+str(i)+".csv", delimiter=',') for i in range(1,7) ]
datosBT = [ np.loadtxt("exp_bt_"+str(i)+".csv", delimiter=',') for i in range(1,7) ]
datosBTCrec = [ np.loadtxt("exp_BTO_"+str(i)+".csv", delimiter=',') for i in range(1,7) ]
datosPD = [ np.loadtxt("exp_pd_"+str(i)+".csv", delimiter=',') for i in range(1,7) ]

# plot a line, implicitly creating a subplot(111)
# plt.plot([1,2,3])
fig, ax = plt.subplots(nrows=2, ncols=3, sharex=True, sharey=True)#, figsize=(6,6))

# linear
# ax[0,0].subplot(231)
ax[0,0].plot(datosFB[0][:,0], datosFB[0][:,1], 'g', linewidth=2)
ax[0,0].plot(datosBT[0][:,0], datosBT[0][:,1], color='orange', linewidth=2)
ax[0,0].plot(datosPD[0][:,0], datosPD[0][:,1], 'm', linewidth=2)
ax[0,0].set_yscale('log')
ax[0,0].set_ylim(ymin=0)
ax[0,0].set_title('(a)')


# log
# plt.subplot(232)
ax[0,1].plot(datosFB[1][:,0], datosFB[1][:,1], 'g', linewidth=2)
ax[0,1].plot(datosBT[1][:,0], datosBT[1][:,1], color='orange', linewidth=2)
ax[0,1].plot(datosPD[1][:,0], datosPD[1][:,1], 'm', linewidth=2)
ax[0,1].set_yscale('log')
ax[0,1].set_ylim(ymin=0)
ax[0,1].set_title('(b)')


# symmetric log
ax[0,2].plot(datosFB[2][:,0], datosFB[2][:,1], 'g', linewidth=2)
ax[0,2].plot(datosBT[2][:,0], datosBT[2][:,1], color='orange',linewidth=2)
ax[0,2].plot(datosPD[2][:,0], datosPD[2][:,1], 'm', linewidth=2)
ax[0,2].set_yscale('log')
ax[0,2].set_ylim(ymin=0)
ax[0,2].set_title('(c)')


# symmetric log
ax[1,0].plot(datosFB[3][:,0], datosFB[3][:,1], 'g', linewidth=2)
ax[1,0].plot(datosBT[3][:,0], datosBT[3][:,1], color='orange', linewidth=2)
ax[1,0].plot(datosPD[3][:,0], datosPD[3][:,1], 'm', linewidth=2)
ax[1,0].set_yscale('log')
ax[1,0].set_ylim(ymin=0)
ax[1,0].set_title('(d)')


# symmetric log
ax[1,1].plot(datosFB[4][:,0], datosFB[4][:,1], 'g', linewidth=2)
ax[1,1].plot(datosBT[4][:,0], datosBT[4][:,1], color='orange', linewidth=2)
ax[1,1].plot(datosPD[4][:,0], datosPD[4][:,1], 'm', linewidth=2)
ax[1,1].set_yscale('log')
ax[1,1].set_ylim(ymin=0)
ax[1,1].set_title('(e)')


# symmetric log
ax[1,2].plot(datosFB[5][:,0], datosFB[5][:,1], 'g', linewidth=2)
ax[1,2].plot(datosBT[5][:,0], datosBT[5][:,1], color='orange', linewidth=2)
ax[1,2].plot(datosPD[5][:,0], datosPD[5][:,1], 'm', linewidth=2)
ax[1,2].set_yscale('log')
ax[1,2].set_ylim(ymin=0)
ax[1,2].set_title('(f)')

fig.text(0.5, 0, 'Cantidad de elementos', ha='center', fontsize=12)
fig.text(0, 0.5, 'Tiempo de ejecucion (ms)', va='center', rotation='vertical', fontsize=12)
# plt.legend( (a1, a2, a3), ('Fuerza bruta', 'Backtracking', 'Programación dinámica'), 
	                        # loc='upper center', bbox_to_anchor=(0.5, 0), bbox_transform=plt.gcf().transFigure )
# plt.legend()
plt.tight_layout()
plt.show()