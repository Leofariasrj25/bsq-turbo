/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 19:52:02 by coder             #+#    #+#             */
/*   Updated: 2022/04/22 08:35:06 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "ft.h"

void	print_matrix(int *matrix[], int lines, int cols, int solution_x, int solution_y, int solution)
{
	int	i;
	int	j;

	i = solution_x - solution;
	while (i < solution_x)
	{
		j = solution_y - solution;
		while (j < solution_y)
			matrix[i][j++] = -1;
		i++;
	}
	i = -1;
	while (++i < lines)
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
	// alocando a matriz
	int **matriz = (int **) malloc(linhas * sizeof(int*));
	int i = 0;
	while (i < colunas)
	{
		matriz[i] = (int *) malloc(colunas * sizeof (int*));
		i++;
	}

	int lin = 0;
	int col;

	int resposta = 0;
	int lin_menor;
	int col_menor;
	
	while (lin < linhas)
	{
		col = 0;
		while (col < colunas)
		{
			if (c[(colunas + 1) * lin + col + 5] == '.')
			{
				matriz[lin][col] = 1;
				if (lin > 0 && col > 0)
				{
					matriz[lin][col] += menor_num(matriz[lin - 1][col], matriz[lin][col - 1], matriz[lin - 1][col - 1]);
				}
				if (matriz[lin][col] > resposta)
				{
					resposta = matriz[lin][col];
					lin_menor = lin + 1;
					col_menor = col + 1;
				}
			}
			col++;
		}
		lin++;
	}
	printf("Resposta: %d\n", resposta);
	printf("Lugar: %d, %d\n", lin_menor, col_menor);

	// PRINTANDO A MATRIZ RESULTADO
	/*int a = 0;
	int b = 0;
	while (a < linhas)
	{
		b = 0;
		while (b < colunas)
		{
			printf("%d ", matriz[a][b]);
			b++;
		}
		printf("\n");
		a++;
	}*/
	print_matrix(matriz, linhas, colunas, lin_menor, col_menor, resposta);
	free(matriz);
	free(c);
	return (0);
}

