#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define queueSize 5
#define Max_Int 2147483647
#define initBinaryTree(P) (P=init(P)) 

typedef int ElementType;
typedef struct binaryTreeNode{
  ElementType element;
  struct binaryTreeNode *nextNode;
  struct binaryTreeNode *leftChild;
}TreeNode;
typedef struct binaryTreeNode *pBinaryTree;
struct binaryQueue{
  int nodeSize;
  struct binaryTreeNode **theTree;
};
typedef struct binaryQueue *pBinaryQueue;

#ifndef _Binary_Queue_H
pBinaryQueue init(pBinaryQueue pQueue);
pBinaryTree mergeTree(pBinaryTree T1,pBinaryTree T2);
pBinaryQueue mergeQueue(pBinaryQueue pQueue1,pBinaryQueue pQueue2);
int isEmpty(pBinaryQueue pQueue);
int deleteMinNode(pBinaryQueue pQueue);
void printf_BinaryQueue(pBinaryQueue pQueue);
void printf_Tree(int count,pBinaryTree T);
void insertNode(ElementType elementKey,pBinaryQueue pQueue);
void randomBulidQueue(pBinaryQueue pQueue1,pBinaryQueue pQueue2);
void disposeQueue(pBinaryQueue pQueue1,pBinaryQueue pQueue2);
void dispose(pBinaryTree T);
#endif

void disposeQueue(pBinaryQueue pQueue1,pBinaryQueue pQueue2){
  int i;
  if(!pQueue1&&!pQueue2){
    fprintf(stderr,"Both queue isn't existed!\n");
    return ;
  }
  if(pQueue1){
    for(i=0;i<queueSize;i++)
      dispose(pQueue1->theTree[i]);
    //free(pQueue1->theTree);
    free(pQueue1);
  }
  if(pQueue2){
    for(i=0;i<queueSize;i++)
      dispose(pQueue2->theTree[i]);
    //free(pQueue2->theTree);
    free(pQueue2);
  }  
}

void dispose(pBinaryTree T){
  if(T){
    dispose(T->leftChild);
    dispose(T->nextNode);
    free(T);
  }
}

void randomBulidQueue(pBinaryQueue pQueue1,pBinaryQueue pQueue2){
  int i,bulidNum1, bulidNum2;
  srand((unsigned) time(NULL));
  bulidNum1=rand()%13+2;
  bulidNum2=rand()%13+2;
  for(i=0;i<bulidNum1;i++)
    insertNode(rand()%99+1,pQueue1);
  for(i=0;i<bulidNum2;i++)
    insertNode(rand()%99+1,pQueue2);
}

int deleteMinNode(pBinaryQueue pQueue){
  int i, minElementPosition;
  pBinaryQueue tmpQueue=NULL;
  pBinaryTree deleteNode, oldNode;
  ElementType deleteNodeElement=Max_Int;
  if(!pQueue){
    fprintf(stderr,"Queue isn't existed!\n");
    return -Max_Int;
  }
  else if(isEmpty(pQueue)){
    fprintf(stderr,"Queue is empty!\n");
    return -Max_Int;
  }
  initBinaryTree(tmpQueue);
  if(tmpQueue){
    for(i=0;i<queueSize;i++){      //找出二项队列中最小的根节点树位置
      if(pQueue->theTree[i]&&pQueue->theTree[i]->element<deleteNodeElement){
        deleteNodeElement=pQueue->theTree[i]->element;
        minElementPosition=i;
      }
    }
    deleteNode=pQueue->theTree[minElementPosition];
    oldNode=deleteNode;
    deleteNode=deleteNode->leftChild;
    free(oldNode);
    tmpQueue->nodeSize=(1<<minElementPosition)-1;
    for(i=minElementPosition-1;i>=0;i--){
      tmpQueue->theTree[i]=deleteNode;
      deleteNode=deleteNode->nextNode;
      tmpQueue->theTree[i]->nextNode=NULL;
    }
    pQueue->theTree[minElementPosition]=NULL;
    pQueue->nodeSize=pQueue->nodeSize-tmpQueue->nodeSize-1;
    mergeQueue(pQueue,tmpQueue);
    free(tmpQueue);  
  }
  return deleteNodeElement;
}

void insertNode(ElementType elementKey,pBinaryQueue pQueue){
  pBinaryQueue tmpQueue=NULL;
  pBinaryTree tmpTree;
  initBinaryTree(tmpQueue);
  if(tmpQueue){
    tmpTree=malloc(sizeof(pBinaryTree));
    if(!tmpTree){
      fprintf(stderr,"Out of space!\n");
      return ;
    }
    tmpTree->element=elementKey;
    tmpTree->leftChild=tmpTree->nextNode=NULL;
    tmpQueue->theTree[0]=tmpTree;
    tmpQueue->nodeSize=1;
    pQueue=mergeQueue(pQueue,tmpQueue);
    free(tmpQueue);
    free(tmpQueue->theTree);
  }
}

void printf_Tree(int count,pBinaryTree T){
  int i=count;
  if(T){
    while(i--)
      printf("  ");
    printf("%d\n",T->element);
    count++;
    printf_Tree(count,T->leftChild);
    printf_Tree(count,T->nextNode);
  }
}

void printf_BinaryQueue(pBinaryQueue pQueue){
  int i;
  if(!pQueue){
    fprintf(stderr,"Queue isn't existed!\n");
    return ;
  }
  else if(isEmpty(pQueue)){
    printf("Queue has on element!\n");
    return ;
  }
  else{
    for(i=0;i<queueSize;i++){
      printf("[%2d]:\n",i);
      if(pQueue->theTree[i])
        printf_Tree(0,pQueue->theTree[i]);
    }
  }
}

int isEmpty(pBinaryQueue pQueue){
  if(pQueue->nodeSize==0)
    return 1;
  else
    return 0;
}

pBinaryQueue mergeQueue(pBinaryQueue pQueue1,pBinaryQueue pQueue2){
  int i, j, maxTreeNode=(1<<queueSize)-1;
  pBinaryTree T1, T2, priMergeTree=NULL;
  if(pQueue1->nodeSize+pQueue2->nodeSize>maxTreeNode)
    fprintf(stderr,"Queue full!\n");
  else{
    pQueue1->nodeSize+=pQueue2->nodeSize;
    for(i=0,j=1;j<=pQueue1->nodeSize;i++,j*=2){
      T1=pQueue1->theTree[i];
      T2=pQueue2->theTree[i];
      switch(!!T1+2*!!T2+4*!!priMergeTree){
        case 0:      /*两个二项队列对应位置的树都为NULL*/
        case 1:      /*二项队列二的对应位置树为NULL*/
          break;
        case 2:      /*二项队列一的对应位置树为NULL*/
          pQueue1->theTree[i]=T2;
          pQueue2->theTree[i]=NULL;break;
        case 4:      /*两个二项队列对应位置的树都为NULL,但是上个位置的树进行过合并*/
          pQueue1->theTree[i]=priMergeTree;
          priMergeTree=NULL;break;
        case 3:      /*两个二项队列对应位置的树都存在,这时将他们进行合并*/
          priMergeTree=mergeTree(T1,T2);
          pQueue1->theTree[i]=pQueue2->theTree[i]=NULL;break;
        case 5:      /*二项队列二的对应位置树为NULL,上个位置的树进行过合并,此时将上次合并后的树与队列一中的树合并*/
          priMergeTree=mergeTree(T1,priMergeTree);
          pQueue1->theTree[i]=NULL;break;
        case 6:      /*二项队列一的对应位置树为NULL,上个位置的树进行过合并,此时将上次合并后的树与队列二中的树合并*/
          priMergeTree=mergeTree(T2,priMergeTree);
          pQueue2->theTree[i]=NULL;break;
        case 7:      /*两个二项队列对应位置的树都存在,且上个位置的树进行过合并,此时将上次合并的值存入队列一中对应位置,
                      再将在两个二项队列中对应位置的树(队列一中的树是上次合并存入前的原始树)合并并存入priMergeTree中*/
          pQueue1->theTree[i]=priMergeTree;
          priMergeTree=mergeTree(T1,pQueue2->theTree[i]);
          pQueue2->theTree[i]=NULL;break;       
      }
    }
    pQueue2->nodeSize=0;
  }
  return pQueue1;
}

pBinaryTree mergeTree(pBinaryTree T1,pBinaryTree T2){  //合并两棵相同大小二项树
  if(T1->element>T2->element)
    return mergeTree(T2,T1);
  T2->nextNode=T1->leftChild;
  T1->leftChild=T2;
  return T1;
}

pBinaryQueue init(pBinaryQueue pQueue){
  if(pQueue)
    fprintf(stderr,"Queue has existed!\n");
  else{
    pQueue=malloc(sizeof(pBinaryQueue));
    if(!pQueue)
      fprintf(stderr,"Out of space!\n");
    else{
      pQueue->theTree=malloc(sizeof(pBinaryTree)*queueSize);
      if(!pQueue->theTree){
        fprintf(stderr,"Out of space");
        return NULL;
      }
    }
    pQueue->nodeSize=0;
  }
  return pQueue;
}

int main(){
  pBinaryQueue pQueue1, pQueue2;
  pQueue1=pQueue2=NULL;
  int opterate, elementKey;
  printf("1.创建 2.打印 3.插入队列1 4.插入队列2 5.删除Min1 6.删除Min2 7.合并 8.释放 0.退出\n");
  while(scanf("%d",&opterate)){
    switch(opterate){
      case 1:
        if(!pQueue1||!pQueue2){
          initBinaryTree(pQueue1);
          initBinaryTree(pQueue2);
          randomBulidQueue(pQueue1,pQueue2);
        }
        else
          printf("Queue has existed!\n");
        printf("1.创建 2.打印 3.插入队列1 4.插入队列2 5.删除Min1 6.删除Min2 7.合并 8.释放 0.退出\n");break;
      case 2:
        printf("Queue1:\n");
        printf_BinaryQueue(pQueue1);
        printf("Queue2:\n");
        printf_BinaryQueue(pQueue2);
        printf("1.创建 2.打印 3.插入队列1 4.插入队列2 5.删除Min1 6.删除Min2 7.合并 8.释放 0.退出\n");break;
      case 3:
        if(pQueue1){
          printf("input a element:\n");
          scanf("%d",&elementKey);
          insertNode(elementKey,pQueue1);
        }
        else
          fprintf(stderr,"Queue isn't existed\n");
        printf("1.创建 2.打印 3.插入队列1 4.插入队列2 5.删除Min1 6.删除Min2 7.合并 8.释放 0.退出\n");break;
      case 4:
        if(pQueue2){
          printf("input a element:\n");
          scanf("%d",&elementKey);
          insertNode(elementKey,pQueue2);
        }
        else
          fprintf(stderr,"Queue isn't existed\n");
        printf("1.创建 2.打印 3.插入队列1 4.插入队列2 5.删除Min1 6.删除Min2 7.合并 8.释放 0.退出\n");break;
      case 5:
        deleteMinNode(pQueue1);
        printf("1.创建 2.打印 3.插入队列1 4.插入队列2 5.删除Min1 6.删除Min2 7.合并 8.释放 0.退出\n");break;
      case 6:
        deleteMinNode(pQueue2);
        printf("1.创建 2.打印 3.插入队列1 4.插入队列2 5.删除Min1 6.删除Min2 7.合并 8.释放 0.退出\n");break;
      case 7:
        if(pQueue1&&pQueue2){
          mergeQueue(pQueue1,pQueue2);
        }
        else
          fprintf(stderr,"Queue1 or Queue2 isn't existed!\n");
        printf("1.创建 2.打印 3.插入队列1 4.插入队列2 5.删除Min1 6.删除Min2 7.合并 8.释放 0.退出\n");break;
      case 8:
        disposeQueue(pQueue1,pQueue2);
        pQueue1=pQueue2=NULL;
        printf("1.创建 2.打印 3.插入队列1 4.插入队列2 5.删除Min1 6.删除Min2 7.合并 8.释放 0.退出\n");break;
      case 0:
        return 0;
      default:
        printf("1.创建 2.打印 3.插入队列1 4.插入队列2 5.删除Min1 6.删除Min2 7.合并 8.释放 0.退出\n");break;
    }
  }
}
