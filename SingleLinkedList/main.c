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
SLLI * Find(int sayi);
SLLI * bubbleSort(SLLI ** head);
SLLI * swapNode(SLLI *a, SLLI *b);
SLLI * deleteNode(SLLI ** head,int data);

/// LINKED LISTEYI YAZDIRMA FONKSIYONU
void printList(SLLI * head)
{
    /// LISTENIN BASI BOSMU KONTROLU YAPILIR
    while(head != NULL)
    {
        if(head == root)
        {
            printf("%d",head->data);
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

    /// LISTE BOS ISE YENI DUGUM LISTENIN BASINA GETIRILIR
    if((*head) == NULL)
    {
        (*head) = newNode;
        return newNode;
    }

    iter = (*head);
    
    /// LISTE GEZILIR VE ITER'IN NEXT'I NULL OLANA KADAR GIDILIR , BOYLECE SON ELEMAN ELIMIZDE OLUR
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
    
    /// LISTE BOS ISE YENI DUGUM LISTENIN BASINA GETIRILIR
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
        /// LISTE GEZILIR VE EKLENICEK SAYI HER DATAYLA KARŞILAŞTIRILARAK UYGUN OLAN YERE YERLESTIRILIR
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

    /// LISTE DE TEK ELEMAN VARSA VE O SAYI DOGRU ISE YENI HEAD'IMIZ YENI DUGUMDUR 
    if (iter -> next == NULL && iter -> data == sonrakiSayi)
    {
        newNode -> next = (*head);
        (*head) = newNode;
        return newNode;
    }

    /// LISTE DE TEK ELEMAN YOKSA AMA ISTENILEN SAYI HEAD VE O SAYI DOGRU ISE YENI HEAD'IMIZ YENI DUGUMDUR
    if (iter == (*head) && iter -> data == sonrakiSayi)
    {
        newNode -> next = (*head);
        (*head) = newNode;
        return newNode;
    }
    /// LISTEDE TEK ELEMAN YOK VE ISTENILEN SAYIDA HEAD DEGIL ISE DONGU ILE O SAYI BULUNUR TABI VAR ISE EGER
    while (iter -> next != NULL && iter -> next -> data != sonrakiSayi)
    {
        if (iter -> next -> data == sonrakiSayi)
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

    newNode -> next = iter -> next;
    iter -> next = newNode;
    return newNode;
    
}
// ISTENILEN SAYININ SONRASINA ISTENILEN SAYIYI YERLESTIREN FOKNSIYON
SLLI * addAfterNumber(SLLI ** head,int oncekiSayi,int eklenecekSayi)
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

    /// LISTE DE TEK ELEMAN VARSA VE O SAYI DOGRU ISE HEAD'IN NEXT I YENI DUGUM , YENI DUGUM'UN NEXT'I HEAD'DIR 
    if (iter -> next == NULL && iter -> data == oncekiSayi)
    {
        iter -> next = newNode;
        return newNode;
    }

    /// LISTEDE TEK ELEMAN YOK ISE DONGU ILE O SAYI BULUNUR TABI VAR ISE EGER
    while (iter -> next != NULL && iter -> data != oncekiSayi)
    {
            if (iter -> data == oncekiSayi)
            {
                break;
            }
            iter = iter -> next;
    }

    /// LISTEDE SONRASINA EKLENILMESI ISTENEN SAYI YOKTUR
    if(iter -> next == NULL)
    {
        printf("%d listede yoktur bu yuzden %d sayisi listeye eklenemez",oncekiSayi,eklenecekSayi);
        exit(1);
    }

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

        /// NEXT ITER'IN NEXTINI GOSTERIR
        next = iter->next;
        /// ITER'IN NEXT'ININ YONU DEGISIR BURDA OKLARIN YONU TERSE DONER  
        iter->next = prev;

        /// PREV ITER'IN YERINI GOSTERIR BURDA PREVI ITER KADAR KAYDIRIYORUZ BOYLECE DONGU BITINCE YENI HEAD PREV OLACAK 
        prev = iter;
        /// ITER = ITER -> NEXT DEMIS OLDUK 
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
SLLI * Find(int sayi)
{
    iter = root;
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
    if(iter == NULL)
    {
       printf("Listede %d sayisi yok\n",sayi);
    }
}
/// LISTEDEKI ELEMANLARI SIRALAR
SLLI * bubbleSort(SLLI ** head)
{
    iter = (*head);
    SLLI * temp;

    /// LISTE BOS ISE PROGRAM DURUR
    if (iter == NULL)
    {
        exit(0);
    }
    /// LISTENIN SONUNA KADAR GIDILIR
    while(iter != NULL)
    {

        temp = iter -> next;
        while(temp != NULL)
        {
            /// EGER GELEN DATA BIR SONRAKI DATADAN BUYUKSE SWAP FONKSIYONU ILE YER DEGISTIRIRLER
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

    /// LISTENIN BASI SILINMEK ISTENIYORSA GECICI DEGISKENE DEGER ATILIR HEAD BIR SAGA KAYDIRILIR VE GECICI DEGISKEN SILINIR
    if((*head)->data == data)
    {
        temp = (*head);
        (*head) = (*head)->next;
        free(temp);
        return (*head);
    }
    /// LISTE DONGU ILE GEZILIR VE DEGER ARANIR EGER VARSA SILINIR YOK ISE KULLANICIYA LISTEDE YOK DIYE MESAJ GONDERILIR
    while(iter -> next != NULL && iter -> next -> data != data)
    {
        iter = iter -> next;
    }
    if(iter -> next == NULL)
    {
        printf("Listede %d sayisi yok\n",data);
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
    
    // addToBegin(&root,5);
    // addToBegin(&root,0);
    // addToBegin(&root,-10);
    
    // addToEnd(&root,10);
    // addToEnd(&root,20);
    // addToEnd(&root,30);
    
    // addSequence(&root,7);
    // addSequence(&root,14);
    // addSequence(&root,3);
    // addSequence(&root,9);
    
    //  addToBegin(&root,5);
    //  addBeforeNumber(&root,5,2);
    //  addBeforeNumber(&root,3,1);
    
    //  addToBegin(&root,5);
    //  addAfterNumber(&root,5,20);
    //  addAfterNumber(&root,5,10);
    //  addAfterNumber(&root,20,30);

    // addToEnd(&root,10);
    // addToEnd(&root,12);
    // addToEnd(&root,7);
    // addToEnd(&root,8);
    // addToEnd(&root,3);
    // addToEnd(&root,-2);
    // addToEnd(&root,60);
    // addToEnd(&root,35);

    // reverseList(&root);
    // printList(root);
    // printf("\n");
    // countList(root);
    // Find(5);
    // bubbleSort(&root);
    // printList(root);
    // printf("\n");
    
    // addToEnd(&root,10);
    // addToEnd(&root,12);
    // addToEnd(&root,7);
    // deleteNode(&root,7);
    // printList(root);
    return 0;
}

