import matplotlib.pyplot as plt
x = [1,2,3,5]
y = [208,470.3,467.3,326]
plt.xlim([0,7])
plt.ylim([0,500])
plt.plot(x,y,'r')
plt.xlabel('Neighbour Number(4 neighbour node is not present)')
plt.ylabel('Avarage genesis frequency')
plt.show()
