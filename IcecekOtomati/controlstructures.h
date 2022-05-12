//
//  controlstructures.h
//  IcecekOtomati
//
//  Created by Alperen Acer on 12.05.2022.
//

#ifndef controlstructures_h
#define controlstructures_h

/*
 In this header we conducts 
 */
typedef struct cash_register {
    int customer_balance;
    int cnt_2d;
    int cnt_1d;
    int cnt_50c;
    int cnt_25c;
    int cnt_10c;
    int cnt_5c;
    int cnt_1c;
} cash_register;

typedef struct Product {
    char* name;
    float price;
    int stock;
    int sold;
} Product;


Product* create_product(char* name, int stock, float price);
cash_register* create_cashregister(void);
void reset_vallet(cash_register* vallet);
void print_cash(cash_register* vallet);
int add_coin(cash_register* vallet, char* input);
int cash_return(cash_register* vallet);
#endif /* controlstructures_h */
