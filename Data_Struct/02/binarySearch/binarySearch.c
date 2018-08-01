#include <stdio.h>
#define N 20

void bubbleSort(int arr[],int n){
  int i,j,temp;
  for(i=0;i<N-1;i++){
    for(j=0;j<N-i-1;j++){
      if(arr[j]>arr[j+1]){
        temp=arr[j];
        arr[j]=arr[j+1];
        arr[j+1]=temp;
      }
    }
  }
}

int binarySearch(int arr[],int n,int num){
  int i,lift,right,mid;
  lift=0;
  right=n-1;
  while(lift<right){
    mid=(right+lift)/2;
    if(num==arr[mid]){
      return mid+1;
    }
    if(num<arr[mid]){
      right=mid;
    }
    else if(num>arr[mid]){
      lift=mid;
    }
  }
  return -1;
}

int main()
{
  int result,num,i,test[N]={5,7,3,17,90,57,34,78,53,55,78,96,54,32,44,67,98,45,76,88};
  bubbleSort(test,N);
  for(i=0;i<N;i++){
    printf("%-4d",test[i]);
  }
  printf("please input the search number:");
  scanf("%d",&num);
  result=binarySearch(test,N,num);
  if(result!=-1){
    printf("the number is the %d \n",result);
  }
  else
    printf("the number can't find\n");
  return 0;
}
