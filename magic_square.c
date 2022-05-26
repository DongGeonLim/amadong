#include <stdio.h>

int N, N_square, row, column, idx, sum;

void magic_square(int matrix[], int count)
{
	if (count == 0)
	{
		idx = (N - 1) / 2;
		matrix[idx] = count + 1;
		row = 1;
		column = idx + 1;
	}

	else
	{
		if (--row == 0) row = N;
		if (--column == 0) column = N;

		idx = (row - 1) * N + column - 1;
		
		if (matrix[idx] == -1)
		{
			matrix[idx] = count + 1;
		}

		else
		{
			if (++row > N) row = 1;
			if (++row > N) row = 1;
			if (++column > N) column = 1;
			
			idx = (row - 1) * N + column - 1;
			matrix[idx] = count + 1;
		}
	}
}

int main()
{
	while(1)
	{
		sum = 0;

		printf("마방진의 크기(1~10 사이의 홀수)를 입력하세요.(0을 입력하면 종료합니다.): ");
		scanf("%d", &N);

		if (N == 0)
		{
			printf("프로그램을 종료합니다.\n\n");
			return 0;
		}

		else if (N % 2 == 0)
		{
			printf("짝수를 입력하였습니다.\n\n");
		}

		else
		{
			N_square = N * N;

			int matrix[81];

			for (int i = 0; i < N_square; i++)
			{
				matrix[i] = -1;
			}

			for (int i = 0; i < N_square; i++)
			{
				magic_square(matrix, i);
			}

			for (int x = 0; x < N; x++)
			{
				for (int y = 0; y < N; y++)
				{
					printf("%d ", matrix[N*x+y]);
					if (x == 0 && y < N) sum = sum + matrix[N*x+y];
				}
				printf("\n");
			}
			printf("가로/세로/대각선의 합 = %d\n\n", sum);
		}
	}
}