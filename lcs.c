#include "lcs.h"

int LCS(char *str1, char *str2, char *str3)
{
	int mov[5][5] = {{0, 0}, {-1, -1}, {-1, -1}, {-1, 0}, {0, -1}};
	int i, j;
	int max, f[MAX][MAX], p[MAX][MAX];
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	for (i = 0; i <= len1; i++)
		for (j = 0; j <= len2; j++)
		{
			f[i][j] = 0;
			p[i][j] = 0;
		}
	for (i = 1; i <= len1; i++)
		for (j = 1; j <= len2; j++)
		{
			max = 0;	
			if (str1[i-1] == str2[j-1])
			{
				max = f[i-1][j-1] + 1;
				p[i][j] = 1;
			}
			else
			{
				max = f[i-1][j-1];
				p[i][j] = 2;				
			}
			if (max < f[i-1][j])
			{
				max = f[i-1][j];
				p[i][j] = 3;
			}
			if (max < f[i][j-1])
			{
				max = f[i][j-1];
				p[i][j] = 4;
			}
			f[i][j] = max;
		}
/*
	for (i = 1; i <= len1; i++)
	{
		for (j = 1; j <= len2; j++)
			printf("%d  ", f[i][j]);
		printf("\n");
	}
	printf("\n");
	for (i = 1; i <= len1; i++)
	{
		for (j = 1; j <= len2; j++)
			printf("%d  ", p[i][j]);
		printf("\n");
	}
*/
	int r = len1, c = len2;
	if (str3 == NULL)
		return f[len1][len2]; 
	for (i = f[len1][len2] - 1; i >= 0;)
	{
		if (p[r][c] == 1)
		{
			str3[i] = str1[r - 1];
			j = p[r][c];
			r += mov[1][0];
			c += mov[1][1];
			i--;
			printf("i : %d pos r:%d c:%d\n", i, r, c);
		}
		else
		{
			j = p[r][c];
			r += mov[j][0];
			c += mov[j][1];
			printf("i : %d pos r:%d c:%d\n", i, r, c);
		}
	}
	return f[len1][len2];
}

