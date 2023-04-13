/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:18:06 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/13 17:34:19 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

int	ft_isspace(char c);
int	len_word(char *str);
int	len_metachars(char *str, int metachar);
int	len_delim_word(char *str, int delim);

#endif
