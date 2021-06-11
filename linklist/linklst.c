#include "stdlib.h"

typedef struct ElemType {
    struct ElemType *v;
} ElemType;

typedef struct LNode{
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;
//LinkList L;
//LNode *a;

int GetElem_L(LinkList L,int i, ElemType *e) {
    LNode *p = L->next;
    int j=1;
    while (p && j < i) {
        p = p->next; ++j;
    }
    if (!p || j > i) return -1;
    *e = p->data; // j=i 指针指向第i个Node节点
    return 0;
}; 