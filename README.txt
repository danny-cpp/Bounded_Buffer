1. Introduction:
	The implementation of a bounded-buffer that then used to schedule tasks from a Producer thread and assign to Consumer threads. This is essentially a finite-capacity-multithreaded-queue. The Producer should hold what is equivalent to a "unique mutex" whereas the Consumers should hold "shared-mutex". However we are implementing the synchronization from scratch. Blocking occurs on threads that wish to write to a full queue or read from an empty queue.


2. Algorithm:
	- This program uses thread-pooling as the distribution algorithm over a bounded buffer. Worker threads are created at the "Scheduler" constructor.
	  Workers are infinite loop that look for jobs over the buffer - which is a multithreaded queue. Workers wait if there is no job. Producer waits if
	  pool is full. Everything ends when EOF detected. Summarized and reported in corresponding log file.


3. Compilation:
	- Change MODE in Makefile line 23. RELEASE/DEBUG. Change -Oflags in line 19/20. Default at -O3 for RELEASE. Binaries stored in /bin/. Execute at main ex.:
	  >> ./bin/prodcon 3 < input.txt



Copyright Danh Nguyen 2021
