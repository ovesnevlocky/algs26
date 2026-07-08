#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

bool isOp(char ch);

bool isUnaryOp(char ch);

bool isLeftToRight(char ch);

bool isRightToLeft(char ch);

bool isOpenB(char ch);

bool isCloseB(char ch);

bool isBracket(char ch);

int digits(int a);

int add(int a, int b);

int sub(int a, int b);

int multiply(int a, int b);

int devide(int a, int b);

int getExp(int base, int exp);

int calculate(char op, int a, int b);

int cutS(const char *str, int *idx, char buff[64]);

int factorial(int a);

#endif
