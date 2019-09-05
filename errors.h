/*
** errors.h for ok in /home/essian_b/rendu/lemipc
**
** Made by Essiane Abel
** Login   <essian_b@epitech.net>
**
** Started on  Wed Mar 23 22:10:24 2016 Essiane Abel
** Last update Sun Mar 27 16:13:57 2016 Essiane Abel
*/

#ifndef ERRORS_H_
# define ERRORS_H_

# define INV_TN	"%s: the team number must be a valid integer greater than 0.\n"
# define FTOK_ERROR	"%s: Error while using ftok: %m.\n"
# define USAGE		"Usage: %s PATH TEAM_NUMBER\n"
# define PTC_ERROR	"%s: error while using pthread_create: %m\n"
# define SHMGET_ERROR	"%s: error while using shmget: %m\n"
# define SEMGET_ERROR	"%s: error while using semget: %m\n"
# define SEMCTL_ERROR	"%s: error while using semctl: %m\n"
# define MSGGET_ERROR	"%s: error while using msgget: %m\n"
# define MSGCTL_ERROR	"%s: error while using msgctl: %m\n"
# define MSGSND_ERROR	"%s: error while using msgsnd: %m\n"
# define MSGRCV_ERROR	"%s: error while using msgrcv: %m\n"
# define MALLOC_ERROR	"%s: error while using malloc: %m\n"
# define SHMAT_ERROR	"%s: error while using shmat: %m\n"

int		perr(char const *msg, ...);

#endif /* !ERRORS_H_ */
