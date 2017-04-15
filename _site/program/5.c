#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

long jiecheng(int n){//阶乘函数
  long result=1;
  if ( n<=0 ) return 1;
  for ( int i=n;i>=1;i--)
    result *= i;
  return result;
}


long C(int m,int n){//组合数
  long result;
  result = jiecheng(m)/(jiecheng(n)*jiecheng(m-n));
  return result;
}

long catalan(int n){//卡特兰数
  return C(2*n,n)/(n+1);
}

void solution(char **p,char **result,long m, long n){//有m个序列，每个序列2n个字符
  int i,j,k;
  long next = catalan(n+1);
  long count=0;//目标数组行数
  long place;//插入位置
  for ( i=0 ; i<m ; i++ ){
    for ( j=2*n-1 ; j>=1; j-- ){
      if ( p[i][j]==')' && p[i][j-1]=='('){//找到第一个括号序列或者１０序列
        place = j;
        for ( ; place<=2*n;place++){
          memcpy(result[count],p[i],place);
          result[count][place] = '(';
          result[count][place+1] = ')';
          memcpy(result[count]+place+2,p[i]+place,2*n-place);
          count++;
        }
        break;
      }
    }
  }
  if ( count==next) printf("success!!!\n");
}

int main(){
  char **p;
  int i,j;
  char **first;
  first = (char **)malloc(sizeof(char *)*1);
  first[0] = (char *)malloc(sizeof(char)*3);
  first[0][0] = '(';
  first[0][1] = ')';
  first[0][2] = '\0';
  long n;
  p = first;
  char **result;
  for ( i=2;i<=6;i++){
    n = catalan(i);
    //给下一个结果的二位字符数组分配内存
    result = (char **)malloc(sizeof(char *)*(n));
    for ( j=0;j<n;j++){
      result[j] = (char *)malloc(sizeof(char)*(2*i+1));
      memset(result[j],0,2*i+1);
    }

    solution( p,result,catalan(i-1),i-1);

    //释放上一个结果的内存
    for ( j=0;j<catalan(i-1);j++){
      free(p[j]);
    }
    free(p);

    //结果作为下一个的输入
    p = result;
    for ( j=0;j<n;j++)
      printf("%s ",result[j]);
  }
}
