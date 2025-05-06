#include "minishell.h"

typedef struct s_teraform
{
	char	*left;
	char	*right;
	char	*token;
	char	**sp;
	int		ljoin;
	int		rjoin;
	int		inquote;
	size_t	rlen;
} t_teraform;

static char	*ft_get_token(char *str)
{
	size_t i;

	i = 1;
	if (str[i] != '?')
	{
		while (ft_isalpha(str[i]) || str[i] == '_')
			i++;
	}
	else
		i = 2;
	return (ft_substr(str, 0, i));
}

static int	ft_set_terraform(t_teraform *teraform, char *begin_str, char *str)
{
	size_t blen;

	if (begin_str != str)
	{
		teraform->left = ft_substr(begin_str, 0, str - begin_str);
		if (teraform->left == NULL)
			return (FAIL);
	}
	teraform->token = ft_get_token(str);
	if (teraform->token == NULL)
		return (FAIL);
	blen = strlen(teraform->token);
	if (str[blen])
	{
		teraform->right = ft_substr(str + blen, 0, ft_strlen(str + blen));
		if (teraform->right == NULL)
			return (FAIL);
	}
	ft_printf("L:%s\n", teraform->left);
	ft_printf("R:%s\n", teraform->right);
	ft_printf("T:%s\n", teraform->token);
	return (SUCCESS);
}

static char *ft_research_token(char *token, t_data *data)
{
	if (token[1] == '?')
		return (ft_itoa(data->exit_program));
	return (ft_env_tab_get_null(data->env->envp, token + 1));
}

static int	ft_set_expand(t_teraform *teraform, t_data *data)
{
	char	*buffer;

	buffer = ft_research_token(teraform->token, data);
	if (ft_strlen(buffer) >= 1)
	{
		if (ft_strchr("\t\v\n\r ", buffer[0]))
			teraform->ljoin = FALSE;
		if (ft_strchr("\t\v\n\r ", buffer[ft_strlen(buffer) - 1]))
			teraform->rjoin = FALSE;
	}
	if (teraform->inquote || buffer == NULL)
	{
		teraform->sp = malloc(sizeof(char *) * 2);
		if (!teraform->sp)
			return (free(buffer), FAIL);
		teraform->sp[0] = buffer;
		teraform->sp[1] = NULL;
	}
	else
		teraform->sp = the_mastermind(buffer);
	if (!teraform->sp)
		return (FAIL);
	return (SUCCESS);
}

static void	ft_free_teraform(t_teraform *teraform)
{
	if (teraform->left)
		free(teraform->left);
	if (teraform->right)
		free(teraform->right);
	if (teraform->token)
		free(teraform->token);
	if (teraform->sp)
		ft_tab_free(teraform->sp);
}

#define LEFT 0
#define RIGHT 1

static int	joint_expand_strs(char **tabelement, char **jstr, int pos)
{
	char *newstr;
	size_t l_tab;
	size_t l_jstr;

	l_tab = ft_strlen(*tabelement);
	l_jstr = ft_strlen(*jstr);
	newstr = malloc(l_tab + l_jstr + 1);
	if (newstr == NULL)
		return (FAIL);
	newstr[l_tab + l_jstr] = '\0';
	if (pos == LEFT)
	{
		ft_strlcpy(newstr, *jstr, l_jstr + 1);
		ft_strlcpy(newstr + l_jstr, *tabelement, l_tab + 1);
	}
	else
	{
		ft_strlcpy(newstr, *tabelement, l_tab + 1);
		ft_strlcpy(newstr + l_tab, *jstr, l_jstr + 1);
	}
	free(*tabelement);
	free(*jstr);
	*jstr = NULL;
	*tabelement = newstr;
	return (SUCCESS);
}

char	*join_expand(t_list **lst, t_teraform *teraform, char *str)
{
	teraform->rlen = strlen(teraform->right);
	if (teraform->ljoin == TRUE)
		joint_expand_strs(teraform->sp, &teraform->left, LEFT);
	if (teraform->rjoin == TRUE)
		joint_expand_strs(teraform->sp + ft_tab_len(teraform->sp) - 1, &teraform->right, RIGHT);
	(void)lst;
	return (str + 1);
}

char	*ft_expend_teraform(t_data *data, t_list **lst, char *str, int inquote)
{
	t_teraform	teraform;
	char		*ret;

	ft_bzero(&teraform, sizeof(t_teraform));
	teraform.inquote = inquote;
	teraform.rjoin = TRUE;
	teraform.ljoin = TRUE;
	ret = str;
	if (ft_set_terraform(&teraform, ((t_word *)(*lst)->content)->word, str) == SUCCESS && ft_set_expand(&teraform, data) == SUCCESS)
		//ret = join_expand(lst, &teraform, str);

	ft_printf("%w\n", teraform.sp);
	ft_free_teraform(&teraform);
	return (ret); // return the same *str if problem
}
