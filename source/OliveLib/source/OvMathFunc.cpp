#include "OvMathFunc.h"

unsigned int Factorial( unsigned int total )
{
	unsigned int result = 1;
	while ( total )
	{
		result *= total;
		--total;
	}
	return result;
}

unsigned int Factorial( unsigned int total, unsigned int select )
{
	return ( Factorial( total ) / Factorial( select ) );
}

unsigned int Combination( unsigned int total, unsigned int select )
{
	return ( Factorial( total ) / ( Factorial( select ) * Factorial( total - select ) ) );
}

unsigned int Sigma( unsigned int total )
{
	return ((total * ( total + 1 )) / 2);
}