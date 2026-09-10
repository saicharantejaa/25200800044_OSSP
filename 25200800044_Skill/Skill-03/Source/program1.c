#include <stdio.h>
#include <stdlib.h>

/* Structure for Linked List */
struct Node
{
    int data;
    struct Node *next;
};

/* Function to display array */
void displayArray(int arr[], int size)
{
    printf("Array: ");

    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
}

/* Function to insert a node into Linked List */
void insertNode(struct Node **head, int value)
{
    struct Node *newNode;

    /* Dynamically allocate memory for new node */
    newNode = malloc(sizeof(struct Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->data = value;
    newNode->next = *head;

    *head = newNode;
}

/* Function to display linked list */
void displayList(struct Node *head)
{
    printf("Linked List: ");

    while (head != NULL)
    {
        printf("%d -> ", head->data);
        head = head->next;
    }

    printf("NULL\n");
}

/* Function to free linked list */
void freeList(struct Node *head)
{
    struct Node *temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;

        free(temp);
    }
}

int main()
{
    /* ================================= */
    /* 1. DYNAMIC ARRAY ALLOCATION       */
    /* ================================= */

    int size = 5;

    int *arr = malloc(size * sizeof(int));

    if (arr == NULL)
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Dynamic array allocated.\n");

    for (int i = 0; i < size; i++)
    {
        arr[i] = (i + 1) * 10;
    }

    displayArray(arr, size);


    /* ================================= */
    /* 2. RESIZE ARRAY USING REALLOC      */
    /* ================================= */

    int newSize = 10;

    int *temp = realloc(arr, newSize * sizeof(int));

    if (temp == NULL)
    {
        printf("Memory reallocation failed!\n");
        free(arr);
        return 1;
    }

    arr = temp;

    printf("Array resized from %d to %d elements.\n",
           size, newSize);

    for (int i = size; i < newSize; i++)
    {
        arr[i] = (i + 1) * 10;
    }

    size = newSize;

    displayArray(arr, size);


    /* ================================= */
    /* 3. PREVENT BUFFER OVERFLOW         */
    /* ================================= */

    int index = 12;

    if (index >= 0 && index < size)
    {
        arr[index] = 999;

        printf("Value inserted safely.\n");
    }
    else
    {
        printf("Prevented buffer overflow: index %d is invalid.\n",
               index);
    }


    /* ================================= */
    /* 4. LINKED LIST                    */
    /* ================================= */

    struct Node *head = NULL;

    insertNode(&head, 10);
    insertNode(&head, 20);
    insertNode(&head, 30);

    displayList(head);


    /* ================================= */
    /* 5. FREE LINKED LIST MEMORY        */
    /* ================================= */

    freeList(head);

    head = NULL;

    printf("Linked list memory released.\n");


    /* ================================= */
    /* 6. FREE ARRAY MEMORY              */
    /* ================================= */

    free(arr);

    arr = NULL;

    printf("Dynamic array memory released.\n");

    return 0;
}
