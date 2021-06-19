#include <stdio.h>
#include <stdlib.h>

typedef struct DoubleLinkedListItem
{
    int data;
    struct DoubleLinkedListItem * prev;
    struct DoubleLinkedListItem * next;
}DLLI;

DLLI * root;
DLLI * iter;

DLLI * addToBegin(DLLI ** head,int data);
DLLI * addToEnd(DLLI ** head,int data);
DLLI * addSequence(DLLI ** head,int data);
DLLI * addBeforeNumber(DLLI ** head,int sonrakiSayi,int eklenecekSayi);
DLLI * addAfterNumber(DLLI ** head,int sonrakiSayi,int eklenecekSayi);
DLLI * reverseList(DLLI ** head);
DLLI * countList(DLLI * head);
DLLI * Find(DLLI ** head,int sayi);
DLLI * bubbleSort(DLLI ** head);
DLLI * swapNode(DLLI *a, DLLI *b);
DLLI * deleteNode(DLLI ** head,int data);

void printList(DLLI * head)
{
    iter = head;
    /// LISTENIN BASI BOSMU KONTROLU YAPILIR
    while(iter != NULL)
    {
        if(iter == head)
        {
            printf("%d",iter->data);
        }
        else
        {
           printf(" --> %d",iter->data); 
        }
        
        iter = iter -> next;
    }
}
/// LISTENIN BASINA ELEMAN EKLEME
DLLI * addToBegin(DLLI ** head,int data)
{
    /// YENI DUGUM OLUSTURULDU
    DLLI * newNode;
    newNode = (DLLI *)malloc(sizeof(DLLI));
    /// YENI DUGUME PARAMETRE OLARAK GELEN DATA ATILDI
    newNode -> data = data;
    /// BASA GELICEK DUGUMUN PREV'I NULL YAPILIR
    newNode -> prev = NULL;
    /// YENI DUGUM BASA EKLENILMEK ISTENIYORSA BU DUGUMUN NEXT'I LISTENIN BASI OLMALIDIR
    newNode -> next = (*head);
    /// LISTENIN BASI ARTIK YENI DUGUMDUR
    (*head) = newNode;
    return newNode;

}
/// SAYIYI LINKED LISTIN SONUNA EKLEYEN FONKSIYON
DLLI * addToEnd(DLLI ** head,int data)
{
     /// YENI DUGUM OLUSTURULDU
    DLLI * newNode;
    newNode = (DLLI *)malloc(sizeof(DLLI));
    /// YENI DUGUME PARAMETRE OLARAK GELEN DATA ATILDI
    newNode -> data = data;
    /// NULL DEGERLER ATANDI
    newNode -> prev = NULL;
    newNode -> next = NULL;

    if((*head) == NULL)
    {
        (*head) = newNode;
        return newNode;
    }

    iter = (*head);
    
    while (iter -> next != NULL)
    {
        iter = iter -> next;
    }

    iter -> next = newNode;
    newNode -> prev = iter;
    newNode -> next = NULL;
    return newNode;
}
/// ISTENILEN SAYIYI LISTEYE SIRALI BIR SEKILDE KOYAN FONKSIYON
DLLI * addSequence(DLLI ** head,int data)
{
    /// YENI DUGUM OLUSTURULDU
    DLLI * newNode;
    DLLI * temp;
    newNode = (DLLI *)malloc(sizeof(DLLI));
    /// YENI DUGUME PARAMETRE OLARAK GELEN DATA ATILDI
    newNode -> data = data;
    /// NULL DEGERLER ATANDI
    newNode -> prev = NULL;
    newNode -> next = NULL;
    

    if((*head) == NULL)
    {
        (*head) = newNode;
        return newNode;
    }

    iter = (*head);

    /// SIRALI EKLENMEK ISTENEN DEGER ROOT DAN KUCUK ISE BASA EKLENIR
    if (iter -> data > data)
    {
        newNode -> data = data;
        newNode -> prev = NULL;
        newNode -> next = (*head);
        (*head) = newNode;
        return (*head);
    }
    
    else
    {
        while (iter -> next != NULL && iter -> next -> data < data)
        {
            iter = iter -> next;       
        }
        newNode -> data = data;
        newNode -> prev = iter;
        newNode -> next = iter -> next;
        if (iter -> next != NULL)
        {
            iter -> next -> prev = newNode;  
        }
        iter -> next = newNode;
        return newNode;
    }
    
}
/// ISTENILEN SAYININ ONCESINE ISTENILEN SAYIYI YERLESTIREN FOKNSIYON
DLLI * addBeforeNumber(DLLI ** head,int sonrakiSayi,int eklenecekSayi)
{
    /// YENI DUGUM OLUSTURULDU
    DLLI * newNode;
    newNode = (DLLI *)malloc(sizeof(DLLI));
    /// YENI DUGUME PARAMETRE OLARAK GELEN DATA ATILDI VE NEXT'I NULL YAPILDI
    /// !! NEXT'ININ NULL YAPILMASI ONEMLI
    newNode -> data = eklenecekSayi;
    newNode -> next = NULL;

    /// LISTE BOS ISE ISLEM IPTAL
    if((*head) == NULL)
    {
        exit(1);
    }

    /// GECICI DEGISKEN ILE LISTE GEZILMELI AKSI TAKDIRDE ROOT YANI LISTENIN BASI KAYAR
    iter = *head;

    /// EKLENILMEK ISTENILEN SAYI LISTEDE SADECE ROOT VARSA ONUN ONUNE EKLEMELIDIR YANI LISTENIN BASI ARTIK YENI DUGUM OLMALIDIR
    if(iter -> next == NULL && iter -> data == sonrakiSayi)
    {
        newNode -> data = eklenecekSayi;
        newNode -> next = (*head);
        (*head) -> prev = newNode;
        newNode -> prev = NULL;
        (*head) -> next = NULL;
        (*head) = newNode;
        return (*head);
    }

    /// LISTE KOMPLE GEZILIR VE ISTENILEN SAYININ ONCESINE EKLENMEK ICIN ISTENILEN SAYI LISTEDE ARANIR VARSA SAYIMIZ BU SAYININ BIR ONCESINE EKLENIR
    while(iter -> next != NULL)
    {
        if(iter -> next -> data == sonrakiSayi)
        {
            break;
        }
        iter = iter -> next;
    }
    /// LISTEDE ONCESINE EKLENILMESI ISTENEN SAYI YOKTUR
    if(iter -> next == NULL)
    {
        printf("%d listede yoktur bu yuzden %d sayisi listeye eklenemez",sonrakiSayi,eklenecekSayi);
        exit(1);
    }
    /// EGER BU SAYI VARSA SAYIMIZ BIR ONCESINE EKLENIR
   
    newNode -> data = eklenecekSayi;
    newNode -> next = iter -> next;
    newNode -> prev = iter;
    iter -> next = newNode;
    if (iter -> next != NULL)
    {
            iter -> next -> prev = newNode;  
    }
    return newNode;
}
/// ISTENILEN SAYININ SONRASINA ISTENILEN SAYIYI YERLESTIREN FOKNSIYON
DLLI * addAfterNumber(DLLI ** head,int sonrakiSayi,int eklenecekSayi)
{
    ///  YENI DUGUM OLUSTURULDU
    DLLI * newNode;
    newNode = (DLLI *)malloc(sizeof(DLLI));
    ///YENI DUGUME PARAMETRE OLARAK GELEN DATA ATILDI VE NEXT'I NULL YAPILDI
    /// !! NEXT'ININ NULL YAPILMASI ONEMLI
    newNode -> data = eklenecekSayi;
    newNode -> next = NULL;

    /// LISTE BOS ISE ISLEM IPTAL
    if((*head) == NULL)
    {
        exit(1);
    }

    /// GECICI DEGISKEN ILE LISTE GEZILMELI AKSI TAKDIRDE ROOT YANI LISTENIN BASI KAYAR
    iter = *head;

    /// EKLENILMEK ISTENEN SAYI LISTEDE SADECE ROOT VARSA ONUN NEXT'INE EKLENMELIDIR
     if(iter -> next == NULL && iter -> data == sonrakiSayi)
    {
        newNode -> data = eklenecekSayi;
        newNode -> prev = (*head);
         newNode -> next = NULL;
        (*head) -> next = newNode;
        (*head) -> prev = NULL;
        return (*head);
    }

    /// LISTE KOMPLE GEZILIR VE ISTENILEN SAYININ SONRASINA EKLENMEK ICIN ISTENILEN SAYI LISTEDE ARANIR VARSA SAYIMIZ BU SAYININ BIR SONRASINA EKLENIR
    while(iter -> next != NULL)
    {
        iter = iter -> next;
        if(iter -> data == sonrakiSayi)
        {
            break;
        }
    }
    /// LISTEDE SONRASINA EKLENILMESI ISTENEN SAYI YOKTUR
    if(iter == NULL)
    {
        exit(1);
    }
    /// EGER BU SAYI VARSA SAYIMIZ BIR SONRASINA EKLENIR
  
    newNode -> data = eklenecekSayi;
    newNode -> prev = iter;
    newNode -> next = iter -> next;
    iter -> next = newNode;
    if (iter -> next != NULL)
    {
            iter -> next -> prev = newNode;  
    }
    return newNode;
    
}
/// LISTEYI TERSTEN printList
DLLI * reverseList(DLLI ** head)
{
    DLLI* prev = NULL;
    DLLI* next = NULL;
    iter = *head;

    /// LISTE DONGU ILE GEZILIR
    while (iter != NULL) {

        next = iter->next;
        iter->next = prev;

        prev = iter;
        iter = next;
    }
    *head = prev;
    return (*head);
}
/// LISTEDEKI DUGUM SAYISINI VERIR
DLLI * countList(DLLI * head)
{
    int count=0;

    for(iter = head;iter != NULL;iter=iter->next)
    {
        count++;
    }
     printf("Listedeki eleman sayisi : %d\n",count);
}
/// LISTEDE ISTENILEN ELEMAN VAR MI VARSA KACINCI DUGUMDE OLDUGUNU GOSTEREN FONKSIYON
DLLI * Find(DLLI ** head,int sayi)
{
    iter = (*head);
    int i = 1;
    /// LISTE DONGU ILE GEZILIR
    while(iter != NULL)
    {
        /// ARANAN SAYI VARSA BURDA EKRANA BASILIR
        if(iter -> data == sayi)
        {
            printf("Listede %d sayisi %d. node'da var\n",sayi,i);
            break;
        }
        i++;
        iter = iter -> next;
    }
    /// ISTENILEN SAYI LISTEDE YOKSA KULLANICIYA GOSTERILIR
    if(iter -> next == NULL)
    {
       printf("Listede %d sayisi yok\n",sayi);
    }
}
/// LISTEDEKI ELEMANLARI SIRALAR
DLLI * bubbleSort(DLLI ** head)
{
    iter = (*head);
    DLLI * temp;

    if (iter == NULL)
    {
        exit(1);
    }
    while(iter != NULL)
    {

        temp = iter -> next;
        while(temp != NULL)
        {
            if(iter -> data > temp -> data)
            {
                swapNode(iter,temp);
            }
            temp = temp -> next;
        }

        iter = iter -> next;
    }
}
/// DUGUM DEGERLERI YER DEGISTIRIR
DLLI * swapNode(DLLI *a, DLLI *b)
{
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}
///DUGUM SILME
DLLI * deleteNode(DLLI ** head,int data)
{
    DLLI * temp;
    iter = (*head);
    if((*head)->data == data)
    {
        temp = (*head);
        (*head) = (*head)->next;
        free(temp);
        return (*head);
    }
    while(iter -> next != NULL && iter -> next -> data != data)
    {
        iter = iter -> next;
    }
    if(iter -> next == NULL)
    {
        printf("Sayi bulunamadi\n");
        return (*head);
    }
    temp = iter -> next;
    iter -> next = iter -> next -> next;
    free(temp);
    return (*head);
}

int main()
{
    root = NULL;
    
    addToBegin(&root,5);
    addToBegin(&root,0);
    addToEnd(&root,10);
    addToEnd(&root,15);
    addToEnd(&root,20);
    addSequence(&root,-10);
    addSequence(&root,30);
    addSequence(&root,-2);
    addSequence(&root,7);
    addSequence(&root,25);
    addBeforeNumber(&root,5,2);
    addAfterNumber(&root,30,40);
    printList(root);
    printf("\n");
    countList(root);
    printf("\n");
    Find(&root,5);
    addToBegin(&root,100);
    printList(root);
    printf("\n");
    bubbleSort(&root);
    printList(root);
    printf("\n");
    deleteNode(&root,-10);
    deleteNode(&root,10);
    printList(root);
    printf("\n");
    reverseList(&root);
    printList(root);
    return 0;
}

