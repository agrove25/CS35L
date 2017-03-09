randlibhw.so: randlibhw.c
	$(CC) randlibhw.c -shared -fPIC -mrdrnd -o randlibhw.so

randlibsw.so: randlibsw.c
	$(CC) randlibsw.c -shared -fPIC -o randlibsw.so

randmain: randmain.c
	$(CC) -g -c randcpuid.c
	$(CC) -g -c randmain.c
	$(CC) $(CFLAGS) randcpuid.o randmain.o -ldl -Wl,-rpath=$(PWD) -o randmain
