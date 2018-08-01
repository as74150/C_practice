#include <stdio.h>
#include <sys/time.h>
#define N 1000

int max3(int x,int y,int z){
  int result;
  result=(x>y)?x:y;
  result=(result>z)?result:z;
  return result;
}

int plan1(int arr[],int n){   //O(N^3)
  int thisSum,maxSun=0;
  int i,j,k;
  for(i=0;i<n;i++){
    for(j=i;j<n;j++){
      thisSum=0;
      for(k=i;k<j+1;k++){
        thisSum+=arr[k];
        if(thisSum>maxSun){
          maxSun=thisSum;
        }
      }
    }
  }
  return maxSun;
}

int plan2(int arr[],int n){  //O(N^2)
  int thisSum,maxSun=0;
  int i,j;
  for(i=0;i<n;i++){
    thisSum=0;
    for(j=i;j<n;j++){
      thisSum+=arr[j];
      if(thisSum>maxSun){
        maxSun=thisSum;
      }
    }
  }
  return maxSun;
}

int plan3(int arr[],int lift,int right){    //O(Nlog2(N)) 分治的思维 lift=0,center=N/2,right=N-1分成两份递归 
  int maxLiftSum,maxRightSum;
  int maxLiftBorderSum,maxRightBorderSum;
  int thisLiftBorderSum,thisRightBorderSum;
  int center;
  if(lift==right){
    if(arr[lift]>=0){
      return arr[lift];
    }
    else
      return 0;
  }
  center=(lift+right)/2;
  maxLiftSum=plan3(arr,lift,center);
  maxRightSum=plan3(arr,center+1,right);
  int i;
  maxLiftBorderSum=0;
  thisLiftBorderSum=0;
  for(i=center;i>=lift;i--){
    thisLiftBorderSum+=arr[i];
    if(thisLiftBorderSum>maxLiftBorderSum){
      maxLiftBorderSum=thisLiftBorderSum;
    }
  }
  maxRightBorderSum=0;
  thisRightBorderSum=0;
  for(i=center+1;i<=right;i++){
    thisRightBorderSum+=arr[i];
    if(thisRightBorderSum>maxRightBorderSum){
      maxRightBorderSum=thisRightBorderSum;
    }
  }
  return max3(maxLiftSum,maxRightSum,maxLiftBorderSum+maxRightBorderSum);
}

int plan4(int arr[],int n){    //O(N)
  int thisSum,maxSum=0;
  int i;
  thisSum=0;
  for(i=0;i<n;i++){
    thisSum+=arr[i];
    if(thisSum>maxSum){
      maxSum=thisSum;
    }
    else if(thisSum<0){
      thisSum=0;
    }
  }
  return maxSum;  
}

int main()
{
  struct timeval start,end;
  long timer;
  int arr[N];
  int i,max;
  for(i=0;i<N;i++){
    arr[i]=100-i;
  }
  gettimeofday(&start,NULL);
  max=plan1(arr,N);
  gettimeofday(&end,NULL); 
  timer=1000000*(end.tv_sec-start.tv_sec)+(end.tv_usec-start.tv_usec);   //时间差（us）
  printf("the max=%d plan1 used time:%ldus\n",max,timer);
  gettimeofday(&start,NULL);
  max=plan2(arr,N);
  gettimeofday(&end,NULL); 
  timer=1000000*(end.tv_sec-start.tv_sec)+(end.tv_usec-start.tv_usec);   //时间差（us）
  printf("the max=%d plan2 used time:%ldus\n",max,timer);
  gettimeofday(&start,NULL);
  max=plan3(arr,0,N-1);
  gettimeofday(&end,NULL);
  timer=1000000*(end.tv_sec-start.tv_sec)+(end.tv_usec-start.tv_usec);   //时间差（us）
  printf("the max=%d plan3 used time:%ldus\n",max,timer);
   gettimeofday(&start,NULL);
  max=plan4(arr,N);
  gettimeofday(&end,NULL);
  timer=1000000*(end.tv_sec-start.tv_sec)+(end.tv_usec-start.tv_usec);   //时间差（us）
  printf("the max=%d plan4 used time:%ldus\n",max,timer);
  return 0;
}
