#include <stdio.h>
#include <stdlib.h>

/// STRUCT YAPISININ KULLANILMASININ SEBEBI BIRDEN FAZLA FARKLI STACK ISTENEBILECEGI ICINDIR
typedef struct StackOfList
{
    int data;
    struct StackOfList * next;
}Stack;


Stack * push(Stack * root,int data);

int pop(Stack * root)
{
    if(root == NULL)
    {
        printf("Stack bos");
        exit(0);
    }
    
    Stack * iter = root;

    if(iter -> next == NULL)
    {
        int deleteData = iter -> data; 
        free(root);
        return deleteData;
    }

    while (iter -> next -> next != NULL)
    {
        iter = iter -> next;
    }

    Stack * temp = iter -> next;
    int deleteData = temp -> data;
    iter -> next = NULL;
    free(temp);
    return deleteData;
}

Stack * push(Stack * root,int data)
{
    if(root == NULL)
    {
        root = (Stack*)malloc(sizeof(Stack));
        root -> data = data;
        root -> next = NULL;
        return root;
    }

    Stack * iter = root;
    while (iter -> next != NULL)
    {
        iter = iter -> next;
    }
    Stack * newNode = (Stack*)malloc(sizeof(Stack));
    newNode -> data = data;
    iter -> next = newNode;
    newNode -> next = NULL;
    return root;
}

void printList(Stack * root)
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
    Stack * stack = NULL;
    stack = push(stack,10);
    stack = push(stack,20);
    printList(stack);
    printf("\n");
    printf("%d --> ",pop(stack));
    printf("%d",pop(stack));
    return 0;
}