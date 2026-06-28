#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include <stdint.h>

void freeBacket(int **backetArr)
{
	for(int i = 0; i < 10; i++)
		free(backetArr[i]);

	free(backetArr);

}


static inline uint32_t bitSignReverseToU32(int a)
{
	return (uint32_t)a ^ 0x80000000u;

}

static inline int bitSignReverseToInt(uint32_t a)
{
	return (int)a ^ 0x80000000;

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
		for(int j = 1; j < tmpArr[0] + 1; j++)
		{
			arr[idxArr] = tmpArr[j];
			idxArr++;

		}
		tmpArr[0] = 0;
	}	

}

int main()
{

	int test =INT_MAX;
	uint32_t result;
	result = bitSignReverseToU32(test);

	printf("%i converted to %lu\n",test,  result);
	
	printf("and back to %i\n", bitSignReverseToInt(result));
	int pos = 2;
	int arr[] = {12, 3423, 4, 1,23, 19111919, 23223, 323253, 9876543, 77, 3, 2, 5, 34, 221, 853, 232223 , 0 , 0};
	int size = sizeof(arr)/sizeof(arr[0]); 
	int num = 12345;
	
	//printf("%is %is position is %i\n", num, pos, getIndex(num, pos));

	int biggestNum = findBiggestNumarr(arr, size);
	int *tmp_arr = NULL;
	printf("biggest num is %i\n", biggestNum);	
	int **backetArr = prepareArr(size + 1);
	
	for(int i = 0; i < biggestNum; i++)
	{
		for(int j = 0; j < size; j++)
		{
			int target = arr[j];
			int idx = getIndex(target,i );
			//idx should be from 0 to 9
			tmp_arr = backetArr[idx];
			int idxInArr = tmp_arr[0];
			tmp_arr[idxInArr + 1] = target;
			//0th index holds number of elements in the array//
		       	tmp_arr[0]+= 1;	
			//tmp_arr = NULL;
		}
		tmp_arr = NULL;
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
