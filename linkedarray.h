//
// Created by edward on 19-3-26.
//

#ifndef NORESPONSESERVER_LINKEDARRAY_H
#define NORESPONSESERVER_LINKEDARRAY_H

#include <malloc.h>
#include <search.h>

struct _Node{
    struct _Node *next;
    void * data;
};
typedef  struct _Node Node;
extern int linkArraryDestroy(Node *head);
extern int linkArraryLength(Node *head);
extern void linkArrayAppend(Node ** head,void * data);
extern void * linkArrayGet(Node * head,int pos);


#endif //NORESPONSESERVER_LINKEDARRAY_H
