#include <stdio.h>
#include <stdlib.h>

typedef struct Tree_node
{
	int item;
	int valor;
	int level;
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

void add_bb(tree_node **root, int item);
tree_node* search_node(tree_node *root, int item);
int assign(tree_node *root, int count, int arr[], int menor[]);

int main()
{
	int count, n1, n2, n3;

	scanf("%d", &count);
	
	tree_node * nodearr[count];
	for (int i = 0; i < count; i++)
	{
		scanf("%d%d%d\n", &n1, &n2, &n3);

		tree_node *root = create_tree(i, NULL, NULL);
		tree_node *node1;
		if(n2 != -1)
			node1 = create_tree(n2, NULL, NULL);
		else
			node1 = NULL;

		tree_node *node2;
		if(n3 != -1)
			node2 = create_tree(n3, NULL, NULL);
		else
			node2 = NULL;

		root->left = node1;
		root->right = node2;
		root->valor = n1;

		nodearr[i] = root;
	}

	for (int i = 0; i < count; i++)
	{
		tree_node *node = nodearr[i];
		int index;

		if(node->left)
		{
			index = node->left->item;
			node->left = nodearr[index];
		}

		if(node->right)
		{
			index = node->right->item;
			node->right = nodearr[index];
		}

	}

	int size = 100;
	int arr[size];
	int menor[size];

	for (int i = 0; i <size; i++)
	{
		arr[i] = 0;
	}

	for (int i = 0; i <size; i++)
	{
		menor[i] = __INT16_MAX__;
	}

	int num = assign(nodearr[0], 0, arr, menor);
	
	for (int i = 0; i <num; i++)
	{
		int big = arr[i];
		int smalls = menor[i];
		printf("Nivel %d: Maior = %d, Menor = %d\n", i, big, smalls);
	}

    return 0;
}

tree_node *make_tree()
{	
	return NULL;
}

int assign(tree_node *root, int count, int arr[], int menor[])
{
	if(root == NULL)
	{
		return count;
	}

	root->level = count;

	if(root->valor > arr[count])
	{
		arr[count] = root->valor;
	}

	if(root->valor < menor[count])
	{
		menor[count] = root->valor;
	}

	int a = assign(root->left, count+1, arr, menor);
	int b = assign(root->right, count+1, arr, menor);

	return (a > b) ? a : b;
}

tree_node* search_node(tree_node *node, int key)
{
	if (node == NULL)
		return NULL;

	else if (node->item == key)
		return node;
	else 
	{
		tree_node *left = search_node(node->left, key);
		return left? left: search_node(node->right, key);
	} 
}

void add_bb(tree_node **root, int item)
{
	if(*root == NULL)
	{
		tree_node* node = create_tree(item, NULL, NULL);
		*root = node;
		return;
	}

	else if(item > (*root)->item)
	{
			add_bb(&(*root)->right, item);
	}
	else 
	{
			add_bb(&(*root)->left, item);
	}
}

tree_node *lisp_tree(char str[], int *index)
{
	if(str[*index] == '(' && str[((*index)+1)] != ')')	
	{
		(*index)++;

		char num[5];
		char *ptr;

		int i = 0;
		while(str[*index] != '(')
		{
			num[i] = str[*index];
			(*index)++;
			i++;
		}
		num[i] = '\0';

		int item = strtol(num, &ptr, 10);

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
	tree_node *new_tree = malloc(sizeof(tree_node));
	new_tree->item = item;
	new_tree->right = right;
	new_tree->left = left;
	return new_tree;
}

void print_tree(tree_node *root)
{
	printf(" (");
	if(root != NULL)	
	{
		printf(" %d ", root->level);
		print_tree(root->left);
		print_tree(root->right);
		printf(") ");
	}
	else 
	{
		printf(") ");
		return;
	}
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
