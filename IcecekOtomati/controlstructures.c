//
//  controlstructures.c
//  IcecekOtomati
//
//  Created by Alperen Acer on 12.05.2022.
//

#include "controlstructures.h"
#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
Product* create_product(char* name, int stock, float price) {
    Product* new_prd = (Product*)malloc(sizeof(Product));
    new_prd->name = name;
    new_prd->stock = stock;
    new_prd->price = price;
    new_prd->sold = 0;
    return new_prd;
}
cash_register* create_cashregister(void){
    cash_register* vallet = (cash_register*)malloc(sizeof(cash_register));
    vallet->cnt_2d = 0;
    vallet->cnt_1d = 0;
    vallet->cnt_50c = 0;
    vallet->cnt_25c = 0;
    vallet->cnt_10c = 0;
    vallet->cnt_5c = 0;
    vallet->cnt_1c = 0;
    return vallet;
}
void reset_vallet(cash_register* vallet){
    vallet->cnt_2d = 0;
    vallet->cnt_1d = 0;
    vallet->cnt_50c = 0;
    vallet->cnt_25c = 0;
    vallet->cnt_10c = 0;
    vallet->cnt_5c = 0;
    vallet->cnt_1c = 0;
}

void print_cash(cash_register* vallet){
    int total_c = vallet->customer_balance;
    if(total_c >= 100)
        printf("Bakiye: %.2lf$\n", total_c/100.0);
    else
        printf("Bakiye: %dc\n", total_c);
}
int add_coin(cash_register* vallet, char* input) {
    if(strcmp(input,"2$\n") == 0){
        vallet->cnt_2d++;
        vallet->customer_balance+=200;
        return 1;
    }
    if(strcmp(input,"1$\n") == 0){
        vallet->cnt_1d++;
        vallet->customer_balance+=100;
        return 1;
    }
    if(strcmp(input,"50c\n") == 0){
        vallet->cnt_50c++;
        vallet->customer_balance+=50;
        return 1;
    }
    if(strcmp(input,"25c\n") == 0){
        vallet->cnt_25c++;
        vallet->customer_balance+=25;
        return 1;
    }
    if(strcmp(input,"10c\n") == 0){
        vallet->cnt_10c++;
        vallet->customer_balance+=10;
        return 1;
    }
    if(strcmp(input,"5c\n") == 0){
        vallet->cnt_5c++;
        vallet->customer_balance+=5;
        return 1;
    }
    if(strcmp(input,"1c\n") == 0){
        vallet->cnt_1c++;
        vallet->customer_balance+=1;
        return 1;
    }
    return 0;
}

int cash_return(cash_register* vallet){
    int remain = vallet->customer_balance;
    int is_coin_available = 1;
    while(is_coin_available){
        if(remain >= 200 && vallet->cnt_2d > 0) {
            remain -= 200;
            vallet->cnt_2d--;
        }
        else if(remain >= 100 &&  vallet->cnt_1d > 0) {
            remain -= 100;
            vallet->cnt_1d--;
        }
        else if(remain >= 50 && vallet->cnt_50c > 0){
            remain -= 50;
            vallet->cnt_50c--;
        }
        else if(remain >= 25 && vallet->cnt_25c > 0){
            remain -= 25;
            vallet->cnt_25c--;
        }
        else if(remain >= 10 && vallet->cnt_10c > 0){
            remain -= 10;
            vallet->cnt_10c--;
        }
        else if(remain >= 5 && vallet->cnt_5c > 0){
            remain -= 5;
            vallet->cnt_5c--;
        }
        else if(remain >= 1 && vallet->cnt_1c > 0){
            remain -= 1;
            vallet->cnt_1c--;
        } else {
            is_coin_available = 0;
        }
    }
    return remain;
}


