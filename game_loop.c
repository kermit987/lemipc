/*
** game_loop.c for ok in /home/essian_b/rendu/PSU_2015_lemipc
**
** Made by Essiane Abel
** Login   <essian_b@epitech.net>
**
** Started on  Sat Mar 26 18:52:55 2016 Essiane Abel
** Last update Sun Mar 27 22:55:15 2016 Essiane Abel
*/

#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include "lemipc.h"
#include "appear.h"
#include "errors.h"
#include "displayer.h"
#include "move.h"
#include "getters.h"
#include "liberathor.h"

static void	check_turns(t_infos *infos)
{
  t_msg		msg;
  unsigned	i;

  i = 0;
  while (i < WIDTH * HEIGHT)
    {
      if (infos->map[i].nteam && !infos->map[i].played)
	return ;
      ++i;
    }
  i = 0;
  while (i < WIDTH * HEIGHT)
    {
      infos->map[i].played = 0;
      ++i;
    }
  msg.mtype.type = get_type(DISPLAY, 0);
  msg.mtext.nb = 0;
  msgsnd(infos->msg_id, &msg, 4, 0);
  sleep(1);
}

static int	define_strategy(t_infos *infos, t_msg *msg)
{
  int		ret;
  int		errmaroc;

  pthread_mutex_lock(infos->mutex);
  ret = msgrcv(infos->msg_id, msg, 4,
	       get_type(HELP, infos->me.nteam), IPC_NOWAIT);
  errmaroc = errno;
  pthread_mutex_unlock(infos->mutex);
  if (ret == -1)
    return (errmaroc != ENOMSG ?
	    perr(MSGRCV_ERROR, infos->pg_name) - 2 : ATTACK);
  return (HELP);
}

static int	algo(t_infos *infos)
{
  int		strategy;
  int		direction;
  t_msg		msg;

  if ((strategy = define_strategy(infos, &msg)) == -1)
    return (1);
  direction = msg.mtext.nb;
  if (strategy == ATTACK)
    {
      direction = get_nearest_ennemy(infos);
      msg.mtype.type = get_type(HELP, infos->me.nteam);
      msg.mtext.nb = direction;
      msgsnd(infos->msg_id, &msg, 4, 0);
    }
  go_to_direction(infos, direction);
  return (0);
}

static int      where_is_the_displayer(t_infos *infos)
{
  t_msg		msg;
  int		ret;
  int		errmaroc;

  semop(infos->sem_id, &infos->lock, 1);
  infos->map[GET(infos->me.x, infos->me.y)].played = 1;
  if ((get_players(infos) == 1 || !get_ennemies(infos)) ||
      get_tmates(infos) == 1)
    return ((get_players(infos) == 1 || !get_ennemies(infos)) ? 2 : 4);
  else if (get_players(infos) == 2 && get_ennemies(infos) == 1)
    return (3);
  ret = attributions(infos, &msg, &errmaroc, NEW_DISPLAYER);
  msg.mtype.type = get_type(NEW_DISPLAYER_FOUND, 0);
  if ((ret == -1 && errmaroc != ENOMSG))
    return (perr(MSGRCV_ERROR, infos->pg_name));
  if (!infos->first_player)
    return (0);
  if (!errmaroc &&
      (pthread_create(&infos->fp_id, NULL, &displayer, infos) == -1))
    return (perr(PTC_ERROR, infos->pg_name));
  else if (msgsnd(infos->msg_id, &msg, 4, 0) == -1)
    return (perr(MSGSND_ERROR, infos->pg_name));
  return (0);
}

int		game_loop(t_infos *infos)
{
  int		ret;

  while (!*infos->go) ;
  while (42)
    {
      while (infos->map[GET(infos->me.x, infos->me.y)].played)
	if (msgrcv(infos->msg_id, &infos->msg, 4,
		   get_type(FREED_ALL, 0), IPC_NOWAIT)
	    && errno != ENOMSG && (ret = 1))
	  break ;
      if ((ret = where_is_the_displayer(infos)))
	{
	  check_turns(infos);
	  break ;
	}
      algo(infos);
      check_turns(infos);
      ret = dead(infos);
      if (ret)
	break ;
      semop(infos->sem_id, &infos->unlock, 1);
    }
  leave_board(infos);
  semop(infos->sem_id, &infos->unlock, 1);
  return (ret);
}
