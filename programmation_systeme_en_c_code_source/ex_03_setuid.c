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

# include "stdio.h"
# include "unistd.h"
# include "sys/types.h"

int main()
{
	uid_t uid_reel;
	uid_t uid_eff;

	uid_reel = getuid();
	uid_eff = geteuid();

	fprintf(stdout, "UID-R = %u // uid-e = %u\n", getuid(), geteuid());
	fprintf(stdout, "sutuid = (%d) = %d\n", uid_reel, setuid(uid_reel));
	fprintf(stdout, "UID-R = %u // uid-e = %u\n", getuid(), geteuid());
	fprintf(stdout, "sutuid = (%d) = %d\n", uid_reel, setuid(uid_eff));
	fprintf(stdout, "UID-R = %u // uid-e = %u\n", getuid(), geteuid());

	return (0);
}
