/*
** appear.c for ok in /home/essian_b/rendu/PSU_2015_lemipc
**
** Made by Essiane Abel
** Login   <essian_b@epitech.net>
**
** Started on  Sat Mar 26 03:58:13 2016 Essiane Abel
** Last update Sun Mar 27 21:43:49 2016 Essiane Abel
*/

#include <time.h>
#include <stdlib.h>
#include <sys/sem.h>
#include "lemipc.h"
#include "errors.h"
#include "getters.h"

int		appear(t_infos *infos)
{
  int		good;
  unsigned	x;
  unsigned	y;

  good = 0;
  if (get_players(infos) == WIDTH * HEIGHT)
    return (perr("Too many players, please wait a bit !\n"));
  srand(time(NULL));
  while (!good)
    {
      x = rand() % WIDTH;
      y = rand() % HEIGHT;
      if (!infos->map[GET(x, y)].nteam)
	good = 1;
    }
  infos->me.x = x;
  infos->me.y = y;
  infos->map[GET(x, y)].nteam = infos->me.nteam;
  infos->map[GET(x, y)].played = 0;
  infos->map[GET(x, y)].rpz = infos->me.rpz;
  infos->map[GET(x, y)].color = infos->me.color;
  return (0);
}
