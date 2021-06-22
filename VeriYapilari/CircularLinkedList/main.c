#include <stdio.h>
#include <stdlib.h>

typedef struct CircleLinkedListItem
{
    int data;
    struct CircleLinkedListItem * next;
}CLLI;

CLLI * root;
CLLI * root2;
CLLI * iter;
CLLI * newHead;

CLLI * addToBegin(CLLI ** head,int data);
CLLI * addToEnd(CLLI ** head,int data);
CLLI * addSequence(CLLI ** head,int data);
CLLI * addBeforeNumber(CLLI ** head,int sonrakiSayi,int eklenecekSayi);
CLLI * addAfterNumber(CLLI ** head,int sonrakiSayi,int eklenecekSayi);
CLLI * reverseList(CLLI ** head);
CLLI * countList(CLLI * head);
CLLI * Find(int sayi);
CLLI * bubbleSort(CLLI ** head);
CLLI * swapNode(CLLI *a, CLLI *b);
CLLI * deleteNode(CLLI ** head,int data);
CLLI * mergeLists(CLLI ** head,CLLI ** head2);
CLLI * splitTheListIntoOddOrEven(CLLI ** head);

/// LINKED LISTEYI YAZDIRMA FONKSIYONU
void printList(CLLI * head)
{
    if (head == NULL)
    {
        exit(0);
    }
    
    iter = head;
    printf("%d",iter->data);
    iter = iter -> next;
    /// LISTENIN BASI BOSMU KONTROLU YAPILIR
    while(iter != head)
    {
        printf(" --> %d",iter->data);
        iter = iter -> next;
    }
}
/// LISTENIN BASINA ELEMAN EKLEME
CLLI * addToBegin(CLLI ** head,int data)
{
    /// YENI DUGUM OLUSTURULDU
    CLLI * newNode;
    newNode = (CLLI *)malloc(sizeof(CLLI));
    /// YENI DUGUME PARAMETRE OLARAK GELEN DATA ATILDI
    newNode -> data = data;

    if ((*head) == NULL)
    {
        (*head) = newNode;
        /// YENI DUGUM BASA EKLENILMEK ISTENIYORSA BU DUGUMUN NEXT'I LISTENIN BASI OLMALIDIR
        newNode -> next = (*head);
        return newNode;
    }
    
    iter = (*head);
    while (iter -> next != (*head))
    {
        iter = iter -> next;
    }
    /// YENI DUGUM BASA EKLENILMEK ISTENIYORSA BU DUGUMUN NEXT'I LISTENIN BASI OLMALIDIR
    newNode -> next = (*head);
    /// SON DUGUMUN NEXTI ARTIK YENI HEAD I GOSTERMELIDIR
    iter -> next = newNode;
    /// LISTENIN BASI ARTIK YENI DUGUMDUR
    (*head) = newNode;
    return newNode;
}
/// SAYIYI LINKED LISTIN SONUNA EKLEYEN FONKSIYON
CLLI * addToEnd(CLLI ** head,int data)
{
     /// YENI DUGUM OLUSTURULDU
    CLLI * newNode;
    newNode = (CLLI *)malloc(sizeof(CLLI));
    /// YENI DUGUME PARAMETRE OLARAK GELEN DATA ATILDI
    newNode -> data = data;
    /// NULL DEGERLER ATANDI
    newNode -> next = NULL;

    if((*head) == NULL)
    {
        (*head) = newNode;
        /// YENI DUGUM BASA EKLENILMEK ISTENIYORSA BU DUGUMUN NEXT'I LISTENIN BASI OLMALIDIR
        newNode -> next = (*head);
        return newNode;
    }

    iter = (*head);
    
    while (iter -> next != (*head))
    {
        iter = iter -> next;
    }

    iter -> next = newNode;
    newNode -> next = (*head);
    return newNode;
}
/// ISTENILEN SAYIYI LISTEYE SIRALI BIR SEKILDE KOYAN FONKSIYON
CLLI * addSequence(CLLI ** head,int data)
{
    /// YENI DUGUM OLUSTURULDU
    CLLI * newNode;
    CLLI * temp;
    newNode = (CLLI *)malloc(sizeof(CLLI));
    /// YENI DUGUME PARAMETRE OLARAK GELEN DATA ATILDI
    newNode -> data = data;
    /// NULL DEGERLER ATANDI
    newNode -> next = NULL;
    
    if((*head) == NULL)
    {
        newNode -> next = newNode;
        (*head) = newNode;
        return newNode;
    }

    iter = (*head);

    /// SIRALI EKLENMEK ISTENEN DEGER ROOT DAN KUCUK ISE BASA EKLENIR
    if (iter -> data > data)
    {
        newNode -> next = (*head);
        while (iter -> next != (*head))
        {
            iter = iter -> next;       
        }
        iter -> next = newNode;
        (*head) = newNode;
        return newNode;
    }
    
    
    while (iter -> next != (*head) && iter -> next -> data < data)
    {
        iter = iter -> next;       
    }

    newNode -> next = iter -> next;
    iter -> next = newNode;
    return newNode;
    
    
}
// ISTENILEN SAYININ ONCESINE ISTENILEN SAYIYI YERLESTIREN FOKNSIYON
CLLI * addBeforeNumber(CLLI ** head,int sonrakiSayi,int eklenecekSayi)
{
    /// YENI DUGUM OLUSTURULDU
    CLLI * newNode;
    newNode = (CLLI *)malloc(sizeof(CLLI));
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
    if (iter -> next == (*head) && iter -> data == sonrakiSayi)
    {
        newNode -> next = (*head);
        iter -> next = newNode;
        (*head) = newNode;
        return newNode;
    }

    /// LISTE DE TEK ELEMAN YOKSA AMA ISTENILEN SAYI HEAD VE O SAYI DOGRU ISE YENI HEAD'IMIZ YENI DUGUMDUR
    if (iter == (*head) && iter -> data == sonrakiSayi)
    {
        while (iter -> next != (*head))
        {
            iter = iter -> next;
        }
        
        newNode -> next = (*head);
        iter -> next = newNode;
        (*head) = newNode;
        return newNode;
    }
   
    /// LISTEDE TEK ELEMAN YOK VE ISTENILEN SAYIDA HEAD DEGIL ISE DONGU ILE O SAYI BULUNUR TABI VAR ISE EGER
    while (iter -> next != (*head) && iter -> next -> data != sonrakiSayi)
    {
        if (iter -> next -> data == sonrakiSayi)
        {
            break;
        }
            
        iter = iter -> next;
    }

    /// LISTEDE ONCESINE EKLENILMESI ISTENEN SAYI YOKTUR
    if(iter -> next == (*head) && iter -> next -> data != sonrakiSayi)
    {
        printf("%d listede yoktur bu yuzden %d sayisi listeye eklenemez",sonrakiSayi,eklenecekSayi);
        exit(1);
    }

    newNode -> next = iter -> next;
    iter -> next = newNode;
    return newNode;
    
}
// ISTENILEN SAYININ SONRASINA ISTENILEN SAYIYI YERLESTIREN FOKNSIYON
CLLI * addAfterNumber(CLLI ** head,int oncekiSayi,int eklenecekSayi)
{
    /// YENI DUGUM OLUSTURULDU
    CLLI * newNode;
    newNode = (CLLI *)malloc(sizeof(CLLI));
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
    if (iter -> next == (*head) && iter -> data == oncekiSayi)
    {
        iter -> next = newNode;
        newNode -> next = (*head);
        return newNode;
    }

    /// LISTEDE TEK ELEMAN YOK ISE DONGU ILE O SAYI BULUNUR TABI VAR ISE EGER
    while (iter -> next != (*head) && iter -> data != oncekiSayi)
    {
            if (iter -> data == oncekiSayi)
            {
                break;
            }
            iter = iter -> next;
    }

    /// LISTEDE SONRASINA EKLENILMESI ISTENEN SAYI YOKTUR
    if(iter -> next == (*head) && iter -> data != oncekiSayi)
    {
        printf("%d listede yoktur bu yuzden %d sayisi listeye eklenemez",oncekiSayi,eklenecekSayi);
        exit(1);
    }

    newNode -> next = iter -> next;
    iter -> next = newNode;
    return newNode;
}
/// LISTEYI TERSTEN printListIR
CLLI * reverseList(CLLI ** head)
{
    CLLI* prev = (*head);
    CLLI* current = (*head);
    iter = *head;

    prev  = *head;
    current  = (*head)->next;
    (*head) = (*head)->next;

    // Iterate till you reach the initial node in circular list
    while (*head != iter)
    {
        /// NEXT ITER'IN NEXTINI GOSTERIR
        (*head) = (*head)->next;
        /// ITER'IN NEXT'ININ YONU DEGISIR BURDA OKLARIN YONU TERSE DONER  
        current->next = prev;

        /// PREV ITER'IN YERINI GOSTERIR BURDA PREVI ITER KADAR KAYDIRIYORUZ BOYLECE DONGU BITINCE YENI HEAD PREV OLACAK 
        prev = current;
        /// ITER = ITER -> NEXT DEMIS OLDUK 
        current = (*head);
    }

    current->next = prev;
    *head = prev;  
}
/// LISTEDEKI DUGUM SAYISINI VERIR
CLLI * countList(CLLI * head)
{
    int count=0;

    iter = head;
    do
    {
        count++;
        iter = iter -> next;
    } while (iter != head);
    
    printf("Listedeki eleman sayisi : %d\n",count);
}
/// LISTEDE ISTENILEN ELEMAN VAR MI VARSA KACINCI DUGUMDE OLDUGUNU GOSTEREN FONKSIYON
CLLI * Find(int sayi)
{
    iter = root;
    int i = 1;
    /// LISTE DONGU ILE GEZILIR
    do
    {
        /// ARANAN SAYI VARSA BURDA EKRANA BASILIR
        if(iter -> data == sayi)
        {
            printf("Listede %d sayisi %d. node'da var\n",sayi,i);
            break;
        }
        i++;
        iter = iter -> next;
    } while (iter != root);
    
    /// ISTENILEN SAYI LISTEDE YOKSA KULLANICIYA GOSTERILIR
    if(iter == root)
    {
       printf("Listede %d sayisi yok\n",sayi);
    }
}
/// LISTEDEKI ELEMANLARI SIRALAR
CLLI * bubbleSort(CLLI ** head)
{
    iter = (*head);
    CLLI * temp;

    if (iter == NULL)
    {
        exit(1);
    }
    do
    {
        temp = iter -> next;
        while(temp != (*head))
        {
            /// EGER GELEN DATA BIR SONRAKI DATADAN BUYUKSE SWAP FONKSIYONU ILE YER DEGISTIRIRLER
            if(iter -> data > temp -> data)
            {
                swapNode(iter,temp);
            }
            temp = temp -> next;
        }

        iter = iter -> next;
    } while (iter != (*head));
}
/// DUGUM DEGERLERI YER DEGISTIRIR
CLLI * swapNode(CLLI *a, CLLI *b)
{
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}
/// DUGUM SILME
CLLI * deleteNode(CLLI ** head,int data)
{
    CLLI * temp;
    iter = (*head);

    /// LISTEDE TEK ELEMAN VAR ISE SILINIR VE HEAD'E NULL DEGER ATANIR
    if ((*head)->data == data && iter -> next == (*head))
    {
        temp = (*head);
        free(temp);
        (*head) = NULL;
        return (*head);
    }
    
    /// SILINMEK ISTENEN DEGER BASTA ISE VE LISTEDE TEK ELEMAN YOKSA HEAD KAYDIRILIR VE ESKI DUGUM ILINIR
    if((*head)->data == data)
    {
        temp = (*head);
        (*head) = (*head)->next;
        free(temp);
        return (*head);
    }
    
    /// SILINMEK ISTENEN DEGER BASTA DEGIL VE LISTEDE TEK ELEMAN YOKSA SAYI DONGU ILE ARANIR VARSA SILINIR YOKSA SILINEMEZ
    while(iter -> next != (*head) && iter -> next -> data != data)
    {
        iter = iter -> next;
    }
    if(iter -> next == (*head))
    {
        printf("%d sayisi listede yok\n",data);
        return (*head);
    }
    temp = iter -> next;
    iter -> next = iter -> next -> next;
    free(temp);
    return (*head);
}
/// IKI LISTEYI SIRALI BIRLESTIRME
CLLI * mergeLists(CLLI ** head,CLLI ** head2)
{
    /// YENI BIR DUGUM OLUSTURULDU BU DUGUM HEAD'I TUTACAK VE BU DUGUMUN BIRDE ITER'I OLUSTURULDU
    newHead = NULL;
    newHead -> data;
    CLLI * iter = (*head);
    CLLI * iter2 = (*head2);
    CLLI * newHeadIter = NULL;
    newHeadIter -> data;
    int count = 0;

    /// LISTELERDEN BIRI BOS ISE ISLEM IPTAL
    if(*head == NULL || *head2 == NULL)
    {
        printf("Bir liste bos oldugu icin birlestirilemezler");
        exit(0);
    }
    /// DONGU ILE LISTELER GEZILIR LISTELERDEN HERHANGI BIRI BITENE KADAR 2 LISTEDE DONULUR
    do
    {
        /// BURASI LISTEYI BIRLESTIRINCE YENI HEAD'I BELIRLEDIGIMIZ YER
        if (count == 0)
        {
            /// EGER ILK LISTENIN HEAD'I IKINCI LISTENIN HEAD'INDEN KUCUK ISE YENI HEAD ODUR
            if ((iter -> data < iter2 -> data))
            {
                newHead = (*head);
                newHead -> data = iter -> data;
                newHeadIter = newHead;
                iter = iter -> next;
                count++;
            }
            else
            {
                newHead = (*head2);
                newHead -> data = iter2 -> data;
                newHeadIter = newHead;
                iter2 = iter2 -> next; 
                count++;
            }
            
        }
        /// HEAD BELIRLENDIKTEN SONRA SIRA NEXT'LERE GELDI , LISTENIN ELEMANLARI KARSILASTIRILIR
        /// ORNEGIN ILK LISTEDEKI HEAD DEN SONRAKI ELEMAN IKINCI LISTENIN HEAD'INDEN BUYUK ISE MERGE LISTESINDEKI YENI NEXT IKINCI LISTENIN HEAD'I OLUR
      
        if ((iter -> data < iter2 -> data))
        {
            newHeadIter -> next = iter;
            newHeadIter = newHeadIter -> next;
            newHeadIter -> data = iter -> data;
            iter = iter -> next; 
        }
        else
        {
            newHeadIter -> next = iter2;
            newHeadIter = newHeadIter -> next;
            newHeadIter -> data = iter2 -> data;
            iter2 = iter2 -> next;
        }
          
    } while (iter != (*head) && iter2 != (*head2));
    /// LISTELERDEN BIRI BITTI ISE VE DIGER LISTEDE ELEMAN VARSA ODA NULL OLANA KADAR MERGE LISTESINE EKLENIR
    if (iter == (*head) && iter2 != (*head2))
    {
        while (iter2 != (*head2))
        {
            newHeadIter -> next = iter2;
            newHeadIter -> next -> data = iter2 -> data;
            newHeadIter = newHeadIter -> next;
            iter2 = iter2 -> next;
        }
    }
    
    if (iter != (*head) && iter2 == (*head2))
    {
        while (iter != (*head))
        {
            newHeadIter -> next = iter;
            newHeadIter -> next -> data = iter -> data;
            newHeadIter = newHeadIter -> next;
            iter = iter -> next;
        }
    }
    
    /// YENI HEAD YAZMA FONKSIYONUNA GONDERILIR VE MERGE LISTESI EKRANA BASILIR
    printList(newHead);
    return newHead;
}
/// LISTEYI TEK,ÇIFT OLARAK 2 LISTEYE AYIRMA
CLLI * splitTheListIntoOddOrEven(CLLI ** head)
{
    /// YENI BIR DUGUM OLUSTURULDU BU DUGUM HEAD'I TUTACAK VE BU DUGUMUN BIRDE ITER'I OLUSTURULDU
    CLLI * newOddHead = NULL;
    CLLI * newEvenHead = NULL;
    CLLI * newOddHeadIter;
    CLLI * newEvenHeadIter;
    iter = (*head);
    CLLI * temp = iter;
    int oddCount = 0;
    int evenCount = 0;
    int count = 0;
    
    
    /// LISTE BOS VEYA TEK ELEMANLI ISE ISLEM IPTAL
    if(iter == NULL || iter -> next == (*head))
    {
        printf("Bu liste bos oldugu icin veya listede tek eleman oldugu icin ayrilamaz");
        exit(0);
    }
    /// LISTEDE SON ELEMANA KADAR GIDILIR
    do
    {
        /// IF VE ELSE IF'TE YAPILMAK ISTENEN SUDUR : COUNTLARIN 0 OLDUGU DEGERLER HEAD'LERDIR BOYLELIKLE ILK TEK VE CIFT LISTENIN HEADLERI BELIRLENMIS OLUR
        if (oddCount == 0 && iter -> data % 2 != 0)
        {
            newOddHead = iter;
            iter = iter -> next;
            newOddHead -> next = newOddHead;
            newOddHeadIter = newOddHead;
            newOddHeadIter -> next = newOddHead;
            oddCount++;
        }
        else if (evenCount == 0 && iter -> data % 2 == 0)
        {
            newEvenHead = iter;
            iter = iter -> next;
            newEvenHead -> next = newEvenHead;
            newEvenHeadIter = newEvenHead;
            newEvenHeadIter -> next = newEvenHead;
            evenCount++;
        }
        /// ELSE DE ISE SAYI TEK MI CIFT MI KONRTOL EDILIR VE LISTEYE BAGLANIR
        else
        {
            if (iter -> data % 2 == 0)
            {
                newEvenHeadIter -> next = iter;
                iter = iter -> next;
                newEvenHeadIter -> next -> next = newEvenHead;
                newEvenHeadIter = newEvenHeadIter -> next;
            }
            else
            {
                newOddHeadIter -> next = iter;
                iter = iter -> next;
                newOddHeadIter -> next -> next = newOddHead;
                newOddHeadIter = newOddHeadIter -> next;  
            }
        }
    } while (iter != (*head));

    /// ORIJINAL LISTEDE EGER TEK VEYA CIFT SAYI YOK ISE BU LISTE AYRILAMAZ
    if(evenCount == 0 || oddCount == 0)
    {
        printf("Bu liste tek cift olarak 2 listeye ayrilamaz");
        exit(0);
    }

    printList(newOddHead);
    printf("\n");
    printList(newEvenHead);

    return newEvenHead,newOddHead;
}
int main()
{
    root = NULL;
    root2 = NULL;

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
    
    // addToBegin(&root,5);
    // addBeforeNumber(&root,5,2);
    // addBeforeNumber(&root,4,1);
    
    // addToBegin(&root,5);
    // addAfterNumber(&root,5,20);
    // addAfterNumber(&root,5,10);
    // addAfterNumber(&root,20,30);

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
    // deleteNode(&root,5);
    // printList(root);

    // addToEnd(&root,1);
    // addToEnd(&root,3);
    // addToEnd(&root,5);
    // addToEnd(&root,7);

    // printList(root);
    // printf("\n");

    // addToEnd(&root2,2);
    // addToEnd(&root2,4);
    // addToEnd(&root2,6);

    // printList(root2);
    // printf("\n");

    // mergeLists(&root,&root2);
    // printf("\n");
    // splitTheListIntoOddOrEven(&newHead);

    // addToEnd(&root,1);
    // addToEnd(&root,2);  
    // addToEnd(&root,3);
    // addToEnd(&root,4);
    // addToEnd(&root,5);
    // addToEnd(&root,6);
   
   
    // splitTheListIntoOddOrEven(&root);

    return 0;
}

