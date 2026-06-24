#include <stdio.h>
#include <stdlib.h>

int findBiggestNum(int a)
{
	int ret = 0;
	while(a > 0)
	{
		a = a/10;
		ret++;
	}

	return ret;
}

int getIndex(int num, int count)
{

	if(num < 0)
		return 0;
	if(num <= 9 && count > 0)
		return 0;
	if(num <= 9 && count == 0)
		return num;	
	while(count > 0)
	{
		num = num/10;
		count--;
		printf("num: %i, count: %i \n", num, count);
		if(num < 0)
			break;
	}


	return  num % 10;
}


int **prepareArr(int size)
{
	int **arrForSorting = malloc(sizeof(int*) * 10);

	for(int i = 0;  i < 10; i++)
		arrForSorting[i] = calloc(sizeof(int)* size, 1);

	int *tmp_arr = NULL; 
	for(int i = 0; i < size; i++)
	{
		tmp_arr = arrForSorting[i];
		for(int j = 0; j < size; j++)
		{
			tmp_arr[j] = -1;		
		}
		tmp_arr = NULL;

	}

	return arrForSorting;
}

int findBiggestNumarr(int *arrForSorting, int size)
{

	int biggestNum = 0;
	int *tmp_arr = NULL;
	int tmp = 0;
	for(int i = 0; i < size; i++)
	{
		tmp = findBiggestNum(arrForSorting[i]);
		if(tmp > biggestNum)
			biggestNum = tmp;
	}
	return biggestNum; 
}

int main()
{
	int size = 10; 
	int tmp = 0;
	int num = 942256;
	int pos = 0;
	
	int arr[] = {12, 3423, 2, 1, 77, 3};


	printf("%is %is position is %i\n", num, pos, getIndex(num, pos));

	int sorted[size];

	int biggestNum = findBiggestNumarr(arr, 6);
	int *tmp_arr = NULL;
	
	int **arrForSorting = prepareArr(biggestNum);
	for(int i = 0; i < 6; i++)
	{
		int target = arr[i];
		int idx = getIndex(target, i);
		tmp_arr = arrForSorting[idx];
		int idxInArr = 0;
		while(idxInArr < 10)
		{
			if(tmp_arr[idxInArr] == -1)
			{
				tmp_arr[idxInArr] = target;
				break;
			}
			idxInArr++;
		}
	}
	for(int i = 0; i < size; i++)
	{
		tmp_arr = arrForSorting[i];
		for(int j = 0; j < biggestNum; j++)
		{
			printf("%i ", tmp_arr[j]);		
		}
		putchar('\n');
		tmp_arr = NULL;
	}
	printf("biggest num has %i digits\n", biggestNum);	
	putchar('\n');



		
}
