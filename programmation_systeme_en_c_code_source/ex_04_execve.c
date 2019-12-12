/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpusel <adpusel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 10:48:07 by adpusel           #+#    #+#             */
/*   Updated: 2017/11/16 12:45:50 by adpusel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
# include "stdlib.h"
# include "unistd.h"
# include "errno.h"

// respect la norme posix pour l'env.
extern char **environ;

int
main(void)
{
	char *argv[] = { "sh", "-c", "echo $SHLVL", NULL };
	fprintf(stdout, "Je lance /bin/sh -c ... \n");
	execve("/bin/sh", argv, environ);
}
