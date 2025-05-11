#include "minishell.h"

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

void	join_add_node(t_list **begin, t_list *add)
{
	if (add)
	{
		if (*begin)
			ft_lstlast(*begin)->next = add;
		else
			*begin = add;
	}
}

int	join_create_set_node(t_list **begin, char *buffer, int type)
{
	t_list	*newnode;

	if (buffer == NULL)
		return (FAIL);
	newnode = ft_word_lst_make_join(buffer, type);
	if (newnode == NULL)
	{
		free(buffer);
		return (FAIL);
	}
	join_add_node(begin, newnode);
	return (SUCCESS);
}

int	join_expand_left_node(t_list **begin, t_teraform *teraform, int type)
{
	char	*buffer;

	if (teraform->left)
	{
		if (teraform->sp[0] && teraform->ljoin)
			buffer = ft_strjoin(teraform->left, teraform->sp[0]);
		else
			buffer = ft_strdup(teraform->left);
		return (join_create_set_node(begin, buffer, type));
	}
	return (SUCCESS);
}

int	join_expand_right_node(t_list **begin, t_teraform *teraform, int type, char **newpos)
{
	char	*buffer;
	t_word	*last;
	size_t	len;

	if (teraform->right)
	{
		if (teraform->rjoin && *begin)
		{
			last = ft_lstlast(*begin)->content;
			len = ft_strlen(last->word);
			buffer = ft_strjoin(last->word, teraform->right);
			if (buffer == NULL)
				return (FAIL);
			free(last->word);
			last->word = buffer;
			*newpos = buffer + len;
		}
		else
		{
			if (join_create_set_node(begin, ft_strdup(teraform->right), type))	
				return (FAIL);
			*newpos = ((t_word *)ft_lstlast(*begin)->content)->word;
		}
	}
	return (SUCCESS);
}

int	join_middle(t_list **begin, t_teraform *teraform, int type)
{
	size_t	i;

	i = 0;
	if (teraform->sp[i])
	{
		if (teraform->left && teraform->ljoin)
			i++;
		while (teraform->sp[i])
		{
			if (join_create_set_node(begin, ft_strdup(teraform->sp[i]), type) == FAIL)
				return (FAIL);
			i++;
		}
	}
	return (SUCCESS);
}

char	*join_nodes(t_list **lst, t_list *newlst, char *newpos)
{
	t_word	*buffer;
	t_list	*last;

	if (newlst == NULL)
	{
		buffer = (*lst)->content;
		free(buffer->word);
		buffer->word = NULL;
		return (NULL);
	}
	last = ft_lstlast(newlst);
	ft_word_free((*lst)->content);
	(*lst)->content = newlst->content;	
	if (last != newlst)
	{
		last->next = (*lst)->next;
		(*lst)->next = newlst->next;
		*lst = last;
	}
	free(newlst);
	return (newpos);
}

char	*join_expand(t_list **lst, t_teraform *teraform, char *str)
{
	t_list	*newlst;
	int		type;
	char	*newpos;

	newlst = NULL;
	type = ((t_word *)(*lst)->content)->type;
	newpos = NULL;
	if (join_expand_left_node(&newlst, teraform, type) == FAIL)
		return (str);
	if (join_middle(&newlst, teraform, type) == FAIL)
		return (ft_words_clear(&newlst), str);
	if (join_expand_right_node(&newlst, teraform, type, &newpos) == FAIL)
		return (ft_words_clear(&newlst), str);
	if (newlst == NULL)
		return (NULL);
	return (join_nodes(lst, newlst, newpos));
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
		ret = join_expand(lst, &teraform, str);
	ft_free_teraform(&teraform);
	return (ret);
}
