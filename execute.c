#include "header.h"

int convertStringToInt(const char *str, int length)
{
	/* variable declarations */
	int i, base, result, digit;

	/* variable initializations */
	result = 0;
	base = 1;

	for (i = 0; i < length; i++)
	{
		digit = str[length - i - 1] - 48;
		result += digit * base;
		base = base * 10;
	}

	return result;
}
