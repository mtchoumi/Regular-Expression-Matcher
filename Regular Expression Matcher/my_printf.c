#include "libobjdata.h"

void itoa (char *buf, int base, int d)
{
  char *p = buf;
  char *p1, *p2;
  unsigned long ud = d;
  int divisor = 10;
     
  /* If %d is specified and D is minus, put `-' in the head. */
  if (base == 'd' && d < 0)
    {
      *p++ = '-';
      buf++;
      ud = -d;
    }
  else if (base == 'x')
    divisor = 16;
     
  /* Divide UD by DIVISOR until UD == 0. */
  do
    {
      int remainder = ud % divisor;
     
      *p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
    }
  while (ud /= divisor);
     
  /* Terminate BUF. */
  *p = 0;
     
  /* Reverse BUF. */
  p1 = buf;
  p2 = p - 1;
  while (p1 < p2)
    {
      char tmp = *p1;
      *p1 = *p2;
      *p2 = tmp;
      p1++;
      p2--;
    }
}

void my_printf(char *str, ...)
{
  void *stack_address;
  char *arg[5];
  int i = 0;
  __asm__
  (
   ".intel_syntax noprefix;"
   "mov %0, rsi;"
   "mov %1, rdx;"
   "mov %2, rcx;"
   "mov %3, r8;"
   "mov %4, r9;"
   "mov rax, rbp;"
   "add rax, 16;"
   "mov %5, rax;"
   ".att_syntax prefix"
   : "=r" (arg[0]), "=r" (arg[1]), "=r" (arg[2]), "=r" (arg[3]), "=r" (arg[4]), "=r"(stack_address)
   :
   : "esi", "edx", "ecx", "r8", "r9", "rax"
  );
  void **argp = stack_address;
  while (*str != '\0')
  {
    if (*str == '%')
    {
      if (i < 5)
      {
	if (*(str + 1) == 's')
	{
	  write(1, arg[i], strlen(arg[i]));
	  i++;
	  str += 2;
	}
	else if (*(str + 1) == 'c')
	{
	  char buf[1];
	  buf[0] = arg[i];
	  write(1, buf, 1);
	  i++;
	  str += 2;
	}
	else
	{
	  char buf[11];
	  itoa(buf, *(str + 1), arg[i]);
	  write(1, buf, strlen(buf));
	  i++;
	  str += 2;
	}
      }
      else
      {
	if (*(str + 1) == 's')
	{
	  char *s = *(char**)(argp);
	  write(1, s, strlen(s));
	  argp++;
	  str += 2;
	}
	else if (*(str + 1) == 'c')
	{
	  char c = *(char*)(argp);
	  char buf[1];
	  buf[0] = c;
	  write(1, buf, 1);
	  argp++;
	  str += 2;
	}
	else if (*(str + 1) == 'd')
	{
	  int num = *(int*)(argp);
	  char buf[11];
	  itoa(buf, *(str + 1), arg[i]);
	  write(1, buf, strlen(buf));
	  argp++;
	  str += 2;
	}
	else
	{
	  unsigned int num = *(unsigned int*)(argp);
	  char buf[11];
	  itoa(buf, *(str + 1), arg[i]);
	  write(1, buf, strlen(buf));
	  argp++;
	  str += 2;
	}
      }
    }
    else
    {
      char buf[1];
      buf[0] = *str;
      write(1, buf, 1);
      str++;
    }
  }
}

int main()
{
  my_printf("Hello, %s! Your age is %d and your score is %u. Hex value: %x Char: %c String: %s WT%c \n", "John", 25, 100, 0xDEADBEEF, 'c', "hello", 'f');
  
  return 0;
}
