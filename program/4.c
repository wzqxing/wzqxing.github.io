#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

void printPar(int left, int right, char * str,int count){
  if ( left<0 || right<left) {
    return;
  }

  if ( left==0 && right==0 ){
    printf("%s\n",str);
  }
  else{
    if ( left>0 ){
      str[count] = '1';
      printPar(left-1,right,str,count+1);
    }
    if ( right>left ){
      str[count] = '0';
      printPar(left,right-1,str,count+1);
    }
  }
}

int main(){
  char s[101]="\0";
  memset(s,0,101);
  int n=3;
  printPar(n,n,s,0);
}
