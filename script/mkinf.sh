#!/bin/bash

grep "hops" $1 | awk '{print $NF}' | sort | uniq -c > hops.txt
grep "Node" $1 | awk '{print $NF}' | sort | uniq -c > rep-ct.txt
grep "UDP" -A3 $1 | grep "Node" | awk '{print $NF}' | sort | uniq -c > gen-rep-ct.txt


grep Entries $1 -B5 | grep Node | awk '{print $NF}' | sort | uniq -c > genesis.txt
python count.py $1

