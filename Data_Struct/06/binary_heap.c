#include <stdio.h>
#include <stdlib.h>
#define minHeapSize 10
typedef int ElementType;
typedef struct binaryHeap{
  int heapSize;
  int elePosition;
  ElementType *Array;
}BinaryHeap;
typedef struct binaryHeap *pHeap;

#ifndef _Binary_Heap_By_Array_H
pHeap initBinaryHeap(pHeap p);
void insert_eletemt(pHeap p);
void printf_heap(pHeap p);
int power(int m);
ElementType delete_MinElement(pHeap p);
pHeap dispose_heap(pHeap p);
#endif

pHeap initBinaryHeap(pHeap p){
  if(p)
    printf(",Error,heap has exist!\n");
  else{
    int heapSize;
    printf("please input heap size:\n");
    scanf("%d",&heapSize);
    while(heapSize<minHeapSize){
      printf("Size bigger:\n");
      scanf("%d",&heapSize);
    }
    p=malloc(sizeof(pHeap));
    if(!p)
      printf("Out of space!\n");
    p->heapSize=heapSize;
    p->Array=malloc(sizeof(ElementType)*(p->heapSize+1));
    if(p->Array==NULL)
      printf("Out of space!\n");
    p->elePosition=0;
  }
  return p;
}

void insert_eletemt(pHeap p){
  ElementType element;
  if(!p){
    printf("Error:heap isn't exist!\n");
    return ;
  }
  else if(p->elePosition==p->heapSize){
    printf("Error:heap fill!\n");
    return ;
  }
  else{
    printf("please input the element:\n");
    scanf("%d",&element);
    int i;
    for(i=++p->elePosition;element<p->Array[i/2];i=i/2)
      p->Array[i]=p->Array[i/2];
    p->Array[i]=element;
  }
}

void printf_heap(pHeap p){
  if(!p){
    printf("Error:heap isn't exist!\n");
    return ;
  }
  else if(p->elePosition==0){
    printf("Heap empty!\n");
    return ;
  }
  else{
    int i, j, k, pj;
    printf("Complete Binary Tree Mod:");
    for(i=1,j=0;i<=p->elePosition;i++){
      if(i==(pj=power(j))){
        printf("\n");
        for(k=0;k<40-2*pj;k++)
          printf(" ");
        j++;
      }
      printf("%-4d",p->Array[i]);
    }
    printf("\nArray Mod:\n");
    for(i=1;i<=p->elePosition;i++)
      printf("%-4d",p->Array[i]);
    printf("\n");
  }
}

int power(int m){
  int i, res=1;
  for(i=0;i<m;i++)
    res=res*2;
  return res;
}

ElementType delete_MinElement(pHeap p){
  if(!p){
    printf("Error:heap isn't exist!\n");
    return -1;
  }
  if(p->elePosition==0){
   printf("Error:heap empty!\n");
   return -1;
  }
  int i, child;
  ElementType minElement, lastElement;
  minElement=p->Array[1];
  lastElement=p->Array[p->elePosition--];
  for(i=1;i*2<=p->elePosition;i=child){
    child=2*i;
    if(child!=p->elePosition&&p->Array[child+1]<p->Array[child])
      child++;
    if(p->Array[child]<lastElement)
      p->Array[i]=p->Array[child];
  }
  p->Array[i]=lastElement;
  return minElement;
}

pHeap dispose_heap(pHeap p){
  if(!p){
    printf("Error:heap isn't exist!\n");
    return NULL;
  }
  free(p->Array);
  free(p);
  return NULL;
}

int main(){
  int opterate;
  pHeap pStart=NULL;
  printf("1.创建 2.打印 3.插入 4.删除 5.释放 0.退出\n");
  while(scanf("%d",&opterate)){
    switch(opterate){
      case 1:
        pStart=initBinaryHeap(pStart);
        printf("1.创建 2.打印 3.插入 4.删除 5.释放 0.退出\n");break;
      case 2:
        printf_heap(pStart);
        printf("1.创建 2.打印 3.插入 4.删除 5.释放 0.退出\n");break;
      case 3:
        insert_eletemt(pStart);
        printf("1.创建 2.打印 3.插入 4.删除 5.释放 0.退出\n");break;
      case 4:
        printf("Deleted min element=%d(-1为出错)\n",delete_MinElement(pStart));    
        printf("1.创建 2.打印 3.插入 4.删除 5.释放 0.退出\n");break;
      case 5:
        pStart=dispose_heap(pStart);
        printf("1.创建 2.打印 3.插入 4.删除 5.释放 0.退出\n");break;
      case 0:
        printf("Quit soon....\n");
        return 0;
      default:
        printf("无此操作\n1.创建 2.打印 3.插入 4.删除 5.释放 0.退出\n");break;
    }
  }
}
