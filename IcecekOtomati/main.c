//
//  main.c
//  IcecekOtomati
//
//  Created by Alperen Acer on 12.05.2022.
//
#include <stdio.h>
#include <stdlib.h>
#include "controlstructures.h"
#include "linkedlist.h"
#include <string.h>

int read_products(DoublyLinkedList* prd_list){
    FILE* file_ptr = NULL;
    char* line = NULL;
    size_t line_len = 0;
    ssize_t size = 0;
    
    file_ptr = fopen("Prices.txt", "r");
    if(file_ptr == NULL)
        return -1;
    Product* prd;
    char* name;
    char* stock;
    char* price;
    int stock_num;
    while((size = getline(&line, &line_len, file_ptr)) != -1){
        name = strtok(line, ",");
        stock = strtok(NULL, ",");
        price = strtok(NULL, ",");
        stock_num = atoi(stock);
        //correct the price!
        prd = create_product(name, stock_num ,254);
        addToTail(prd_list, prd);
    }
    return 0;
}
void read_coins(void){
    
}
int main(int argc, const char * argv[]) {
    // insert code here...
    cash_register* poss;
    int status = 0;
    DoublyLinkedList* prd_list = initializeList();
    Product* prd1 = create_product("prd1", 10, 254);
    Product* prd2 = create_product("prd2", 15, 253);
    Product* prd3 = create_product("prd3", 1, 252);
    addToTail(prd_list, prd1);
    addToTail(prd_list, prd2);
    addToTail(prd_list, prd3);
    printf("İçecek Listesi\n");
    print_list(prd_list);
    printf("Lütfen Para Atınız\n");
    cash_register* vallet = create_cashregister();
    printf("Bakım menüsü için 'bakım' yazıp enter a basabilirsiniz...\n");
    printf("Uygulamadan çıkmak için 'çıkış' yazıp enter a basabilirsiniz...\n");
    while(status != -1){
        char* line = NULL;
        size_t line_len = 0;
        ssize_t line_size = 0;
        switch(status){
            case 0:
                printf("Lütfen para miktarını giriniz!\nPara atmayı sonlandırmak için giriş yapmadan enter'a basınız.\n");
                break;
            case 1:
                print_list(prd_list);
                print_cash(vallet);
                printf("Lütfen ürünü numarasını girip enter a basınız.\nBakiye eklemek için 'e' yazıp enter'a basınız.\nPara üstünüzü almak için enter'a basınız.\nUygulamadan çıkmak için 'çıkış' yazıp enter a basabilirsiniz...\n");
                break;
            case 2:
                break;
     
        }
        line_size = getline(&line, &line_len, stdin);
        if(strcmp(line,"bakım\n") == 0)
            status = 3;
        if(strcmp(line,"çıkış\n") == 0)
            break;
        switch(status){
            case 0:
                if(add_coin(vallet, line))
                    print_cash(vallet);
                else if(line_size != 1)
                    printf("Yanlış format!Geçerli formatlar \"2$ 1$ 50c 25c 10c 5c 1c\"\n");
                else if(line_size == 1)
                    status = 1;
                break;
            case 1:
                if(line_size == 1){
                    int remain = cash_return(vallet);
                    if(remain == 0)
                        printf("Tüm bakiyeniz iade edilmiştir.\n");
                    else
                        printf("%dc bakiye kasada yeterli bozukluk olmadığı için iade edilememiştir.\n", remain);
                    printf("Satın alma sonlandırılmıştır.\n");
                    status = 0;
                } else if(strcmp(line, "e\n") == 0){
                    status = 0;
                } else {
                    int result = sell_product(prd_list, line, vallet);
                    if(result == -1)
                        printf("Yanlış giriş yaptınız!\n");
                    if(result == 0)
                        printf("Yetersiz bakiye!\n");
                    if(result == 1)
                        printf("Satın alma başarılı!\n");
                }
                
                    
                break;
            case 2:
                break;
     
        }
    }
    printf("Uygulama sonlandı!\n");
    destroy_list(prd_list);
    free(vallet);
    
    return 0;
}
