#include <stdio.h>
#include <stdlib.h>

typedef struct SingleLinkedListItem
{
    int data;
    struct SingleLinkedListItem * next;
}SLLI;

SLLI * root;
SLLI * iter;

SLLI * addToBegin(SLLI ** head,int data);
SLLI * addToEnd(SLLI ** head,int data);
SLLI * addSequence(SLLI ** head,int data);
SLLI * addBeforeNumber(SLLI ** head,int sonrakiSayi,int eklenecekSayi);
SLLI * addAfterNumber(SLLI ** head,int sonrakiSayi,int eklenecekSayi);
SLLI * reverseList(SLLI ** head);
SLLI * countList(SLLI * head);
SLLI * Find(SLLI ** head,int sayi);
SLLI * bubbleSort(SLLI ** head);
SLLI * swapNode(SLLI *a, SLLI *b);
SLLI * deleteNode(SLLI ** head,int data);

/// LINKED LISTEYI printListMA FONKSIYONU
void printList(SLLI * head)
{
    /// LISTENIN BASI BOSMU KONTROLU YAPILIR
    while(head != NULL)
    {
        if(head == root)
        {
            printf("%d",head->data);
        }
        else if(head -> next == NULL)
        {
            printf(" --> %d\n",head->data);
        }
        else
        {
            printf(" --> %d",head->data);
        }

        head = head -> next;
    }
}
/// SAYIYI LINKED LISTIN SONUNA EKLEYEN FONKSIYON
SLLI * addToEnd(SLLI ** head,int data)
{
     /// YENI DUGUM OLUSTURULDU
    SLLI * newNode;
    newNode = (SLLI *)malloc(sizeof(SLLI));
    /// YENI DUGUME PARAMETRE OLARAK GELEN DATA ATILDI
    newNode -> data = data;
    /// NULL DEGERLER ATANDI
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
    newNode -> next = NULL;
    return newNode;
}
/// LISTENIN BASINA ELEMAN EKLEME
SLLI * addToBegin(SLLI ** head,int data)
{
    /// YENI DUGUM OLUSTURULDU
    SLLI * newNode;
    newNode = (SLLI *)malloc(sizeof(SLLI));
    /// YENI DUGUME PARAMETRE OLARAK GELEN DATA ATILDI
    newNode -> data = data;
    /// YENI DUGUM BASA EKLENILMEK ISTENIYORSA BU DUGUMUN NEXT'I LISTENIN BASI OLMALIDIR
    newNode -> next = (*head);
    /// LISTENIN BASI ARTIK YENI DUGUMDUR
    (*head) = newNode;
    return newNode;

}
/// ISTENILEN SAYIYI LISTEYE SIRALI BIR SEKILDE KOYAN FONKSIYON
SLLI * addSequence(SLLI ** head,int data)
{
    /// YENI DUGUM OLUSTURULDU
    SLLI * newNode;
    SLLI * temp;
    newNode = (SLLI *)malloc(sizeof(SLLI));
    /// YENI DUGUME PARAMETRE OLARAK GELEN DATA ATILDI
    newNode -> data = data;
    /// NULL DEGERLER ATANDI
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
        newNode -> next = (*head);
        (*head) = newNode;
        return newNode;
    }
    
    else
    {
        while (iter -> next != NULL && iter -> next -> data < data)
        {
            iter = iter -> next;       
        }
        newNode -> data = data;
        newNode -> next = iter -> next;
        iter -> next = newNode;
        return newNode;
    }
    
}
// ISTENILEN SAYININ ONCESINE ISTENILEN SAYIYI YERLESTIREN FOKNSIYON
SLLI * addBeforeNumber(SLLI ** head,int sonrakiSayi,int eklenecekSayi)
{
    /// YENI DUGUM OLUSTURULDU
    SLLI * newNode;
    newNode = (SLLI *)malloc(sizeof(SLLI));
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
        (*head) -> next = NULL;
        (*head) = newNode;
        return newNode;
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
    iter -> next = newNode;
    return newNode;
}
// ISTENILEN SAYININ SONRASINA ISTENILEN SAYIYI YERLESTIREN FOKNSIYON
SLLI * addAfterNumber(SLLI ** head,int sonrakiSayi,int eklenecekSayi)
{
    ///  YENI DUGUM OLUSTURULDU
    SLLI * newNode;
    newNode = (SLLI *)malloc(sizeof(SLLI));
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
        newNode -> next = NULL;
        (*head) -> next = newNode;
        return newNode;
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
    newNode -> next = iter -> next;
    iter -> next = newNode;
    
    return newNode;
    
}
/// LISTEYI TERSTEN printListIR
SLLI * reverseList(SLLI ** head)
{
    SLLI* prev = NULL;
    SLLI* next = NULL;
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
SLLI * countList(SLLI * head)
{
    int count=0;

    for(iter = head;iter != NULL;iter=iter->next)
    {
        count++;
    }
    printf("Listedeki eleman sayisi : %d\n",count);
}
/// LISTEDE ISTENILEN ELEMAN VAR MI VARSA KACINCI DUGUMDE OLDUGUNU GOSTEREN FONKSIYON
SLLI * Find(SLLI ** head,int sayi)
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
SLLI * bubbleSort(SLLI ** head)
{
    iter = (*head);
    SLLI * temp;

    if (iter == NULL)
    {
        return;
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
SLLI * swapNode(SLLI *a, SLLI *b)
{
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}
///DUGUM SILME
SLLI * deleteNode(SLLI ** head,int data)
{
    SLLI * temp;
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
    
    addToEnd(&root,0);
    addToEnd(&root,5);
    addToEnd(&root,20);
    addToBegin(&root,-10);
    addSequence(&root,10);
    addSequence(&root,15);
    addSequence(&root,30);
    addSequence(&root,-20);
    addBeforeNumber(&root,10,7);
    addAfterNumber(&root,10,12);
    printList(root);
    deleteNode(&root,-20);
    printList(root);
    reverseList(&root);
    printList(root);
    countList(root);
    Find(&root,12);
    reverseList(&root);
    addToEnd(&root,3);
    printList(root);
    bubbleSort(&root);
    printList(root);

    return 0;
}

