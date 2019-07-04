import matplotlib.pyplot as plt
x = [1,2,3,4,5]
y = [282,288.3,311.33,223,192]
plt.xlim([0,7])
plt.ylim([0,320])
plt.plot(x,y,'r')
plt.xlabel('Neighbour Number')
plt.ylabel('Avarage genesis frequency')
plt.show()
