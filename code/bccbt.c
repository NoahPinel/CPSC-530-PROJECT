#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG TRUE
#define TEST TRUE

// ==================================================================================================
// Integer array copy function adapted from:
// https://stackoverflow.com/questions/8287109/how-to-copy-one-integer-array-to-another

int * intdup(int const * src, size_t len)
{
	int * p = malloc(len * sizeof(int));
	memcpy(p, src, len * sizeof(int));
	return p;
}

// ====================================== End of adapted code =======================================

// ==================================================================================================
// Key Value Dictionary implementation adapted from:
// https://gist.githubusercontent.com/kylef/86784/raw/fe97567ec9baf5c0dce3c7fcbec948e21dfcce09/dict.c

typedef struct dict_t_struct {
	unsigned char key;
	int value;
	struct dict_t_struct *next;
} dict_t;

dict_t **dictAlloc(void) {
	return malloc(sizeof(dict_t));
}

void dictDealloc(dict_t **dict) {
	free(dict);
}

int getItem(dict_t *dict, unsigned char key) {
	dict_t *ptr;
	for (ptr = dict; ptr != NULL; ptr = ptr->next) {
		if (ptr->key == key) {
			return ptr->value;
		}
	}

	return 0;
}

void delItem(dict_t **dict, unsigned char key) {
	dict_t *ptr, *prev;
	for (ptr = *dict, prev = NULL; ptr != NULL; prev = ptr, ptr = ptr->next) {
		if (ptr->key == key) {
			if (ptr->next != NULL) {
				if (prev == NULL) {
					*dict = ptr->next;
				} else {
					prev->next = ptr->next;
    				}
			} else if (prev != NULL) {
				prev->next = NULL;
			} else {
				*dict = NULL;
			}

			free(ptr);

			return;
		}
	}
}

void addItem(dict_t **dict, unsigned char key, int value) {
	delItem(dict, key); /* If we already have a item with this key, delete it. */
	dict_t *d = malloc(sizeof(struct dict_t_struct));
	d->key = key;
	d->value = value;
	d->next = *dict;
	*dict = d;
}

// ====================================== End of adapted code =======================================

// ==================================================================================================
// Binary Tree Implementation adapted from:
// https://www.programiz.com/dsa/binary-tree

struct node {
	unsigned char item;
	int level;
	int *code;
	struct node* left;
	struct node* right;
};

// Inorder traversal
void inorderTraversal(struct node* root) {
	if (root == NULL) return;
	inorderTraversal(root->left);
	//printf("%c ->", root->item);
	printf("%c : ", root->item);
	for(int i = 0; i < root->level; i++) printf("%d",root->code[i]);
	printf(" ->");
	inorderTraversal(root->right);
}

// Preorder traversal
void preorderTraversal(struct node* root) {
	if (root == NULL) return;
	//printf("%c ->", root->item);
	printf("%c : ", root->item);
	for(int i = 0; i < root->level; i++) printf("%d",root->code[i]);
	printf(" ->");
	preorderTraversal(root->left);
	preorderTraversal(root->right);
}

// Postorder traversal
void postorderTraversal(struct node* root) {
	if (root == NULL) return;
	postorderTraversal(root->left);
	postorderTraversal(root->right);
	//printf("%c ->", root->item);
	printf("%c : ", root->item);
	for(int i = 0; i < root->level; i++) printf("%d",root->code[i]);
	printf(" ->");
}

// Create a new Node
struct node* createNode(unsigned char value, int bitcode[], int level) {
	struct node* newNode = malloc(sizeof(struct node));
	newNode->item = value;
	newNode->level = level;
	newNode->code = intdup(bitcode, 9);
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

// Insert on the left of the node
struct node* insertLeft(struct node* root, unsigned char value, int code[], int level) {
	root->left = createNode(value,code,level);
	return root->left;
}

// Insert on the right of the node
struct node* insertRight(struct node* root, unsigned char value, int code[], int level) {
	root->right = createNode(value,code,level);
	return root->right;
}

// ====================================== End of adpated code =======================================

// Function that recursively fills a complete binary tree
void fill_tree(struct node* root, int i, unsigned char freq_table[], int size, int level)
{
	// Get indicies for left and right child nodes
	int left_child_index = 2*i+1;
	int right_child_index = 2*i+2;

	// Create int array to keep track of bitcodes for each symbol
	int *code_left = intdup(root->code,9);
	int *code_right = intdup(root->code,9);

	// Since we are filling from left to right then check left child first
	if(left_child_index > size-2) return;

	// Insert left child node
	code_left[level] = 0;
	level++;
	struct node* left_child = insertLeft(root,freq_table[left_child_index],code_left,level);

	// Now check if we have a right child node
	if(right_child_index > size-2) return;
	
	// Insert right child node
	level--;
	code_right[level] = 1;
	level++;
	struct node* right_child = insertRight(root,freq_table[right_child_index],code_right,level);

	// Recurse
	fill_tree(left_child,left_child_index,freq_table,size,level);
	fill_tree(right_child,right_child_index,freq_table,size,level);
}

// Function that recursively searchs the complete binary tree for the desired symbol given a symbol
struct node* find_symbol_by_symbol(struct node* root, unsigned char c)
{
	// Check if NULL node
	if(root == NULL)
		return NULL;
	// Check for symbol
	if(root->item == c)
		return root;

	// Recurse down left subtree
	struct node* left_subtree = find_symbol_by_symbol(root->left, c);

	// See if symbol was in left subtree
	if(left_subtree != NULL)
		return left_subtree;

	// Recurse down right subtree
	struct node* right_subtree = find_symbol_by_symbol(root->right, c);

	// Return result
	return right_subtree;
}

// Main Function
int main(int argc, char *argv[])
{
	// Declare variables used throughout main function
	FILE *src, *bitcodes, *bin, *lvls, *freqs, *output;
	int c, frequency, max_frequency, unique_chars;
	unsigned char ch, max_ch;
	struct node* symbol_node = NULL;
	struct node* root = NULL;


	// Checking usage
	if(argc != 6)
	{
		// If ENCODING:
		// - Need to pass Filepath of source file to compress
		// - Need to pass 0 to indicate encoding
		// If DECODING
		// - Need to pass Bitcodes in the form of a binary file
		// - Need to pass Level codes to read binary file
		// - Need to pass order of Frequency table to initialize complete binary tree
		// - Need to pass 1 to indicate decoding
		printf("Usage: %s SRC BIN LVLS FREQS ENCODE(0)/DECODE(1)\n",argv[0]);
		return 0;
	}

	// Both parts need a frequency table
	dict_t **dict = dictAlloc();

	// Encoding
	if(!atoi(argv[argc-1]))
	{
		// Check if files readable
		if((src = fopen(argv[1],"r")) == NULL)
			return 1;

		// Read file character by character filling in the frequency table
		unique_chars = 0;
		while((c=fgetc(src)) != EOF)
		{
			ch = c;
			// If the character is not already in the table then add it
			if((frequency = getItem(*dict, ch)) == 0)
			{
				addItem(dict, ch, 1);
				unique_chars++;
			}
			// Else increment the characters frequency by 1
			else
			{
				frequency++;
				addItem(dict, ch, frequency);
			}
		}
		fclose(src);

#ifdef TEST
		// Test that prints off frequency table by looping through all 256 ascii codes
		printf("\nKey/value pairs for symbols from input file:\n");
		int test_value;
		for(int k = 0; k < 255 ; k++)
		{
			unsigned char test_ch = k;
			if((test_value = getItem(*dict, test_ch)) != 0)
				printf("%c : %d\n", test_ch, test_value);
		}
#endif
		
		// Define frequency table to order frequency of symbols
		unsigned char freq_table[unique_chars+1]; // will be at most 256 (ascii chars) + 1 (null terminator) bytes long
		memset(freq_table, '\0', unique_chars+1);

		// Order frequencies of symbols (does this in constant time)
		for(int i = 0; i < unique_chars; i++)
		{
			max_frequency = 0;
			//max_ch = 0; probably don't need this
			for(int j = 0; j < 255; j++)
			{
				ch = j;
				if((frequency = getItem(*dict, ch)) != 0)
				{
					if(frequency > max_frequency)
					{
						max_frequency = frequency;
						max_ch = ch;
					}
				}
				
			}
			freq_table[i] = max_ch;
			delItem(dict, max_ch); // Deleteing symbol so we can search for symbol with next highest freq

		}

#ifdef TEST
		printf("\nFrequency of symbols ordered:\n");
		for(int i = 0; i < unique_chars; i++) printf("%c\n",freq_table[i]);
#endif

		// Initialize and fill Complete Binary Tree
		int code[9] = {-1}; // Initialized at -1 as root symbol doesn't need a bitcode
		root = createNode(freq_table[0],code,0); // Create root node with symbol with highest frequency
		fill_tree(root,0,freq_table,sizeof(freq_table),0);

#ifdef TEST
		// Test to make sure the Binary tree is in the correct order 
		printf("\nPreorder traversal:\n");
		preorderTraversal(root);
		printf("\nPostorder traversal:\n");
		postorderTraversal(root);
		printf("\nInorder traversal:\n");
		inorderTraversal(root);
#endif

#ifdef TEST
		// Test to check if the find_symbol_by_symbol function is working correctly
		if((symbol_node = find_symbol_by_symbol(root,'c')) != NULL)
		{
			// If bitcode starts with -1 then this is the root node
			if(symbol_node->code[0] == -1)
				printf("\n\nFound root symbol %c at level %d.",symbol_node->item, symbol_node->level);
			else
			{
				printf("\n\nFound symbol %c at level %d which has bitcode: ",symbol_node->item, symbol_node->level);
				for(int i = 0; i < symbol_node->level; i++) printf("%d", symbol_node->code[i]);
				printf("\n");
			}
		}
		else
		{
			printf("\n\nThis symbol could not be found.\n");
		}
#endif

		// Check source file is readable
		if((src = fopen(argv[1],"r")) == NULL)
			return 1;

		// Create file to temporarily store the string of bitcodes (i.e. the encoding of the src file)
		if((bitcodes = fopen("bitcodes","w")) == NULL)
			return 1;
		
		// Create file to store bitcode levels (used to uniquely decode binary file)
		if((lvls = fopen("lvls","w")) == NULL)
			return 1;
		
		// Create file to store symbol frequencies
		if((freqs = fopen("freqs","w")) == NULL)
			return 1;

		// Read the src file character by character
		while((c=fgetc(src)) != EOF)
		{
			ch = c;
			// Find the node containing the symbol
			symbol_node = find_symbol_by_symbol(root,ch);
			// Write the symbols bitcode to the bitcodes file
			for(int i = 0; i < symbol_node->level; i++)
				fprintf(bitcodes, "%d",symbol_node->code[i]);
			// Write the level of the bitcode to the levels file
			fprintf(lvls, "%d",symbol_node->level);

		}

		// Write symbols to file in order of their frequencies
		for(int i = 0; i < unique_chars; i++)
			fprintf(freqs, "%c", freq_table[i]);

		// Close files
		fclose(src);
		fclose(bitcodes);
		fclose(lvls);
		fclose(freqs);

		// TODO:
		// - Can now encode input file symbol by symbol.
		// - Encoding of the file needs to be written to another file as a string of 1's and 0's (these will be 1 bit characters),
		//   then pad the file so that the number of 1's and 0's is a multiple of 8,
		//   then use python (https://stackoverflow.com/questions/7290943/write-a-string-of-1s-and-0s-to-a-binary-file)
		//   to convert the string of 1's and 0's to a bytearray which can then be written as bits to a binary file.
		// - The corresponding string of levels of the bitcodes in the binary tree needs to be written to a separate file
		//   which can be compressed using a different lossless compression algorithm. (lz4 is a native linux compression tool)

	}
	// Decoding
	else
	{
		// Open frequency file
		if((freqs = fopen(argv[4],"r")) == NULL)
			return 1;
		
		// Read the frequency file to get the number of unique characters
		unique_chars = 0;
		while((c=fgetc(freqs)) != EOF)
			unique_chars++;
		//unique_chars--; // It will count the last line break as unqiue even if there was already a line break, so decrement by 1
		fclose(freqs);

		// Define frequency table
		unsigned char freq_table[unique_chars+1]; // will be at most 256 (ascii chars) + 1 (null terminator) bytes long
		memset(freq_table, '\0', unique_chars+1);

		// Again, open the frequency file
		if((freqs = fopen(argv[4],"r")) == NULL)
			return 1;
		
		// And now fill the frequency table knowing how many characters to read
		for(int i = 0; i < unique_chars; i++)
		{
			c = fgetc(freqs);
			ch = c;
			freq_table[i] = ch;
		}
		fclose(freqs);

		// Initialize and fill Complete Binary Tree
		int code[9] = {-1}; // Initialized at -1 as root symbol doesn't need a bitcode
		root = createNode(freq_table[0],code,0); // Create root node with symbol with highest frequency
		fill_tree(root,0,freq_table,sizeof(freq_table),0);

#ifdef TEST
		// Test to make sure the Binary tree is in the correct order 
		printf("\nPreorder traversal:\n");
		preorderTraversal(root);
		printf("\nPostorder traversal:\n");
		postorderTraversal(root);
		printf("\nInorder traversal:\n");
		inorderTraversal(root);
#endif

		// TODO: Decompress the levels file with what ever algorithm was used to compress it
		// ...

		// Open file contatin the levels of the bitcodes
		if((lvls = fopen(argv[3],"r")) == NULL)
			return 1;
		
#ifdef TEST		
		// For this test we will just use the temporary bitcode file (WHICH IS NOT COMPRESSED TO ACTUAL BITS)
		// to test the functionality for searching the binary tree by bitcodes (DO NOT KEEP THIS FUNCTIONALITY, ONLY FOR TESTING).
		if((bitcodes = fopen("lamont","r")) == NULL)
			return 1;
		
		// Open output file to write decoded symbols to
		if((output = fopen("output","w")) == NULL)
			return 1;
		
		// Now read levels and search for symbols
		int lvl;
		int bit;
		while((c = fgetc(lvls)) != EOF)
		{
			lvl = c - '0'; // convert to int
			symbol_node = root; // start from root each time
			// Now read level amount of bits from the "binary" file
			// while at the same time traversing the binary tree
			if(lvl != 0)
			{
				for(int i = 0; i < lvl; i++)
				{
					c = fgetc(bitcodes);
					bit = c - '0';
					if(bit == 0)
						symbol_node = symbol_node->left;
					else
						symbol_node = symbol_node->right;
				}
			}
			fprintf(output,"%c",symbol_node->item);
		}
		// Close files related to testing here
		fclose(bitcodes);
		fclose(output);
#endif
		
		// Remember to close files used in decoding here
		// SAFETY FIRST NO LEAKY WEAKIES Xd
		fclose(lvls);
	}

	// Deallocate the dictionary
	dictDealloc(dict);
	return 0;
}


/*
ENCODING
	Get the frequency of each symbol from the input stream (AIDEN: DONE)
	Set the frequency table to the frequency of each symbol (AIDEN: DONE)
	Create a complete binary tree using the frequency table (AIDEN: DONE)
	Set the bit codes according to where the symbols are in the tree (AIDEN: DONE)
	While more symbols to read from the input stream
		Read one symbol from the input stream
		Get the symbol’s bit code from the complete binary tree
		Write the symbol’s bit code to the bit code stream
		Write the length of the bit code to the level stream
		Move the symbol to the root node of the complete binary tree
	Compress the level stream with a lossless algorithm
	Write the frequency table to the output stream
	Write the compressed level stream and the bit code stream to the output
	stream
*/

/*
DECODING
	Read the frequency table from the input stream (AIDEN: DONE)
	Create a complete binary tree using the frequency table (AIDEN: DONE)
	Read the compressed level stream from the input stream
	Uncompress the compressed level stream
	Read the bit code stream from the input stream (AIDEN: DONE)
	While more levels to read from the level stream
		Read one level from the level stream
		Read level bits from bit code stream
		Find the symbol in the complete binary tree using the level and
		the bit code
		Write the symbol to the output stream 
*/
