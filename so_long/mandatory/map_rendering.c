/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rendering.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugi <ahugi@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:43:39 by ahugi             #+#    #+#             */
/*   Updated: 2025/02/10 14:43:41 by ahugi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	render_sprite(t_map *map, t_sprite sprite, int height, int width)
{
	mlx_put_image_to_window (map->mlx, map->win, \
	sprite.xpm_ptr, width * sprite.y, height * sprite.x);
}

void	render_tile(t_map *map, int height, int width)
{
	if (map->map_array[height][width] == '1')
		render_sprite(map, map->wall, height, width);
	if (map->map_array[height][width] == '0')
		render_sprite(map, map->floor, height, width);
	if (map->map_array[height][width] == 'P')
		render_sprite(map, map->player, height, width);
	if (map->map_array[height][width] == 'C')
		render_sprite(map, map->chicken, height, width);
	if (map->map_array[height][width] == 'E')
		render_sprite(map, map->exit, height, width);
}

void	render_collectibles(t_map *map)
{
	char	*coll;
	int		height;
	int		width;

	height = map->win_y / 2 - 15;
	width = map->win_x - 100;
	mlx_string_put(map->mlx, map->win, width, height, GREEN, "collectibles");
	coll = ft_itoa(map->old_collect_count);
	mlx_string_put(map->mlx, map->win, width + 30, height + 15, 0, coll);
	free(coll);
	coll = ft_itoa(map->collect_count);
	mlx_string_put(map->mlx, map->win, width + 30, height + 15, GREEN, coll);
	free(coll);
}

void	render_win_screen(t_map *map)
{
	int	x;
	int	y;

	x = map->win_x / 4;
	y = map->win_y / 2;
	if (!map->win_clear)
	{
		mlx_clear_window(map->mlx, map->win);
		map->win_clear = 1;
	}
	mlx_string_put(map->mlx, map->win, x, y, RED, 
		"Press R to restart or Esc to quit.");
	render_sprite(map, map->won, 0, map->width / 1.2);
}

int	render_map(t_map *map)
{
	int	x;
	int	y;

	if (!map->game_won)
	{
		x = 0;
		while (x < map->height)
		{
			y = 0;
			while (y < map->width)
			{
				render_tile(map, x, y);
				y++;
			}
			x++;
		}
		render_collectibles(map);
	}
	else
		render_win_screen(map);
	return (0);
}
