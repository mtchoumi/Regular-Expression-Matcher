#include "libobjdata.h"

void loopdir(char *pathname, char *fval, int lflag, char *str)
{
  struct dirent *de;   
  DIR *dr = opendir(pathname);
  struct stat buf;
  char *ptr;
  char *actualpath;
  
  if (dr == NULL) 
  {
    printf("Could not open current directory" ); 
  }
  
  while ((de = readdir(dr)) != NULL)
  {
    char full_name[256] = { 0 };
    snprintf(full_name, 100, "%s/%s", pathname, de->d_name);
    if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0)
    {
      lstat(full_name, &buf);
      if (S_ISDIR(buf.st_mode))
      {
	loopdir(full_name, fval, lflag, str);
      }
      else if (S_ISLNK(buf.st_mode))
      {
	actualpath = realpath(full_name, NULL);
	lstat(actualpath, &buf);
	if ((S_ISDIR(buf.st_mode) || S_ISLNK(buf.st_mode)) && lflag == 1)
	{
	  if (actualpath != NULL)
	  {
	    loopdir(actualpath, fval, lflag, str);
	  }
	  else
          {
	    perror("realpath");
	  }
	}
	else
	{
	  if (lflag == 1 && fval == NULL)
	  {
	    if (actualpath != NULL)
	    {
	      checkfile(actualpath, full_name, fval, lflag, str);
	    }
	    else
	    {
	      perror("realpath");
	    }
	  }
	  else if (lflag == 1 && fval != NULL && actualpath[strlen(actualpath)-1] == fval[strlen(fval)-1])
	  {
	    if (actualpath != NULL)
	    {
	      checkfile(actualpath, full_name, fval, lflag, str);
	    }
	    else
	    {
	      perror("realpath");
	    }
	  }
	}
      }
      else
      {
	if (fval != NULL && de->d_name[strlen(de->d_name)-1] == fval[strlen(fval)-1])
	{
	  checkfile(full_name, "", fval, lflag, str);
	}
	else if (fval == NULL)
	{
	  checkfile(full_name, "", fval, lflag, str);
	}
      }
    }
  }
  closedir(dr);
}
