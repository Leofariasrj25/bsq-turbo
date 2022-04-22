# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfarias- <leofariasrj25@gmail.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/22 05:57:24 by lfarias-          #+#    #+#              #
#    Updated: 2022/04/22 06:01:21 by lfarias-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS=-g
SRCS=./srcs/
INCLUDES=./includes/

all:
	$(CC) $(CFLAGS) $(SRCS)*.c main.c -o bsq

clean:
	rm -f ./bsq
