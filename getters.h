/*
** getters.h for ok in /home/essian_b/rendu/PSU_2015_lemipc
**
** Made by Essiane Abel
** Login   <essian_b@epitech.net>
**
** Started on  Fri Mar 25 19:04:08 2016 Essiane Abel
** Last update Sun Mar 27 16:08:45 2016 Essiane Abel
*/

#ifndef GETTERS_H_
# define GETTERS_H_

unsigned		get_tmates(t_infos const *infos);
unsigned		get_players(t_infos const *infos);
t_case			*get_mate_infos(t_infos const *infos);
unsigned		get_ennemies(t_infos const *infos);
int			get_nearest_ennemy(t_infos *infos);

#endif /* !GETTERS_H_ */
