#include "randcpuid.h"
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <errno.h>
#include <stdbool.h>

static bool
writebytes (unsigned long long x, int nbytes)
{
  int ndigits = nbytes * 2;
  do
    {
      if (putchar ("0123456789abcdef"[x & 0xf]) < 0)
	return false;
      x >>= 4;
      ndigits--;
    }
  while (0 < ndigits);

  return 0 <= putchar ('\n');
}

int
main (int argc, char **argv)
{
  /* Check arguments.  */
  bool valid = false;
  long long nbytes;
  if (argc == 2)
    {
      char *endptr;
      errno = 0;
      nbytes = strtoll (argv[1], &endptr, 10);
      if (errno)
	perror (argv[1]);
      else
	valid = !*endptr && 0 <= nbytes;
    }
  if (!valid)
    {
      fprintf (stderr, "%s: usage: %s NBYTES\n", argv[0], argv[0]);
      return 1;
    }

  /* If there's no work to do, don't worry about which library to use.  */
  if (nbytes == 0)
    return 0;
  
  /* Now that we know we have work to do, arrange to use the
     appropriate library.  */
  unsigned long long (*rand64) (void);
  void* handle;
  
  if (rdrand_supported ())
    {
      handle = dlopen("randlibhw.so", RTLD_NOW);
      if (!handle) {
	fprintf(stderr, "unable to open randlibhw.so: %s", dlerror());
	exit(1);
      }
      printf("HW\n");
    }
  else
    {
      handle = dlopen("randlibsw.so", RTLD_NOW);
      if (!handle) {
	fprintf(stderr, "unable to open randlibsw.so: %s", dlerror());
	exit(1);
      }
      printf("SW\n");
    }

  rand64 = dlsym(handle, "rand64");
  if (dlerror()) {
    fprintf(stderr, "unable to locate function rand64 : %s", dlerror());
    exit(1);
  }
  
  int wordsize = sizeof rand64 ();
  int output_errno = 0;

  do
    {
      unsigned long long x = rand64 ();
      int outbytes = nbytes < wordsize ? nbytes : wordsize;
      if (!writebytes (x, outbytes))
	{
	  output_errno = errno;
	  break;
	}
      nbytes -= outbytes;
    }
  while (0 < nbytes);

  if (fclose (stdout) != 0)
    output_errno = errno;

  if (output_errno)
    {
      errno = output_errno;
      perror ("output");
      if (dlclose(handle) != 0) {
	fprintf(stderr, "unable to close dynamic library: %s", dlerror());
	exit(1);
      }
      return 1;
    }

  
  if (dlclose(handle) != 0) {
    fprintf(stderr, "unable to close dynamic library: %s", dlerror());
    exit(1);
  }
  return 0;
}