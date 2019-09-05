/*
** move.c for ok in /home/essian_b/rendu/PSU_2015_lemipc
**
** Made by Essiane Abel
** Login   <essian_b@epitech.net>
**
** Started on  Sat Mar 26 14:09:15 2016 Essiane Abel
** Last update Sat Mar 26 19:22:39 2016 Essiane Abel
*/

#include <sys/types.h>
#include <sys/sem.h>
#include "lemipc.h"

static void     swap(t_infos *infos, t_case *old, t_case *new)
{
  new->color = infos->me.color;
  new->rpz = infos->me.rpz;
  new->true_nteam = infos->me.true_nteam;
  new->nteam = infos->me.nteam;
  new->played = 1;
  old->color = 0;
  old->rpz = 0;
  old->played = 0;
  old->true_nteam = 0;
  old->nteam = 0;
}

void		go_left(t_infos *infos)
{
  if (infos->me.x == 0 || infos->map[GET(infos->me.x - 1, infos->me.y)].nteam)
    return ;
  swap(infos, infos->map + GET(infos->me.x, infos->me.y),
       infos->map + GET(infos->me.x - 1, infos->me.y));
  --infos->me.x;
}

void		go_right(t_infos *infos)
{
  if (infos->me.x == WIDTH - 1 ||
      infos->map[GET(infos->me.x + 1, infos->me.y)].nteam)
    return ;
  swap(infos, infos->map + GET(infos->me.x, infos->me.y),
       infos->map + GET(infos->me.x + 1, infos->me.y));
  ++infos->me.x;
}

void		go_up(t_infos *infos)
{
  if (infos->me.y == 0 || infos->map[GET(infos->me.x, infos->me.y - 1)].nteam)
    return ;
  swap(infos, infos->map + GET(infos->me.x, infos->me.y),
       infos->map + GET(infos->me.x, infos->me.y - 1));
  --infos->me.y;
}

void		go_down(t_infos *infos)
{
  if (infos->me.y == HEIGHT - 1 ||
      infos->map[GET(infos->me.x, infos->me.y + 1)].nteam)
    return ;
  swap(infos, infos->map + GET(infos->me.x, infos->me.y),
       infos->map + GET(infos->me.x, infos->me.y + 1));
  ++infos->me.y;
}
