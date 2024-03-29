/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_door.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzi-xian <lzi-xian@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:51:14 by lzi-xian          #+#    #+#             */
/*   Updated: 2023/08/31 13:16:23 by lzi-xian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_remove_line(t_game *game, int px, int py)
{
	t_line	*temp;
	t_line	*hold;

	temp = game->line;
	hold = game->line;
	while (temp && temp->next && temp->next->next)
	{
		if (temp->next->x == px && temp->next->y == py)
		{
			free(hold->next);
			free(hold->next->next);
			free(hold->next->next->next);
			free(hold->next->next->next->next);
			temp->next = temp->next->next->next->next->next;
			break ;
		}
		hold = hold->next;
		temp = temp->next;
	}
}

void	ft_add_line(t_game *game, int px, int py)
{
	ft_node_line1(game, px, py, 2);
	ft_node_line2(game, px, py, 2);
	ft_node_line3(game, px, py, 2);
	ft_node_line4(game, px, py, 2);
}

void	ft_door_line(t_game *game, int px, int py)
{
	if (game->map[px][py])
	{
		if (game->map[px][py] == '2')
		{
			ft_remove_line(game, px, py);
			game->map[px][py] = '3';
		}
		else if (game->map[px][py] == '3')
		{
			ft_add_line(game, px, py);
			game->map[px][py] = '2';
		}
	}
}

void	ft_door_open(t_game *game)
{
	int	l;

	if (game->player.x + 2 < game->map_i)
		ft_door_line(game, game->player.x + 2, game->player.y);
	if (game->player.x + 1 < game->map_i)
		ft_door_line(game, game->player.x + 1, game->player.y);
	if (game->player.x - 2 >= 0)
		ft_door_line(game, game->player.x - 2, game->player.y);
	if (game->player.x - 1 >= 0)
		ft_door_line(game, game->player.x - 1, game->player.y);
	l = ft_strlen(game->map[(int)game->player.x]);
	if (game->player.y + 2 < l)
		ft_door_line(game, game->player.x, game->player.y + 2);
	if (game->player.y + 1 < l)
		ft_door_line(game, game->player.x, game->player.y + 1);
	if (game->player.y - 2 >= 0)
		ft_door_line(game, game->player.x, game->player.y - 2);
	if (game->player.y - 1 >= 0)
		ft_door_line(game, game->player.x, game->player.y - 1);
	ft_change_pos(game, game->player.x, game->player.y);
}
