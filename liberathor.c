/*
** liberathor.c for ok in /home/essian_b/rendu/PSU_2015_lemipc
**
** Made by Essiane Abel
** Login   <essian_b@epitech.net>
**
** Started on  Sat Mar 26 14:34:12 2016 Essiane Abel
** Last update Sun Mar 27 23:01:52 2016 Essiane Abel
*/

#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "lemipc.h"
#include "lemipc.h"

void		leave_board(t_infos *infos)
{
  infos->map[GET(infos->me.x, infos->me.y)].played = 0;
  infos->map[GET(infos->me.x, infos->me.y)].color = 0;
  infos->map[GET(infos->me.x, infos->me.y)].rpz = 0;
  infos->map[GET(infos->me.x, infos->me.y)].nteam = 0;
  infos->map[GET(infos->me.x, infos->me.y)].true_nteam = 0;
}

void		free_ressources(t_infos *infos)
{
  shmctl(infos->shm_id, IPC_RMID, NULL);
  semctl(infos->sem_id, 1, IPC_RMID);
  msgctl(infos->msg_id, IPC_RMID, NULL);
  infos->thread_quit = 1;
}
