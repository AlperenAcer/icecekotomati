//
//  linkedlist.h
//  IcecekOtomati
//
//  Created by Alperen Acer on 12.05.2022.
//

#ifndef linkedlist_h
#define linkedlist_h

#include "controlstructures.h"


/**
 Doubly Linked List and Product implementation
 */

typedef struct Product {
    char* name;
    float price;
    int stock;
    int sold;
} Product;

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

/**
 Method for allocating and initializing the doublylinked list.
 İnputs:
    None
 Outputs:
    a pointer to the allocated and initialized list.
 */
DoublyLinkedList* initializeList(void);

/**
 Method for adding product to the list.
 İnputs:
    list_ptr: a pointer that holds the list of products
    prd_ptr: a pointer to the product.
 Outputs:
    None
 */
void addToTail(DoublyLinkedList* list_ptr, Product* prd_ptr);

/**
 Method for getting the object from list
 İnputs:
    list_ptr: a pointer that holds the list of products
 Outputs:
    NULL: if product with given id not found
    product pointer: if search succesfull.
 */
Product* get_product(DoublyLinkedList* list_ptr, int prd_id);

/**
 Method for freeing the space allocated on the list.
 İnputs:
    list_ptr: a pointer that holds the list of products
 Outputs:
    None
 Information:
    Also frees related allocations: products, name strings, nodes.
 */
void destroy_list(DoublyLinkedList* list_ptr);

/**
 Method for listing every product that is in the stock
 İnputs:
    list_ptr: a pointer that holds the list of products
 Outputs:
    Lists in-stock products to the console.
 */
void print_list(DoublyLinkedList* list_ptr);

/**
 Method for listing sold product counts
 İnputs:
    list_ptr: a pointer that holds the list of products
 Outputs:
    Lists sold products to the console.
 */
void print_sold(DoublyLinkedList* list_ptr);

/**
 Method for initializing product
 İnputs:
    name: name of the product
    stock: stock count of the product
    price: price of the product
 Outputs:
    a pointer to the allocated and initialized product.
 */
Product* create_product(char* name, int stock, float price);

/**
 Method for selling a product
 İnputs:
    vallet: cash_register pointer which holds coins data
    list_ptr: a pointer that holds the list of products
    line: a char pointer that holds user input for selected product
 Outputs:
    -1: if there isn't enough coin
    0: if there is an input type error
    1: if operation succesfull
 */
int sell_product(DoublyLinkedList* list_ptr,char* line, cash_register* vallet);

#endif /* linkedlist_h */
