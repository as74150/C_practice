#include <stdio.h>
#include <malloc.h>

typedef struct node{
  int data;
  struct node *next;
}Node;

typedef struct node *pNode;

typedef struct pri{
  pNode front;   //队首
  pNode rear;    //队尾
}Pri;

Pri creat_queue(){
  pNode p1, p2, head;
  Pri pr;
  printf("please input the datas:\n");
  head=NULL;
  p1=p2=(pNode)malloc(sizeof(pNode));
  scanf("%d",&p1->data);
  while(p1->data!=0){
    if(head==NULL){
      head=p1;
    }
    else{
      p2->next=p1;
    }
    p2=p1;
    p1=(pNode)malloc(sizeof(pNode));
    scanf("%d",&p1->data);
  }
  p2->next=NULL;
  pr.front=head;
  pr.rear=p2;
  return pr;
}

void printf_queue(pNode head){
  pNode p=head;
  if(head!=NULL){
    while(p){
      printf("%-5d",p->data);
      p=p->next;
    }
    printf("\n");
  }
  else
    printf("Queue Empty!\n");
}

Pri enqueue(Pri pri){
  pNode p;
  Pri pr;    
  p=(pNode)malloc(sizeof(pNode));
  printf("please input the data you want to enqueue:\n");
  scanf("%d",&p->data);
  if(!pri.front){
    pr.front=pr.rear=p;    
  }
  else{
    pri.rear->next=p;
    p->next=NULL;
    pr.front=pri.front;
    pr.rear=p;
  }
  return pr;
}

Pri dequeue(Pri pri){
  Pri pr;
  pNode p;
  if(!pri.front){
    printf("Queue Empty!\n");
    return pri;
  }
  else{
    p=pri.front->next;
    free(pri.front);
    pr.front=p;
    pr.rear=pri.rear;
    return pr;
  }
}

Pri clear_queue(Pri pri){
  if(!pri.front){
    printf("Queue Empty!\n");
  }
  else{
    while(pri.front){
      pri=dequeue(pri);
    }
  }
  return pri;
}

int main()
{
  Pri pri;
  pri.front=pri.rear=NULL;
  int operate;
  printf("1.创建队列 2.打印 3.入队 4.出队 5.清空 0.退出\n请输入操作：\n");
  while(scanf("%d",&operate)){
    switch(operate){
      case 1:
        if(pri.front){
          printf("已存在队列！\n");
        }
        else
          pri=creat_queue();
        printf("1.创建队列 2.打印 3.入队 4.出队 5.清空 0.退出\n请输入操作：\n");
        break;
      case 2:
        printf_queue(pri.front);
        printf("1.创建队列 2.打印 3.入队 4.出队 5.清空 0.退出\n请输入操作：\n");
        break;
      case 3:
        pri=enqueue(pri);
        printf("1.创建队列 2.打印 3.入队 4.出队 5.清空 0.退出\n请输入操作：\n");
        break;
      case 4:
        pri=dequeue(pri);
        printf("1.创建队列 2.打印 3.入队 4.出队 5.清空 0.退出\n请输入操作：\n");
        break;
      case 5:
        pri=clear_queue(pri);
        printf("1.创建队列 2.打印 3.入队 4.出队 5.清空 0.退出\n请输入操作：\n");
        break;
      case 0:
        return 0;
      default:
        printf("无此操作!\n1.创建队列 2.打印 3.入队 4.出队 5.清空 0.退出\n请输入操作：\n");
        break;
    }
  }
}
