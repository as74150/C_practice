#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define minTableSize 10
#define initDataSize 50

typedef struct linkListNode{
  int data;
  struct linkListNode *next;
}Node;

typedef struct hashTbale{
  int tableSize;
  struct linkListNode **hashList;    //相当与二维数组的指针
}HashTable;

typedef struct linkListNode *pNode;

typedef struct hashTbale *pHashNode;

#ifndef _Hash_Table_Separate_Chaining_H
pHashNode initHashTable();
int nextPrime(int );
int Hash(int,pHashNode);
pNode find_node(int,pHashNode);
void insert_node(int ,pHashNode);
void delete_node(int ,pHashNode);
void printf_Table(pHashNode);
#endif

int nextPrime(int num){
  int i,k;
  for(i=num;;i++){
    k=sqrt(i);
    int j;
    for(j=2;j<=k;j++){
      if(i%j==0)
        break; 
    }
    if(j>k){
      return i;
    }
  }
}

pHashNode initHashTable(){
  pHashNode p;
  int i, tableSize;
  printf("please input the table size:\n");
  scanf("%d",&tableSize);
  while(tableSize<minTableSize){
    printf("input bigger:\n");
    scanf("%d",&tableSize);
  }
  p=(pHashNode)malloc(sizeof(pHashNode));
  if(p==NULL){
    printf("Out of space!\n");
    return NULL;
  }
  p->tableSize=nextPrime(tableSize);
  p->hashList=malloc(sizeof(pNode)*p->tableSize);
  for(i=0;i<p->tableSize;i++){
    p->hashList[i]=malloc(sizeof(Node));
    p->hashList[i]->next=NULL;
  }
  return p;
}

int Hash(int data,pHashNode p){
  return data%p->tableSize;
}

pNode find_node(int key,pHashNode p){
  pNode pn;
  pn=p->hashList[Hash(key,p)]->next;
  while(pn!=NULL&&pn->data!=key){
    pn=pn->next;
  }
  return pn;
}

void insert_node(int key,pHashNode p){
  pNode ptemp, pHead;
  if(find_node(key,p)==NULL){
    ptemp=malloc(sizeof(pNode));
    ptemp->data=key;
    pHead=p->hashList[Hash(key,p)];
    ptemp->next=pHead->next;
    pHead->next=ptemp;
  }
}


void printf_Table(pHashNode p){
  int i;
  pNode pn;
  for(i=0;i<p->tableSize;i++){
    pn=p->hashList[i]->next;
    printf("[%3d]:",Hash(i,p));
    while(pn!=NULL){
      printf("%-4d",pn->data);
      pn=pn->next;
    }
    printf("\n");
  }
}

void delete_node(int key,pHashNode p){
  pNode pn, ptemp, pHead;
  pn=pHead=p->hashList[Hash(key,p)];
  while(pn->next!=NULL&&pn->next->data!=key){
    pn=pn->next;
  }
  if(pn->next!=NULL){
    if(pn->next->next==NULL){
      ptemp=pn->next;
      pn->next=NULL;
      free(ptemp);
    }
    else{
      ptemp=pn->next;
      pn->next=ptemp->next;
      free(ptemp);
    }
  }
  else
    printf("can't find data!\n");
}

int main()
{
  pHashNode pTable=initHashTable();
  pNode pFind=NULL;
  srand((unsigned) time(NULL));
  int i, opterate, key;
  for(i=0;i<initDataSize;i++){
    insert_node(rand()%200+1,pTable);  
  }
  //随机建立一个hash表
  printf("1.插入 2.打印 3.删除 4.查找 0.退出\n");  
  while(scanf("%d",&opterate)){
    switch(opterate){
      case 1:
        printf("please input the insert value:\n");
        scanf("%d",&key);
        insert_node(key,pTable);
        printf("1.插入 2.打印 3.删除 4.查找 0.退出\n");break;
      case 2:
        printf_Table(pTable);
        printf("1.插入 2.打印 3.删除 4.查找 0.退出\n");break;
      case 3:
        printf("please input the delete value\n");
        scanf("%d",&key);
        delete_node(key,pTable);
        printf("1.插入 2.打印 3.删除 4.查找 0.退出\n");break;
      case 4:
        printf("please input the value you want to find\n");
        scanf("%d",&key);
        pFind=find_node(key,pTable);
        if(pFind){
          printf("find it,it's data = %d\n",pFind->data);
        }
        else
          printf("can't find it!\n");
        printf("1.插入 2.打印 3.删除 4.查找 0.退出\n");break;
      case 0:
        return 0;
      default:
        printf("无此操作\n1.插入 2.打印 3.删除 4.查找 0.退出\n");break;
    }
  }
}
