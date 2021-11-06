!!!KNOWN BUGS:
	- Do not remove "prodcon.log". Please re-create this file if deleted. Program has a bug that fails to create a new prodcon.log; however 
	  prodcon.XX.log should not be a problem. Every other aspects should not have any bugs.


1. Algorithm:
	- This program uses thread-pooling as the distribution algorithm over a bounded buffer. Worker threads are created at the "Scheduler" constructor.
	  Workers are infinite loop that look for jobs over the buffer - which is a multithreaded queue. Workers wait if there is no job. Producer waits if
	  pool is full. Everything ends when EOF detected. Summarized and reported in corresponding log file.


2. Compilation:
	- Change MODE in Makefile line 23. RELEASE/DEBUG. Change -Oflags in line 19/20. Default at -O3 for RELEASE. Binaries stored in /bin/. Execute at main ex.:
	  >> ./bin/prodcon 3 < input.txt



Copyright Danh Nguyen 2021