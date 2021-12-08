#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

typedef struct Node Node;

Node *create_new_node(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

void add_element_left(Node **root, int data)
{
    (*root)->left = create_new_node(data);
}

void add_element_right(Node **root, int data)
{
    (*root)->right = create_new_node(data);
}

void print_tabs(int num)
{
    for (int i = 0; i < num; i++)
    {
        printf("\t");
    }
}

void print_tree(Node *root, int level)
{
    if (root == NULL)
    {
        return;
    }

    print_tabs(level);
    printf("data = %d\n", root->data);

    print_tabs(level);
    printf("left\n");
    print_tree(root->left, level + 1);

    print_tabs(level);
    printf("right\n");
    print_tree(root->right, level + 1);
}

void free_tree(Node *root)
{
    if (root->left)
    {
        free_tree(root->left);
    }

    if (root->right)
    {
        free_tree(root->right);
    }

    free(root);
}

int main()
{
    Node *n1 = create_new_node(12);
    Node *n2 = create_new_node(13);

    n1->left = n2;

    add_element_right(&n1, 15);
    add_element_left(&n2, 21);
    add_element_right(&n2, 54);

    print_tree(n1, 0);
    free_tree(n1);

    return 0;
}
