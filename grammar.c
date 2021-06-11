#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#include "stdlib.h"

typedef int Status;

typedef struct ElemType {
    struct ElemType *v;
} ElemType;
typedef ElemType *Triplet;

Status InitTriple(Triplet T,ElemType e1,ElemType e2,ElemType e3) {
    T = (ElemType *)malloc(3*sizeof(ElemType));
    if (!T) exit(OVERFLOW);
    T[0] = e1,T[1] = e2,T[2] = e3;
    return OK;
}
