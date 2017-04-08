#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SIZE 128

typedef struct tree{
  char value;
  struct tree *lchild;
  struct tree *rchild;
} tree;

int include(char *c1, char * c2){
  if ( c1==NULL && c2==NULL) return 1;
  else if ( c1==NULL ) return 0;
  else if ( c2==NULL ) return 0;
  int len1 = strlen(c1);
  int len2 = strlen(c2);
  if ( len1!=len2) return 0;
  int i,j,flag=1,isbreak=0;
  for ( i=0; i<len1; i++){
    for ( j=0; j<len2; j++)
      if ( c2[j]==c1[i] )
      {
        isbreak = 1;
        break;
      }
    if ( isbreak==1){
      isbreak = 0;
      continue;
    }
    flag = 0;
  }
  return flag;
}




tree * initTree(char *pre,char *back){
  if ( pre==NULL || back==NULL) return NULL;
  int n = strlen(pre);
  if (n==0) return NULL;
  tree * result = (tree *)malloc(sizeof(tree));
  result->value = pre[0];
  if ( n==1 ) return result;
  char *c1,*c2;
  int i;
  for ( i=0; i<n-1; i++){
    c1 = (char *)malloc(sizeof(char)*(i+1)+2);
    c2 = (char *)malloc(sizeof(char)*(i+1)+2);
    memset(c1,0,i+3);
    memset(c2,0,i+3);
    memcpy(c1,pre+1,i+1);
    memcpy(c2,back,i+1);
    c1[i+2] = '\0';
    c2[i+2] = '\0';

    if ( include(c1,c2)==1 ){
      break;
    }
    free(c1);
    free(c2);
    c1=NULL;
    c2=NULL;
  }
  char * s1 = (char *)malloc(n-1-i);
  memcpy(s1 ,pre+i+1+1,n-i-2);
  s1[n-i] = '\0';
  char * s2 = (char *)malloc(n-i-1);
  memcpy(s2 , back+i+1,n-i-2);
  s2[n-i-1] = '\0';

  result->lchild = initTree(c1,c2);
  result->rchild = initTree(s1,s2);
  return result;
}

void print_pre(tree *t)  //前序便利二叉树
{
  if ( t!=NULL ){
    printf("%c ",t->value );
    print_pre(t->lchild);
    print_pre(t->rchild);
  }
}

typedef struct node{
  char key;
  tree *value;
} node;//哈希表结点定义

typedef struct hash{
  node bucket[SIZE];
} hash;//哈希表定义

hash * initHash(){
  hash * result = (hash *)malloc(sizeof(hash));
  for ( int i=0; i<SIZE; i++){
    result->bucket[i].key = '\0';
    result->bucket[i].value = NULL;
  }
  return result;
}

int keyToIndex(char key,int i){//散列函数
  int h1,h2;
  h1 = (int)key%SIZE;
  h2 = 1 + (int)key%(SIZE-1);
  int index = (h1+i*h2)%SIZE;
  return index;
}

tree * search(hash * h,char key){//查找
  int i,j;
  i = 0;
  while ( i<SIZE ){
    j = keyToIndex(key,i);
    if ( h->bucket[j].key==key )
      return h->bucket[j].value;
    i++;
  }
  return NULL;
}

//插入
void insert(hash *h,char key,tree *value){
  int i,j;
  i=0;
  while ( i<SIZE ){
    j = keyToIndex(key,i);
    if ( h->bucket[j].key=='\0' || h->bucket[j].key==key ){
      h->bucket[j].key = key;
      h->bucket[j].value = value;
      return;
    }
    i++;
  }
  printf("error:the hash table is overflow\n");
}

//栈的定义，辅助非递归中序遍历二叉树建立
typedef struct stack{
  tree * value[SIZE];
  int top;
} stack;

void initStack(stack *s){
  if ( s==NULL ) return;
  s->top = -1;
}

void push(stack *s,tree *p)
{
  if ( s==NULL ) return;
  s->top++;
  s->value[s->top] = p;
}

tree * pop(stack *s){
  if (s==NULL || s->top==-1) return NULL;
  int temp;
  temp = s->top;
  s->top--;
  return s->value[temp];
}


//在一棵不带有父指针的二叉树中通过一个结点找到它的父结点，若是需要频繁调用此过程，将遍历记录过程提出来
tree * parent(tree *root,tree *p){
  if ( root==NULL || p==NULL ) return NULL;
  tree *x,*x1;
  stack s;
  initStack(&s);
  hash *h;
  h = initHash();
  x=root;
  while ( x!=NULL || s.top!=-1){
    if ( x!=NULL ){
      push(&s,x);
      x1 = x;
      x = x->lchild;
      if ( x!=NULL )
        insert(h,x->value,x1);
    }
    else{
      x = pop(&s);
      x1 = x;
      x = x->rchild;
      if ( x!=NULL )
        insert(h,x->value,x1);
    }
  }
  //显示散列表中存储的键值对
/*
  printf("----------------------------------------------------------------------------------------\n");
  int j=0;
  for (j=0;j<SIZE;j++)
  {
    if (h->bucket[j].value!=NULL)
    {
      printf("h->bucket[%d]:\n",j );
      printf("\t\tkey %c:\t%c\n", h->bucket[j].key,h->bucket[j].value->value);
    }
  }
*/
  tree *result;
  result = search(h,p->value);
  return result;
}

void solution(tree *root,tree *p){
  if ( root==NULL || p==NULL ) return;
  printf("%c ",p->value );
  tree *p1;
  while ( p!=root){
    p1 = parent(root,p);
    printf("%c ",p1->value );
    p = p1;
  }
  printf("\n");
}

int main()
{
  tree *t;
  t = initTree("abdhiejkcflmgno","hidjkeblmfnogca");
  print_pre(t);
  printf("\n");
  solution(t,t->rchild->lchild->lchild);
  return 1;
}
