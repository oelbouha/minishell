

#include "../parser/parser.h"

int	quotes_len(char *str)
{
	char	next_quote;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == SINGLE_QUOTE || str[i] == DOUBLE_QUOTE)
		{
			next_quote = str[i];
			while (str[++i] && str[i] != next_quote)
				;
			i++;
		}
		else if (str[i] == '$')
			return (i);
		else
			i++;
	}
	return (i);
}

int	get_key_len(char *str)
{
	int		i;

	i = 1;
	while(str[i] && str[i] == '$')
		i++;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'' || str[i] == '$')
			return (i);
		i++;
	}
	return (i);
}

int	simple_word_len(char *str)
{
	char	next_quote;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == SINGLE_QUOTE || str[i] == DOUBLE_QUOTE)
		{
			next_quote = str[i];
			while (str[++i] && str[i] != next_quote)
				;
			i++;
		}
		else if (str[i] == '$')
			return (i);
		else
			i++;
	}
	return (i);
}

int	get_len(char *line)
{
	int			len;

	len = 0;
	if (line[0] == '\''|| line[0] == '"')
		len = quotes_len(line);
	else if (*line == '$')
		len = get_key_len(line);
	else
		len = simple_word_len(line);
	return (len);
}

char	*create_token(char *str)
{
	char	*token;
	int		len;

	len = get_len(str);
	if (len == 0)
		return (NULL);
	token = ft_substr(str, 0, len);
	return (token);
}

t_list	*split_content(char *line)
{
	t_list	*lst;
	char	*token;
	int		i;

	lst = NULL;
	i = 0;
	while (line[i])
	{
		while (line[i] && (line[i] == SPACE || line[i] == TAB))
			i++;
		token = create_token(&line[i]);
		if (push_token_to_list(&lst, token))
			return (ft_lstclear(&lst, free), NULL);
		i += ft_strlen(token);
	}
	return (lst);
}