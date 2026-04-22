#include "../includes/cub.h"

int main(int ac, char **av)
{
	if (ac != 2)
		return (1);

	// init_data
	t_data *data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (printf("2\n"), 1);
	if (!parse_file(av[1], data))
		return (1);
	// init mlx
	t_screen *screen;

	screen = ft_calloc(1, sizeof(t_screen));
	if (!screen)
		return (printf("2\n"), free_preprocessing_data(data), 1);
	if (!init_mlx(screen, "SUPER FENETRE"))
		return (free_preprocessing_data(data), 1);
	if (!get_all_tex(data, screen))
		return (printf("ERROR MLX\n"), free_screen(screen), free_preprocessing_data(data), 1);
	// draw_tex_lib(screen, data);
	
	printf("BLOBBING\n");
	// build blob;
	void *blob;
	if (!build_blob(data, &blob))
		return (printf("1\n"), false);

	print_blob(blob);

	free(blob);

	// print
	// print_parsing(data);

	free_img_tab(screen->mlx_ptr, data->img_tab, data->textures_len);
	free_screen(screen);
	free_preprocessing_data(data);
	// ownership free
	free(data);
	free(screen);
	return (0);
}