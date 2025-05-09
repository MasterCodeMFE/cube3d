/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igcastil <igcastil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:51:28 by igcastil          #+#    #+#             */
/*   Updated: 2024/01/29 09:43:43 by igcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/*
**								MACROS
**______________________________________________________________________________
*/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

/*
**								HEADERS
**______________________________________________________________________________
*/

# include <stdlib.h>
# include <unistd.h>

/*
**								FUNCTION PROTOTYPES
**______________________________________________________________________________
*/

char	*get_next_line(int fd);
char	*read_from_fd_to_remainder(int fd, char *remainder);
char	*trim_remainder(char	**remainder_addr);
char	*ft_strjoin_gnl(char *s1, char *s2);
size_t	ft_strlen_gnl(const char *s);
void	*ft_memcpy_gnl(void *dest, const void *src, size_t n);
char	*ft_strchr_gnl(char *s, int c);
char	*ft_strdup_gnl(char *s);

#endif