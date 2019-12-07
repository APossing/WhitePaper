#!/bin/sh
for j in 0 0.05 0.1 0.15 0.2 
do
	for i in 0 1 2 3
	do
		./out ${i} 100 'd' ${j}
	done
done
