/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 18:48:02 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/11 01:04:52 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_args(int argc, char const *argv[]);
void	read_map(t_fdf_map *map, char const *map_path);

/**
 * @brief Checks if a registered key has been pressed every frame and executes
 * an action if so.
 *
 * @param key [bind] The key pressed.
 * @param param [in] Optional param, can be anything.
 */
// void	check_keypress(mlx_key_data_t key, void *param)
// {
	// mlx_t	*mlx = param;

	// if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
		// mlx_close_window(mlx);
// }

// void	show_fps(void *param)
// {
	// t_fdf	*fdf;
	// char	*fps;

	// fdf = param;
	// // Remove previous text
	// mlx_delete_image(fdf->mlx, fdf->fps_img);
	// // Print new text
	// fps = ft_itoa((int)(1000 / fdf->mlx->delta_time));
	// fdf->fps_img = mlx_put_string(fdf->mlx, fps, 10, 10);
	// free(fps);
	// // Attempt to show text in window
	// if (mlx_image_to_window(fdf->mlx, fdf->fps_img, 10, 10) < 0)
		// // If fails, close window
		// mlx_close_window(fdf->mlx);
// }

// void	fdf_close(void *param)
// {
	// t_fdf	*fdf;

	// fdf = (t_fdf *)param;
	// if (fdf || !fdf)
		// ft_putendl("Closing");
// }

/**
 * @brief Main entry point for the Fdf program.
 *
 * Checks and parses command-line arguments and initializes the Fdf application.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 *
 * @return Exit status code.
 */
int	main(
	int argc,
	char const *argv[]
)
{
	t_fdf	fdf;

	check_args(argc, argv);
	ft_bzero(&fdf, sizeof(t_fdf));
	read_map(&fdf.map, argv[1]);
	fdf.map.name = argv[1];
	// fdf.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, true);
	// fdf.map_img = mlx_new_image(fdf.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	// fdf.fps_img = mlx_new_image(fdf.mlx, 200, WINDOW_HEIGHT);
	// if (!fdf.map_img || mlx_image_to_window(fdf.mlx, fdf.map_img, 0, 0) < 0
		// || !fdf.fps_img || mlx_image_to_window(fdf.mlx, fdf.fps_img, 0, 0) < 0)
		// return (EXIT_FAILURE);
	// mlx_loop_hook(fdf.mlx, &show_fps, (void *)&fdf.mlx);
	// mlx_key_hook(fdf.mlx, &check_keypress, (void *)fdf.mlx);
	// mlx_close_hook(fdf.mlx, &fdf_close, (void *)&fdf);
	// mlx_loop(fdf.mlx);
	// mlx_close_window(fdf.mlx);
	// mlx_terminate(fdf.mlx);
	// free(fdf.map.color_map);
	free_height_map(fdf.map.height_map, fdf.map.rows);
	return (EXIT_SUCCESS);
}

/**
 * @brief Checks the validity of command-line arguments for the Fdf program.
 *
 * This function verifies that the correct number of arguments is provided,
 * that the input file has a ".fdf" extension, and that the file can be opened
 * for reading. It prints appropriate error messages to STDERR if any check
 * fails.
 *
 * @param[in] argc The number of command-line arguments.
 * @param[in] argv The array of command-line argument strings.
 */
void	check_args(
	int argc,
	char const *argv[]
)
{
	int	map_fd;

	if (argc != 2)
	{
		ft_eputendl(RED_TEXT"ERROR: Invalid number of arguments"RESET);
		ft_eputendl("Usage: ./fdf <path-to-map>");
		exit(EXIT_FAILURE);
	}
	if (!ft_strrchr(argv[1], '.')
		|| ft_strncmp(".fdf\0", ft_strrchr(argv[1], '.'), 5))
	{
		ft_eputendl(RED_TEXT"ERROR: Invalid file extension"RESET);
		ft_eputendl("File must have "BOLD".fdf"RESET" extension");
		exit(EXIT_FAILURE);
	}
	map_fd = open(argv[1], O_RDONLY);
	if (map_fd == -1)
	{
		ft_eputendl(RED_TEXT"ERROR: Unable to open map"RESET);
		ft_eputendl(strerror(errno));
		exit(errno); // 2 = ENOENT / 13 = EACCES / 24 = EMFILE
	}
	close(map_fd);
}



/**
 * @brief Reads and parses the passed map.
 *
 * This function verifies each line of the passed file and stores it.
 *
 * @param[in,out] map The map struct.
 * @param[in] map_path The path to the map.
 *
 * @return Returns a `t_fdf_map struct` with all the necessary data.
 */
void	read_map(
	t_fdf_map *map,
	char const *map_path
)
{
	char		*row;
	char		**splitted_row;
	int			map_file;

	map_file = open(map_path, O_RDONLY);
	row = get_next_line(map_file);
	while (row && *row)
	{
		splitted_row = ft_split(row, ' ');
		if (!splitted_row)
		{
			ft_eputendl(RED_TEXT"ERROR: malloc"RESET);
			ft_eputendl(strerror(errno));
			close(map_file);
			exit(errno); // ENOMEM
		}
		if (!check_row(splitted_row, map))
		{
			ft_eputendl(RED_TEXT"ERROR: Map is invalid"RESET);
			ft_eputstr("line ");
			ft_eputnbr(map->rows + 1);
			ft_eputchar('\n');
			ft_eputstr(row);
			ft_free_split(splitted_row);
			free(row);
			close(map_file);
			exit(EXIT_FAILURE); // invalid map
		}
		if (!save_row(splitted_row, map))
		{
			ft_eputendl(RED_TEXT"ERROR: malloc"RESET);
			ft_eputendl(strerror(errno));
			ft_free_split(splitted_row);
			free(row);
			close(map_file);
			exit(errno); // ENOMEM
		}
		ft_free_split(splitted_row);
		free(row);
		row = get_next_line(map_file);
	}
	ft_putstr(RESET);
}
