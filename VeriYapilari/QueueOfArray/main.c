#include <stdio.h>
#include <stdlib.h>

/// STRUCT YAPISININ KULLANILMASININ SEBEBI BIRDEN FAZLA FARKLI QUEUE ISTENEBILECEGI ICINDIR
typedef struct queueOfArray
{
    int size;
    int * array;
    int head;
    int iter;
}Queue;

/// QUEUE DEGERLERI BURDA OLUSTURULUR STRUCT YAPISI ICINDE DEGER VERILMEZ
Queue * createQueue()
{
    Queue * queue = (Queue*)malloc(sizeof(Queue));
    queue -> size = 2;
    queue -> array = NULL;
    queue -> head = 0;
    queue -> iter = 0;
    return queue;
}

/// DIZIDEN ILK GIRENI ILK CIKARIR  FIFO KONSEPTI ILE CALISIR DIZI BOS ISE CIKARMA ISLEMI YAPMAZ 
int dequeue(Queue * queue)
{
    /// DIZI BOS ISE CIKARMA ISLEMI YAPMAZ 
    if (queue -> head == queue -> iter)
    {
        printf("Dizi bos");
        exit(0);
    }

    /// CIKRILAN DEGERLER DIZININ DORTTE BIRI ISE BU SAYI DEGISEBILIR DIZININ BELLEKTE KAPLADIGI ALAN YARIYA INDIRILIR
    if ((queue -> iter - queue -> head) <= (queue -> size/4))
    {
        int *newArray = (int*)malloc(sizeof(int)*(queue->size)/2);
        /// DIZI YENI DIZIYE KOPYALANIR
        for (int i = 0; i < (queue -> iter - queue -> head); i++)
        {
            newArray[i] = queue -> array[queue -> head+i];
        }
        queue -> iter -= queue -> head;
        queue -> head=0;
        /// ESKI DIZI TEMIZLENIR VE BELLEKTE ALAN KAZANILIR
        free(queue -> array);
        /// ESKI DIZININ ICI TEMIZLENDIGI ICIN BOSTUR VE ARTIK YENI DIZIYI ALMAYA HAZIRDIR
        queue -> array = newArray;
        queue -> size /= 2;
    }
    /// DIZIDEN ELEMAN CIKARILINCA BOYUT BIR DUSURULUR
    return queue -> array[queue->head++];
}
/// DIZIYE ELEMAN EKLER
void enqueue(Queue * queue,int data)
{
    /// DIZI NULL ISE DIZIYE BELLEKTEN YER AYRILIR
    if (queue -> array == NULL)
    {
        queue -> array = (int*)malloc(sizeof(int)*2);
    }

    /// GIRILEN DEGERLER DIZININ BOYUTUNDAN BIR EKSIK ISE BU SAYI DEGISEBILIR DIZININ BELLEKTE KAPLADIGI ALAN IKI KATINA CIKARILIR
    if (queue -> iter >= queue -> size)
    {
        int *newArray = (int*)malloc(sizeof(int)*(queue->size)*2);
        /// DIZI YENI DIZIYE KOPYALANIR
        for (int i = 0; i < queue -> size; i++)
        {
            newArray[i] = queue -> array[i];
        }
        /// ESKI DIZI TEMIZLENIR VE BELLEKTE ALAN KAZANILIR
        free(queue -> array);
        /// ESKI DIZININ ICI TEMIZLENDIGI ICIN BOSTUR VE ARTIK YENI DIZIYI ALMAYA HAZIRDIR
        queue -> array = newArray;
        queue -> size *= 2;
    }
    /// DIZIYE ELEMAN EKLENINCE BOYUT BIR ARTTIRILIR
    queue -> array[queue -> iter++] = data;
}
/// DIZIYE GIREN SON ELEMANI GOSTERIR
int peek(Queue * queue)
{
    if(queue -> array == NULL)
    {
        exit(0);
    }
    return queue -> array[queue -> head++];
}
/// DIZI DE ARTA KALAN BOS YERE BELLEKTE YER KAPLAYAN BOS ALANI TEMIZLER VE HEAD I TEKRAR BASA KAYDIRIR
void cleanMemory(Queue * queue)
{
    if(queue -> head == 0)
    {
        exit(0);
    }
    for (int i = 0; i < queue -> size; i++)
    {
        queue -> array[i] = queue -> array[i+queue->head];
    }
    
}
void printList(Queue * queue)
{
    for (int i = (queue -> iter - queue -> head) - 1; i >= 0; i--)
    {
        printf("%d ",queue -> array[i]);  
    }
    
}
int main()
{
    Queue * queue = createQueue();
    
    for (int i = 0; i < 20; i++)
    {
        enqueue(queue,i*10);
    }
    printList(queue);
    printf(queue);
    // printf(" peek --> %d\n",peek(queue));
    // printf(" peek --> %d\n",peek(queue));
    // printf(" peek --> %d\n",peek(queue));

    for (int i = 0; i < 13; i++)
    {
        printf("%d ",dequeue(queue));
    }
    
    return 0;
}