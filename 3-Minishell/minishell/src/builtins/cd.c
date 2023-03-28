/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/26 04:06:00 by pdong         #+#    #+#                 */
/*   Updated: 2023/03/26 04:06:01 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	change_pwd(char *var, char *cwd, t_minishell *shell)
{
	char	*str;

	if (!cwd)
	{
		return ;
	}
	str = ft_strjoin(var, cwd);
	free(cwd);
	if (in_env(str, shell->env))
		export_replacevar(shell->env, str);
	else
		shell->env = export_addvar(shell->env, str);
	if (in_env(str, shell->expo))
		export_replacevar(shell->expo, str);
	else
		shell->expo = export_addvar(shell->expo, str);
	free(str);
}

void	ft_cd_home(char *cwd, t_minishell *shell)
{
	if (cwd)
		change_pwd("OLDPWD=", cwd, shell);
	cwd = get_env_var(ft_strdup("~"), shell);
	if (cwd)
	{
		chdir(cwd);
		change_pwd("PWD=", cwd, shell);
	}
}

int	ft_cd(char **arguments, t_minishell *shell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (ft_matrixlen((void **)arguments) > 1)
	{
		if (chdir(arguments[1]) == -1)
		{
			write(STDERR_FILENO, "cd: ", 4);
			write(STDERR_FILENO, arguments[1], ft_strlen(arguments[1]));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
			write(STDERR_FILENO, "\n", 1);
			return (1);
		}
		else
		{
			change_pwd("OLDPWD=", cwd, shell);
			cwd = getcwd(NULL, 0);
			change_pwd("PWD=", cwd, shell);
		}
	}
	else
		ft_cd_home(cwd, shell);
	return (0);
}
