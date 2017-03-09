randlibhw.so: randlibhw.c
	gcc -shared -fPIC randlibhw.c -o -mrdrnd randlibhw.so

randlibsw.so: randlibsw.c
	gcc -shared -fPIC randlibsw.c -o randlibsw.so

randmain: randmain.c
	gcc randcpuid.c -c -o randcpuid.o
	gcc randmain.c -c -o randmain.o
	gcc randmain.o randcpuid.o -o randmain  -ldl -Wl,-rpath,$(PWD)
