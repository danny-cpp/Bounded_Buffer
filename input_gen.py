import random

open("input.txt", 'w').close()
f = open("input.txt", "a")


for i in range(200):
	mode = str()
	if random.randint(0,1) == 0: # 0 for T 1 for S
		mode = "S"
	else:
		mode = "T"


	n = random.randint(1000, 2000)
	res = str(mode) + str(n) + str("\n")
	f.write(res)

f.close()
