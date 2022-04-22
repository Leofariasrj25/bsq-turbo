# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfarias- <leofariasrj25@gmail.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/22 05:57:24 by lfarias-          #+#    #+#              #
#    Updated: 2022/04/22 06:06:02 by lfarias-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS=-g
SRCS=./src/
INCLUDES=-I ./includes/

all:
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS)*.c main.c -o bsq

clean:
	rm -f ./bsq
