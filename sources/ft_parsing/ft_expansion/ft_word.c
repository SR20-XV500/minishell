
#include "minishell.h"

static t_word	*ft_word_make(char *str, int type)
{
	t_word	*word;

	word = malloc(sizeof(t_word));
	if (word)
	{
		word->type = type;
		word->word = str;
	}
	return (word);
}

t_list	*ft_word_lst_make_join(char *str, int type)
{
	t_list	*lst;
	t_word	*word;

	lst = NULL;
	word = ft_word_make(str, type);
	if (word)
	{
		lst = ft_lstnew(word);
		if (lst == NULL)
			free(word);
	}
	return (lst);
}
