#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 1

// ==================================================================================================
// Key Value Dictionary implementation copied from:
// https://gist.githubusercontent.com/kylef/86784/raw/fe97567ec9baf5c0dce3c7fcbec948e21dfcce09/dict.c

typedef struct dict_t_struct {
	char *key;
	void *value;
	struct dict_t_struct *next;
} dict_t;

dict_t **dictAlloc(void) {
	return malloc(sizeof(dict_t));
}

void dictDealloc(dict_t **dict) {
	free(dict);
}

void *getItem(dict_t *dict, char *key) {
	dict_t *ptr;
	for (ptr = dict; ptr != NULL; ptr = ptr->next) {
		if (strcmp(ptr->key, key) == 0) {
			return ptr->value;
		}
	}

	return NULL;
}

void delItem(dict_t **dict, char *key) {
	dict_t *ptr, *prev;
	for (ptr = *dict, prev = NULL; ptr != NULL; prev = ptr, ptr = ptr->next) {
		if (strcmp(ptr->key, key) == 0) {
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

			free(ptr->key);
			free(ptr);

			return;
		}
	}
}

void addItem(dict_t **dict, char *key, void *value) {
	delItem(dict, key); /* If we already have a item with this key, delete it. */
	dict_t *d = malloc(sizeof(struct dict_t_struct));
	d->key = malloc(strlen(key)+1);
	strcpy(d->key, key);
	d->value = value;
	d->next = *dict;
	*dict = d;
}

// ====================================== End of copied code ========================================

// ==================================================================================================
// Binary Tree Implementation copied from:
// https://www.programiz.com/dsa/binary-tree

struct node {
	int item;
	struct node* left;
	struct node* right;
};

// Inorder traversal
void inorderTraversal(struct node* root) {
	if (root == NULL) return;
	inorderTraversal(root->left);
	printf("%d ->", root->item);
	inorderTraversal(root->right);
}

// Preorder traversal
void preorderTraversal(struct node* root) {
	if (root == NULL) return;
	printf("%d ->", root->item);
	preorderTraversal(root->left);
	preorderTraversal(root->right);
}

// Postorder traversal
void postorderTraversal(struct node* root) {
	if (root == NULL) return;
	postorderTraversal(root->left);
	postorderTraversal(root->right);
	printf("%d ->", root->item);
}

// Create a new Node
struct node* createNode(value) {
	struct node* newNode = malloc(sizeof(struct node));
	newNode->item = value;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

// Insert on the left of the node
struct node* insertLeft(struct node* root, int value) {
	root->left = createNode(value);
	return root->left;
}

// Insert on the right of the node
struct node* insertRight(struct node* root, int value) {
	root->right = createNode(value);
	return root->right;
}

// ====================================== End of copied code ========================================


// Main Function
int main(int argc, char *argv[])
{
	// Checking usage
	if(argc != 6)
	{
		printf("Usage: %s FILEPATH BITCODES LEVELS FREQUENCY ENCODE(0)/DECODE(1)",argv[0]);
		return 0;
	}

	// Encoding
	if(!atoi(argv[argc-1]))
	{
		// TODO (Aiden): Create frequency table
		// ...
		// TODO (Aiden): Initialize Complete Binary Tree
		// ...
	}
	// Decoding
	else
	{
		// TODO (Aiden): Read frequency table
		// ...
		// TODO (Aiden): Initialize Complete Binary Tree
		// (Create function for this since done in at least two places)
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
