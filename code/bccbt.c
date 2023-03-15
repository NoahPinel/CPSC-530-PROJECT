// TODO:
// - Encoding Portion
// - Decoding Portion
// - Find other lossless algorithm (pseudocode says we need another one?)

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1

/* Main Function */
int main(int argc, char *argv[])
{
	// Checking usage
	if(argc != 3)
	{
		printf("Usage: %s FILEPATH ENCODE(0)/DECODE(1)",argv[0]);
		return 0;
	}

	// Encode
	if(!atoi(argv[2]))
	{
		// ...
	}
	// Decode
	else
	{
		// ...
	}

	return 0;
}
