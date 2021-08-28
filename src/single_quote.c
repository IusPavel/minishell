#include "minishell.h"

char	*single_quote(char *input, int *i)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	int		j;

	j = *i;
	while (input[++(*i)])
	{
		if (input[*i] == '\'')
			break ;
	}
	tmp = ft_substr(input, 0, j);
	tmp2 = ft_substr(input, j + 1, *i - j - 1);
	tmp3 = ft_strdup(input + *i + 1);
	tmp2 = ft_strjoin_free(tmp2, tmp3);
	tmp = ft_strjoin_free(tmp, tmp2);
	free(input);
	*i -= 2;
	return (tmp);
}

char	*double_quote(char *input, int *i, char **envp)
{
	(void)envp;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	int		j;

	j = *i;
	while (input[++(*i)])
	{
		if (input[*i] == '\"')
			break ;
		// if (input[*i] == '$')
		// 	input = dollar(input, i, envp);
	}
	tmp = ft_substr(input, 0, j);
	tmp2 = ft_substr(input, j + 1, *i - j - 1);
	tmp3 = ft_strdup(input + *i + 1);
	tmp2 = ft_strjoin_free(tmp2, tmp3);
	tmp = ft_strjoin_free(tmp, tmp2);
	free(input);
	*i -= 2;
	return (tmp);
}

char	*dollar(char *input, int *i, char **envp)
{
	(void)i;
	(void)envp;
	printf("dollar\n");
	return input;
}