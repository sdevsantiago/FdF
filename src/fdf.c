/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 18:48:02 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/29 12:17:29 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	check_args(int argc, char const *argv[], t_fdf *fdf);
static void	read_map(t_fdf *fdf);
static void	process_row(char *row, t_fdf *fdf);

/**
 * @brief Entry point for the FdF application.
 *
 * Initializes the FdF structure, processes command-line arguments,
 * reads the map data, sets up the MLX graphics context, scales and centers
 * the map, renders the map to an image, and enters the main event loop.
 * Cleans up resources before exiting.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @return EXIT_SUCCESS on successful execution.
 */
int	main(
	int argc,
	char const *argv[]
)
{
	t_fdf	fdf;

	errno = 0;
	ft_bzero(&fdf, sizeof(t_fdf));
	check_args(argc, argv, &fdf);
	read_map(&fdf);
	setup_mlx(&fdf);
	scale_and_center_map(&fdf.map, WINDOW_WIDTH, WINDOW_HEIGHT);
	render_map(&fdf.map, fdf.map_img);
	fdf.map.view = ISOMETRIC;
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	free_map(fdf.map.points, fdf.map.rows);
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
 *
 * @note If the file can be read, it will be closed in read_map function.
 */
static void	check_args(
	int argc,
	char const *argv[],
	t_fdf *fdf
)
{
	if (argc != 2)
	{
		errno = ENARGS;
		error("Invalid number of arguments", fdf);
	}
	if (!ft_strchr(argv[1], '.')
		|| ft_strncmp(".fdf\0", ft_strrchr(argv[1], '.'), 5))
	{
		errno = EFILEEXT;
		error("Invalid file extension", fdf);
	}
	fdf->map.fd = open(argv[1], O_RDONLY);
	if (fdf->map.fd == -1)
		error("Unable to open map", fdf);
}

/**
 * @brief Reads a map from a file and processes each row.
 *
 * This function reads lines from a file associated with the given
 * `t_fdf` structure. For each line read, it calls the `process_row`
 * function to handle the data. The function continues reading until
 * there are no more lines to read. After processing, it closes the
 * file descriptor associated with the map.
 *
 * @param fdf A pointer to the `t_fdf` structure containing the map
 *            file descriptor and other relevant data.
 */
static void	read_map(
	t_fdf *fdf
)
{
	char	*row;

	row = get_next_line(fdf->map.fd);
	while (row && *row)
	{
		process_row(row, fdf);
		free(row);
		row = get_next_line(fdf->map.fd);
	}
	close(fdf->map.fd);
	fdf->map.fd = -1;
}

/**
 * @brief Processes a single row of the map.
 *
 * This function takes a row of data as a string, splits it into individual
 * components, and checks if the row is valid. If the row is valid, it saves
 * the data into the map structure. In case of any errors, it handles memory
 * cleanup and reports the error.
 *
 * @param row A string representing a single row of the map data.
 * @param fdf A pointer to the t_fdf structure containing the map and related
 *            data.
 *
 * @note This function will terminate the program with an error message if
 *       memory allocation fails or if the row is invalid.
 */
static void	process_row(char *row, t_fdf *fdf)
{
	char	**splitted_row;

	splitted_row = ft_split(row, ' ');
	if (!splitted_row)
		error("Out of memory", fdf);
	if (!check_row(splitted_row, &fdf->map))
	{
		ft_free_split(splitted_row);
		errno = EINVMAP;
		error("Map is invalid", fdf);
	}
	if (!save_row(splitted_row, &fdf->map))
	{
		ft_free_split(splitted_row);
		error("Out of memory", fdf);
	}
	ft_free_split(splitted_row);
}
