#include <stdio.h>
#include <malloc.h>

typedef struct node{
  int item;
  int front;
  int rear;
  int size;
  int *Array;
}Node;

typedef struct node *pNode;
int maxSize;

pNode creat_queue(){
  pNode p;
  p=(pNode)malloc(sizeof(pNode));
  printf("please input the capacity of your queue:\n");
  scanf("%d",&maxSize);
  p->Array=malloc(sizeof(int)*maxSize);
  p->size=p->front=0;
  p->rear=-1;
  return p;
}

void enqueue(pNode p){
  if(!p){
    printf("please creat queue first!\n");
  }
  else if(p->size<maxSize){
    int data;
    printf("please input the data:\n");
    scanf("%d",&data);
    p->Array[(++p->rear)%maxSize]=data;
    if(p->rear==maxSize){
      p->rear=0;
    }
    p->size++;
  }
  else
    printf("Queue Fill!\n");
}

void printf_queue(pNode p){
  if(!p){
    printf("please creat queue first!\n");
  }
  else if(p->size==0){
    printf("Queue empty!\n");
  }
  else{
    int i;
    if(p->front<=p->rear){
      for(i=p->front;i<=p->rear;i++){
        printf("%-5d",p->Array[i]);
      }
      printf("\n");
    }
    else{
      for(i=p->front;i<maxSize;i++){
        printf("%-5d",p->Array[i]);
      }
      for(i=0;i<=p->rear;i++){
        printf("%-5d",p->Array[i]);
      }
      printf("\n");
    }
  }
}

void dequeue(pNode p){
  if(!p){
    printf("please creat queue first!\n");
  }
  else if(p->size==0){
    printf("Queue empty!\n");
  }
  else{
    p->front++;
    if(p->front==maxSize){
      p->front=0;
    }
    p->size--;
  }
}

void empty_queue(pNode p){
  if(!p){
    printf("please creat queue first!\n");
  }
  else{
    p->size=p->front=0;
    p->rear=-1;
  }
}

pNode dispose_queue(pNode p){
  if(!p){
    printf("please creat queue first!\n");
  }
  else{
    free(p->Array);
    free(p);
  }
  return NULL;
}

int main()
{
  pNode pQueue=NULL;
  int opterate;
  printf("1.动态创建队列 2.打印 3.入队 4.队列 5.初始化队 6.释放 0.退出:\n");
  while(scanf("%d",&opterate)){
    switch(opterate){
      case 1:
        if(pQueue){
          printf("Queue is Exist!\n");
        }
        else{
          pQueue=creat_queue();
        }
        printf("1.动态创建队列 2.打印 3.入队 4.队列 5.初始化队 6.释放 0.退出:\n");
        break;
      case 2:
        printf_queue(pQueue);
        printf("1.动态创建队列 2.打印 3.入队 4.队列 5.初始化队 6.释放 0.退出:\n");
        break;
      case 3:
        enqueue(pQueue);
        printf("1.动态创建队列 2.打印 3.入队 4.队列 5.初始化队 6.释放 0.退出:\n");
        break;
      case 4:
        dequeue(pQueue);
        printf("1.动态创建队列 2.打印 3.入队 4.队列 5.初始化队 6.释放 0.退出:\n");
        break;
      case 5:
        empty_queue(pQueue);
        printf("1.动态创建队列 2.打印 3.入队 4.队列 5.初始化队 6.释放 0.退出:\n");
        break;
      case 6:
        pQueue=dispose_queue(pQueue);
        printf("1.动态创建队列 2.打印 3.入队 4.队列 5.初始化队 6.释放 0.退出:\n");
        break;
      default:
        printf("[无此操作]1.动态创建队列 2.打印 3.入队 4.队列 5.初始化队 6.释放 0.退出:\n");
        break;
      case 0:
        return 0;    
    }
  }
}
