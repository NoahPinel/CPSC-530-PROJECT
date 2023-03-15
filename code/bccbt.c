// TODO:
// - Encoding Portion
// - Decoding Portion
// 	- Need Frequency Table for both
// 	- Need Complete Binary Tree for both
// - Find/implement lossless algorithm

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
