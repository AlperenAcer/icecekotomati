//
//  linkedlist.h
//  IcecekOtomati
//
//  Created by Alperen Acer on 12.05.2022.
//

#ifndef linkedlist_h
#define linkedlist_h

#include "controlstructures.h"

typedef struct Node {
    int id;
    Product* prd;
    struct Node* prev_node;
    struct Node* next_node;
} Node;
typedef struct DoublyLinkedList {
    int size;
    Node* head;
    Node* tail;
} DoublyLinkedList;

DoublyLinkedList* initializeList(void);
void addToTail(DoublyLinkedList* list_ptr, Product* prd_ptr);
Product* get_product(DoublyLinkedList* list_ptr, int prd_id);
void destroy_list(DoublyLinkedList* list_ptr);
void print_list(DoublyLinkedList* list_ptr);
int sell_product(DoublyLinkedList* list_ptr,char* line, cash_register* vallet);

#endif /* linkedlist_h */
