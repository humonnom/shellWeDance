#include "../incs/minishell.h"

static int
	get_back_slash_len(char *str, char c)
{
	int		idx;
	int		len;

	idx = -1;
	len = 0;
	while (str[++idx])
	{
		if (str[idx] == c && str[idx + 1] == '\0')
			return (-1);
		if (str[idx] == c && str[idx + 1] != '\0')
		{
			len += 3;
			idx++;
		}
		else
			len++;
	}
	return (len);
}

static void
	remove_back_slash_in_filename(
	char *str,
	char *ret,
	int	*idx,
	int *ret_idx)
{
	while (is_bracket(str[*idx]))
	{
		ret[*ret_idx] = str[*idx];
		++(*idx);
		++(*ret_idx);
	}
	while (str[*idx] && str[*idx] == ' ')
		++(*idx);
	while (str[*idx] && str[*idx] != ' '
			&& !is_bracket(str[*idx]))
	{
		if (str[*idx] == '\\')
			++(*idx);
		ret[(*ret_idx)] = str[(*idx)];
		++(*idx);
		++(*ret_idx);
	}
}

static char
	select_quote(char target)
{
	char	single_quote;
	char	double_quote;

	single_quote = '\'';
	double_quote = '\"';
	if (target == single_quote)
		return(double_quote);
	return (single_quote);
}


static void
	cvt_back_slash_to_quote(char *str, char *ret, int *idx, int *ret_idx)
{
	char	quote;

	quote = select_quote(str[*(idx + 1)]);
	ret[*(ret_idx)] = quote;
	++(*ret_idx);
	++(*idx);
	ret[*(ret_idx)] = str[*(idx)];
	++(*ret_idx);
	ret[*(ret_idx)] = quote;
}

char
	*handle_back_slash(
	char *str,
	char c)
{
	char	*ret;
	int		len;
	int		idx;
	int		ret_idx;

	if ((len = get_back_slash_len(str, c)) == -1)
		return (NULL);
	if (!(ret = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ret[len] = '\0';
	idx = -1;
	ret_idx = -1;
	while (str[++idx] && ++ret_idx < len)
	{
		if (is_bracket(str[idx]))
			remove_back_slash_in_filename(str, ret, &idx, &ret_idx);		
		if (str[idx] == c)
			cvt_back_slash_to_quote(str, ret, &idx, &ret_idx);
		else
			ret[ret_idx] = str[idx];
	}
	return (ret);
}
