import matplotlib.pyplot as plt
import sys
import numpy as np

h = dict()
dr = sys.argv[1][:sys.argv[1].rfind('/')+1]
with open('hops.txt') as f:
  for line in f:
    cols = line.split()
    h[cols[0]] = cols[1]

with open('genesis.txt') as f:
  d = dict()
  for line in f:
    cols = line.split()

    hop_ct = int(h[cols[1]])
    if hop_ct in d.keys():
      d[hop_ct][0] += int(cols[0])
      d[hop_ct][1] += 1
    else:
      d[hop_ct] = [int(cols[0]), 1]

  for key in d.keys():
    d[key] = d[key][0] / d[key][1]

  print d
  i = np.argsort(d.keys())
  d = np.array(d.values())[i]
  print d

  fig, ax = plt.subplots(1)

  ax.plot(range(1, len(d) + 1), d)
  plt.show()
