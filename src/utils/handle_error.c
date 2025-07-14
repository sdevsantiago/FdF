/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sede-san <sede-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 04:39:39 by sede-san          #+#    #+#             */
/*   Updated: 2025/07/13 17:15:32 by sede-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_error(int error)
{
	if (error == ENARGS)
	{
		ft_eputendl(RED_TEXT"ERROR: Invalid number of arguments"RESET);
		ft_eputendl("Usage: ./fdf <path-to-map>");
		error = EINVAL;
	}
	else if (error == EFILEEXT)
	{
		ft_eputendl(RED_TEXT"ERROR: Invalid file extension"RESET);
		ft_eputendl("File must have the "BOLD".fdf"RESET" extension");
		error = EINVAL;
	}
	else if (error == ENOENT || error == EACCES || error == EMFILE)
	{
		ft_eputendl(RED_TEXT"ERROR: Unable to open map"RESET);
		ft_eputendl(strerror(errno));
	}
	else if (error == EINVMAP)
		ft_eputendl(RED_TEXT"ERROR: Map is invalid"RESET);
	else if (error == ENOMEM)
		ft_eputendl(RED_TEXT"ERROR: Out of memory"RESET);
	exit(error);
}
