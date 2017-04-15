---
layout:     post
title:      "实现二叉搜索树"
subtitle:   "C语言"
data:       2017-03-27
authori:    "silence"
header-img: ""
tags:
        - 算法
        - 代码



---




## 二叉搜索树

二叉搜索树是以一棵二叉树来组织的，并且对于任意结点 *x* ，满足：

***x.lchild.value <= x.value <= x.rchild.value***

根据二叉树的性质，很容易知道，它的中序遍历即是所有结点值的升序排列。

二叉搜索树支持以下操作：

 - *search*：在二叉搜索树中查找结点
 - *min*：返回二叉搜索树的最小值结点
 - *max*：返回二叉搜索数的最大值结点
 - *predecessor*：输入二叉树中某一节点并返回它的中序前驱结点
 - *successor*：输入二叉树中某一节点并返回它的中序后继结点
 - *insert*：输入结点并将其插入二叉树中，且满足二叉搜索树的性质
 - *delete*：删除二叉搜索树中某一结点

#### 二叉搜索树定义

二叉搜索树中的操作需要双亲的指针，故构造三叉链表结构

```
typedef struct search_tree{
  int value;
  struct search_tree *pre;
  struct search_tree *lchild;
  struct search_tree *rchild;
} search_tree;
```

#### *search*

```
search_tree * Tree_search(search_tree * T, int key){
  search_tree *p;
  p = T;
  while (p!=NULL){
    if( p->value < key )
      p = p->lchild;
    else if ( p->value > key )
      p = p->rchild;
    else
      return p;
  }
  return NULL;
}
```

#### *max* 和 *min*

```
search_tree * Tree_max(search_tree * T){
  search_tree *p;
  p = T;
  if ( p==NULL ) return NULL;

  while ( p->lchild != NULL )
    p = p->lchild;
  return p;
}

search_tree * Tree_min(search_tree * T){
  search_tree *p;
  p=T;
  if ( p==NULL ) return NULL;

  while ( p->rchild != NULL )
    p = p->rchild;

  return p;
}
```

#### *successor* 和 *predecessor*

```
//寻求某一结点的中序后继
search_tree * Tree_successor( search_tree * T){
  search_tree *p;
  search_tree *p1;
  if ( T==NULL ) return NULL;
  if ( T->rchild != NULL) return Tree_min( T->rchild );
  p = T->pre;
  p1 = T;

  //当结点的右子数为空，则向上寻找一个这样的结点：这个结点的左子树是原结点的祖先或者是它本身

  while ( p!=NULL && p1 != p->lchild ){
    p1 = p;
    p = p->pre;
  }
  return p;
}

//寻求某一结点的中序前驱
search_tree * Tree_predecessor( search_tree * T){
  search_tree *p;
  search_tree *p1;

  if ( T==NULL ) return NULL;

  if ( T->lchild != NULL )
    return Tree_max( T->lchild );

  p1 = T;
  p = T->pre;

  while ( p!=NULL && p->rchild != p1 ){
    p1 = p;
    p = p->pre;
  }

  return p;
}
```

#### *insert*

```
void Tree_insert(search_tree * T, search_tree * x){
  search_tree *p;
  search_tree *p1;//指向p的双亲结点
  p = T;
  while ( p != NULL )
  {
    if ( p->value > x->value){
      p1 = p;
      p = p->lchild;
    }
    else{
      p1 = p;
      p = p->rchild;
    }
  }
  //T为空
  if ( p1 == NULL ){
    *T = *x;
  }
  if ( p1->value <= x->value ){ //注意，此处的<=号要和上面对应，否则将会出现覆盖结点
    p1->rchild = x;
    x->pre = p1;
  }
  else{
    p1->lchild = x;
    x->pre = p1;
  }
}
```

#### *delete*

```
//将v结点替换掉u结点:更换自身的前序和双亲的子数关系
void transplant( search_tree * T, search_tree * u, search_tree * v){
  if ( u->pre == NULL )
    *T = *v;
  else if ( u==u->pre->lchild )
    u->pre->lchild = v;
  else
    u->pre->rchild = v;
  if ( v!=NULL )
    v->pre = u->pre;
}
void Tree_delete ( search_tree * T, search_tree * x){
  search_tree *p;
  //如果x的左子树为空，则将x的右子数移动到x的位置
  if ( x->lchild == NULL)
    transplant(T, x, x->rchild );
  else if ( x->rchild == NULL )
    transplant( T, x, x->lchild );
  else{
    p = Tree_min( x->rchild );//找到被删除结点的直接后续结点
    if ( p->pre != x){        //如果直接后续结点不是被删除结点的右子树，则将后续结点的右子树代替后续结点，后续结点代替被删除结点
      transplant( T, p, p->rchild);//后续结点的右子树代替后续结点
      p->rchild = x->rchild;  //后续结点接收被删除结点右子树
      p->rchild->pre = p;
    }
    transplant(T,x,p);
    p->lchild = x->lchild;
    p->lchild->pre = p;
  }
}
```

#### 随机构建二叉搜索数

```
search_tree * create_tree(int *a,int n){
  srand( time(NULL) ); //随机数种子
  search_tree * result = (search_tree *)malloc( sizeof(search_tree) );
  int first;
  int *record = (int *)malloc(sizeof(int)*n);//记录那些已经插入过的数
  if(record !=NULL)
    memset(record,0,sizeof(int)*n);

  first = rand()%n;
  result->value = a[first];
  result->pre = NULL;
  result->lchild = NULL;
  result->rchild = NULL;
  record[first] = 1;
  int index;
  for ( int i=0;i<n-1;i++){
    index = rand()%n;
    if ( record[index]!=1 ){//此数未插入树中
      search_tree * p = (search_tree *)malloc( sizeof(search_tree) );
      p->value = a[index];
      p->pre = NULL;
      p->lchild = NULL;
      p->rchild = NULL;
      Tree_insert(result,p);
      record[index]=1;
    }
    else
      i--;
  }
  return result;
}
```

####　非递归中序遍历二叉搜索树

```
typedef struct stack{
  search_tree  bucket[50];
  int top;
} stack;

void initStack(stack * s){
  if ( s==NULL ) return;
  s->top = -1;
}

void push(stack *s,search_tree t){
  s->top++;
  s->bucket[s->top] = t;
}

search_tree * pop(stack *s){
  s->top--;
  return &(s->bucket[s->top+1]);
}

void print_in(search_tree * T){
  if ( T==NULL ) return;
  stack s;
  search_tree *p;
  initStack(&s);
  p=T;
  while ( p!=NULL || s.top!= -1 ){
    if(p!=NULL){
      push(&s,*p);
      p = p->lchild;
    }
    else{
      p = pop(&s);
      printf("%d ",p->value );
      p = p->rchild;
    }
  }
  printf("\n");
}
```
