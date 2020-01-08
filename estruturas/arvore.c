#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tree_node
{
	int item;
	struct Tree_node *right;
	struct Tree_node *left;
} 
tree_node;

void add_one(tree_node **root, int item);
void add_node(tree_node **root, int item);

void add_binary(tree_node **root, int item);
tree_node *create_tree(int item, tree_node *right, tree_node *left);
void print_tree(tree_node *root);

tree_node *make_tree();
tree_node *lisp_tree(char str[], int *index);
void isitbb(tree_node *root, int *fake);

void concatena(tree_node *root, tree_node *new);
void merge_tree(tree_node *root, tree_node *new);

void depth(tree_node *root, int *coisa);
tree_node *input(int *bool);

int main()
{
    tree_node *root = make_tree();
    
    int bool = 0;

    root = input(&bool);

	int a = 0;
	depth(root, &a);
	
	if(a) printf("FALSO\n");
	else printf("VERDADEIRO\n");

    return 0;
}

tree_node *make_tree()
{	
	return NULL;
}

void depth(tree_node *root, int *coisa)
{
	if(root == NULL) 
	{
		return;
	}
	
	if(root->left != NULL)
	{
		if(root->item < root->left->item)
		{
			*coisa = 1;
		}
	}

	if(root->right != NULL)
	{
		if(root->item > root->right->item)
		{
			*coisa = 1;
		}
	}
	depth(root->left, coisa);
	depth(root->right, coisa);
}

tree_node *input(int *bool)
{
    int size = 1000;
    char buffer[size];
    char *b = buffer;
    size_t bs = size;
    
    fgets(buffer, size, stdin);
    //printf("%s\n", buffer);

    if(!strcmp(buffer, "()\n")) 
    {
	*bool = 1;
	return NULL;
    }

    tree_node *root = make_tree();
    int index = 0;
    root = lisp_tree(buffer, &index);
    return root;
}

void concatena(tree_node *root, tree_node *new)
{
    if(root != NULL)    
    {
	if(root->item == new->item)
	{
	    merge_tree(root, new);
	    return;
	}
	else
	{
	    concatena(root->left, new);
	    concatena(root->right, new);
	}
    }
    else return;
}

void merge_tree(tree_node *root, tree_node *new)
{
    root->left = new->left;    
    root->right = new->right;    
    new->left = NULL;
    new->right = NULL;
}

tree_node *lisp_tree(char str[], int *index)
{
	if(str[(*index)] == '(' && str[((*index)+1)] != ')')	
	{
		(*index)++;

		char num[5];

		int i = 0;
		while(str[(*index)] != '(')
		{
			num[i] = str[(*index)];
			(*index)= (*index)+1;
			i = i+1;
		}
		num[i] = '\0';

		int item;
		sscanf(num, "%d", &item);

		tree_node *son1	= lisp_tree(str, index);
		tree_node *son2	= lisp_tree(str, index);

		return create_tree(item, son1, son2);
	}

	else if(str[(*index)] == '(' && str[((*index)+1)] == ')')	
	{
		*index = *index + 2;

		int i = 0;
		while(str[*index] != '(')
		{
			(*index)++;
			if(*index > strlen(str)) return NULL;
		}

		return NULL;
	}
}

void add_binary(tree_node **root, int item)
{
	if((*root)!= NULL)	
	{	
		if((*root)->item > item)
		{
			if((*root)->left != NULL)
			{
				add_binary(&(*root)->left, item);
			}
			else 
			{
				(*root)->left = create_tree(item, NULL, NULL);
			}
		}
		else
		{
			if((*root)->right != NULL)
			{
				add_binary(&(*root)->right, item);
			}
			else 
			{
				(*root)->right = create_tree(item, NULL, NULL);
			}
		}
	}
}

tree_node *create_tree(int item, tree_node *left, tree_node *right)
{
	tree_node *new_tree = (tree_node*)malloc(sizeof(tree_node));
	new_tree->item = item;
	new_tree->right = right;
	new_tree->left = left;
	return new_tree;
}

void print_tree(tree_node *root)
{
	printf("(");
	if(root != NULL)	
	{
		printf("%d", root->item);
		print_tree(root->left);
		print_tree(root->right);
		printf(")");
	}
	else printf(")");
}

void add_node(tree_node **root, int item)
{
	if(*root != NULL)	
	{	
		if((*root)->item > item)
		{
			if((*root)->left != NULL)
			{	
				add_node(&(*root)->left, item);
			}
			else
			{
				add_one(&(*root)->left, item);
			}
		}
		else
		{
			if((*root)->right != NULL)
			{	
				add_node(&(*root)->right, item);
			}
			else
			{
				add_one(&(*root)->right, item);
			}
		}
	}
	add_one(root, item);
}

void add_one(tree_node **root, int item)
{
	tree_node *new_node = malloc(sizeof(tree_node));

	new_node->item = item;
	new_node->left= NULL;
	new_node->right= NULL;

	*root = new_node;
}


