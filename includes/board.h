/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <leofariasrj25@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:21:16 by lfarias-          #+#    #+#             */
/*   Updated: 2022/04/23 21:28:39 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOARD_H
# define BOARD_H

typedef struct s_board
{
	char	**board;
	int		lines;
	int		cols;
	char	filled;
	char	obstacle;
	char	empty;
} t_board;
#endif
