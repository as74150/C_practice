#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define minTableSize 20

enum isEmpty{empty,legitimate};

typedef struct dataNode{
  int data;
  enum isEmpty flag;
}Node;

typedef struct dataNode *pNode;

typedef struct hashTable{
  int tableSize;
  int elemNum;
  struct dataNode *table;
}HashTable;

typedef struct hashTable *pHashNode;

#ifndef _Hash_Open_Addressing_H
pHashNode initHashTable(int );
int nextPrime(int );
int Hash(int ,pHashNode );
int find_node(int ,pHashNode );
pHashNode insert_node(int ,pHashNode );
void printf_node(pHashNode );
void lazyDelete_node(int ,pHashNode );
void dispose_Table(pHashNode );
pHashNode rehash(pHashNode );
#endif

pHashNode initHashTable(int tableSize){
  pHashNode p;
  int i;
  p=malloc(sizeof(pHashNode));
  if(p==NULL){
    printf("Out of space!\n");
    return ;
  }
  p->tableSize=nextPrime(tableSize);
  p->elemNum=0;
  p->table=malloc(sizeof(pNode)*p->tableSize);
  if(p->table==NULL){
    printf("Out of space!\n");
    return ;
  }
  for(i=0;i<p->tableSize;i++)
    p->table[i].flag=empty;
  return p;
}

int nextPrime(int num){
  int i,j,k;
  for(i=num;;i++){
    k=sqrt(i);
    for(j=2;j<=k;j++){
      if(i%j==0)
        break;
    }
    if(j>k)
      return i;
  }
}

int find_node(int key,pHashNode p){
  int position, count=0;
  position=Hash(key,p);
  while(p->table[position].flag==legitimate&&p->table[position].data!=key){
    position+=2*++count-1;
  }
  if(position>=p->tableSize)
    position-=p->tableSize;
    return position;
}

pHashNode insert_node(int key,pHashNode p){
  int position;
  position=find_node(key,p);
  if(p->table[position].flag==empty){
    p->table[position].flag=legitimate;
    p->table[position].data=key;
    p->elemNum++;
  }
  if(p->elemNum==(int)p->tableSize/2){
    printf("Table element enough,So rehash!\n");
    p=rehash(p);
  }
  return p;
}

void printf_node(pHashNode p){
  int i;
  for(i=0;i<p->tableSize;i++){
    printf("[%3d]:",i);
    if(p->table[i].flag==legitimate)
      printf("%-4d",p->table[i].data);
    printf("\n");
  }
  printf("element number=%d\n",p->elemNum);
}

int Hash(int key,pHashNode p){
  return key%p->tableSize;
}

void lazyDelete_node(int key,pHashNode p){
  int position;
  position=find_node(key,p);
  if(p->table[position].flag==legitimate&&p->table[position].data==key){
    p->table[position].flag=empty;
    p->elemNum--;
  }
  else
    printf("can't find the data!\n");
}

void dispose_Table(pHashNode p){
  free(p->table);
  free(p);
}

pHashNode rehash(pHashNode p){
  int i;
  pHashNode pNew;
  pNew=initHashTable(2*p->tableSize);   //再散列
  for(i=0;i<p->tableSize;i++){
    if(p->table[i].flag==legitimate)
      pNew=insert_node(p->table[i].data,pNew);
  }
  free(p->table);
  free(p);
  return pNew;
}

int main()
{
  int key, opterate, tableSize;
  pHashNode pTable;
  printf("please input the size:\n");
  scanf("%d",&tableSize);
  if(tableSize<minTableSize){
    printf("Size bigger!\n");
    scanf("%d",&tableSize);
  }
  pTable=initHashTable(tableSize);
  printf("1.插入 2.打印 3.删除(懒惰) 4.查询 0.退出\n");
  while(scanf("%d",&opterate)){
    switch(opterate){
      case 1:
        printf("please input data to insert:\n");
        scanf("%d",&key);
        pTable=insert_node(key,pTable);
        printf("1.插入 2.打印 3.删除(懒惰) 4.查询 0.退出\n");break;
      case 2:
        printf_node(pTable);
        printf("1.插入 2.打印 3.删除(懒惰) 4.查询 0.退出\n");break;
      case 3:
        printf("please input data to delete:\n");
        scanf("%d",&key);
        lazyDelete_node(key,pTable);
        printf("1.插入 2.打印 3.删除(懒惰) 4.查询 0.退出\n");break;
      case 4:
        printf("please input data to search:\n");
        scanf("%d",&key);
        int position=find_node(key,pTable);
        if(pTable->table[position].flag==legitimate&&pTable->table[position].data==key){
          printf("Find it,it't position=[%d]\n",position);
        }
        else
          printf("can't find it!\n");
        printf("1.插入 2.打印 3.删除(懒惰) 4.查询 0.退出\n");break;
      case 0:
        dispose_Table(pTable);
        return 0;
      default:
        printf("无此操作\n1.插入 2.打印 3.删除(懒惰) 4.查询 0.退出\n");break;
    }
  }
}
