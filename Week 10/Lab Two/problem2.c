#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node* next;
};
typedef struct Node NODE;

// Funtion Prototypes.
NODE* createNode(int val);
void insertHead(NODE** head, NODE* newNode);
void insertTail(NODE** head, NODE* newNode);
void deleteNode(NODE** head, int val);
void deleteHead(NODE** head);
void deleteTail(NODE** head);
void deleteDuplicates(NODE** head);
void printLinkedList(NODE** head);
NODE* findNode(NODE** head, int val);
void destroyList(NODE** head);
int countNodes(NODE** head);
void reverse(NODE** head);

// Create the header pointer.
NODE* head = NULL;

int main()
{

    // Create the header pointer.
    NODE* head = NULL;

    // Declare a new list. When the pointer is set to NULL, there is nothing else in the list past this point.
    NODE* one = createNode(1);
    NODE* two = createNode(1);
    NODE* three = createNode(2);
    NODE* four = createNode(2);
    NODE* five = createNode(2);
    NODE* six = createNode(3);
    insertHead(&head, one);
    insertTail(&head, two);
    insertHead(&head, three);
    insertTail(&head, four);
    insertHead(&head, five);
    insertHead(&head, six);
    printf("%d\n", countNodes(&head));
    reverse(&head);
    deleteNode(&head, 1);
    deleteHead(&head);
    deleteTail(&head);
    deleteDuplicates(&head);
    printLinkedList(&head);
    NODE* found = findNode(&head, 2);
    if (found != NULL)
    {
        printf("%d\n", found->data);
    }
    destroyList(&head);
    return 0;
}

NODE* createNode(int val)
{
    // Allocate memory for new node.
    NODE* ptr = (NODE*)malloc(sizeof(NODE));
    if (ptr == NULL)
    {
        printf("Fail to create new node\n");
        exit(1);
    }
    else
    {
        ptr->data = val;
        ptr->next = NULL;
    }
    return ptr;
}

void insertHead(NODE** head, NODE* newNode)
{
    NODE* ptr = *head;
    if (ptr == NULL)                // If it is an empty list...
    {
        *head = newNode;
    }
    else
    {
        newNode->next = *head;
        *head = newNode;
    }
}


void insertTail(NODE** head, NODE* newNode)
{
    NODE* ptr = *head;
    if (ptr == NULL)                // If it is an empty list...
    {
        *head = newNode;
    }
    else
    {
        while (ptr->next != NULL)   // Else, traverse list to the end.
        {
            ptr = ptr->next;
        }
        ptr->next = newNode;
    }
}

void deleteNode(NODE** head, int val)
{
    NODE* ptr = *head;
    NODE* temp = NULL;
    NODE* prevNode = NULL;
    if (ptr == NULL)                // If it is an empty list...
    {
        return;
    }
    else if (ptr->data == val)      // If the head is the node to delete...
    {
        temp = ptr->next;
        free(ptr);
        *head = temp;
    }
    else                            // Search for node to delete...
    {
        while ((ptr != NULL) && (ptr->data != val))
        {
            prevNode = ptr;
            ptr = ptr->next;        // Link the previous node to next node
        }
        if (ptr != NULL)
        {
            prevNode->next = ptr->next;
            free(ptr);
        }
    }
}

void deleteHead(NODE** head)
{
    NODE* ptr = *head;
    if (ptr == NULL)                // If it is an empty list...
    {
        return;
    }
    else     // If the head is the node to delete...
    {
        NODE* temp = ptr->next;
        free(ptr);
        *head = temp;
    }
}


void deleteTail(NODE** head)
{
    NODE* ptr = *head;
    if (ptr == NULL)                // If it is an empty list...
    {
        return;
    }
    else
    {
        NODE* prevNode = NULL;
        while (ptr->next != NULL)   // Else, traverse list to the end.
        {
            prevNode = ptr;
            ptr = ptr->next;      
        }
        free(ptr);
        prevNode->next = NULL;
    }
}

void deleteDuplicates(NODE** head)
{
    NODE* ptr = *head;

    while (ptr != NULL)
    {
        NODE* previous = ptr;
        NODE* current = ptr->next;

        while (current != NULL)
        {
            if (current->data == ptr->data)
            {
                NODE* temp = current;
                previous->next = current->next;
                free(temp);
                current = previous;
            }
            else
            {
                previous = current;
            }
            current = current->next;
        }
        ptr = ptr->next;
    }
}

void printLinkedList(NODE** head)
{
    NODE* ptr = *head;
    while (ptr != NULL)
    {
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}

NODE* findNode(NODE** head, int val)
{
    NODE* ptr = *head;
    while (ptr != NULL)
    {
        if (ptr->data == val)
        {
            return ptr;
        }
        else
        {
            ptr = ptr->next;
        }    
    }
    return ptr;
}

void destroyList(NODE** head)
{
    NODE *ptr = *head;
    NODE *nextNode = NULL;
    while (ptr != NULL)
    {
        nextNode = ptr->next;
        free(ptr);
        ptr = nextNode;
    }
    *head = NULL;
}

int countNodes(NODE** head)
{
    int count = 0;
    NODE* ptr = *head;
    while (ptr != NULL)
    {
        count++;
        ptr = ptr->next;
    }
    return count;
}

void reverse(NODE** head)
{
    NODE* current = *head;
    NODE* previous = NULL;
    NODE* next = NULL;
    
    while (current != NULL)
    {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    *head = previous;
}