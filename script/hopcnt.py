import matplotlib.pyplot as plt
import sys
import numpy as np
 
h = dict()
#dr = sys.argv[1][:sys.argv[1].rfind('/')+1]
with open('hops.txt') as f:
  for line in f:
    cols = line.split()
    h[cols[0]] = cols[1]
#print(h)
d = h.keys()
#print(d)
m = h.values()
#print(m)
plt.plot(m,d,'bo')
plt.xlabel('Number of hops')
plt.ylabel('No of appearance')
plt.show()
