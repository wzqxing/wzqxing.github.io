---
layout:     post
title:      "寻找无父指针二叉树的父结点算法"
subtitle:   "代码"
data:       2017-04-08
authori:    "silence"
header-img: ""
tags:
        - 代码



---




## 无父指针二叉树

一般来讲，二叉树在计算机内部的存储结构是二叉链表，包含一个关键字和左右子数的指针，即：

```
typedef struct tree{
  char value;
  struct tree *lchild;
  struct tree *rchild;
} tree;
```

也有在上述结构中加一个父指针指向它的父结点，对于根结点，其父指针指向`NULL`。那么对于一棵没有设定父指针的二叉树如何寻找其父结点呢？

一个办法是让其他一个数据结构记录每一个结点的父指针，然后查询。寻找父结点对很多问题有帮助，如：

  - 最近公共祖先：寻找两个结点的最近公共祖先，如果存在查询父结点操作，那么这个问题就化为***寻找两个链表的第一个公共结点***，对于这个问题，只需要先遍历求出两个链表的长度，然后让长链表先走**两者长度差值**步数，使得**指向两个链表的指针和公共结点的距离相同**，然后再次遍历，当两个指针指向同一结点时，此结点就是所求结点。


  - 判断某一结点是其父结点的左子树还是右子树


  - 寻找中序后继结点：如果此结点(*x*)的右子树非空，那么它的后继结点(*y*)是它右子树的**最左结点**；如果右子树为空，则*y*是*x*的最底层祖先，并且*y*的左子树也是*x*的祖先。


## 原理

凭空寻找一个结点的父结点是不可能的，采用哈希表来记录二叉树，将二叉树结点的值和它的父结点指针作为一个键值对存储在哈希表中，这个方法不能处理带有相同值的二叉树，替代方法是将此结点的指针作为关键字，然而这样由于程序每次运行分配的内存地址是不同的，可能会引发一些其他问题。中序遍历二叉树，在这个过程中将键值对存储在哈希表中。

```
//在一棵不带有父指针的二叉树中通过一个结点找到它的父结点，若是需要频繁调用此过程，将哈希表记录过程提出来
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
```

>当然，最好的方法是设置一个父指针，源文件中的代码是一个打印一个结点到根结点的路径

[源文件](https://wzqxing.github.io/program/2.c)
