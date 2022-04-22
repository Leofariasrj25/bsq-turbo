/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 1LINE:52:02 by coder             #+#    #+#             */
/*   Updated: 2022/04/22 19:38:15 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "ft.h" // nosso arquivo de cabeçalho contendo todas a funções que iremos criar/usar
# define COL 28
# define LINE 9

// definindo um struct que irá conter as coordenadas da posição onde se desenha o quadrado
// e o tamanho deste
typedef struct s_square
{
	int	x;
	int	y;
	int	size;
} t_square;

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
			matrix[i][j++] = 'X'; // preenchendo a área do maior quadrado
		i++;
	}
	i = -1;
	while (++i < lines)
	{
		printf("%s\n", matrix[i]);
	}
}

int menor_num (int n1, int n2, int n3)
{
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

int	**matrix_clone(char matrix[LINE][COL], int line_size, int col_size)
{
	int	i;
	int	j;
	int **clone;
		
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

t_square	*find_square(char matrix[LINE][COL], int line_size, int col_size)
{
	int lin;
	int col;
	t_square *resposta;
	int **cache;

	resposta = malloc(sizeof(t_square));
	cache = matrix_clone(matrix, line_size, col_size);
	lin = -1;
	while (++lin < line_size)
	{
		col = -1;
		while (++col < col_size)
		{
			if (cache[lin][col] == 1)
			{
				//matrix[lin][col] = 1;
				if (lin > 0 && col > 0)
					cache[lin][col] += menor_num(cache[lin - 1][col], cache[lin][col - 1], cache[lin - 1][col - 1]);
				if (cache[lin][col] > resposta->size)
				{
					resposta->size = cache[lin][col];
					resposta->x = lin + 1;
					resposta->y = col + 1;
				}
			}
		}
	}
	return (resposta);
}

int	main(void)
{
	/*// Essa primeira parte tem que ser feita em uma funcao separada,
	// pra saber quantos mapas foram recebidos, se recebeu mapa ou nao etc;
	//se for 3 quer dizer que ele conseguiu ler e existe (olhar melhor sobre)
	int fd = open("maps/map2", 'r');
	int sz = 0;
	char *c = malloc(100);

	// numero de bytes lidos
	sz = read(fd, c, 100);
	printf("sz: %d\n", sz);

	// -----------------
	// Comeca a partir do 5 para pular a primeira linha, onde só tem as informações
	//Checar se precisa ler as informações da primeira linha, já sei que o primeiro precisa por ser o numero de linhas
	int x = 5;
	while (c[x])
	{
		// printf("Escrito: %c\n", c[x]);
		x++;
	}
	int linhas = c[0] - 48;
	int colunas = (sz - 5 - linhas) / linhas;
	printf("Coluna: %d\n", colunas);
	printf("Linhas: %d\n", linhas);*/

	/*char **matrix = (char **) malloc(linhas * sizeof(int*));
	int i = 0;
	while (i < linhas)
		matrix[i++] = (char *) malloc(colunas * sizeof(int));*/
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
	print_matrix(matrix, linhas, colunas, solution);
	//free(matrix);
	//free(c);
	return (0);
}

