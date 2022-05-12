//
//  linkedlist.c
//  IcecekOtomati
//
//  Created by Alperen Acer on 12.05.2022.
//

#include "linkedlist.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
DoublyLinkedList* initializeList(void) {
    DoublyLinkedList* list_ptr = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
    list_ptr->size = 0;
    list_ptr->head = NULL;
    list_ptr->tail = NULL;
    return list_ptr;
}

void addToTail(DoublyLinkedList* list_ptr, Product* prd_ptr) {
    if (list_ptr == NULL)
        return;
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->id = ++(list_ptr->size);
    newNode->prd = prd_ptr;
    newNode->prev_node = list_ptr->tail;
    newNode->next_node = NULL;
    if (list_ptr->head == NULL) {
        list_ptr->head = newNode;
        list_ptr->tail = newNode;
        return;
    }
    list_ptr->tail->next_node = newNode;
    list_ptr->tail = newNode;
}

Product* get_product(DoublyLinkedList* list_ptr, int prd_id) {
    Node* current_node = list_ptr->head;
    while (current_node != NULL) {
        if (current_node->id == prd_id)
            return current_node->prd;
        current_node = current_node->next_node;
    }
    return NULL;
}

void destroy_list(DoublyLinkedList* list_ptr) {
    Node* current_node = list_ptr->head;
    while (current_node != NULL) {
        list_ptr->head = current_node->next_node;
        free(current_node->prd->name);
        free(current_node->prd);
        free(current_node);
        current_node = list_ptr->head;
    }
    free(list_ptr);
    return;
}

void print_list(DoublyLinkedList* list_ptr) {
    Node* current_node = list_ptr->head;

    while (current_node != NULL) {
        if (current_node->prd->stock > 0){
            int price = current_node->prd->price;
            printf("%d. %s\n", current_node->id, current_node->prd->name);
            if(price >= 100)
                printf("Price: %.2lf$\n", price/100.0);
            else
                printf("Price: %dc\n", price);
        }
            
        current_node = current_node->next_node;
    }
}
void print_sold(DoublyLinkedList* list_ptr) {
    Node* current_node = list_ptr->head;
    int prints = 0;
    while (current_node != NULL) {
        int count = current_node->prd->sold;
        if(count > 0){
            prints++;
            int price = current_node->prd->price * count;
            printf("%s ürününden %d adet satılarak toplam ", current_node->prd->name, count);
            if(price >= 100)
                printf("%.2lf$", price/100.0);
            else
                printf("%dc", price);
            printf(" alındı.\n");
        }
        current_node = current_node->next_node;
    }
    if(prints == 0)
        printf("Satış bulunamadı!\n");
}
Product* create_product(char* name, int stock, float price) {
    Product* new_prd = (Product*)malloc(sizeof(Product));
    long name_len = strlen(name);
    new_prd->name = (char*)malloc(name_len*sizeof(char));
    strncpy(new_prd->name, name, name_len);
    new_prd->stock = stock;
    new_prd->price = price;
    new_prd->sold = 0;
    return new_prd;
}

int sell_product(DoublyLinkedList* list_ptr, char* line, cash_register* vallet){
    int id = atoi(line);
    Product* prd = get_product(list_ptr, id);
    if(prd == NULL)
        return -1;
    if(prd->price > vallet->customer_balance)
        return 0;
    prd->stock--;
    vallet->customer_balance -= prd->price;
    prd->sold++;
    return 1;
}

