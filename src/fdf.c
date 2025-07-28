/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 18:48:02 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/28 16:33:32 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	check_args(int argc, char const *argv[], t_fdf *fdf);
static void	read_map(t_fdf *fdf);

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

	errno = 0;
	ft_bzero(&fdf, sizeof(t_fdf));
	check_args(argc, argv, &fdf);
	read_map(&fdf);
	setup_mlx(&fdf);
	scale_and_center_map(&fdf.map, WINDOW_WIDTH, WINDOW_HEIGHT);
	render_map(&fdf.map, fdf.map_img);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
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
		error("Invalid number of arguments", fdf);
	if (ft_strncmp(".fdf\0", ft_strrchr(argv[1], '.'), 5))
		error("Invalid file extension", fdf);
	fdf->map.fd = open(argv[1], O_RDONLY);
	if (fdf->map.fd == -1)
		error("Unable to open map", fdf);
}

/**
 * @brief Reads and parses the passed map.
 *
 * This function verifies each line of the passed file and stores it.
 *
 * @param[in,out] fdf The fdf struct.
 */
static void	process_row(char *row, t_fdf *fdf);

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

static void	process_row(char *row, t_fdf *fdf)
{
	char	**splitted_row;

	splitted_row = ft_split(row, ' ');
	if (!splitted_row)
		error("Out of memory", fdf);
	if (!check_row(splitted_row, &fdf->map))
	{
		ft_free_split(splitted_row);
		error("Map is invalid", fdf);
	}
	if (!save_row(splitted_row, &fdf->map))
	{
		ft_free_split(splitted_row);
		error("Out of memory", fdf);
	}
	ft_free_split(splitted_row);
}
