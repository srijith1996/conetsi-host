import matplotlib.pyplot as plt
x = [1,2,3,4,5,6]
y = [114,113.3,115.6,97.2,95.42,112]
plt.xlim([0,7])
plt.ylim([0,125])
plt.plot(x,y,'r')
plt.xlabel('Neighbour Number')
plt.ylabel('Avarage genesis frequency')
plt.show()
