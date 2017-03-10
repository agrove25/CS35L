randlibhw.so: randlibhw.c
	gcc randlibhw.c -shared -fPIC -mrdrnd -o randlibhw.so

randlibsw.so: randlibsw.c
	gcc randlibsw.c -shared -fPIC -o randlibsw.so

randmain: randmain.c
	gcc -g -c randcpuid.c
	gcc -g -c randmain.c
	gcc randcpuid.o randmain.o -ldl -Wl,-rpath,$(PWD) -o randmain
