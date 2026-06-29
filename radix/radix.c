#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include <stdint.h>

void freeBacket(uint32_t **backetArr)
{
	for(int i = 0; i < 10; i++)
		free(backetArr[i]);

	free(backetArr);

}


//flip the sign bit to make
//comparison of negative ints possible
//what it does is add 2^31 to shift all values
//into unsigned while preserving order
static inline uint32_t bitSignReverseToU32(int a)
{
	return (uint32_t)a ^ 0x80000000u;

}

static inline int bitSignReverseToInt(uint32_t a)
{
	return (int)a ^ 0x80000000;

}

void convertToInt(uint32_t *src,int *dst,   int size)
{
	for(int i = 0; i < size; i++)
		dst[i] = bitSignReverseToInt(src[i]);

}
	
void convertToU32(uint32_t *dst,int *src,   int size)
{
	for(int i = 0; i < size; i++)
		dst[i] = bitSignReverseToU32(src[i]);

}
	
int findBiggestNum(uint32_t a)
{
	int ret = 0;
	while(a > 0)
	{
		a = a/10;
		ret++;
	}

	return ret;
}

uint32_t **prepareArr(int size)
{
	uint32_t **arrForSorting = calloc(sizeof(uint32_t*),  10);

	//biggest possible size of subarray is the sizeof  the original length of array//	
	for(int i = 0;  i < 10; i++)
		arrForSorting[i] = calloc(sizeof(uint32_t) , size);

	return arrForSorting;
}

//function to find max number of digits in an array
int findBiggestNumarr(uint32_t *arrForSorting, int size)
{
	int biggestNum = 0;
	uint32_t *tmp_arr = NULL;
	int tmp = 0;
	for(int i = 0; i < size; i++)
	{
		tmp = findBiggestNum(arrForSorting[i]);
		if(tmp > biggestNum)
			biggestNum = tmp;
	}
	return biggestNum; 
}

//function to find count-th location of digit in a value 
int getIndex(uint32_t num, int count)
{
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


void setSorted(uint32_t *arr, uint32_t **backetArr, int biggestNum, int sizeArr)
{
	int idxArr = 0;
	for(int i = 0; i < 10; i++)
	{
		uint32_t *tmpArr = backetArr[i];
		for(int j = 1; j < tmpArr[0] + 1; j++)
		{
			arr[idxArr] = tmpArr[j];
			idxArr++;

		}
		//reset the count//
		tmpArr[0] = 0;
	}	

}

int main()
{
	FILE *fp = fopen("test100k.txt", "r");
	
	int size;
	fscanf(fp, "%i", &size);
	int input;
	int count_file = 0;
	int *arr = malloc(sizeof(int) * size);
	while(!feof(fp))
	{
		fscanf(fp, "%i\n", &input);
		arr[count_file] = input;
		count_file++;
				
	}
	
	uint32_t *arr32 = malloc(sizeof(uint32_t) * size);
		
	convertToU32(arr32, arr, size);
	int biggestNum = findBiggestNumarr(arr32, size);
	printf("%i\n", size);	
	
	uint32_t *tmp_arr = NULL;
	//0th idx of each array have count variable
	//thats why + 1
	uint32_t **backetArr = prepareArr(size + 1);

		
	for(int i = 0; i < biggestNum; i++)
	{
		for(int j = 0; j < size; j++)
		{
			uint32_t target = arr32[j];
			int idx = getIndex(target,i);
			//idx should be from 0 to 9
			tmp_arr = backetArr[idx];
			int idxInArr = tmp_arr[0];
			tmp_arr[idxInArr + 1] = target;
			//0th index holds number of elements in the array//
		       	tmp_arr[0]+= 1;	
		}
		tmp_arr = NULL;
		setSorted(arr32, backetArr, biggestNum, size);

	}

	//flip the sign bit back to original//
	convertToInt(arr32, arr, size);
	
	for(int i = 0; i < size; i++)
		printf("%i\n", arr[i]);

	freeBacket(backetArr);
	return 0;
		
}
