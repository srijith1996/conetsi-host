import matplotlib.pyplot as plt
x = [2,3]
y = [187,1726]
plt.xlim([0,7])
plt.ylim([0,1800])
plt.plot(x,y,'r')
plt.xlabel('Neighbour Number(1,4 neighbour nodes are not present)')
plt.ylabel('Avarage genesis frequency')
plt.show()
