#include "../../includes/cub.h"

void free_screen(t_screen *s)
{
	if (!s)
		return ;
	if (s->img.img_ptr)
		mlx_destroy_image(s->mlx_ptr, s->img.img_ptr);
	if (s->win_ptr)
		mlx_destroy_window(s->mlx_ptr, s->win_ptr);
	if (s->mlx_ptr)
	{
		mlx_destroy_display(s->mlx_ptr);
		free(s->mlx_ptr);
	}
}

bool	init_mlx(t_screen *screen, char *title)
{
	screen->mlx_ptr = mlx_init();
	if (!screen->mlx_ptr)
		return (false);
	screen->win_ptr = mlx_new_window(screen->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, title);
	if (!screen->win_ptr)
		return (free_screen(screen), false);
	screen->img.img_ptr = mlx_new_image(screen->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!screen->img.img_ptr)
		return (free_screen(screen), false);
	screen->img.addr = mlx_get_data_addr(screen->img.img_ptr, &screen->img.bpp, &screen->img.line_len, &screen->img.endian);
	if (!screen->img.addr)
		return (free_screen(screen), false);
	return (true);
}