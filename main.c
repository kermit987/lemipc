/*
** main.c for ok in /home/essian_b/rendu/lemipc
**
** Made by Essiane Abel
** Login   <essian_b@epitech.net>
**
** Started on  Tue Mar 22 21:56:34 2016 Essiane Abel
** Last update Sun Mar 27 23:11:11 2016 Essiane Abel
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "lemipc.h"
#include "appear.h"
#include "errors.h"
#include "getters.h"
#include "displayer.h"
#include "liberathor.h"

static const char		*go =
  "	GGGGGGGGGGGGG                       !!!\n"
  "     GGG::::::::::::G                      !!:!!\n"
  "   GG:::::::::::::::G                      !:::!\n"
  "  G:::::GGGGGGGG::::G                      !:::!\n"
  " G:::::G       GGGGGG   ooooooooooo        !:::!\n"
  "G:::::G               oo:::::::::::oo      !:::!\n"
  "G:::::G              o:::::::::::::::o     !:::!\n"
  "G:::::G    GGGGGGGGGGo:::::ooooo:::::o     !:::!\n"
  "G:::::G    G::::::::Go::::o     o::::o     !:::!\n"
  "G:::::G    GGGGG::::Go::::o     o::::o     !:::!\n"
  "G:::::G        G::::Go::::o     o::::o     !!:!!\n"
  " G:::::G       G::::Go::::o     o::::o      !!!\n"
  "  G:::::GGGGGGGG::::Go:::::ooooo:::::o\n"
  "   GG:::::::::::::::Go:::::::::::::::o      !!!\n"
  "     GGG::::::GGG:::G oo:::::::::::oo      !!:!!\n"
  "	GGGGGG   GGGG   ooooooooooo         !!!\n";

static pthread_mutex_t	lock_errno = PTHREAD_MUTEX_INITIALIZER;
static char const       * const g_colors[] = {
  "\033[1;31m",
  "\033[1;32m",
  "\033[1;33m",
  "\033[1;34m",
  "\033[1;35m",
  "\033[1;36m",
  "\033[1;37m",
};

static int      getnbr(const char *str)
{
  int		i;
  int		nbr;

  i = 0;
  nbr = 0;
  while (str && str[i] >= '0' && str[i] <= '9')
    nbr = nbr * 10 + (str[i++] - '0');
  return ((!str[0] || str[i]) ? -1 : nbr);
}

static int      get_args(int ac, char * const *av, t_infos *infos)
{
  if (ac != 3)
    return (perr(USAGE, av[0]));
  else if ((infos->common_key = ftok(av[1], PROJ_ID)) == -1)
    return (perr(FTOK_ERROR, av[0]));
  else if ((infos->me.nteam = getnbr(av[2])) < 1)
    return (perr(INV_TN, av[0]));
  infos->pg_name = av[0];
  return (0);
}

static int	quit(t_infos *infos, int retval)
{
  if (infos->map)
    shmdt(infos->map);
  return (retval);
}

static void	intro(t_infos *infos)
{
  unsigned	i;
  unsigned	timer;

  timer = time(NULL) + TIMER;
  while (time(NULL) < timer)
    {
      printf("\e[1;1H\e[2J%sLOAD YOUR PLAYERS, the game will start in"
	     " %lu seconds.%s\n", WHT, timer - time(NULL), NRM);
      usleep(300000);
    }
  while (time(NULL) < timer + 3)
    {
      i = 0;
      printf("\e[1;1H\e[2J");
      while (go[i])
	printf("%s%c%s",
	       g_colors[rand() % (sizeof(g_colors) / sizeof(g_colors[0]))],
	       go[i++], NRM);
      printf("\n");
      usleep(80000);
    }
  semop(infos->sem_id, &infos->lock, 1);
  *infos->go = 1;
  semop(infos->sem_id, &infos->unlock, 1);
}

int		main(int ac, char **av)
{
  int		ret;
  t_infos	infos;

  srand(time(NULL));
  memset(&infos, 0, sizeof(infos));
  infos.mutex = &lock_errno;
  if (get_args(ac, av, &infos) || init_ipcs(&infos) ||
      appear(&infos))
    return (quit(&infos, EXIT_FAILURE));
  if (infos.first_player)
    intro(&infos);
  init_handler(&infos);
  ret = game_loop(&infos);
  if (!get_players(&infos))
    free_ressources(&infos);
  if (infos.first_player && get_players(&infos))
    pthread_join(infos.fp_id, NULL);
  if (ret == 2)
    printf("%sTHE TEAM %d WON THE GAME !%s\n", GRN, infos.me.nteam, NRM);
  else if (ret == 3)
    printf("%sGOT A DRAW!%s\n", GRN, NRM);
  return (quit(&infos, EXIT_SUCCESS));
}
