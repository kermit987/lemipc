/*
** lemipc.h for ok in /home/essian_b/rendu/lemipc
**
** Made by Essiane Abel
** Login   <essian_b@epitech.net>
**
** Started on  Wed Mar 23 02:28:19 2016 Essiane Abel
** Last update Sun Mar 27 23:15:13 2016 Essiane Abel
*/

#ifndef LEMIPC_H_
# define LEMIPC_H_

# define WIDTH		(10)
# define HEIGHT		(10)
# define PROJ_ID	('L')
# define GET(x, y)	((y) * WIDTH + (x))
# define TIMER		(10)


struct			s_case
{
  int			x;
  int			y;
  int			nteam;
  int			true_nteam;
  char			*color;
  int			played;
  char			rpz;
};

typedef struct s_case	t_case;

# define TEAM		(0)
# define MSG		(1)

union		e_mtype
{
  long		type;
  int		infos[2];
};

union		e_mtext
{
  char		tab[4];
  unsigned      nb;
};

enum		e_msgtypes
  {
    FREE_ALL = 1,
    FREED_ALL,
    DISPLAY,
    NEW_DISPLAYER,
    NEW_DISPLAYER_FOUND,
    HELP,
    ATTACK
  };

typedef struct		s_msg
{
  union e_mtype		mtype;
  union e_mtext		mtext;
}			t_msg;

typedef struct		s_infos
{
  struct sembuf		lock;
  struct sembuf		unlock;
  pthread_t		fp_id;
  t_msg			msg;
  char			*pg_name;
  pthread_mutex_t	*mutex;
  t_case		*map;
  unsigned		*players;
  unsigned		*go;
  t_case		me;
  key_t			common_key;
  int			shm_id;
  int			sem_id;
  int			msg_id;
  int			first_player;
  int			thread_quit;
}			t_infos;

void			*displayer(void *);
int			init_ipcs(t_infos *);
long			get_type(int, int);
int			dead(t_infos *);
int			game_loop(t_infos *);
void			go_to_direction(t_infos *, unsigned);
void			init_handler(t_infos *);
int			attributions(t_infos *, t_msg *, int *, int);
void			init_handler(t_infos *infos);

#endif /* !LEMIPC_H_ */
