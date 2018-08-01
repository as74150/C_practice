#include <stdio.h>
#include <stdlib.h>
#define insert_node(Heap) (Heap=insert(Heap))
#define delete_MinNode(Heap) (Heap=deleteMin(Heap))
#define dispose_heap(Heap) (Heap=dispose_node(Heap))

typedef int ElementType;
typedef struct treeNode{
  ElementType element;
  int Npl;
  struct treeNode *left;
  struct treeNode *right;
}TreeNode;
typedef struct treeNode *pPriorityQueueNode;

#ifndef _Leftist_Heap_H
void swapChildNode(pPriorityQueueNode p);
pPriorityQueueNode merge(pPriorityQueueNode p1,pPriorityQueueNode p2);
pPriorityQueueNode merge1(pPriorityQueueNode p1,pPriorityQueueNode p2);
pPriorityQueueNode dispose_node(pPriorityQueueNode p);
pPriorityQueueNode insert(pPriorityQueueNode p);
pPriorityQueueNode deleteMin(pPriorityQueueNode p);
void printf_heap(pPriorityQueueNode p1,pPriorityQueueNode p2);
void printf_node(int count,pPriorityQueueNode p);
#endif

pPriorityQueueNode deleteMin(pPriorityQueueNode p){
  if(!p){
    fprintf(stderr,"Heap empty!\n");
  }
  else{
    pPriorityQueueNode pLeft, pRight;
    pLeft=p->left;
    pRight=p->right;
    free(p);
    p=merge(pLeft,pRight);
  }
  return p;
}

void printf_node(int count,pPriorityQueueNode p){
  if(!p)
    return ;
  int i=count;
  while(i--)
    printf("  ");
  printf("%d\n",p->element);
  count++;
  printf_node(count,p->left);
  printf_node(count,p->right);
}

void printf_heap(pPriorityQueueNode p1,pPriorityQueueNode p2){
  printf("Heap 1:\n");
  if(!p1)
    printf("Empty!\n");
  else
    printf_node(0,p1);
  printf("Heap 2:\n");
  if(!p2)
    printf("Empty!\n");
  else
    printf_node(0,p2);
}

pPriorityQueueNode merge(pPriorityQueueNode p1,pPriorityQueueNode p2){
  if(p1==NULL)
    return p2;
  if(p2==NULL)
    return p1;
  if(p1->element<p2->element)
    return merge1(p1,p2);
  else
    return merge1(p2,p1);
}

pPriorityQueueNode merge1(pPriorityQueueNode pSmall,pPriorityQueueNode pBig){  //用根节点小的堆的右节点再与根节点大堆
  if(pSmall->left==NULL){                                                      //合成(Merge)
    pSmall->left=pBig;   //左氏堆,p->left=NULL,则p->Npl=0
  }
  else{
    pSmall->right=merge(pSmall->right,pBig);
    if(pSmall->left->Npl<pSmall->right->Npl)
      swapChildNode(pSmall);
    pSmall->Npl=pSmall->right->Npl+1;
  }
  return pSmall;
}

void swapChildNode(pPriorityQueueNode p){
  pPriorityQueueNode pTemp;
  pTemp=p->left;
  p->left=p->right;
  p->right=pTemp;
}

pPriorityQueueNode insert(pPriorityQueueNode p){
  pPriorityQueueNode pNew;
  ElementType key;
  pNew=malloc(sizeof(pPriorityQueueNode));
  if(!pNew)
    fprintf(stderr,"Out of space!\n");
  else{
    printf("Please input the insert element:\n");
    scanf("%d",&key);
    pNew->element=key;
    pNew->Npl=0;
    pNew->left=pNew->right=NULL;
    p=merge(pNew,p);
  }
  return p;
}

pPriorityQueueNode dispose_node(pPriorityQueueNode p){
  if(p){
    dispose_node(p->left);
    dispose_node(p->right);
    free(p);
  }
  return NULL;
}

int main(){
  pPriorityQueueNode pHeap1, pHeap2;
  pHeap1=pHeap2=NULL;
  int opterate, otherOpt;
  printf("1.插入 2.打印 3.删除Min 4.合并 5.释放 0.退出\n");
  while(scanf("%d",&opterate)){
    switch(opterate){
      case 1:
        printf("堆几?(1 or 2):\n");
        scanf("%d",&otherOpt);
        if(otherOpt==1)
          insert_node(pHeap1);
        else if(otherOpt==2)
          insert_node(pHeap2);
        else{
          printf("堆几?(1 or 2):\n");
          scanf("%d",&otherOpt);
        } 
        printf("1.插入 2.打印 3.删除Min 4.合并 5.释放 0.退出\n");break;
      case 2:
        printf_heap(pHeap1,pHeap2); 
        printf("1.插入 2.打印 3.删除Min 4.合并 5.释放 0.退出\n");break;
      case 3:
        printf("堆几?(1 or 2):\n");
        scanf("%d",&otherOpt);
        if(otherOpt==1)
          delete_MinNode(pHeap1);
        else if(otherOpt==2)
          delete_MinNode(pHeap2);
        else{
          printf("堆几?(1 or 2):\n");
          scanf("%d",&otherOpt);
        } 
        printf("1.插入 2.打印 3.删除Min 4.合并 5.释放 0.退出\n");break;
      case 4:
        pHeap1=merge(pHeap1,pHeap2);
        pHeap2=NULL;
        printf("1.插入 2.打印 3.删除Min 4.合并 5.释放 0.退出\n");break;
      case 5:
        dispose_heap(pHeap1);
        dispose_heap(pHeap2);
        printf("1.插入 2.打印 3.删除Min 4.合并 5.释放 0.退出\n");break;
      case 0:
        return 0;
      default:printf("无此操作:1.插入 2.打印 3.删除Min 4.合并 5.释放 0.退出\n");break;
        
    } 
  }
  return 0;
}
