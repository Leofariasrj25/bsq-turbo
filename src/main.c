/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 1LINE:52:02 by coder             #+#    #+#          */
/*   Updated: 2022/04/23 21:30:59 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "ft.h" // nosso arquivo de cabeçalho contendo todas a funções que iremos criar/usar
#include "square.h"
#include "board.h"
# define COL 28
# define LINE 9

// definindo um struct que irá conter as coordenadas da posição onde se desenha o quadrado
// e o tamanho deste
// isso precisa ser refatorado, muitos argumentos.
// possívelmente podemos mudar a matrix para tipo char
// isso faria o cálculo do tamanho do tabuleiro bem mais simples.
void	print_matrix(char matrix[LINE][COL], int lines, int cols, t_square *solution)
{
	int	i;
	int	j;

	i = 0;
	i = (solution->x) - solution->size;
	while (i < solution->x)
	{
		j = 0;
		j = solution->y - solution->size;
		while (j < solution->y)
			matrix[i][j++] = 'x'; // preenchendo a área do maior quadrado
		i++;
	}
	i = -1;
	while (++i < lines)
	{
		ft_putstr(matrix[i]);
		ft_putstr("\n");
	}
}

int	menor_num(int **cache, int lin, int col)
{
	int	n1;
	int	n2;
	int	n3;

	n1 = cache[lin - 1][col];
	n2 = cache[lin][col - 1];
	n3 = cache[lin - 1][col - 1];
	if (n1 < n2)
	{
		if (n1 < n3)
			return (n1);
		else
			return (n3);
	}
	else
	{
		if (n2 < n3)
			return (n2);
		else
			return (n3);
	}
}

int	**matrix_clone(char **matrix, int line_size, int col_size)
{
	int	i;
	int	j;
	int	**clone;

	clone = malloc(sizeof(int *) * line_size);
	i = -1;
	while (++i < line_size)
		clone[i] = malloc(sizeof(int) * col_size);
	i = -1;
	while (++i < line_size)
	{
		j = -1;
		while (++j < col_size)
		{
			if (matrix[i][j] == '.')
				clone[i][j] = 1;
			else
				clone[i][j] = 0;
		}
	}
	return (clone);
}

t_square	*find_square(t_board *board, int line_size, int col_size)
{
	int lin;
	int col;
	t_square *resposta;
	int **cache;

	resposta = malloc(sizeof(t_square));
	cache = matrix_clone(board->board, board->lines, board->cols);
	lin = -1;
	while (++lin < line_size)
	{
		col = -1;
		while (++col < col_size)
		{
			if ((lin > 0 && col > 0) && cache[lin][col] != 0)
				cache[lin][col] += menor_num(cache, lin, col);
			if (cache[lin][col] > resposta->size)
			{
				resposta->size = cache[lin][col];
				resposta->x = lin + 1;
				resposta->y = col + 1;
			}
		}
	}
	return (resposta);
}

int	main(int argc, char *argv[])
{
	// Essa primeira parte tem que ser feita em uma funcao separada,
	// pra saber quantos mapas foram recebidos, se recebeu mapa ou nao etc;
	//se for 3 quer dizer que ele conseguiu ler e existe (olhar melhor sobre)
	int map_fd;
	int map_size;
	char *map_buffer;

	// rewriting
	int arg = 1;
	while (argc > 1 && arg < argc)
	{
		map_fd = open(argv[arg], O_RDONLY);
		if (map_fd != -1)
		{
			map_size = ft_file_size(argv[arg]);
			map_buffer = malloc(sizeof(char) * map_size + 1);
			read(map_fd, map_buffer, map_size);
			printf("%s\n", map_buffer);
		}
		else
		{
			// TO-DO: logica para tratar cada argv como linha do array;
		}
		// lógica para montar a string em matriz de char
		
		// inserir o tabuleiro em uma struct que contém todos os dados
		// matrix = o tabuleiro montado a partir da string
		// empty, filled, obstacle são os caracteres enviados pelo usuário
		t_board *board = create_board(matrix, empty, filled, obstacle);
		t_square *solution = find_square(board, board->lines, board->cols);
		arg++;
	}
	free(map_buffer);
	return (0);
	/*char **matrix = (char **) malloc(linhas * sizeof(int*));
	int i = 0;
	while (i < linhas)
		matrix[i++] = (char *) malloc(colunas * sizeof(int));
	char matrix[LINE][COL] = {
		"...........................\0",
		"....o......................\0",
		"............o..............\0",
		"...........................\0",
		"....o......................\0",
		"...............o...........\0",
		"...........................\0",
		"......o..............o.....\0",
		"..o.......o................\0"
	};
	//matrix[0][6] = 'X';
	int linhas = LINE;
	int colunas = ft_strlen(matrix[0]);
	t_square *solution = find_square(matrix, linhas, colunas);
	print_matrix(matrix, linhas, colunas, solution);*/
}
