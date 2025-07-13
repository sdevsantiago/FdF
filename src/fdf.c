/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 18:48:02 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/11 20:19:49 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_args(int argc, char const *argv[]);
void	read_map(t_map *map);

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
	fdf.map.name = argv[1];
	read_map(&fdf.map);
	setup_mlx(&fdf);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx); //! No leaks
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
 *
 * @return Returns a `t_fdf_map struct` with all the necessary data.
 */
void	read_map(
	t_map *map
)
{
	char		*row;
	char		**splitted_row;
	int			map_file;

	map_file = open(map->name, O_RDONLY);
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
