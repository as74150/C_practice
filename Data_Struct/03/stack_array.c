#include <stdio.h>
#include <malloc.h>
#define emptyStackTop -1

typedef struct node{    //声明栈信息
  int count;            //栈元素个数
  int top;              //栈的top
  int *array;           //指向栈数组
}Node;

typedef struct node *pNode;

int isEmpty(pNode p){
  if(p->top==emptyStackTop){
    return 1;
  }
  else
    return 0;
}

int isFull(pNode p,int n){
  if(p->top>=n-1){
    return 1;
  }
  else
    return 0;
}

void Empty_stack(pNode p){
  if(!p){
    printf("Stact has disposed!\n");
  }
  else{
    p->top=emptyStackTop;
  }
}

pNode creat_stack(int maxSize){
  pNode p;
  p=(pNode)malloc(sizeof(pNode));
  p->array=malloc(sizeof(int)*maxSize);
  p->count=maxSize;
  Empty_stack(p);
  return p;
}

void push_stack(pNode p){
  int data;
  if(!p){
    printf("Stact has disposed!\n");
  }
  else if(isFull(p,p->count)){
    printf("Stack Fulled");
  }
  else{
    printf("please input the data:");
    scanf("%d",&data);
    p->array[++p->top]=data;
  }
}

void pop_stack(pNode p){
  if(!p){
    printf("Stact has disposed!\n");
  }
  else if(isEmpty(p)){
    printf("Stact empty!\n");
  }
  else{
    p->top--;
  }
}

void printf_stack(pNode p){
  if(!p){
    printf("Stact has disposed!\n");
  }
  else if(isEmpty(p)){
    printf("Stact empty!\n");
  }
  else{
    int i;
    for(i=0;i<=p->top;i++){
      printf("%-5d",p->array[i]);
    }
    printf("\n");
  }
}

pNode clear_stack(pNode p){
  if(!p){
    printf("Stact has disposed!\n");
  }
  else{
    free(p->array);
    free(p);
    return NULL;
  }
}

int main()
{
  pNode pArray=NULL;
  int operate;
  printf("1.动态创建栈 2.打印 3.入栈 4.出栈 5.初始化栈 6.释放资源 0.退出\n请输入操作:\n");
  while(scanf("%d",&operate)){
    switch(operate){
      case 1:
        if(pArray){
          printf("栈已存在！先释放\n");
        }
        else{
          int m;
          printf("请输入栈的大小:");
          scanf("%d",&m);
          pArray=creat_stack(m);
        }
        printf("1.动态创建栈 2.打印 3.入栈 4.出栈 5.初始化栈 6.释放资源 0.退出\n请输入操作:\n");
        break;
      case 2:
        printf_stack(pArray);
        printf("1.动态创建栈 2.打印 3.入栈 4.出栈 5.初始化栈 6.释放资源 0.退出\n请输入操作:\n");
        break;
      case 3:
        push_stack(pArray);
        printf("1.动态创建栈 2.打印 3.入栈 4.出栈 5.初始化栈 6.释放资源 0.退出\n请输入操作:\n");
        break;
      case 4:
        pop_stack(pArray);
        printf("1.动态创建栈 2.打印 3.入栈 4.出栈 5.初始化栈 6.释放资源 0.退出\n请输入操作:\n");
        break;
      case 5:
        Empty_stack(pArray);
        printf("1.动态创建栈 2.打印 3.入栈 4.出栈 5.初始化栈 6.释放资源 0.退出\n请输入操作:\n");
        break;
      case 6:
        pArray=clear_stack(pArray);
        printf("1.动态创建栈 2.打印 3.入栈 4.出栈 5.初始化栈 6.释放资源 0.退出\n请输入操作\n");
        break;
      case 0:
        return 0;
      default:
        printf("输入操作错误\n1.动态创建栈 2.打印 3.入栈 4.出栈 5.初始化栈 6.释放资源 0.退出\n请输入操作");
        break;
    }
  }

}
