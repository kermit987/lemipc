/*
** displayer.c for ok in /home/essian_b/rendu/lemipc
**
** Made by Essiane Abel
** Login   <essian_b@epitech.net>
**
** Started on  Wed Mar 23 22:26:25 2016 Essiane Abel
** Last update Sun Mar 27 23:05:34 2016 Essiane Abel
*/

#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <string.h>
#include "displayer.h"
#include "lemipc.h"
#include "errors.h"

static int	can_print(t_infos *infos)
{
  int		ret;
  int		errmaroc;
  t_msg		msg;

  while (42)
    {
      if (infos->thread_quit)
	return (0);
      ret = attributions(infos, &msg, &errmaroc, FREE_ALL);
      if ((ret == -1 && errmaroc != ENOMSG) || !errmaroc)
	return (0);
      ret = attributions(infos, &msg, &errmaroc, DISPLAY);
      if ((ret == -1 && errmaroc != ENOMSG) || ret != -1)
	return (ret != -1 ? 1 : perr(MSGRCV_ERROR, infos->pg_name));
    }
}

static void	display(t_infos const *infos, char *screen, unsigned size)
{
  unsigned	i;
  unsigned	j;
  unsigned	idx;

  i = -1;
  idx = 0;
  printf("\e[1;1H\e[2J");
  memset(screen, 0, size);
  while (++i < HEIGHT)
    {
      j = -1;
      while (++j < WIDTH)
	{
	  strcpy(screen + idx, infos->map[GET(j, i)].nteam ?
		 infos->map[GET(j, i)].color : GREY);
	  idx = idx + (sizeof(GREY) - 1);
	  screen[idx++] = infos->map[GET(j, i)].nteam ?
	    infos->map[GET(j, i)].rpz : '.';
	  screen[idx++] = ' ';
	}
      screen[idx++] = '\n';
    }
  strcpy(screen + idx, NRM);
  printf(screen);
}

void		*displayer(void *arg)
{
  t_msg		msg;
  t_infos	*infos;
  char		*zob;
  unsigned	size;

  size = (WIDTH * HEIGHT * (sizeof(YEL) + sizeof(". ") - 2)) +
    (sizeof(NRM) - 1) +
    (HEIGHT * sizeof('\n')) + 1;
  infos = arg;
  if ((zob = malloc(size)) == NULL)
    {
      perr(MALLOC_ERROR, infos->pg_name);
      return (NULL);
    }
  while (can_print(arg) && !infos->thread_quit)
    display(infos, zob, size);
  free(zob);
  infos->thread_quit = 0;
  msg.mtype.type = FREED_ALL;
  msg.mtext.nb = 0;
  msgsnd(infos->msg_id, &msg, 4, 0);
  return (NULL);
}

int		attributions(t_infos *infos, t_msg *msg,
			     int *errmaroc, int type)
{
  int		ret;

  *errmaroc  = 0;
  ret = msgrcv(infos->msg_id, msg, 4, get_type(type, 0), IPC_NOWAIT);
  *errmaroc = errno;
  return (ret);
}
