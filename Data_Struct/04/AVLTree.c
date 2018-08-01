#include <stdio.h>
#include <malloc.h>

typedef struct AVLtreeNode{
  int data;
  int height;
  struct AVLtreeNode *left;
  struct AVLtreeNode *right;
}Node;

typedef struct AVLtreeNode *pNode;

#ifndef _AVLTree_H
int height(pNode p);
int max_height(int,int);
pNode singleRotate_left(pNode p);
pNode singleRotate_right(pNode p);
pNode doubleRotate_left(pNode p);
pNode doubleRotate_right(pNode p);
pNode insert_node(int x,pNode p);
void pfnode(int count,pNode p);
pNode findMin_node(pNode p);
pNode findMax_node(pNode p);
pNode delete_node(int x,pNode p);
pNode find_node(int x,pNode p);
pNode clear_tree(pNode p);
#endif

int max_height(int a,int b){
  return (a>b)?a:b;
}

int height(pNode p){
  if(!p){
    return -1;
  }
  else{
    return p->height;
  }
}

pNode singleRotate_left(pNode p){    
  pNode p1;
  p1=p->left;
  p->left=p1->right;
  p1->right=p;
  p->height=max_height(height(p->left),height(p->right))+1;
  p1->height=max_height(height(p1->left),height(p1->right))+1;
  return p1;
}

pNode singleRotate_right(pNode p){
  pNode p1;
  p1=p->right;
  p->right=p1->left;
  p1->left=p;
  p->height=max_height(height(p->left),height(p->right))+1;
  p1->height=max_height(height(p1->left),height(p1->right))+1;
  return p1;
}

pNode doubleRotate_left(pNode p){
  p->left=singleRotate_right(p->left);
  return singleRotate_left(p);
}

pNode doubleRotate_right(pNode p){
  p->right=singleRotate_left(p->right);
  return singleRotate_right(p);
}

pNode insert_node(int x,pNode p){
  if(p==NULL){
    p=(pNode)malloc(sizeof(pNode));
    p->data=x;
    p->height=0;
    p->left=p->right=NULL;
  }
  else if(x<p->data){
    p->left=insert_node(x,p->left);
    if(height(p->left)-height(p->right)==2){    //打破平衡
      if(x<p->left->data){                         //情况1
        p=singleRotate_left(p);
      }
      else{                                        //情况3
        p=doubleRotate_left(p); 
      }        
    }
  }
  else if(x>p->data){
    p->right=insert_node(x,p->right);
    if(height(p->right)-height(p->left)==2){    //打破平衡
       if(x>p->right->data){                       //情况2  
        p=singleRotate_right(p);  
      }
      else{                                        //情况4
        p=doubleRotate_right(p);
      }
    }
  }
  p->height=max_height(height(p->left),height(p->right))+1;
  return p;
}

void pfnode(int count,pNode p){
  if(p){
    int i=count;
    while(i--){
      printf("   ");
    }
    printf("%d\n",p->data);
    count++;
    pfnode(count,p->left);
    pfnode(count,p->right);
  }
}

void printf_tree(pNode p){
  if(!p){
    printf("Tree empty!\n");
  }
  else{
    pfnode(0,p);
  }
}

pNode findMin_node(pNode p){
  if(!p){
    return NULL;
  }
  else if(p->left==NULL){
    return p;
  }
  else
    return findMin_node(p->left);
}

pNode findMax_node(pNode p){
  if(!p){
    return NULL;
  }
  else if(p->right==NULL){
    return p;
  }
  else
    return findMax_node(p->right);
}

pNode delete_node(int x,pNode p){
  pNode ptemp;
  if(p==NULL){
    printf("can't find it!\n");
  }
  else if(x<p->data){
    p->left=delete_node(x,p->left);
    if(height(p->right)-height(p->left)==2){     //打破平衡
      ptemp=p->right;
      if(height(ptemp->left)<height(ptemp->right)){    //情况2
        p=singleRotate_right(p);
      }
      else                                             //情况4
        p=doubleRotate_right(p);
    }
    p->height=max_height(height(p->left),height(p->right))+1; 
  }
  else if(x>p->data){
    p->right=delete_node(x,p->right);
    if(height(p->left)-height(p->right)==2){    //打破平衡
      ptemp=p->left;
      if(height(ptemp->left)>height(ptemp->right)){    //情况1
        p=singleRotate_left(p);
      }
      else
        p=doubleRotate_left(p);                        //情况3
    }
    p->height=max_height(height(p->left),height(p->right))+1;   
  }
  else if(p->left&&p->right){
    if(height(p->left)<height(p->right)){
      ptemp=findMin_node(p->right);
      p->data=ptemp->data;
      p->right=delete_node(ptemp->data,p->right);
    }
    else{
      ptemp=findMin_node(p->left);
      p->data=ptemp->data;
      p->left=delete_node(ptemp->data,p->left);
    }
  }
  else{
    if(!p->left){
      ptemp=p;
      p=p->right;
      free(ptemp);
    }
    else{
      ptemp=p;    
      p=p->left;
      free(ptemp);
    }
  }
  return p;
}

pNode find_node(int x,pNode p){
  if(!p){
    return NULL;
  }
  else if(x<p->data){
    return find_node(x,p->left);
  }
  else if(x>p->data){
    return find_node(x,p->right);
  }
  else
    return p;
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
  pNode pFind, pRoot=NULL;
  int opterat,data;
  printf("1.插入 2.打印 3.删除 4.查询 5.Max 6.Min 7.清空 0.退出：\n");
  while(scanf("%d",&opterat)){
    switch(opterat){
      case 1:
        printf("please input the data to insert:\n");
        scanf("%d",&data);
        pRoot=insert_node(data,pRoot);
        printf("1.插入 2.打印 3.删除 4.查询 5.Max 6.Min 7.清空 0.退出：\n");break;
      case 2:
        printf_tree(pRoot);
        printf("1.插入 2.打印 3.删除 4.查询 5.Max 6.Min 7.清空 0.退出：\n");break;
      case 3:
        if(pRoot){
          printf("please input a data to delete:\n");
          scanf("%d",&data);
          pRoot=delete_node(data,pRoot);
        }
        else
          printf("Tree empty!\n");
        printf("1.插入 2.打印 3.删除 4.查询 5.Max 6.Min 7.清空 0.退出：\n");break;
      case 4:
        if(pRoot){
          printf("please input a data to search:\n");
          scanf("%d",&data);
          pFind=find_node(data,pRoot);
          if(pFind){
            printf("Find it,it's data=%d,height=%d\n",pFind->data,pFind->height);
          }
          else
            printf("can't find it!\n");
        }
        else
          printf("Tree empty!\n");
        printf("1.插入 2.打印 3.删除 4.查询 5.Max 6.Min 7.清空 0.退出：\n");break;
      case 5:
        if(pRoot){
          pFind=findMax_node(pRoot);
          printf("The max=%d\n",pFind->data);
        }
        else
          printf("Tree empty!\n");
        printf("1.插入 2.打印 3.删除 4.查询 5.Max 6.Min 7.清空 0.退出：\n");break;
      case 6:
        if(pRoot){
          pFind=findMin_node(pRoot);
          printf("The min=%d\n",pFind->data);
        }
        else
          printf("Tree empty!\n");
        printf("1.插入 2.打印 3.删除 4.查询 5.Max 6.Min 7.清空 0.退出：\n");break;
      case 7:
        if(pRoot){
          pRoot=clear_tree(pRoot);
        }
        else
          printf("Tree empty!\n");
        printf("1.插入 2.打印 3.删除 4.查询 5.Max 6.Min 7.清空 0.退出：\n");break;
      case 0:
        return 0;
      default:
        printf("无此操作\n1.插入 2.打印 3.删除 4.查询 5.Max 6.Min 7.清空 0.退出：\n");break;
    }
  }
}
