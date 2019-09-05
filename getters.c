/*
** getters.c for ok in /home/essian_b/rendu/PSU_2015_lemipc
**
** Made by Essiane Abel
** Login   <essian_b@epitech.net>
**
** Started on  Fri Mar 25 18:52:08 2016 Essiane Abel
** Last update Sun Mar 27 23:18:47 2016 Essiane Abel
*/

#include <math.h>
#include <sys/sem.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include "lemipc.h"

t_case			*get_mate_infos(t_infos const *infos)
{
  unsigned		idx;
  unsigned		max;

  max = WIDTH * HEIGHT;
  idx = 0;
  while (idx < max)
    {
      if (infos->map[idx].nteam == infos->me.nteam)
	return (infos->map + idx);
      ++idx;
    }
  return (NULL);
}

unsigned		get_tmates(t_infos const *infos)
{
  unsigned		idx;
  unsigned		mates;
  unsigned		max;

  max = WIDTH * HEIGHT;
  mates = 0;
  idx = 0;
  while (idx < max)
    {
      if (infos->map[idx].nteam == infos->me.nteam)
	++mates;
      ++idx;
    }
  return (mates);
}

unsigned		get_ennemies(t_infos const *infos)
{
  unsigned		idx;
  unsigned		ennemies;
  unsigned		max;

  max = WIDTH * HEIGHT;
  ennemies = 0;
  idx = 0;
  while (idx < max)
    {
      if (infos->map[idx].nteam && infos->map[idx].nteam != infos->me.nteam)
	++ennemies;
      ++idx;
    }
  return (ennemies);
}

unsigned		get_players(t_infos const *infos)
{
  unsigned		idx;
  unsigned		players;
  unsigned		max;

  max = WIDTH * HEIGHT;
  players = 0;
  idx = 0;
  while (idx < max)
    {
      if (infos->map[idx].nteam)
	++players;
      ++idx;
    }
  return (players);
}

int		get_nearest_ennemy(t_infos *infos)
{
  double	x;
  double	y;
  unsigned	i;
  double	dist;
  int		pos;

  i = -1;
  pos = -1;
  dist = -1;
  while (++i < WIDTH * HEIGHT)
    if (infos->map[i].nteam != infos->me.nteam)
      {
	x = (i % WIDTH);
	y = (i / WIDTH);
	if (sqrt(x * x + y * y) < dist || dist == -1)
	  {
	    dist = sqrt(x * x + y * y);
	    pos = i;
	  }
      }
  return (pos);
}
