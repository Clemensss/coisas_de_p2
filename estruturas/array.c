#include <stdio.h>
#include <string.h>

int main()
{
	int coisa, thing;
	scanf("%d\n", &coisa);
	int i, j;
	for(i=0; i<coisa; i++)
	{
		scanf("%d\n", &thing);
		int count = 0;
		for(j=0; j < thing; j++)
		{
			int k;
			char str[50];
			fgets(str, sizeof(str), stdin);
			for(k=0; k<strlen(str)-1;k++ )
			{
				int a = str[k] - 65;
				count += k + j + a;
			}
		}
		printf("%d\n", count);
	}
    return 0;
}


