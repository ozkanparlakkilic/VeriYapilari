#include <stdio.h>
#include <stdlib.h>

/// STRUCT YAPISININ KULLANILMASININ SEBEBI BIRDEN FAZLA FARKLI STACK ISTENEBILECEGI ICINDIR
typedef struct StackOfArray
{
    int size;
    int * array;
    int top;
}Stack;

/// STACK DEGERLERI BURDA OLUSTURULUR STRUCT YAPISI ICINDE DEGER VERILMEZ
Stack * createStack()
{
    Stack * stack = (Stack*)malloc(sizeof(Stack));
    stack -> size = 2;
    stack -> array = NULL;
    stack -> top = 0;
    return stack;
}

/// DIZIDEN SON GIRENI ILK CIKARIR LIFO KONSEPTI ILE CALISIR DIZI BOS ISE CIKARMA ISLEMI YAPMAZ 
int pop(Stack * stack)
{
    /// DIZI BOS ISE CIKARMA ISLEMI YAPMAZ 
    if (stack -> top <= 0  || stack -> array == NULL)
    {
        printf("Dizi bos");
        exit(0);
    }

    /// CIKRILAN DEGERLER DIZININ DORTTE BIRI ISE BU SAYI DEGISEBILIR DIZININ BELLEKTE KAPLADIGI ALAN YARIYA INDIRILIR
    if (stack -> top <= stack -> size/4)
    {
        int *newArray = (int*)malloc(sizeof(int)*(stack->size)/2);
        /// DIZI YENI DIZIYE KOPYALANIR
        for (int i = 0; i < stack -> top; i++)
        {
            newArray[i] = stack -> array[i];
        }
        /// ESKI DIZI TEMIZLENIR VE BELLEKTE ALAN KAZANILIR
        free(stack -> array);
        /// ESKI DIZININ ICI TEMIZLENDIGI ICIN BOSTUR VE ARTIK YENI DIZIYI ALMAYA HAZIRDIR
        stack -> array = newArray;
        stack -> size /= 2;
    }
    /// DIZIDEN ELEMAN CIKARILINCA BOYUT BIR DUSURULUR
    return stack -> array[-- stack -> top];
}
/// DIZIYE ELEMAN EKLER
void push(int data,Stack * stack)
{
    /// DIZI NULL ISE DIZIYE BELLEKTEN YER AYRILIR
    if (stack -> array == NULL)
    {
        stack -> array = (int*)malloc(sizeof(int)*2);
    }

    /// GIRILEN DEGERLER DIZININ BOYUTUNDAN BIR EKSIK ISE BU SAYI DEGISEBILIR DIZININ BELLEKTE KAPLADIGI ALAN IKI KATINA CIKARILIR
    if (stack -> top >= stack -> size - 1)
    {
        int *newArray = (int*)malloc(sizeof(int)*(stack->size)*2);
        /// DIZI YENI DIZIYE KOPYALANIR
        for (int i = 0; i < stack -> size; i++)
        {
            newArray[i] = stack -> array[i];
        }
        /// ESKI DIZI TEMIZLENIR VE BELLEKTE ALAN KAZANILIR
        free(stack -> array);
        /// ESKI DIZININ ICI TEMIZLENDIGI ICIN BOSTUR VE ARTIK YENI DIZIYI ALMAYA HAZIRDIR
        stack -> array = newArray;
        stack -> size *= 2;
    }
    /// DIZIYE ELEMAN EKLENINCE BOYUT BIR ARTTIRILIR
    stack -> array[stack -> top++] = data;
}
/// DIZIYE GIREN SON ELEMANI GOSTERIR
int peek(Stack * stack)
{
    if(stack -> array == NULL)
    {
            exit(0);
    }
    return stack -> array[stack -> top - 1];
}
void printList(Stack * stack)
{
    for (int i = stack -> top - 1; i >= 0; i--)
    {
        printf("%d\n",stack -> array[i]);  
    }
    
}
int main()
{
    Stack * stack1 = createStack();
    
    push(10, stack1);
    push(20, stack1);
    push(30, stack1);
    push(40, stack1);
    push(50, stack1);
   
    printList(stack1);
    printf(" peek --> %d\n",peek(stack1));
    
    
    // printf(" popped --> %d\n",pop(stack1));
    // printList(stack1);
    // printf(" popped --> %d\n",pop(stack1));
    // printf(" popped --> %d\n",pop(stack1));
    // printf(" popped --> %d\n",pop(stack1));
    // printf(" popped --> %d\n",pop(stack1));
    // printf(" popped --> %d\n",pop(stack1));
    
    return 0;
}