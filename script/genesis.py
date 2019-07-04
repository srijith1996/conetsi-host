import matplotlib.pyplot as plt
#import sys
#import numpy as np
   
h = dict()
k = []
l = []
#dr = sys.argv[1][:sys.argv[1].rfind('/')+1]
with open('rep-ct.txt') as f:
  for line in f:
    cols = line.split()
    h[cols[0]] = cols[1]
#print(h)
d = h.keys()
for i in d:
  k.append(int(i))  
print(k)
m =h.values()
#print(m)
for x in m:
 n =  int(x[4],16) 
# print(x[4]) 
 print(n)
 l.append(n)
#print(l)
plt.plot(l,k,'ro')
plt.xlabel('Node number')
plt.ylabel('Genesis time')
plt.show()