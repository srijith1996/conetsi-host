import matplotlib.pyplot as plt
x = [1,2,3,4,5]
y = [189,111.3,158.6,116.3,150]
plt.xlim([0,7])
plt.ylim([0,200])
plt.plot(x,y,'r')
plt.xlabel('Neighbour Number')
plt.ylabel('Avarage genesis frequency')
plt.show()
