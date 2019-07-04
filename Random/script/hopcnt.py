import matplotlib.pyplot as plt
import sys
import numpy as np
 
h = dict()
k = []
l = []
#dr = sys.argv[1][:sys.argv[1].rfind('/')+1]
with open('ch-len.txt') as f:
  for line in f:
    cols = line.split()
    h[cols[0]] = cols[1]
print(h)
d = h.keys()
print(d)
for i in d:
  l.append(int(i))
print(l)
m = h.values()
print(m)
for j in m: 
  k.append(int(j))
print(k)
plt.xlim([0,6])
plt.ylim([0,2000])
plt.plot(k,l,'ro')
plt.xlabel('Number of hops')
plt.ylabel('No of appearance')
plt.show()
