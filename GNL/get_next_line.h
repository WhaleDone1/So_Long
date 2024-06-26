/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarpent <bcarpent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:09:35 by bcarpent          #+#    #+#             */
/*   Updated: 2024/05/06 15:52:04 by bcarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "../Ft_Printf/ft_printf.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

// size_t	ft_strlen(const char *s);
int		check_nl(char *stash);
char	*get_next_line(int fd);
char	*ft_strjoin(char *stash, char *buffer);
char	*ft_strdup(char *buffer);
char	*ft_strcpy(char *dst, const char *src);

#endif
