#include <stdio.h>
#include <stdlib.h>

typedef struct n
{
    int data;
    struct n * left;
    struct n * right;
}Node;

Node * addNode(Node * head,int data);
int Find(Node * head,int searchedData);
Node* deleteNode(Node *root, int deletedData);
Node * minNode(Node * head);
Node * maxNode(Node * head);

/// AGACA ELEMAN EKLEME
Node * addNode(Node * head,int data)
{
    if (head == NULL)
    {
        Node * root = (Node *)malloc(sizeof(Node));
        root -> left = NULL; 
        root -> right = NULL;
        root -> data = data; 
        return root;
    }

    if (head -> data < data)
    {
        head -> right = addNode(head -> right,data);
        return head;
    }
    
    head -> left = addNode(head -> left,data);
    return head;  
    
}
/// AGACTA ELEMAN ARAMA
int Find(Node * head,int searchedData)
{
    if (head == NULL)
    {
        return -1;
    }
    if (head -> data == searchedData)
    {
        return 1;
    }
    if (Find(head -> right,searchedData) == 1)
    {
        return 1;
    }
    if (Find(head -> left,searchedData) == 1)
    {
        return 1;
    }
    return -1;
}
/// LNR şeklinde listeler
void printList(Node * root)
{
    if (root == NULL)
    {
        return;
    }
    printList(root -> left);
    printf("%d ",root -> data);
    printList(root -> right);
}
/// AGACTAKI MAXIMUMU BULMA
int Max(Node * head)
{
    while (head -> right!=NULL)
    {
        head = head -> right;
    }
    return head -> data;
}
/// AGACTAKI MINIMUMU BULMA
int Min(Node * head)
{
    while (head -> left!=NULL)
    {
        head = head -> left;
    }
    return head -> data;
}
/// AGACTAKI MINUMUM NODE'U DONDURUR
Node * minNode(Node * head)
{
    while (head -> left!=NULL)
    {
        head = head -> left;
    }
    return head;
}
/// AGACTAKI MAXIMUM NODE'U DONDURUR
Node * maxNode(Node * head)
{
    while (head -> right!=NULL)
    {
        head = head -> right;
    }
    return head;
}
/// AGACTAN SILMA ISLEMI
Node* deleteNode(Node *root, int deletedData)
{
    //searching for the item to be deleted
    if(root == NULL)
        return NULL;
    if (deletedData > root -> data)
        root -> right = deleteNode(root -> right, deletedData);
    else if(deletedData < root->data)
        root->left = deleteNode(root -> left, deletedData);
    else
    {
        //No Children
        if(root -> left == NULL && root -> right == NULL)
        {
            free(root);
            return NULL;
        }

        //One Child
        else if(root -> left == NULL || root -> right == NULL)
        {
            Node *temp;
            if(root->left == NULL)
                temp = root -> right;
            else
                temp = root -> left;
            free(root);
            return temp;
        }

        //Two Children
        else
        {
            Node *temp = minNode(root -> right);
            root -> data = temp -> data;
            root -> right = deleteNode(root -> right, temp -> data);
        }
    }
    return root;
}
int main()
{
    Node * root = NULL;
    root = addNode(root,5);
    root = addNode(root,1);
    root = addNode(root,10);
    root = addNode(root,3);
    root = addNode(root,7);
    root = addNode(root,2);
    root = addNode(root,4);
    root = addNode(root,6);
    root = addNode(root,8);
    root = addNode(root,9);
  
    // printList(root);
    // printf("\n");
    // printf("Aranan Deger Sonuc = %d\n ",Find(root,11));
    // printf("Max Deger = %d\n ",Max(root));
    // printf("Min Deger = %d\n ",Min(root));

    root = deleteNode(root,9);
    root = deleteNode(root,10);
    root = deleteNode(root,1);
    root = deleteNode(root,2);
    root = deleteNode(root,3);
    root = deleteNode(root,4);
    root = deleteNode(root,5);
    root = deleteNode(root,6);
    root = deleteNode(root,7);
    root = deleteNode(root,8);
    root = deleteNode(root,11);
    printList(root);
    // printf("Max Deger = %d\n ",Max(root));
    // printf("Min Deger = %d\n ",Min(root));
    
    return 0;
}