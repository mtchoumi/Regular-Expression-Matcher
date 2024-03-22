#include "libobjdata.h"

void checkfile(char *filename, char *symname, char *fval, int lflag, char *str)
{
  FILE * fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  int line_num = 0;
  fp = fopen(filename, "r");
  if (fp == NULL)
  {
    printf("no file");
  }
  char temp[512];
  while(fgets(temp, 512, fp) != NULL)
  {
    for (int i = 0; i < strlen(temp); i++)
    {
      temp[i] = tolower(temp[i]);
    }
    matchall(filename, symname, line_num, str, temp);
    line_num++;
  }

  fclose(fp);
  if (line)
  {
    free(line);
  }
}
