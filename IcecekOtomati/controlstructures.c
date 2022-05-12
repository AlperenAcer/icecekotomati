//
//  controlstructures.c
//  IcecekOtomati
//
//  Created by Alperen Acer on 12.05.2022.
//

#include "controlstructures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

cash_register* create_cashregister(void){
    cash_register* vallet = (cash_register*)malloc(sizeof(cash_register));
    vallet->cnt_2d = -1;
    vallet->cnt_1d = -1;
    vallet->cnt_50c = -1;
    vallet->cnt_25c = -1;
    vallet->cnt_10c = -1;
    vallet->cnt_5c = -1;
    vallet->cnt_1c = -1;
    return vallet;
}
void print_vallet(cash_register* vallet){
    if(vallet->cnt_2d >= 0){
        printf("2$ Coin Sayısı: %d\n",vallet->cnt_2d);
    }
    if(vallet->cnt_1d >= 0){
        printf("1$ Coin Sayısı: %d\n", vallet->cnt_1d);
    }
    if(vallet->cnt_50c >= 0){
        printf("50c Coin Sayısı: %d\n", vallet->cnt_50c);
    }
    if(vallet->cnt_25c >= 0){
        printf("25c Coin Sayısı: %d\n", vallet->cnt_25c);
    }
    if(vallet->cnt_10c >= 0){
        printf("10c Coin Sayısı: %d\n", vallet->cnt_10c);
    }
    if(vallet->cnt_5c >= 0){
        printf("5c Coin Sayısı: %d\n", vallet->cnt_5c);
    }
    if(vallet->cnt_1c >= 0){
        printf("1c Coin Sayısı: %d\n", vallet->cnt_1c);
    }
}
void print_cash(cash_register* vallet){
    int total_c = vallet->customer_balance;
    if(total_c >= 100)
        printf("Bakiye: %.2lf$\n", total_c/100.0);
    else
        printf("Bakiye: %dc\n", total_c);
}
int add_coin(cash_register* vallet, char* input) {
    if(strcmp(input,"2$\n") == 0 && vallet->cnt_2d >= 0){
        vallet->cnt_2d++;
        vallet->customer_balance+=200;
        return 1;
    }
    if(strcmp(input,"1$\n") == 0 && vallet->cnt_1d >= 0){
        vallet->cnt_1d++;
        vallet->customer_balance+=100;
        return 1;
    }
    if(strcmp(input,"50c\n") == 0 && vallet->cnt_50c >= 0){
        vallet->cnt_50c++;
        vallet->customer_balance+=50;
        return 1;
    }
    if(strcmp(input,"25c\n") == 0 && vallet->cnt_25c >= 0){
        vallet->cnt_25c++;
        vallet->customer_balance+=25;
        return 1;
    }
    if(strcmp(input,"10c\n") == 0 && vallet->cnt_10c >= 0){
        vallet->cnt_10c++;
        vallet->customer_balance+=10;
        return 1;
    }
    if(strcmp(input,"5c\n") == 0 && vallet->cnt_5c >= 0){
        vallet->cnt_5c++;
        vallet->customer_balance+=5;
        return 1;
    }
    if(strcmp(input,"1c\n") == 0 && vallet->cnt_1c >= 0){
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
    vallet->customer_balance = 0;
    return remain;
}


int get_number(char *input){
    if(input == NULL)
        return -1;
    long len = strlen(input);
    for(int i = 0; i < len ; i++){
        if(input[i] <= '0' && input[i] >= '9')
            return -1;
    }
    return atoi(input);
}

int cash_retrieve(cash_register* vallet, char* input){
    printf("hello world!");
    int wanted_2d = 0;
    int wanted_1d = 0;
    int wanted_50c = 0;
    int wanted_25c = 0;
    int wanted_10c = 0;
    int wanted_5c = 0;
    int wanted_1c = 0;
    
    char* element;
    char* temp;
    while((element = strtok_r(input, " + ", &input))){
        if(strstr(element, "$")){
            temp = strtok(element, "$");
            if(strcmp(element,"2") == 0){
                temp = strtok(NULL, "$");
                printf("temp is : %s\n",temp);
                wanted_2d = get_number(temp);
            }else if(strcmp(element,"1") == 0){
                temp = strtok(NULL, "$");
                wanted_1d = get_number(temp);
            } else
                return 0;
        } else if(strstr(element, "c")){
            temp = strtok(element, "c");
            if(strcmp(element,"50") == 0){
                temp = strtok(NULL, "c");
                wanted_50c = get_number(temp);
            }else if(strcmp(element,"25") == 0){
                temp = strtok(NULL, "c");
                wanted_25c = get_number(temp);
            } else if(strcmp(element,"10") == 0){
                temp = strtok(NULL, "c");
                wanted_10c = get_number(temp);
            } else if(strcmp(element,"5") == 0){
                temp = strtok(NULL, "c");
                wanted_5c = get_number(temp);
            } else if(strcmp(element,"1") == 0){
                temp = strtok(NULL, "c");
                wanted_1c = get_number(temp);
            } else
                return 0;
        }
        element = strtok(NULL, " + ");
    }
    
    if(wanted_2d == -1 || wanted_1d == -1 || wanted_50c == -1 || wanted_25c == -1 || wanted_10c == -1 || wanted_5c == -1 || wanted_1c == -1)
        return 0;
    if(wanted_2d > vallet->cnt_2d && vallet->cnt_2d != -1)
        return -1;
    if(wanted_1d > vallet->cnt_1d && vallet->cnt_1d != -1)
        return -1;
    if(wanted_50c > vallet->cnt_50c && vallet->cnt_50c != -1)
        return -1;
    if(wanted_25c > vallet->cnt_25c && vallet->cnt_25c != -1)
        return -1;
    if(wanted_10c > vallet->cnt_10c && vallet->cnt_10c != -1)
        return -1;
    if(wanted_5c > vallet->cnt_5c && vallet->cnt_5c != -1)
        return -1;
    if(wanted_5c > vallet->cnt_1c && vallet->cnt_1c != -1)
        return -1;
    
    vallet->cnt_2d -= wanted_2d;
    vallet->cnt_1d -= wanted_1d;
    vallet->cnt_50c -= wanted_50c;
    vallet->cnt_25c -= wanted_25c;
    vallet->cnt_10c -= wanted_10c;
    vallet->cnt_5c -= wanted_5c;
    vallet->cnt_1c -= wanted_1c;
    return 1;
}


