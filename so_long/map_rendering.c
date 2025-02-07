#include "so_long.h"

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

void	render_moves(t_map *map)
{
	char	*moves;
	int		height;
	int		width;

	height = map->win_y / 4 - 15;
	width = map->win_x - 60;
	mlx_string_put(map->mlx, map->win, width, height, 65280, "moves");
	moves = ft_itoa(map->old_moves);
	mlx_string_put(map->mlx, map->win, width + 10, height + 15, 0, moves);
	free(moves);
	moves = ft_itoa(map->moves);
	mlx_string_put(map->mlx, map->win, width + 10, height + 15, 65280, moves);
	free(moves);
}

void	render_collectibles(t_map *map)
{
	char	*coll;
	int		height;
	int		width;

	height = map->win_y / 2 - 15;
	width = map->win_x - 60;
	mlx_string_put(map->mlx, map->win, width, height, 65280, "collectibles");
	coll = ft_itoa(map->old_collect_count);
	mlx_string_put(map->mlx, map->win, width + 10, height + 15, 0, coll);
	free(coll);
	coll = ft_itoa(map->collect_count);
	mlx_string_put(map->mlx, map->win, width + 10, height + 15, 65280, coll);
	free(coll);
}

int	render_map(t_map *map)
{
	int	x;
	int	y;

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
	render_moves(map);
	render_collectibles(map);
	return (0);
}