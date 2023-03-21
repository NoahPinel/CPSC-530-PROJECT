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
	int *code_word;
	struct node* left;
	struct node* right;
};

// Inorder traversal
void inorderTraversal(struct node* root) {
	if (root == NULL) return;
	inorderTraversal(root->left);
	//printf("%c ->", root->item);
	printf("%c : ", root->item);
	for(int i = 0; i < root->level + 1; i++) printf("%d",root->code_word[i]);
	printf(" ->");
	inorderTraversal(root->right);
}

// Preorder traversal
void preorderTraversal(struct node* root) {
	if (root == NULL) return;
	//printf("%c ->", root->item);
	printf("%c : ", root->item);
	for(int i = 0; i < root->level + 1; i++) printf("%d",root->code_word[i]);
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
	for(int i = 0; i < root->level + 1; i++) printf("%d",root->code_word[i]);
	printf(" ->");
}

// Create a new Node
struct node* createNode(unsigned char value, int code_word[], int level) {
	struct node* newNode = malloc(sizeof(struct node));
	newNode->item = value;
	newNode->level = level;
	newNode->code_word = intdup(code_word, 9);
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

// Insert on the left of the node
struct node* insertLeft(struct node* root, unsigned char value, int code_word[], int level) {
	root->left = createNode(value,code_word,level);
	return root->left;
}

// Insert on the right of the node
struct node* insertRight(struct node* root, unsigned char value, int code_word[], int level) {
	root->right = createNode(value,code_word,level);
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
	int *code_word_left = intdup(root->code_word,9);
	int *code_word_right = intdup(root->code_word,9);

	// Since we are filling from left to right then check left child first
	if(left_child_index > size-2) return;

	// Insert left child node
	code_word_left[level] = 0;
	level++;
	struct node* left_child = insertLeft(root,freq_table[left_child_index],code_word_left,level);

	// Now check if we have a right child node
	if(right_child_index > size-2) return;
	
	// Insert right child node
	level--;
	code_word_right[level] = 1;
	level++;
	struct node* right_child = insertRight(root,freq_table[right_child_index],code_word_right,level);

	// Recurse
	fill_tree(left_child,left_child_index,freq_table,size,level);
	fill_tree(right_child,right_child_index,freq_table,size,level);
}

// Function that recursively searchs the complete binary tree for the desired symbol
struct node* find_symbol(struct node* root, unsigned char c)
{
	// Check if NULL node
	if(root == NULL)
		return NULL;
	// Check for symbol
	if(root->item == c)
		return root;

	// Recurse down left subtree
	struct node* left_subtree = find_symbol(root->left, c);

	// See if symbol was in left subtree
	if(left_subtree != NULL)
		return left_subtree;

	// Recurse down right subtree
	struct node* right_subtree = find_symbol(root->right, c);

	// Return result
	return right_subtree;
}


// Main Function
int main(int argc, char *argv[])
{
	FILE *fp;

	// Checking usage
	if(argc != 6)
	{
		// If ENCODING:
		// - Need to pass Filepath of file to compress
		// - Need to pass 0 to indicate encoding
		// If DECODING
		// - Need to pass Bitcodes of a compressed file
		// - Need to pass Level codes of a compressed file
		// - Need to pass order of Frequency table of a compressed file
		// - Need to pass 1 to indicate decoding
		printf("Usage: %s FILEPATH BITCODES LEVELS FREQUENCY ENCODE(0)/DECODE(1)\n",argv[0]);
		return 0;
	}

	// Both parts need a frequency table
	dict_t **dict = dictAlloc();

	// Encoding
	if(!atoi(argv[argc-1]))
	{
		// Check if files readable
		if((fp = fopen(argv[1],"r")) == NULL)
			return 1;

		// Read file character by character filling the frequency table
		int c;
		int value;
		int unique_chars = 0;
		while((c=fgetc(fp)) != EOF)
		{
			unsigned char ch = c;
			// If the character is not already in the table then add it
			if((value = getItem(*dict, ch)) == 0)
			{
				addItem(dict, ch, 1);
				unique_chars++;
			}
			// Else increment the characters frequency by 1
			else
			{
				value++;
				addItem(dict, ch, value);
			}
		}
		fclose(fp);

#ifdef TEST
		// Print off frequency table by looping through ascii codes
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
		unsigned char freq_table[unique_chars+1];
		memset(freq_table, '\0', unique_chars+1);

		// Order frequencies of symbols
		for(int i = 0; i < unique_chars; i++)
		{
			int max_value = 0;
			unsigned char max_ch = 0;
			for(int j = 0; j < 255; j++)
			{
				int value;
				unsigned char ch = j;
				if((value = getItem(*dict, ch)) != 0)
				{
					if(value > max_value)
					{
						max_value = value;
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
		int code_word[9] = {-1}; // Initialized at -1 as root symbol doesn't need a bitcode
		struct node* root = createNode(freq_table[0],code_word,0);
		fill_tree(root,0,freq_table,sizeof(freq_table),0);

#ifdef TEST
		printf("\nPreorder traversal:\n");
		preorderTraversal(root);
		printf("\nPostorder traversal:\n");
		postorderTraversal(root);
		printf("\nInorder traversal:\n");
		inorderTraversal(root);
#endif

#ifdef TEST
		struct node* test_node = NULL;
		// Find symbol (change character in function argument to test different values)
		if((test_node = find_symbol(root,'c')) != NULL)
		{
			// If bitcode starts with -1 then this is the root node
			if(test_node->code_word[0] == -1)
				printf("\n\nFound root symbol %c at level %d.",test_node->item,test_node->level);
			else
			{
				printf("\n\nFound symbol %c at level %d which has bitcode: ",test_node->item,test_node->level);
				for(int i = 0; i < test_node->level; i++) printf("%d",test_node->code_word[i]);
				printf("\n");
			}
		}
		else
		{
			printf("\n\nThis symbol could not be found.\n");
		}
#endif
		// TODO: Can now encode input file symbol by symbol, need to write bitcodes of symbols to one file then levels to another file
		// so they can be used as inputs for decoding portion

	}
	// Decoding
	else
	{
		// TODO (Aiden): Read frequency table
		// ...
		// TODO (Aiden): Fill Complete Binary Tree
		// (Create function for this since done in at least two places)
		// ...
	}

	dictDealloc(dict);
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
