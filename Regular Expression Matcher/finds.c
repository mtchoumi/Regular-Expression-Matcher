#include "libobjdata.h"
  
int main(int argc, char *argv[]) 
{
  char *pathname = NULL;
  char *fval = NULL;
  int lflag = 0;
  char *str = NULL;
  int c;

  opterr = 0;

  while ((c = getopt (argc, argv, "p:f:ls:")) != -1)
  {
    switch (c)
    {
    case 'p':
      pathname = optarg;
      break;
    case 'f':
      fval = optarg;
      break;
    case 'l':
      lflag = 1;
      break;
    case 's':
      str = optarg;
      break;
    case '?':
      if (optopt == 'p')
	printf ("Option -%c requires an argument.\n", optopt);
      if (optopt == 'f')
        printf ("Option -%c requires an argument.\n", optopt);
      if (optopt == 's')
        printf ("Option -%c requires an argument.\n", optopt);
      else if (isprint (optopt))
	printf ("Unknown option `-%c'.\n", optopt);
      else
	printf ("Unknown option character `\\x%x'.\n",optopt);
        return 1;
      default:
        abort ();
    }
  }
  for (int i = 0; i < strlen(str); i++)
  {
    if (isalnum(str[i]) == 0)
    {
      if (str[i] != '?' && str[i] != '.' && str[i] != '*' && str[i] != '(' && str[i] != ')')
      {
	printf("Incorrect expression. \n");
	return 1;
      }
    }
  }

  loopdir(pathname, fval, lflag, str);
  return 0; 
} 
