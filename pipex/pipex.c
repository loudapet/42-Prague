/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 08:31:37 by plouda            #+#    #+#             */
/*   Updated: 2023/03/15 12:48:46 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, const char **argv)
{
	char	*infile;
	char	*outfile;
	char	*cmd1;
	char	*cmd2;

	if (argc == 5)
	{
		infile = argv[1];
		cmd1 = argv[2];
		cmd2 = argv[3];
		outfile = argv[4];
	}
}
