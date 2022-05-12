//
//  controlstructures.h
//  IcecekOtomati
//
//  Created by Alperen Acer on 12.05.2022.
//

#ifndef controlstructures_h
#define controlstructures_h

/**
 cash_register type definition
 
members:
    customer_balance: current total balance of customer
    cnt_2d: count of 2$ coins
    cnt_1d: count of 1$ coins
    cnt_50c: count of 50c coins
    cnt_25c: count of 25c coins
    cnt_10c: count of 10c coins
    cnt_5c: count of 5c coins
    cnt_1c: count of 1c coins
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

/**
 cash_register type initializer.
 İnputs:
    none
 Outputs:
    returns the initialized and allocated list.
 Information:
    if a coin is not allowed, it's count value is sets to -1.
 */
cash_register* create_cashregister(void);

/**
 Method for listing the amount of coins
 İnputs:
    vallet: cash_register pointer which holds coins data
 Outputs:
    lists the vallet information  to the console
 */
void print_vallet(cash_register* vallet);

/**
 Method for printing the balance
 İnputs:
    vallet: cash_register pointer which holds coins data
 Outputs:
    prints balance information to the console
 */
void print_cash(cash_register* vallet);

/**
 Method for adding coin to the balance
 İnputs:
    vallet: cash_register pointer which holds coins data
    input: char pointer which holds the user input
 Outputs:
    0: if there is an input type error
    1: if adding successfull
 */
int add_coin(cash_register* vallet, char* input);

/**
 Method for change retrieval
 İnputs:
    vallet: cash_register pointer which holds coins data
 Outputs:
    positive integer: remaining balance if there isn't enough coin
    0: if all balance taken.
 */
int cash_return(cash_register* vallet);

/**
 Method for cash retrieval.
 İnputs:
    vallet: cash_register pointer which holds coins data
    input: a char pointer that holds user input for cash retrieval
 Outputs:
    -1: if there isn't enough coin
    0: if there is an input type error
    1: if operation succesfull
 */
int cash_retrieve(cash_register* vallet, char* input);
#endif /* controlstructures_h */
