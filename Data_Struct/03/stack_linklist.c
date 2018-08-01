#include <stdio.h>
#include <malloc.h>

typedef struct node{
  int data;
  struct node *next;
}Node;
typedef struct node *pNode;
typedef struct pri{
  pNode base;
  pNode top;
}Pri;

Pri creat_stack(){
  pNode base, top, p1, p2;
  Pri pri;
  printf("please input the datas:\n");
  p1=p2=(pNode)malloc(sizeof(Node));
  scanf("%d",&p1->data);
  base=top=NULL;
  while(p1->data!=0){
    if(base==NULL){
      base=p1;
    }
    else{
      p2->next=p1;
    }      
    p2=p1;
    p1=(pNode)malloc(sizeof(Node));
    scanf("%d",&p1->data);
  }
  p2->next=NULL;
  pri.base=base;
  if(base==NULL){
    top=NULL;
  }
  else{
    top=p2;
  }
  pri.top=top;
  return pri;
}

void printf_stack(pNode base){
  pNode p;
  p=base;
  if(base==NULL){
    printf("Stack empty!\n");
  }
  else{
    while(p!=NULL){
      printf("%d->",p->data);
      p=p->next;
    }
    printf("\n");
  }
}

Pri pop_stack(Pri pri){
  pNode p=pri.base;
  Pri pr;
  if(pri.base==NULL){
    printf("Stack empty!\n");
    p=pri.top;
  }
  else if(pri.base==pri.top){
    free(pri.top);
    pr.base=pr.top=NULL;
    return pr;
  }
  else{
    while(p->next!=pri.top){
      p=p->next;
    }
    free(pri.top);
    p->next=NULL;
  }
  pr.base=pri.base;
  pr.top=p;
  return pr;
}

Pri push_stack(Pri pri){
  pNode p;
  Pri pr;
  printf("please input the data you want to push:");
  p=(pNode)malloc(sizeof(pNode));
  scanf("%d",&p->data);
  if(pri.base==NULL){
    pr.base=p;   
  }
  else{
    pr.base=pri.base;
    pri.top->next=p;
  }
  p->next=NULL;
  pr.top=p;
  return pr;
}

Pri clear_stack(Pri pri){
  Pri pr;
  while(pri.base!=NULL){
    pri=pop_stack(pri);
  }
  pr.top=pr.base=NULL;
  return pr;
}

int main()
{
  Pri pri;
  int opterate;
  pri.top=pri.base=NULL;
  printf("1.创建栈 2.打印 3.入栈 4.出栈 5.清空 0.退出\n请输入操作:\n");
  while(scanf("%d",&opterate)){
    switch(opterate){
      case 1:
        if(pri.base!=NULL){
          printf("Error:已经存在一个栈，请先清空栈\n");
        }
        else{
          pri=creat_stack();
        }
        printf("1.创建栈 2.打印 3.入栈 4.出栈 5.清空 0.退出\n请输入操作:\n");
        break;
      case 2:
        printf_stack(pri.base);
        printf("1.创建栈 2.打印 3.入栈 4.出栈 5.清空 0.退出\n请输入操作:\n");
        break;
      case 3:
        pri=push_stack(pri);
        printf("1.创建栈 2.打印 3.入栈 4.出栈 5.清空 0.退出\n请输入操作:\n");
        break;
      case 4:
        pri=pop_stack(pri);
        printf("1.创建栈 2.打印 3.入栈 4.出栈 5.清空 0.退出\n请输入操作:\n");
        break;
      case 5:
        pri=clear_stack(pri);
        printf("1.创建栈 2.打印 3.入栈 4.出栈 5.清空 0.退出\n请输入操作:\n");
        break;
      case 0:
        return 0;
        break; 
      default:
        printf("Error:无此操作\n1.创建栈 2.打印 3.入栈 4.出栈 5.清空 0.退出\n请输入操作:\n");
        break;
    }
  }
}
