#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

bool isOp(char ch);

bool isOpenB(char ch);

bool isCloseB(char ch);

bool isBracket(char ch);

int digits(int a);

int add(int a, int b);

int sub(int a, int b);

int multiply(int a, int b);

int devide(int a, int b);

int calculate(char op, int a, int b);

int cutS(const char *str, int *idx, char buff[64]);

#endif
