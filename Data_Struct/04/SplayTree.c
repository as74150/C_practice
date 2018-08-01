/* Top-Down Splay Tree */
#include <stdio.h>
#include <malloc.h>

typedef struct SplayTreeNode{
  int data;
  struct SplayTreeNode *left;
  struct SplayTreeNode *right;
}Node; 

typedef struct SplayTreeNode *pNode;

#ifndef _SplayTree_H
pNode initNullNode(void);
pNode singleRotateLeft(pNode p);   //单旋转
pNode singleRotateRight(pNode p);  //单旋转
pNode splay_node(int item,pNode p);
pNode insert_node(int item,pNode p);
pNode delete_node(int item,pNode p);
pNode clear_tree(pNode p);
void pTree(int count,pNode p);
void printf_Tree(pNode p);
#endif

static pNode nullNode=NULL;    //声明NULL节点,减少判断节点是否为空

pNode initNullNode(){
  if(nullNode==NULL){
    nullNode=(pNode)malloc(sizeof(pNode));
    nullNode->left=nullNode->right=nullNode;
  }
  return nullNode; 
}

pNode singleRotateLeft(pNode p){
  pNode p1;
  p1=p->left;
  p->left=p1->right;
  p1->right=p;
  return p1;
}

pNode singleRotateRight(pNode p){
  pNode p1;
  p1=p->right;
  p->right=p1->left;
  p1->left=p;
  return p1;
}

pNode splay_node(int item,pNode p){
  static Node header;
  pNode leftMaxTree, rightMinTree;
  header.left=header.right=nullNode;
  leftMaxTree=rightMinTree=&header;
  nullNode->data=item;
  while(item!=p->data){
    if(item<p->data){
      if(item<p->left->data){       //Zig-zig(一字型)型
        p=singleRotateLeft(p);      //      |
      }                             //      |
      if(p->left==nullNode)         //      |
        break;                      //      √
      rightMinTree->left=p;         //Zig-zag(之字型)型  第一次运行时header.left=p;
      rightMinTree=p;
      p=p->left;
    }
    else if(item>p->data){         
      if(item>p->right->data){     //Zig-zig(一字型)型
        p=singleRotateRight(p);    //       |
      }                            //       |
      if(p->right==nullNode)       //       |
        break;                     //       √
      leftMaxTree->right=p;        //Zig-zag(之字型)型   第一次运行时header.right=p;
      leftMaxTree=p;
      p=p->right;
    }
  }
  leftMaxTree->right=p->left;
  rightMinTree->left=p->right;
  p->left=header.right;
  p->right=header.left;
  return p;
}

void pTree(int count,pNode p){
  if(p!=nullNode){
    int i=count;
    while(i--){
      printf("   ");
    }
    printf("%d\n",p->data);
    count++;
    pTree(count,p->left);
    pTree(count,p->right);
  }
}

void printf_Tree(pNode p){
  if(p==nullNode){
    printf("Tree empty!\n");
  }
  else
    pTree(0,p);
}

pNode insert_node(int item,pNode p){
  static pNode pNew=NULL;
  if(pNew==NULL){
    pNew=(pNode)malloc(sizeof(pNode));
  }
  pNew->data=item;
  if(p==nullNode){
    p=pNew;
    p->left=p->right=nullNode;
  }
  else{
    p=splay_node(item,p);
    if(item<p->data){              //插入节点比根节点小,应插入到根节点的左孩子节点处
      pNew->left=p->left;
      pNew->right=p;
      p->left=nullNode;
      p=pNew;
    }
    else if(item>p->data){         //插入节点比根节点大,应插入到根节点的右孩子节点处
      pNew->right=p->right;
      pNew->left=p;
      p->right=nullNode;
      p=pNew;
    }
    else
      return p;                  //item==p->data 即点已存在,不做任何操作
  }
  pNew=NULL;
  return p;          
}

pNode delete_node(int item,pNode p){
  pNode pNew;
  if(p!=nullNode){
    p=splay_node(item,p);
    if(item==p->data){   //找到了
      if(p->left==nullNode){
        pNew=p->right;
      }
      else{
        pNew=p->left;
        pNew=splay_node(item,pNew);   //将p->left存入leftMaxTree中再取出,使其变换后右孩子为空
        pNew->right=p->right;
      }
      free(p);
      p=pNew;
    }
    else
      printf("can't find it!\n");
  }
  else
    printf("Tree empty!\n");
  return p;
}

pNode clear_tree(pNode p){
  if(p!=nullNode){
    clear_tree(p->left);
    clear_tree(p->right);
    free(p);
  }
  return nullNode;
}

int main()
{
  pNode pRoot;
  initNullNode();
  pRoot=nullNode;
  printf("1.插入 2.打印 3.删除 4.查询 5.清空 0.退出:\n");
  int opterate, value;
  while(scanf("%d",&opterate)){
    switch(opterate){
      case 1:
        printf("please input a insert value:\n");
        scanf("%d",&value);
        pRoot=insert_node(value,pRoot);
        printf("1.插入 2.打印 3.删除 4.查询 5.清空 0.退出:\n");break;
      case 2:
        printf_Tree(pRoot);
        printf("1.插入 2.打印 3.删除 4.查询 5.清空 0.退出:\n");break;
      case 3:
        printf("please input a delete value:\n");
        scanf("%d",&value);
        pRoot=delete_node(value,pRoot);
        printf("1.插入 2.打印 3.删除 4.查询 5.清空 0.退出:\n");break;
      case 4:
        if(pRoot==nullNode)
          printf("Tree empty!\n");
        else{
          printf("please input a search value:\n");
          scanf("%d",&value);
          pRoot=splay_node(value,pRoot);
        }
        printf("1.插入 2.打印 3.删除 4.查询 5.清空 0.退出:\n");break;
      case 5:
        pRoot=clear_tree(pRoot);
        printf("1.插入 2.打印 3.删除 4.查询 5.清空 0.退出:\n");break;
      case 0:
        return 0;
      default:
        printf("无此操作\n1.插入 2.打印 3.删除 4.查询 5.清空 0.退出:\n");break;
    }
  }
}
