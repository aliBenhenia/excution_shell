/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 00:01:28 by mazaroua          #+#    #+#             */
/*   Updated: 2023/04/01 01:28:27 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirections_syntax(t_token_list **tokens)
{
	t_token_list	*tokens_;

	tokens_ = *tokens;
	while (tokens_->type != NLINE)
	{
		if (tokens_->type == RIGHTRED || tokens_->type == LEFTRED
			|| tokens_->type == APPEND || tokens_->type == HEREDOC)
		{
			if (tokens_->next && tokens_->next->type == SPACE)
				tokens_ = tokens_->next;
			if (tokens_->next->type == NLINE || tokens_->next->type != WORD)
			{
				write(1, "parse error\n", ft_strlen("parse error\n"));
				return (0);
			}
		}
		tokens_ = tokens_->next;
	}
	return (1);
}

int	pipe_syntax(t_token_list **tokens)
{
	t_token_list *tokens_;

	tokens_ = *tokens;
	while (tokens_->type != NLINE)
	{
		if (tokens_->type == PIPE)
		{
			if (tokens_->next && tokens_->next->type == SPACE)
				tokens_ = tokens_->next;
			if (tokens_->next->type == NLINE || tokens_->next->type == PIPE)
			{
				write(1, "parse error\n", ft_strlen("parse error\n"));
				return (0);
			}
		}
		tokens_ = tokens_->next;
	}
	return (1);
}

int	syntax(t_token_list *tokens)
{
	if (!tokens || tokens->type == NLINE)
		return (0);
	if (redirections_syntax(&tokens) && pipe_syntax(&tokens))
		return (1);
	return (0);
}