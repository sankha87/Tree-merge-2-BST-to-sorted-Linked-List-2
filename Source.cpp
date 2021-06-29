#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

static int nodecount;

struct Node_LL
{
	int data;
	struct Node_LL* next;
}*linkedlist1 = NULL;

struct Node_Tree
{
	int data;
	struct Node_Tree* left;
	struct Node_Tree* right;
	//static int nodecount;
};

//int Node_Tree::nodecount = 0;

struct Node_Tree* Insert(struct Node_Tree*, int);
struct Node_Tree* GetNewNode(int);
void InOrderArray(struct Node_Tree*, int*, int *);
int* merge(int arr1[], int arr2[], int, int);
void InOrderLinkedList(struct Node_Tree*);
void displayLinkedList(struct Node_LL*);
void bubbleSort(struct Node_LL*);
void swap(struct Node_LL*, struct Node_LL*);

int  main()
{
	// create Binary Search Tree
	struct Node_Tree* root1 = NULL; // pointer to root node. Setting Tree as Empty.
	root1 = Insert(root1, 8);
	root1 = Insert(root1, 2);
	root1 = Insert(root1, 1);
	root1 = Insert(root1, 10);

	int nodecount1 = nodecount;
	printf("\n nodecount1 = %d", nodecount1);


	struct Node_Tree* root2 = NULL; // pointer to root node. Setting Tree as Empty.
	root2 = Insert(root2, 5);
	root2 = Insert(root2, 3);
	root2 = Insert(root2, 6);
	root2 = Insert(root2, 0);
	root2 = Insert(root2, 4);
	root2 = Insert(root2, 7);
	root2 = Insert(root2, 9);

	int nodecount2 = nodecount - nodecount1;
	printf("\n nodecount2 = %d", nodecount2);

	int *arr1 = (int *)malloc(nodecount1 * sizeof(int));
	int *arr2 = (int *)malloc(nodecount2 * sizeof(int));
	int *arr;
	int index1 = 0, index2 = 0;

	//	memset(arr1, 0, 10*sizeof(int));
	//	memset(arr2, 0, 10*sizeof(int));

	InOrderArray(root1, arr1, &index1);
	InOrderArray(root2, arr2, &index2);

	printf("\n\nArray1 : \n ");
	for (int i = 0; i < nodecount1; i++)
		printf("%d ", *(arr1 + i));

	printf("\nArray2 : \n ");
	for (int i = 0; i < nodecount2; i++)
		printf("%d ", *(arr2 + i));


	printf("\nMerged Array : \n ");
	arr = merge(arr1, arr2, nodecount1, nodecount2);
	for (int i = 0; i < (nodecount1 + nodecount2); i++)
		printf("%d ", *(arr + i));

	printf("\n\nLinked List 1 : \n ");
	InOrderLinkedList(root1);
	displayLinkedList(linkedlist1);

	printf("\n\nLinked List 1  <append> Linked List 2 : \n ");
	InOrderLinkedList(root2);
	displayLinkedList(linkedlist1);

	bubbleSort(linkedlist1);	// to sort the linked list
	printf("\n\nLinked List 1  <merge> Linked List 2 (SORTED): \n ");
	displayLinkedList(linkedlist1);
	_getch();
}

void InOrderArray(struct Node_Tree* t_root, int* i_arr, int *index)
{
	if (t_root == NULL)
		return;
	else
	{
		InOrderArray(t_root->left, i_arr, index);
		i_arr[*index] = t_root->data;
		(*index)++;
		InOrderArray(t_root->right, i_arr, index);
	}
}

struct Node_Tree* GetNewNode(int value)
{
	struct Node_Tree* newnode = (struct Node_Tree*)malloc(sizeof(struct Node_Tree));
	newnode->data = value;
	newnode->left = newnode->right = NULL;
	nodecount++;
	return newnode;
};

struct Node_Tree* Insert(struct Node_Tree* root, int value)
{
	if (root == NULL) // empty tree
		root = GetNewNode(value);

	else if (value <= root->data)
		root->left = Insert(root->left, value);

	else
		root->right = Insert(root->right, value);

	return root;
}

int* merge(int arr1[], int arr2[], int m, int n)	// A utility unction to merge two sorted arrays into one 
{
	int *mergedArr = (int *)malloc((m + n) * sizeof(int));
	int i = 0, j = 0, k = 0;

	// Traverse through both arrays 
	while (i < m && j < n)
	{
		if (arr1[i] < arr2[j])		// Pick the smaler element and put it in mergedArr 
		{
			mergedArr[k] = arr1[i];
			i++;
		}
		else
		{
			mergedArr[k] = arr2[j];
			j++;
		}
		k++;
	}

	while (i < m)		// If there are more elements in first array 
	{
		mergedArr[k] = arr1[i];
		i++; k++;
	}

	while (j < n)		// If there are more elements in second array 
	{
		mergedArr[k] = arr2[j];
		j++; k++;
	}

	return mergedArr;
}

void InOrderLinkedList(struct Node_Tree* t_root)
{
	if (t_root == NULL)
		return;
	else
	{
		InOrderLinkedList(t_root->left);
		{
			if (linkedlist1 == NULL)
			{
				linkedlist1 = (Node_LL*)malloc(sizeof(Node_LL));
				linkedlist1->data = t_root->data;
				linkedlist1->next = NULL;
			}
			else
			{
				Node_LL *temp = linkedlist1;
				while (temp->next != NULL)
					temp = temp->next;
				temp->next = (Node_LL*)malloc(sizeof(Node_LL));
				temp->next->data = t_root->data;
				temp->next->next = NULL;
			}
		}
		InOrderLinkedList(t_root->right);
	}
}

void linkedListInsert(Node_LL *node, int value)
{
	if (node == NULL)
	{
		node = (Node_LL*)malloc(sizeof(Node_LL));
		node->data = value;
		node->next = NULL;
	}
	else
	{
		Node_LL *temp = node;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = (Node_LL*)malloc(sizeof(Node_LL));
		temp->next->data = value;
		temp->next->next = NULL;
	}
}

void displayLinkedList(Node_LL* node)
{
	while (node != NULL)
	{
		printf("%d  ", node->data);
		node = node->next;
	}
}

void bubbleSort(struct Node_LL *head_ref)
{
	int n = nodecount;

	for (int i = 0; i < n - 1; i++)
	{
		struct Node_LL *head_ref2 = head_ref;

		int flag = 0;

		for (int j = 0; j < n - i - 1; j++)
		{
			if (head_ref2->data > head_ref2->next->data)
			{
				swap(head_ref2, head_ref2->next);
				flag = 1;
			}
			head_ref2 = head_ref2->next;
		}
		// if value of flag is zero after all the iterations of inner loop then break out
		if (flag == 0)
		{
			break;
		}
	}
}

void swap(struct Node_LL *a, struct Node_LL *b)
{
	int temp = a->data;
	a->data = b->data;
	b->data = temp;
}