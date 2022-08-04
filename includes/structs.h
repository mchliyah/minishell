/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 00:01:54 by mchliyah          #+#    #+#             */
/*   Updated: 2022/08/04 00:21:31 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define WHITESPACE " \t\n\r\v"
# define SYMBOLS " |<>"
# define EOS '\0'
# define SPACE ' '

enum
{
	MINUS = '-',
	EPIPE = '|',
	SINGLE_QUOTE = '\'',
	L_DOUBLE_QUOTE = '\"',
	R_DOUBLE_QUOTE = '\"',
	LESS = '<',
	GREATER = '>',
	ASSIGN = '='
};

typedef struct s_args
{
	char			*content;
	struct s_args	*next;
	struct s_args	*prev;
}	t_arg;

// ! content is the txt cmd
typedef struct s_token
{
	enum
	{
		WORD,
		REDIRECT_IN,
		REDIRECT_OUT,
		DELIMITER,
		REDIRECT_OUT_IN_APPEND_MD,
		PIPE,
		SYNTAX_ERR
	} e_type;
	int		type;
	char	*content;
	t_arg	*arg;

}	t_token;

typedef struct s_list
{
	t_token			*content;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

typedef struct s_lexer
{
	char	c;
	size_t	str_len;
	size_t	i;
	char	*content;
}	t_lexer;

typedef struct s_pair
{
	char			*key;
	char			*value;
}	t_pair;

typedef struct s_env
{
	struct s_pair	*pair;
	struct s_env	*next;
}				t_env;

typedef struct s_cmd_word
{
	char	*type;
	char	*arg;
}	t_cmd_word;

typedef struct s_pipeline
{
	int					type;
	struct s_pipeline	*left_p;
	t_list				*left;
	t_list				*right;
}	t_pipe_line;

typedef struct s_redirection
{
	char					*type;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_files
{
	char					*type;
	int						fd;
	struct s_redirection	*next;
}	t_files;

typedef struct s_data
{
	t_env	*env;
	t_env	*exp;
	int		exit;
	int		pip_nb;
	int		*p_fd;
	int		*fd_in;
	int		*fd_out;
	int		p_in;
	int		cmd_i;
}	t_data;

#endif