/*
** errors.c for ok in /home/essian_b/rendu/lemipc
**
** Made by Essiane Abel
** Login   <essian_b@epitech.net>
**
** Started on  Thu Mar 24 00:59:50 2016 Essiane Abel
** Last update Thu Mar 24 01:07:22 2016 Essiane Abel
*/

#include <stdio.h>
#include <stdarg.h>

int		perr(char const *msg, ...)
{
  va_list	ap;

  va_start(ap, msg);
  vfprintf(stderr, msg, ap);
  va_end(ap);
  return (1);
}
