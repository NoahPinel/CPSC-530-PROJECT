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
		Get the frequency of each symbol from the input stream
		Set the frequency table to the frequency of each symbol
		Create a complete binary tree using the frequency table
		Set the bit codes according to where the symbols are in the tree
		While more symbols to read from the input stream
			Read one symbol from the input stream
			Write the symbol’s bit code to the bit code stream
			Write the length of the bit code to the level stream
		Compress the level stream with a lossless algorithm
		Write the frequency table to the output stream
		Write the compressed level stream and the bit code stream to the output
		stream 
	*/

	/*
	DECODING
		Read the frequency table from the input stream
		Create a complete binary tree using the frequency table
		Read the compressed level stream from the input stream
		Uncompress the compressed level stream
		Read the bit code stream from the input stream
		While more levels to read from the level stream
			Read one level from the level stream
			Read level bits from bit code stream
			Find the symbol in the complete binary tree using the level and
			the bit code
			Write the symbol to the output stream
	*/