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
void insertHead(NODE* newNode);
void insertTail(NODE* newNode);
void deleteNode(int val);
void deleteHead();
void deleteTail();
void printLinkedList();
NODE* findNode(int val);
void destroyList();
int countNodes();
void reverse();

// Create the header pointer as a global variable.
NODE* head = NULL;

int main()
{
    // Declare a new list. When the pointer is set to NULL, there is nothing else in the list past this point.
    NODE* one = createNode(1);
    NODE* two = createNode(2);
    NODE* three = createNode(3);
    NODE* four = createNode(4);
    insertHead(one);
    insertTail(two);
    insertHead(three);
    insertTail(four);
    printf("%d\n", countNodes());
    reverse();
    //deleteNode(1);
    //deleteHead();
    //deleteTail();
    printLinkedList();
    NODE* found = findNode(2);
    if (found != NULL)
    {
        printf("%d\n", found->data);
    }
    destroyList();
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

void insertHead(NODE* newNode)
{
    NODE* ptr = head;
    if (ptr == NULL)                // If it is an empty list...
    {
        head = newNode;
    }
    else
    {
        newNode->next = head;
        head = newNode;
    }
}


void insertTail(NODE* newNode)
{
    NODE* ptr = head;
    if (ptr == NULL)                // If it is an empty list...
    {
        head = newNode;
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

void deleteNode(int val)
{
    NODE* ptr = head;
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
        head = temp;
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

void deleteHead()
{
    NODE* ptr = head;
    if (ptr == NULL)                // If it is an empty list...
    {
        return;
    }
    else     // If the head is the node to delete...
    {
        NODE* temp = ptr->next;
        free(ptr);
        head = temp;
    }
}


void deleteTail()
{
    NODE* ptr = head;
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

void printLinkedList()
{
    NODE* ptr = head;
    while (ptr != NULL)
    {
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}

NODE* findNode(int val)
{
    NODE* ptr = head;
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

void destroyList()
{
    NODE *ptr = head;
    NODE *nextNode = NULL;
    while (ptr != NULL)
    {
        nextNode = ptr->next;
        free(ptr);
        ptr = nextNode;
    }
    head = NULL;
}

int countNodes()
{
    int count = 0;
    NODE* ptr = head;
    while (ptr != NULL)
    {
        count++;
        ptr = ptr->next;
    }
    return count;
}

void reverse()
{
    NODE* current = head;
    NODE* previous = NULL;
    NODE* next = NULL;
    
    while (current != NULL)
    {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    head = previous;
}