#include <stdio.h>
#include <stdlib.h>


void freeBacket(int **backetArr)
{
	for(int i = 0; i < 10; i++)
		free(backetArr[i]);

	free(backetArr);

}

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

void printBacket(int size, int **backetArr)
{

	int *tmp_arr = NULL; 
	for(int i = 0; i < 10; i++)
	{
		tmp_arr = backetArr[i];
		for(int j = 0; j < size; j++)
		{
			printf("%i ", tmp_arr[j]);
		}
		putchar('\n');
		tmp_arr = NULL;

	}
}
int **prepareArr(int size)
{
	int **arrForSorting = calloc(sizeof(int*),  10);

	//biggest possible size of subarray is the sizeof  the original length of array//	
	for(int i = 0;  i < 10; i++)
		arrForSorting[i] = calloc(sizeof(int) , size);

	int *tmp_arr = NULL; 
	for(int i = 0; i < 10; i++)
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


int getIndex(int num, int count)
{
	int ret = 0;
	if(num <= 9 && count > 0)
		return 0;
	if(num <= 9 && count == 0)
		return num;
	while(count > 0)
	{
		count--;
		//printf("num: %i, count: %i: modulo%i \n", num, count, num % 10);
		num = num / 10;
		if(num < 0)
			return 0;
	}

	return  num % 10;
}


void setSorted(int *arr, int **backetArr, int biggestNum, int sizeArr)
{
	int idxArr = 0;
	for(int i = 0; i < 10; i++)
	{
		int *tmpArr = backetArr[i];
		int count = 0;
		if(idxArr > sizeArr)
			break;
		while(count <sizeArr)
		{
			//if whats inside is -1 or atleast expected -1// 
			if(tmpArr[count]  < 0)
				break;

			if(tmpArr[count] > -1)
			{
				arr[idxArr++] = tmpArr[count];
			}
			//set -1 to indicate empty//
			tmpArr[count] = -1;	
			count++;
		}
	}	

}

int main()
{
	int pos = 2;
	int arr[] = {12, 3423, 4, 1, 77, 3, 2, 5, 34, 221, 853, 232223 , 0 , 0};
	int size = sizeof(arr)/sizeof(arr[0]); 
	int num = 12345;
	
	//printf("%is %is position is %i\n", num, pos, getIndex(num, pos));

	int biggestNum = findBiggestNumarr(arr, size);
	int *tmp_arr = NULL;
	printf("biggest num is %i\n", biggestNum);	
	int **backetArr = prepareArr(size);
	
	for(int i = 0; i < biggestNum; i++)
	{
		for(int j = 0; j < size; j++)
		{
			int target = arr[j];
			int idx = getIndex(target,i );
			int idxInArr = 0;
			//idx should be from 0 to 9
			tmp_arr = backetArr[idx];
			while(idxInArr < size + 1)
			{
				//if nothing in there, should be initialized as -1
				if(tmp_arr[idxInArr] == -1)
				{
					tmp_arr[idxInArr] = target;
					break;
				}
				idxInArr++;
			}
			tmp_arr = NULL;
		}
		
	setSorted(arr, backetArr, biggestNum, size);
	for(int i = 0; i < size; i++)
		printf("%i ", arr[i]);
	putchar('\n');

	}
	for(int i = 0; i < size; i++)
		printf("%i ", arr[i]);

	putchar('\n');

	freeBacket(backetArr);
	return 0;

		
}
