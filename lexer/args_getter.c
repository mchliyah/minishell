#include "../includes/minishell.h"


char	*get_quote_things(t_lexer **this)
{
	char	*s;

	s = ft_substr("");
	if (!s)
		return (s);
	while ((*this)->c)
	{
		s = join_string(s, (*this)->c);
		*this = advance(*this);
		if ((*this)->c == SINGLE_QUOTE || (*this)->c == EOS)
			break ;
	}
	return (s);
}

char	*get_s_quote_things(t_lexer **this)
{
	char	*s;

	s = ft_substr("");
	if (!s)
		return (s);
	while ((*this)->c)
	{
		s = join_string(s, (*this)->c);
		*this = advance(*this);
		if ((*this)->c == L_DOUBLE_QUOTE || (*this)->c == EOS)
			break ;
	}
	return (s);
}

char	*get_s_word(t_lexer **this)
{
	char	*s;

	s = ft_substr("");
	if (!s)
		return (s);
	while ((*this)->c)
	{
		s = join_string(s, (*this)->c);
		*this = advance(*this);
		if ((*this)->c == L_DOUBLE_QUOTE || (*this)->c == SINGLE_QUOTE
			|| (*this)->c == EPIPE || (*this)->c == REDIRECT_IN
			|| (*this)->c == REDIRECT_OUT || (*this)->c == SPACE
			|| (*this)->c == EOS)
			break ;
	}
	return (s);
}
