/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:05:50 by jole              #+#    #+#             */
/*   Updated: 2023/04/21 21:01:44 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*expand_var_in_string(char *str)
{
	int		i;
	int		len;
	int		delim;
	char	*new_str;

	i = 0;
	delim = 0;
	if (str[i] == '\'' || str[i] == '\"')
	   delim = str[i++];
	else 
		return (expand);
	if (str[i] && delim == '\'')
		return (delete_quotes(str));
	else if (str[i] && delim == '\"')
		return (delete_quotes_and_expand(str));
}
