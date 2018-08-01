#include <stdio.h>
#include <malloc.h>

typedef struct binarySearchTreeNode{      //二差查找树
  int data;
  int deep;
  struct binarySearchTreeNode *left;
  struct binarySearchTreeNode *right;
}Node;

typedef struct binarySearchTreeNode *pNode;

pNode insert(int d,int x,pNode p){
  if(!p){
    p=(pNode)malloc(sizeof(pNode));
    p->data=x; 
    p->deep=d;
    p->left=p->right=NULL;  
  }
  else if(x<p->data){
    p->left=insert(++d,x,p->left);   
  }
  else if(x>p->data){
    p->right=insert(++d,x,p->right);   
  }
  return p;
}

pNode insert_node(pNode p){
  int data;
  pNode pr;
  printf("please input the value you want to insert:\n");
  scanf("%d",&data);
  pr=insert(0,data,p);
  return pr;
}

void printf_tree(pNode p){
  if(p){
    int i;
    for(i=0;i<p->deep;i++){
      printf("  ");
    }
    printf("%d\n",p->data);
    printf_tree(p->left);
    printf_tree(p->right);
  }
}

pNode find(int x,pNode p){  
  if(!p){
    return NULL;
  }
  else if(x<p->data){
    return find(x,p->left);
  }
  else if(x>p->data){
    return find(x,p->right);
  }
  return p;
}

void find_node(pNode p){
  if(!p){
    printf("Tree empty!\n");
  }
  else{
    int data;
    pNode pFind;
    printf("please input the data you want to find:\n");
    scanf("%d",&data);
    pFind=find(data,p);
    if(pFind){
      printf("Find it,and it's deepth=%d\n",pFind->deep);
    }
    else{
      printf("Can't find it!\n");
    }
  }
}

pNode findMin(pNode p){
  if(!p){
    return NULL;
  }
  else if(p->left==NULL){
    return p;
  }
  else{
    return findMin(p->left);
  }
}

void findMin_node(pNode p){
  if(!p){
    printf("Tree empty!\n");
  }
  else{
    printf("the min of Tree=%d\n",findMin(p)->data);
  }
}

pNode findMax(pNode p){
  if(!p){
    return NULL;
  }
  else if(p->right==NULL){
    return p;
  }
  else
    return findMax(p->right);
}

void findMax_node(pNode p){
  if(!p){
    printf("Tree empty!\n");
  }
  else{
    printf("the max of Tree=%d\n",findMax(p)->data);
  }
}

pNode delete(int x,pNode p){
  pNode ptemp;
  if(p==NULL){
    printf("can't find it!\n");
  }
  else if(x<p->data){
    p->left=delete(x,p->left);
  }
  else if(x>p->data){
    p->right=delete(x,p->right);
  }
  else if(p->left&&p->right){   //Node P有左右两个孩子节点
    ptemp=findMin(p->right);
    p->data=ptemp->data;
    p->right=delete(ptemp->data,p->right);
  }
  else{
    ptemp=p;
    if(!p->right){
       p=p->left;
       if(p)
         p->deep--;
    }
    else if(!p->left){
      p=p->right;
      if(p)
        p->deep--;
    }
    free(ptemp);
  }
  return p; 
}

pNode delete_node(pNode p){
  if(!p){
    printf("Tree empty!\n");
    return p;
  }
  else{
    int data;
    printf("please input the data you want to delete:\n");
    scanf("%d",&data);
    return delete(data,p);
  }
}

pNode clear_tree(pNode p){
  if(p){
    clear_tree(p->left);
    clear_tree(p->right);
    free(p);
  }
  return NULL;
}

int main()
{
  pNode pRoot=NULL;
  int opterate;
  printf("1.插入 2.打印 3.删除 4.查询 5.Max 6.Min 7.释放 0.退出:\n");
  while(scanf("%d",&opterate)){
    switch(opterate){
      case 1:
        pRoot=insert_node(pRoot);
        printf("1.插入 2.打印 3.删除 4.查询 5.Max 6.Min 7.释放 0.退出:\n");
        break;
      case 2:
        if(pRoot){
          printf_tree(pRoot);
        }
        else
          printf("Tree empty!\n");
        printf("1.插入 2.打印 3.删除 4.查询 5.Max 6.Min 7.释放 0.退出:\n");
        break;
      case 3:
        pRoot=delete_node(pRoot);
        printf("1.插入 2.打印 3.删除 4.查询 5.Max 6.Min 7.释放 0.退出:\n");
        break;
      case 4:
        find_node(pRoot);
        printf("1.插入 2.打印 3.删除 4.查询 5.Max 6.Min 7.释放 0.退出:\n");
        break;
      case 5:
        findMax_node(pRoot);
        printf("1.插入 2.打印 3.删除 4.查询 5.Max 6.Min 7.释放 0.退出:\n");
        break;
      case 6:
        findMin_node(pRoot);
        printf("1.插入 2.打印 3.删除 4.查询 5.Max 6.Min 7.释放 0.退出:\n");
        break;
      case 7:
        pRoot=clear_tree(pRoot);
        printf("1.插入 2.打印 3.删除 4.查询 5.Max 6.Min 7.释放 0.退出:\n");
        break;
      case 0:
        return 0; 
    }
  }
}
