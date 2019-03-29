//
// Created by edward on 19-3-26.
//

#include "linkedarray.h"

void linkArrayAppend(Node **head, void *data) {
    Node *next = 0;
    Node *dummyHead=*head;
    if (*head == 0) {
        *head = (Node *) (malloc(sizeof(Node)));
        (*head)->data = data;
        (*head)->next = 0;
    } else {
        next = dummyHead->next;
        while (next != 0) {
            dummyHead = next;
            next = dummyHead->next;
        }
        dummyHead->next = (Node *) malloc(sizeof(Node));
        dummyHead->next->data = data;
        dummyHead->next->next = 0;
    }
}

int linkArraryLength(Node *head) {
    int length = 0;
    while (head != 0) {
        head = head->next;
        length++;
    }
    return length;
}

int linkArraryDestroy(Node *head) {
    Node *saver = 0;
    while (head != 0) {
        saver = head->next;
        //free(head->data);
        free(head);
        head = saver;
    }
}

void *linkArrayGet(Node *head, int pos) {
    int counter = -1;
    if (pos < 0) {
        pos = linkArraryLength(head) + pos;
    }
    while (head != NULL) {
        counter++;
        if (counter == pos) {
            return head->data;
        } else {
            head = head->next;
        }
    }
    return  NULL;
}
