/*
** catch.c for ok in /home/essian_b/rendu/PSU_2015_lemipc
**
** Made by Essiane Abel
** Login   <essian_b@epitech.net>
**
** Started on  Sun Mar 27 15:04:56 2016 Essiane Abel
** Last update Sun Mar 27 22:59:24 2016 Essiane Abel
*/

#include <signal.h>
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

static t_infos		*g_infos;

static void		end_communication()
{
  if (g_infos->map)
    shmdt(g_infos->map);
  free_ressources(g_infos);
  signal(SIGINT, SIG_DFL);
  raise(SIGINT);
}

void			init_handler(t_infos *infos)
{
  g_infos = infos;
  signal(SIGINT, &end_communication);
}
