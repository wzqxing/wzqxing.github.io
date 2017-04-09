#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SIZE 128

int date[15] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};


typedef struct full_search_tree{
  int value[SIZE];
  int length;
} full_search_tree;

int parent(int index){
  return index/2;
}

int left(int index){
  return index*2;
}

int right(int index){
  return index*2+1;
}

typedef struct stack{
  int value[SIZE];
  int top;
} stack;

void initStack(stack * s){
  if ( s==NULL ) return;
  s->top=-1;
}

void push(stack *s,int n){
  if ( s==NULL ) return;
  s->top++;
  s->value[s->top] = n;
}

int pop(stack *s){
  int temp = s->top;
  s->top--;
  return s->value[temp];
}

void create_tree(full_search_tree *t,int *date,int n){
  if ( t==NULL || date==NULL || n>SIZE-1) return;
  stack *s = (stack *)malloc(sizeof(stack));
  initStack(s);
  int p,i=0;
  p=1;
  t->length = n;
  while ( p<=t->length || s->top!=-1){
    if ( p<=t->length ){
      push(s,p);
      p = left(p);
    }
    else{
      p = pop(s);
      t->value[p] = date[i];
      i++;
      p = right(p);
    }
  }
  for (i=1;i<=t->length;i++)
    printf("%d ",t->value[i]);
  printf("\n");
  return;
}

int main(){
  full_search_tree * t=(full_search_tree*)malloc(sizeof(full_search_tree));
  create_tree(t,date,15);
  return 0;
}
