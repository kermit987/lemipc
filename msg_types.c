/*
** msg_types.c for ok in /home/essian_b/rendu/PSU_2015_lemipc
**
** Made by Essiane Abel
** Login   <essian_b@epitech.net>
**
** Started on  Fri Mar 25 12:09:31 2016 Essiane Abel
** Last update Sat Mar 26 14:55:53 2016 Essiane Abel
*/

#include <pthread.h>
#include <sys/types.h>
#include <sys/sem.h>
#include "lemipc.h"

long		get_type(int type, int team)
{
  union e_mtype	msg;

  msg.infos[MSG] = type;
  msg.infos[TEAM] = team;
  return (msg.type);
}
