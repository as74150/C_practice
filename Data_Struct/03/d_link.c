#include <stdio.h>
#include <malloc.h>
#include <string.h>
struct student{
  int num;
  char name[20];
  int score;
  struct student * next;
};
int count;
struct student *create_link(){
  struct student *head, *p1, *p2;
  count=0;
  head=NULL;
  printf("please input data(number: name: score:)\n");
  p1=p2=(struct student *)malloc(sizeof(struct student));
  scanf("%d %s %d",&p1->num,p1->name,&p1->score);
  while(p1->num!=0){
    count++;
    if(1==count){
      head=p1;
    }
    else{
      p2->next=p1;
    }
    p2=p1;
    p1=(struct student *)malloc(sizeof(struct student));
    scanf("%d %s %d",&p1->num,p1->name,&p1->score);
  }
  p2->next=NULL;
  return head;
}

void printf_link(struct student *head){
  struct student *p;
  p=head;
  while(p!=NULL){
    printf("num:%-7dname:%-10sscore:%-7d\n",p->num,p->name,p->score);
    p=p->next;
  }
}

void sort_link(struct student *head){
  struct student *p;
  struct student temp;
  if(head!=NULL&&head->next!=NULL){
    int i;
    for(i=0;i<count-1;i++){
      for(p=head;p->next!=NULL;p=p->next){
        if(p->num>p->next->num){
          temp.num=p->num;
          strcpy(temp.name,p->name);
          temp.score=p->score;
          p->num=p->next->num;
          strcpy(p->name,p->next->name);
          p->score=p->next->score;
          p->next->num=temp.num;
          strcpy(p->next->name,temp.name);
          p->next->score=temp.score;
        }
      }
    }
    
  }
}

struct student *insert_link(struct student *head){
  struct student *p, *idata;
  int flag=0;
  printf("please input insert data\n");
  idata=(struct student *)malloc(sizeof(struct student));
  scanf("%d %s %d",&idata->num,idata->name,&idata->score);
  count++;
  if(NULL==head){
    idata->next=NULL;
    return idata;
    flag=1;
  }
  else if(idata->num<=head->num){
    idata->next=head;
    flag=1;
    return idata;
  }
  else{
    for(p=head;p->next!=NULL;p=p->next){
      if(idata->num<=p->next->num){
        idata->next=p->next;
        p->next=idata;
        flag=1;
        return head;
      }
    }
    if(flag==0){
      p->next=idata;
      idata->next=NULL;
      return head;
    }
  }
}

struct student *search_node(struct student *head){
  struct student *p;
  int num;
  printf("please input the number of node:\n");
  scanf("%d",&num);
  for(p=head;p!=NULL;p=p->next){
    if(p->num==num){
      return p;
    }
  }
  printf("can't find the node!\n");
  return NULL;
}

struct student *delete_node(struct student *head){
  struct student *p, *q;
  int num;
  printf("please input the number of node:\n");
  scanf("%d",&num);
  if(num==head->num){
    p=head->next;
    free(head);
    count--;
    return p;
  }
  else{
    for(q=head,p=head->next;p!=NULL;p=p->next,q=q->next){
      if(p->num==num){
        q->next=p->next;
        free(p);
        count--;
        return head;
      }
    }
    printf("can't find the node!\n");
    return head;
  }
}

struct student *clear_list(struct student *head){
  struct student *p, *q;
  if(head->next==NULL){
    free(head);
    return NULL;
  }
  else{
    for(p=head,q=p->next;p!=NULL;p=p->next,q=q->next){
      free(p);
      p=q;
    }
    return p;
  }
}

int main()
{
  struct student *p, *select;
  int operate;
  p=NULL;
  printf("1.动态创建链表 2.打印链表 3.插入节点 4.查询节点 5.删除节点 6.清空链表 0.退出程序\n");
  printf("请输入操作:\n");
  while(scanf("%d",&operate)){
    switch(operate){
      case 1:
        if(!p){
          p=create_link();
          sort_link(p);
        }
        else{
          printf("链表已经存在,请先清空\n");
        }
        printf("1.动态创建链表 2.打印链表 3.插入节点 4.查询节点 5.删除节点 6.清空链表 0.退出程序\n");
        printf("请输入操作:\n");break;
      case 2:
        if(!p){
          printf("Null,先创建吧\n");
        }
        else{
          printf_link(p);
        }
        printf("1.动态创建链表 2.打印链表 3.插入节点 4.查询节点 5.删除节点 6.清空链表 0.退出程序\n");
        printf("请输入操作:\n");break;
      case 3:
        p=insert_link(p);
        printf("1.动态创建链表 2.打印链表 3.插入节点 4.查询节点 5.删除节点 6.清空链表 0.退出程序\n");
        printf("请输入操作:\n");break;
      case 4:
        if(!p){
          printf("Null,先创建吧\n");
        }
        else{
          select=search_node(p);
          if(select){
            printf("num:%-7dname:%-10sscore:%-7d\n",select->num,select->name,select->score);
          }
        }
        printf("1.动态创建链表 2.打印链表 3.插入节点 4.查询节点 5.删除节点 6.清空链表 0.退出程序\n");
        printf("请输入操作:\n");break; 
      case 5:
        if(!p){
          printf("Null,先创建吧\n");
        }
        else{
          p=delete_node(p);
        }
        printf("1.动态创建链表 2.打印链表 3.插入节点 4.查询节点 5.删除节点 6.清空链表 0.退出程序\n");
        printf("请输入操作:\n");break; 
      case 6:
        if(!p){
          printf("Null,先创建吧\n");
        }
        else{
          p=clear_list(p);
        }
        printf("1.动态创建链表 2.打印链表 3.插入节点 4.查询节点 5.删除节点 6.清空链表 0.退出程序\n");
        printf("请输入操作:\n");break; 
      case 0:
        return 0;
      default:
        printf("输出错误\n");
        printf("1.动态创建链表 2.打印链表 3.插入节点 4.查询节点 5.删除节点 6.清空链表 0.退出程序\n");
        printf("请输入操作:\n");break;
    }
  }
}
