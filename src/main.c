/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 19:52:02 by coder             #+#    #+#             */
/*   Updated: 2022/04/22 17:37:15 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "ft.h" // nosso arquivo de cabeçalho contendo todas a funções que iremos criar/usar

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
void	print_matrix(char **matrix, int lines, int cols, t_square *solution)
{
	int	i;
	int	j;

	i = (solution->x) - solution->size;
	while (i < solution->x)
	{
		j = solution->y - solution->size;
		while (j < solution->y)
			matrix[i][j++] = -1; // preenchendo a área do maior quadrado
		i++;
	}
	i = -1;
	while (++i < lines) // imprime a matrix
	{
		j = -1;
		while (++j < cols)
		{
			ft_putchar(matrix[i][j] + 48);
			ft_putchar(' ');
		}
		ft_putchar('\n');
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

t_square	*find_square(char **matrix, int line_size, int col_size)
{
	int lin;
	int col;
	t_square *resposta;
	int **cache;

	resposta = malloc(sizeof(t_square));
	cache = malloc(sizeof(int *) * line_size);
	lin = -1;
	while (++lin < line_size)
		cache[lin] = malloc(sizeof(int) * col_size);
	lin = -1;
	while (++lin < line_size)
	{
		col = -1;
		while (++col < col_size)
		{
			if (cache[(col_size + 1) * lin + col + 5] == '.')
			{
				matrix[lin][col] = 1;
				if (lin > 0 && col > 0)
					cache[lin][col] += menor_num(matrix[lin - 1][col], matrix[lin][col - 1], matrix[lin - 1][col - 1]);
				if (matrix[lin][col] > resposta->size)
				{
					resposta->size = matrix[lin][col];
				}
			}
		}
	}
	return (resposta);
}

int	main(void)
{
	// Essa primeira parte tem que ser feita em uma funcao separada,
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
	printf("Linhas: %d\n", linhas);

	// parte da logica
	// alocando a matrix
	char **matrix = (char **) malloc(linhas * sizeof(int*));
	int i = 0;
	while (i < linhas)
	{
		matrix[i] = (char *) malloc(colunas * sizeof(int));
		i++;
	}
	t_square *solution = find_square(matrix, linhas, colunas);
	print_matrix(matrix, linhas, colunas, solution);
	free(matrix);
	free(c);
	return (0);
}

