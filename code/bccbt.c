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


/*
ENCODING
	Initialize the complete binary tree
	While more symbols to read from the input stream
		Read one symbol from the input stream
		Get the symbol’s bit code from the complete binary tree
		Write the symbol’s bit code to the bit code stream
		Write the length of the bit code to the level stream
		Move the symbol to the root node of the complete binary tree
	Compress the level stream with a lossless algorithm
	Write the compressed level stream and the bit code stream to the output
	stream
*/

/*
DECODING
	Initialize the complete binary tree
	Read the compressed level stream from the input stream
	Uncompress the compressed level stream
	Read the bit code stream from the input stream
	While more levels to read from the level stream
		Read one level from the level stream
		Read level bits from bit code stream
		Find the symbol in the complete binary tree using the level and
		the bit code
		Move the symbol to the root node
		Write the symbol to the output stream 
*/