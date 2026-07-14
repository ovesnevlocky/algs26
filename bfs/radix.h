#ifndef RADIX_H
#define RADIX_H

#include "graph.h"

void freeBacket(edge_t **backetArr);

edge_t **prepareArr(int size);

int getIndex(int num, int count);

int findBiggestNum(int a);

void setSorted(edge_t *arr, edge_t **backetArr);

void radixSort(edge_t *src, int size, int biggestNum);

#endif
