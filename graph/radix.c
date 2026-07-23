#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"

#include <stdint.h>

void freeBacket(edge_t **backetArr)
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


edge_t **prepareArr(int size)
{
	edge_t **arrForSorting = calloc(sizeof(edge_t*),  10);

	//biggest possible size of subarray is the sizeof  the original length of array//	
	for(int i = 0;  i < 10; i++)
		arrForSorting[i] = calloc(sizeof(edge_t) , size);

	return arrForSorting;
}

//function to find count-th location of digit in a value 
int getIndex(int num, int count)
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


void setSorted(edge_t *arr, edge_t **backetArr)
{
	int idxArr = 0;
	for(int i = 0; i < 10; i++)
	{
		edge_t * tmpArr = backetArr[i];
		for(int j = 1; j < tmpArr[0].from + 1; j++)
		{
			arr[idxArr] = tmpArr[j];
			idxArr++;
		}
		//reset the count//
		tmpArr[0].from = 0;
	}	
}

//size is numEdges, biggestNum is number of digits of numNodes
void radixSort(edge_t *src ,int  size, int biggestNum)
{
	edge_t  *tmp_arr = NULL;
	//0th idx of each array have count variable
	//thats why + 1
	edge_t **backetArr = prepareArr(size + 1);
	biggestNum = (biggestNum);

	for(int i = 0; i < biggestNum; i++)
	{
		for(int j = 0; j < size; j++)
		{
			edge_t target = src[j];
			int idx = getIndex(target.from,i);
			//idx should be from 0 to 9
			tmp_arr = backetArr[idx];
			int idxInArr = tmp_arr[0].from;
			tmp_arr[idxInArr + 1] = target;
			//0th index holds number of elements in the array//
		       	tmp_arr[0].from += 1;	
		}
		tmp_arr = NULL;
		setSorted(src, backetArr);

	}

	//flip the sign bit back to original//

	freeBacket(backetArr);
		
}
