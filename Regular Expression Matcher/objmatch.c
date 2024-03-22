#include "libobjdata.h"

void substring(int index, int len, char *str, char *subs)
{
  int j = 0;
  while (j < len) 
  {
    subs[j] = str[index + j];
    j++;
  }
  subs[j] = '\0';
}

void matchall(char *filename,char *symname, int line_num, char *source, char *test)
{
  int arglen = 0;
  int longarg = 0;
  int bestarg = 0;
  int slen = 0;
  for (int i = 0; i < strlen(source); i++)
  {
    if (source[i] != '?' && source[i] != '*')
    {
      int l = 0;
      if (source[i] == '(')
      {
	i++;
	longarg = 0;
	while (source[i] != ')')
	{
	  longarg++;
	  i++;
	}
      } 
      else
      {
	longarg = 1;
      }
      if (longarg > bestarg)
      {
	bestarg = longarg;
      }
      arglen++;
      slen++;
    }
    else
    {
      slen++;
    }
  }
  char arg[arglen][bestarg+1];
  char sexp[slen][bestarg+1];
  int w = 0;
  int si = 0;
  for (int i = 0; i < strlen(source); i++)
  {
    int l = 0;
    if (source[i] != '?' && source[i] != '*')
    {
      if (source[i] == '(')
      {
	i++;
	while (source[i] != ')') 
	{
	  arg[w][l] = source[i];
	  sexp[si][l] = source[i];
	  i++;
	  l++;
	}
      }
      else
      {
	arg[w][l] = source[i];
	sexp[si][l] = source[i];
	l++;
      }
      arg[w][l] = '\0';
      sexp[si][l] = '\0';
      si++;
      w++;
    }
    else
    {
      sexp[si][l] = source[i];
      sexp[si][l+1] = '\0';
      si++;
    }
  }
  int matrix[slen+1][2];
  matrix[slen][1] = -1;
  matrix[slen][0] = -1;
  for(int i = 0; i < slen; i++)
  {
    if ((i+1 < slen && strcmp("*", sexp[i+1]) == 0) || (strcmp("*", sexp[i]) == 0))
    {
      if (strcmp("*", sexp[i]) != 0)
      {
	matrix[i][1] = i+1;
	if (i+2 <= slen)
	{
	  matrix[i][0] = i+2;
	}
	else
	{
	  matrix[i][0] = 0;
	}
      }
      else
      {
	matrix[i][1] = i;
	matrix[i][0] = i+1;
      }
    }
    else  if ((i+1 < slen && strcmp("?", sexp[i+1]) == 0) || (strcmp("?", sexp[i]) == 0))
    {
      if (strcmp("?", sexp[i]) != 0)
      {
	matrix[i][1] = i+1;
	if (i+2 <= slen)
	{
	  matrix[i][0] = i+2;
	}
	else
	{
	  matrix[i][0] = 0;
	}
      }
      else
      {
	matrix[i][1] = 0;
	matrix[i][0] = i+1;
      }
    }
    else
    {
      if (strcmp(".", sexp[i]) != 0)
      {
	matrix[i][1] = i+1;
	matrix[i][0] = 0;
      }
      else
      {
	matrix[i][1] = i+1;
	matrix[i][0] = i+1;
      }
    }
  }
  
  int prevnode = 0;
  int node = 0;
  int index = 0;
  int sindex = 0;
  char subs[bestarg+1];
  substring(index, strlen(arg[sindex]), test, subs);
  while (matrix[node][(strcmp(subs, arg[sindex]) == 0)] != -1 && index <= strlen(test))
  {
    if (node == 0 && (strcmp("*", sexp[node]) == 0 || strcmp("?", sexp[node]) == 0))
    {
      node = matrix[0][0];
    }
    else if ((node + 1 < slen && strcmp("*", sexp[node+1]) == 0) || strcmp("*", sexp[node]) == 0)
    {
      prevnode = node;
      node = matrix[node][(strcmp(subs, arg[sindex]) == 0)];
      index += (strlen(arg[sindex]) * (strcmp(subs, arg[sindex]) == 0));
      if (node % 2 == 0 && node != 0)
      {
	sindex++;
      }
      else if (node == 0)
      {
	sindex = 0;
	index += (strlen(arg[sindex]));
      }
    }
    else if ((node + 1 < slen && strcmp("?", sexp[node+1]) == 0) || strcmp("?", sexp[node]) == 0)
    {
      prevnode = node;
      node = matrix[node][(strcmp(subs, arg[sindex]) == 0)];
      index += (strlen(arg[sindex]) * (strcmp(subs, arg[sindex]) == 0));
      if (node % 2 == 0 && node != 0)
      {
	sindex++;
      }
      else if (node == 0)
      {
	sindex = 0;
	index += (strlen(arg[sindex]));
      }
    }
    else
    {
      prevnode = node;
      node = matrix[node][(strcmp(subs, arg[sindex]) == 0)];
      if (prevnode + 1 == node)
      {
	index += strlen(arg[sindex]);
	sindex++; 
      }
      else
      {
	if (prevnode == 0)
	{
	  index += strlen(arg[sindex]);
	}
	else if (node == 0 && (strcmp("*", sexp[prevnode-1]) == 0 || strcmp("?", sexp[prevnode-1]) == 0))
	{
	  index += 1;
	}
	sindex = 0;
      }
    }
    substring(index, strlen(arg[sindex]), test, subs);
  }
  
  if (matrix[node][(strcmp(subs, arg[sindex]) == 0)] == -1)
  {
    printf("%s %s %d %s\n",symname, filename, line_num, test);
  }
}
