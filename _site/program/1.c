#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//一棵满二叉搜索树，有k层，存储1到2^k-1之间的所有正整数，给任意三个数，求这三个数的最近公共祖先

int * create_tree(int k)
{
  int n = pow(2,k);
  int *result = (int *)malloc(sizeof(int)*n);
  result[0] = k;
  result[1] = 1;
  int i,j,temp;
  for ( i=1; i<k; i++){
    for ( j=1; j<pow(2,i); j++)
      result[j] = 2*result[j];
    temp = 1;
    for ( ; j<pow(2,i+1); j++){
      result[j] = temp;
      temp += 2;
    }
  }

  return result;
}

int parent(int index){
  return index/2;
}

int left(int index){
  return index*2;
}

int right(int index){
  return index*2+1;
}


int find( int *T,int n,int a,int b){
  if ( a>b){
    int temp = a;
    a = b;
    b = temp;
  }
  int p = 1;
  while ( !(a<=T[p] && T[p]<=b) ){
    if ( a>T[p])
      p = right(p);
    else
      p = left(p);
  }
  return p;
}

int solution(int *T, int n, int a, int b, int c)
{
  int p1,p2,p3;
  p1 = find(T,n,a,b);
  p2 = find(T,n,a,c);
  return find(T,n,T[p1],T[p2]);
}

int main()
{
  int *x;
  int k,a,b,c;
  scanf("%d%d%d%d",&k,&a,&b,&c );
  x = create_tree(k);
  int n = pow(2,k);
//  for (int i=1; i<n; i++)
//    printf("%d ",x[i]);
//  printf("\n");

  printf("%d\n",x[solution(x,n,a,b,c)] );

}
