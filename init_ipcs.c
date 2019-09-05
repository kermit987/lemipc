/*
** init_ipcs.c for ok in /home/essian_b/rendu/lemipc
**
** Made by Essiane Abel
** Login   <essian_b@epitech.net>
**
** Started on  Thu Mar 24 06:06:25 2016 Essiane Abel
** Last update Sun Mar 27 18:54:30 2016 Essiane Abel
*/

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include "lemipc.h"
#include "errors.h"
#include "getters.h"

static char		* const g_colors[] = {
  "\033[1;31m",
  "\033[1;32m",
  "\033[1;33m",
  "\033[1;34m",
  "\033[1;35m",
  "\033[1;36m",
  "\033[1;37m",
};

static void	fill_shm(t_case *map, unsigned *tab)
{
  unsigned	i;
  unsigned	j;

  i = -1;
  while (++i < HEIGHT)
    {
      j = -1;
      while (++j < WIDTH)
	{
	  map[GET(j, i)].y = i;
	  map[GET(j, i)].x = j;
	  map[GET(j, i)].nteam = 0;
	  map[GET(j, i)].true_nteam = 0;
	  map[GET(j, i)].played = 0;
	  map[GET(j, i)].color = NULL;
	}
    }
  tab[0] = 0;
  tab[1] = 0;
}

static int	init_shm(t_infos *infos)
{
  infos->first_player = 1;
  if ((infos->shm_id =
       shmget(infos->common_key, WIDTH * HEIGHT * sizeof(t_case) +
	      (2 * sizeof(unsigned)),
	      IPC_CREAT | IPC_EXCL | SHM_R | SHM_W)) == -1)
    {
      infos->first_player = 0;
      if (errno != EEXIST ||
	  (infos->shm_id =
	   shmget(infos->common_key,
		  WIDTH * HEIGHT * sizeof(t_case) +
		  (2 * sizeof(unsigned)),
		  SHM_R | SHM_W)) == -1)
	return (perr(SHMGET_ERROR, infos->pg_name));
    }
  if ((infos->map = shmat(infos->shm_id, NULL, 0)) == (void *)-1)
    return (perr(SHMAT_ERROR, infos->pg_name));
  infos->players = (unsigned *)((char *)infos->map +
				WIDTH * HEIGHT * sizeof(t_case));
  infos->go = infos->players + 1;
  return (0);
}

static int	init_sem(t_infos *infos)
{
  infos->lock.sem_num = 0;
  infos->lock.sem_flg = 0;
  infos->lock.sem_op = -1;
  infos->unlock.sem_num = 0;
  infos->unlock.sem_flg = 0;
  infos->unlock.sem_op = 1;
  if ((infos->sem_id =
       semget(infos->common_key, 1,
	      IPC_CREAT | IPC_EXCL | SHM_R | SHM_W)) == -1)
    {
      if (errno != EEXIST ||
	  (infos->sem_id = semget(infos->common_key, 1, SHM_R | SHM_W)) == -1)
	return (perr(SEMGET_ERROR, infos->pg_name));
      return (0);
    }
  else if ((semctl(infos->sem_id, 0, SETVAL, 1)) == -1)
    return (perr(SEMCTL_ERROR, infos->pg_name));
  return (0);
}

static int	init_msgq(t_infos *infos)
{
  if ((infos->msg_id =
       msgget(infos->common_key, IPC_CREAT | IPC_EXCL | SHM_R | SHM_W)) == -1)
    {
      if (errno != EEXIST ||
	  (infos->msg_id = msgget(infos->common_key, SHM_R | SHM_W)) == -1)
	return (perr(MSGGET_ERROR, infos->pg_name));
      return (0);
    }
  return (0);
}

int		init_ipcs(t_infos *infos)
{
  if (init_shm(infos) || init_sem(infos) || init_msgq(infos))
    return (1);
  else if (infos->first_player)
    {
      fill_shm(infos->map, infos->players);
      if (pthread_create(&infos->fp_id, NULL, &displayer, infos))
	return (perr(PTC_ERROR, infos->pg_name));
    }
  if (!get_tmates(infos))
    {
      semop(infos->sem_id, &infos->lock, 1);
      infos->me.true_nteam = ++(*infos->players);
      semop(infos->sem_id, &infos->unlock, 1);
      while (!infos->me.rpz || infos->me.rpz == '.')
	infos->me.rpz = rand() % 93 + '!';
      infos->me.color =
	g_colors[rand() % (sizeof(g_colors) / sizeof(g_colors[0]))];
      return (0);
    }
  infos->me.true_nteam = get_mate_infos(infos)->true_nteam;
  infos->me.color = get_mate_infos(infos)->color;
  infos->me.rpz = get_mate_infos(infos)->rpz;
  return (0);
}
