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
# include "string.h"
# include "errno.h"

int
main(void)
{
	FILE *out;
	char line[128];
	char state[128];

	if ((out = popen("/bin/ip eth0", "r")) == NULL)
	{
		fprintf(stderr, "Error popen %d\n", errno);
		exit(1);
	}
	while (fgets(line, 127, out) != NULL)
		if (sscanf(line, "%s", state) == 1
			&& strcmp(state, "UP") == 0)
		{
			fprintf(stdin, "working interface eth0\n");
			pclose(out);
			return (0);
		}
	fprintf(stderr, "Not working interface eth0\n");
	pclose(out);
	return (0);
}