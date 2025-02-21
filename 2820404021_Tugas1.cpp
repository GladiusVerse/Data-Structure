#include <stdio.h>
#include <stdlib.h>

typedef struct tnode {
    int data;
    struct tnode *prev, *next;
} tnode;

typedef struct {
    tnode *head, *tail;
} DLL;

DLL* createList() {
    return (DLL*)calloc(1, sizeof(DLL));
}

void append(DLL* list, int val) {
    tnode* newNode = (tnode*)malloc(sizeof(tnode));
    if (!newNode) return;
    newNode->data = val;
    newNode->next = NULL;
    newNode->prev = list->tail;
    if (list->tail) list->tail->next = newNode;
    else list->head = newNode;
    list->tail = newNode;
}

void deleteBack(DLL* list) {
    if (!list->tail) return;
    tnode* temp = list->tail;
    list->tail = list->tail->prev;
    if (list->tail) list->tail->next = NULL;
    else list->head = NULL;
    free(temp);
}

void deleteMid(DLL* list, int pos) {
    if (!list->head || pos <= 0) return;
    tnode* temp = list->head;
    for (int i = 1; temp && i < pos; i++) temp = temp->next;
    if (!temp) return;
    if (temp->prev) temp->prev->next = temp->next;
    else list->head = temp->next;
    if (temp->next) temp->next->prev = temp->prev;
    else list->tail = temp->prev;
    free(temp);
}

void display(DLL* list) {
    tnode* temp = list->head;
    while (temp) {
        printf("%d%s", temp->data, temp->next ? " <-> " : "\n");
        temp = temp->next;
    }
}

int main() {
    DLL* dll = createList();
    for (int i = 5; i <= 25; i += 5) append(dll, i);
    printf("List awal: "); display(dll);
    deleteBack(dll);
    printf("Hapus terakhir: "); display(dll);
    deleteMid(dll, 2);
    printf("Hapus posisi 2: "); display(dll);
    return 0;
}

