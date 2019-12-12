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

int
my_sys(const char *command)
{
	char *argv[4] = { 0 };
	int ret;
	pid_t pid;

	if ((pid == fork()) < 0)
		return -1;

	if (pid == 0)
	{
		argv[0] = "sh";
		argv[1] = "-c";
		argv[2] = command;
		execv("/bin/sh", argv);
		exit(127);
	}

	while (waitpid(pid, &ret, 0) < 0)
	{
	    if (errno != EINTR)
	    	return (-1);
	}
	return (ret);
}
