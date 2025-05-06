#include "minishell.h"

typedef struct s_teraform
{
	char	*left;
	char	*right;
	char	*token;
	int		inquote;
} t_teraform;

static int	ft_set_terraform(t_teraform *teraform, char *begin_str, char *str)
{
	ft_printf("L:%s\n", teraform->left);
	ft_printf("R:%s\n", teraform->right);
	ft_printf("T:%s\n", teraform->token);
	(void)str;
	(void)teraform;
	(void)begin_str;
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
}

char	*ft_expend_teraform(t_data *data, t_list **lst, char *str, int inquote)
{
	t_teraform	teraform;

	ft_bzero(&teraform, sizeof(t_teraform));
	teraform.inquote = inquote;
	ft_set_terraform(&teraform, ((t_word *)(*lst)->content)->word, str);
	(void)data;
	(void)lst;
	ft_free_teraform(&teraform);
	return (str + 1); // return the same *str if problem
}
