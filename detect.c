/*
** detect.c for ok in /home/essian_b/rendu/PSU_2015_lemipc
**
** Made by Essiane Abel
** Login   <essian_b@epitech.net>
**
** Started on  Sat Mar 26 16:02:57 2016 Essiane Abel
** Last update Sun Mar 27 23:40:44 2016 Essiane Abel
*/

#include <sys/sem.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#include "lemipc.h"

static int	check_oppo(unsigned *oppo)
{
  int		i;
  unsigned	j;

  i = -1;
  oppo[4] = 0;
  while (++i < 8)
    {
      if (!oppo[i])
	continue ;
      j = i;
      while (++j < 9)
	if (oppo[i] == oppo[j])
	  return (oppo[i]);
    }
  return (0);
}

int		dead(t_infos *infos)
{
  int		x;
  int		y;
  unsigned	i;
  unsigned	oppo[9];

  y = infos->me.y - 2;
  i = -1;
  memset(oppo, 0, sizeof(oppo));
  while (++y < infos->me.y + 2 && y < HEIGHT)
    {
      if (y < 0 && (i = i + 3))
	continue ;
      x = infos->me.x - 2;
      while (++x < infos->me.x + 2 && x < WIDTH)
	{
	  ++i;
	  if (x < 0)
	    continue ;
	  if (infos->map[GET(x, y)].nteam != infos->me.nteam)
	    oppo[i] = infos->map[GET(x, y)].nteam;
	}
    }
  return (check_oppo(oppo));
}
