/* for printf() */
#include <stdio.h>
/* for atoi() */
#include <stdlib.h>
/* for write() */
#include <unistd.h>

/* exit code if failure */
#define FAIL 84
/* Exit code if OK */
#define SUCCESS 0

/* this program name (argv[0] */
char *progname;


/* Return the length of a string s passed as argucment.
   function is recursive to keep it simple */
size_t
length(char * s)
{
  if (s == NULL) return 0;	/* length of a nnull pointer is 0 */
  if (*s == '\0') return 0;	/* length of a null string is 0 */
  return 1 + length(s + 1);	/* else length is 1 + the length of
				   the string without it's first
				   character */
}


/* Error handling, write string on stderr */
void
err(char *s)
{
  int len, ret;

  len = length(s);		/* calculate length of string */
  if (len == 0) return;		/* if 0, print nothing */

  ret = write(2, s, len);	/* write s to stderr */
  if (ret != len)		/* check if write was a sucess */
    {
      s = "write error\n";	/* if not */
      write(2, s, length(s));	/* write error message */
      exit(FAIL);		/* and exit */
    }
}


/* print usage string to stderr */
void
usage()
{
  err("Usage: ");
  err(progname);
  err(" first-number second-number\n");
  exit(FAIL);
}


int
main(int ac, char **av)
{
  int first, second;		/* first and second parameters as int's */

  
  progname = av[0];		/* save program name */
  ac--, av++;			/* adjust count & pointer to start at 0 */

  if (ac < 2) usage();		/* Print usage and exit if less than 2 args */
  first = (int)atoi(av[0]);	/* Convert first arg */
  second = (int)atoi(av[1]);	/* Convert second */

  if (!(second >= first))	/* if second is not >= to first*/
    {
      err("Error: the second parameter must be greater than the first one\n");
      exit(FAIL);
    }

  /* loop on the interval */
  for (int i = first; i <= second; i++)
    {
      if (!(i & 1) && i % 3 == 0)
	{
	  printf("FuzzBozz\n");
	  continue;
	}

      if (!(i & 1))		/* if odd last bit is 1 (so we !) */
	{
	  printf("Fuzz\n");	/* it's even (last bit is 0) */
	  continue;		/* continue loop */
	}

      if (i % 3 == 0)		/* reminder of / 3 is 0 ? */
	{
	  printf("Bozz\n");	/* yes */
	  continue;		/* continue loop */
	}

      printf("%d\n", i);	/* otherwise print the number */
    }
  exit(SUCCESS);		/* Exit 0 */
}
