/*
** movement.c for ok in /home/essian_b/rendu/PSU_2015_lemipc
**
** Made by Essiane Abel
** Login   <essian_b@epitech.net>
**
** Started on  Sun Mar 27 11:38:59 2016 Essiane Abel
** Last update Sun Mar 27 23:22:12 2016 Essiane Abel
*/

#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include "lemipc.h"
#include "move.h"

void		go_to_direction(t_infos *infos, unsigned direction)
{
  int		x;
  int		y;

  x = direction % WIDTH;
  y = direction / WIDTH;
  if (x > infos->me.x)
    go_right(infos);
  else if (x < infos->me.x)
    go_left(infos);
  else if (y > infos->me.y)
    go_down(infos);
  else if (y < infos->me.y)
    go_up(infos);
}
