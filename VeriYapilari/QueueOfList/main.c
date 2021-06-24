#include <stdio.h>
#include <stdlib.h>

/// STRUCT YAPISININ KULLANILMASININ SEBEBI BIRDEN FAZLA FARKLI Queue ISTENEBILECEGI ICINDIR
typedef struct QueueOfList
{
    int data;
    struct QueueOfList * next;
}Queue;

Queue * root = NULL;
Queue * iter = NULL;

int dequeue()
{
    if(root == NULL)
    {
        printf("Queue bos");
        exit(0);
    }

    Queue * temp = root;
    int deleteData = root -> data;
    root = root -> next;
    free(temp);
    return deleteData;
}

void * enqueue(int data)
{
    if(root == NULL)
    {
        root = (Queue*)malloc(sizeof(Queue));
        root -> data = data;
        root -> next = NULL;
        iter = root;
    }
    else
    {
        iter -> next = (Queue*)malloc(sizeof(Queue));
        iter -> next -> data = data;
        iter = iter -> next;;
        iter -> next = NULL;
    }
}

void printList(Queue * root)
{
    while (root != NULL)
    {
        
        if (root -> next == NULL)
        {
            printf("%d",root -> data);
        }
        else
        {
            printf("%d --> ",root -> data);
        }
        root = root -> next;
    }
}
int main()
{
    for (int i = 0; i < 20; i++)
    {
        enqueue(i*10);
    }
    
   
    printList(root);
    printf("\n");
    
    for (int i = 0; i < 13; i++)
    {
        dequeue();
    }
    

    printList(root);
    return 0;
}