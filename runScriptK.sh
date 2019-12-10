for j in 64 128 512 1024 2048 4096 8192 16384
do
	for i in 0 1 2 3
	do
		./out ${i} ${j} 'K' 0.2
	done
done
