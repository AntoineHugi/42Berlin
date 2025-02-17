/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugi <ahugi@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:48:16 by ahugi             #+#    #+#             */
/*   Updated: 2025/02/17 14:48:17 by ahugi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*find_command(char *path, char *cmd)
{
	int		i;
	char	**directories;
	char	*buffer;
	char	*cmd_path;

	directories = ft_split(path, ':');
	i = 0;
	while (directories[i])
	{
		buffer = ft_strjoin(directories[i], "/");
		cmd_path = ft_strjoin(buffer, cmd);
		free(buffer);
		if (!access(cmd_path, F_OK))
		{
			free_array(directories);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free_array(directories);
	return (NULL);
}

static char	*fetch_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5) && envp[i][5] != '\0')
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

void	run_cmd(char *cmd, char **envp)
{
	char	*path;
	char	*cmd_path;
	char	**full_cmd;

	if (!cmd || cmd[0] == '\0')
		cmd = "cat";
	path = fetch_path(envp);
	if (!path)
		print_error("path not found in envp");
	full_cmd = ft_split(cmd, ' ');
	if (!full_cmd)
		print_error("problem reading command");
	cmd_path = find_command(path, full_cmd[0]);
	if (!cmd_path)
	{
		free_array((full_cmd));
		free(cmd_path);
		print_error("could not find command.");
	}
	execve(cmd_path, full_cmd, envp);
	free_array((full_cmd));
	free(cmd_path);
	print_error("execve failed.");
}
