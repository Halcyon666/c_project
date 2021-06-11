#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

#include "../grammar.c"
#include "stdlib.h"

typedef struct SqList {
    ElemType *elem;
    int length;
    int listsize;
} *SqList;


ElemType *newbase = NULL;

Status InitList_sq(SqList L) {
    L->elem = (ElemType *) malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!L->elem) exit(OVERFLOW);
    L->length = 0;  //当前长度
    L->listsize = LIST_INIT_SIZE; // 分配存储空间的容量
    return OK;
}

Status ListInsert_Sq(SqList L, int i, ElemType e) {

    if (i < 1 || i > L->length + 1) return ERROR;
    if (L->length >= L->listsize) { //空间已满 增加分配
        newbase = (ElemType *) realloc(L->elem, (L->listsize + LISTINCREMENT) * sizeof(ElemType));
        if (!newbase) exit(OVERFLOW);
        L->elem = newbase; // 新基址
        L->listsize += LISTINCREMENT;
    }
    ElemType *q;
    q = &(L->elem[i - 1]); //q为插入位置
    for (ElemType *p = &(L->elem[L->length - 1]); q >= q; --p) // 插入元素之后所有元素后移
        *(p + 1) = *p;
    *q = e; // 插入元素
    ++L->length;
    return OK;
}


Status ListDelete_Sq(SqList L, int i, ElemType *e) {
    if (i < 1 || (i > L->length)) return ERROR;
    ElemType *p = &(L->elem[i - 1]);
    e = p;
    ElemType *q = L->elem + L->length - 1;
    for (++p; p <= q; ++p){
        *(p-1) = *p;
        -- L->length;
        return OK;
    }
}

int LocateElem_Sq(SqList L,ElemType e,Status (*compare)(ElemType,ElemType)){
    // 在顺序线性表中查找第一个值与e，满足的compare()的元素的位置
    int i = 1;
    ElemType *p = L->elem;
    while (i <= L->length && !(*compare)(*p++, e)) ++i;
    if (i<L->length) return i;
    else return -1;
}