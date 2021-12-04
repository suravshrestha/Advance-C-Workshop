#include <stdio.h>
#include <malloc.h>

struct Node
{
    int val;
    struct Node *next;
};

void add_node_front(struct Node **head_address, int data)
{
    if (head_address == NULL)
    {
        return;
    }

    struct Node *temp = malloc(sizeof(struct Node));

    temp->next = *head_address;
    temp->val = data;

    *head_address = temp;
}

void add_node_back(struct Node **head, int data)
{
    if (head == NULL)
    {
        return;
    }

    if (*head == NULL)
    {
        *head = malloc(sizeof(struct Node));
        (*head)->next = NULL;
        (*head)->val = data;

        return;
    }

    struct Node *temp = *head;

    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = malloc(sizeof(struct Node));
    temp = temp->next;
    temp->next = NULL;
    temp->val = data;
};

void print_linked_list(struct Node *head)
{
    if (head == NULL)
    {
        // i am doing this because if I dont tala ko newline to prints even when we didnt write aything to console
        return;
    }

    while (head != NULL)
    {
        printf("%d ", head->val);
        head = head->next;
    }

    printf("\n");
}

void free_linked_list(struct Node *head)
{
    while (head != NULL)
    {
        struct Node *temp = head->next;
        free(head);
        head = temp;
    }
}

int main()
{
    struct Node *head = NULL;

    // adding a node.
    head = malloc(sizeof(struct Node));
    head->next = NULL;
    head->val = 0;

    free(head);
    head = NULL;

    add_node_back(&head, 20);
    add_node_front(&head, 15);
    add_node_front(&head, 16);
    add_node_front(&head, 18);
    add_node_back(&head, 17);

    print_linked_list(head);
    free_linked_list(head);

    return 0;
}
