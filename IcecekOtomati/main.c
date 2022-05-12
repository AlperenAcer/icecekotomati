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

int read_products(DoublyLinkedList* prd_list, const char* path){
    FILE* file_ptr = NULL;
    char* line = NULL;
    size_t line_len = 0;
    ssize_t size = 0;
    char* file_name = "/Prices.txt";
    char* full_path = (char*)malloc(strlen(file_name) + strlen(path) + 1);
    strcat(full_path, path);
    strcat(full_path, file_name);
    file_ptr = fopen(full_path, "r");
    if(file_ptr == NULL)
        return -1;
    Product* prd;
    char* name;
    char* stock;
    char* price;
    int stock_num;
    int price_c = 10000;
    long price_len;
    while((size = getline(&line, &line_len, file_ptr)) != -1){
        name = strtok(line, ",");
        stock = strtok(NULL, ",");
        price = strtok(NULL, ",");
        stock_num = atoi(stock);
        price_len = strlen(price);
        if(price[price_len-1] == 'c')
            price_c = atoi(price);
        else
            price_c = atof(price)*100;
        prd = create_product(name, stock_num ,price_c);
        addToTail(prd_list, prd);
    }
    if(line != NULL)
        free(line);
    fclose(file_ptr);
    free(full_path);
    return 0;
}

char* read_coins(cash_register* vallet, const char* path){
    FILE* file_ptr = NULL;
    char* line = NULL;
    size_t line_len = 0;
    ssize_t size = 0;
    char* accepted_coins = "";
    char* file_name = "/Coins.txt";
    char* full_path = (char*)malloc(strlen(file_name) + strlen(path) + 1);
    strcat(full_path, path);
    strcat(full_path, file_name);
    file_ptr = fopen(full_path, "r");
    if(file_ptr == NULL)
        return NULL;
    if((size = getline(&line, &line_len, file_ptr)) != -1){
        accepted_coins = (char*)malloc(line_len*sizeof(char));
        strcpy(accepted_coins, line);
        char* element;
        element = strtok(line,",");
        while(element != NULL){
            if(strcmp(element,"2$") == 0)
                vallet->cnt_2d = 0;
            else if(strcmp(element,"1$") == 0)
                vallet->cnt_1d = 0;
            else if(strcmp(element,"50c") == 0)
                vallet->cnt_50c = 0;
            else if(strcmp(element,"25c") == 0)
                vallet->cnt_25c = 0;
            else if(strcmp(element,"10c") == 0)
                vallet->cnt_10c = 0;
            else if(strcmp(element,"5c") == 0)
                vallet->cnt_5c = 0;
            else if(strcmp(element,"1c") == 0)
                vallet->cnt_1c = 0;
            element = strtok(NULL, ",");
        }
    }
    if(line != NULL)
        free(line);
    fclose(file_ptr);
    free(full_path);
    return accepted_coins;
}
int main(int argc, const char * argv[]) {
    // insert code here...
    //printf("%s\n", argv[0]);
    char* password = "112358\n";
    cash_register* vallet = create_cashregister();
    int status = 0;
    int last_status = 0;
    DoublyLinkedList* prd_list = initializeList();
    read_products(prd_list, argv[1]);
    char* accepted_coins = read_coins(vallet, argv[1]);
    printf("İçecek Listesi\n");
    print_list(prd_list);
    printf("Lütfen Para Atınız\n");
    
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
                printf("Lütfen şifreyi giriniz: ");
                status = 3;
                break;
            case 3:
                break;
            case 4:
                printf("Otomat Kasasını Açmak için '1' Satışları Görüntülemek için '2' yazıp enter'a basınız!\nBakım menüsünden çıkmak için giriş yapmadan enter'a basınız.\n");
                break;
            case 5:
                printf("Çekmek istediğiniz coinleri giriniz. Örnek Kullanım aşağıdaki gibidir.\n2$4 + 1$4 + 50c3 + 25c40 + 5c8 + 1c23\nKasayı kapatmak için giriş yapmadan enter'a basınız.");
                break;
     
        }
        line_size = getline(&line, &line_len, stdin);
        if(strcmp(line,"bakım\n") == 0){
            
            if(vallet->customer_balance > 0){
                
                printf("Devam eden alışveriş bulunmakta. Bakım moduna geçmek için alışverişi sonlandırıp para üstü alın.\n");
                } else {
                    last_status = status;
                    status = 2;
                }
            
        } else if(strcmp(line,"çıkış\n") == 0)
            break;
        switch(status){
            case 0:
                if(add_coin(vallet, line))
                    print_cash(vallet);
                else if(line_size != 1)
                    printf("Yanlış coin!\nGeçerli Coinler: %s\n", accepted_coins);
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
            case 3:
                if(line_size == 1) {
                    status = last_status;
                }
                else if(strcmp(line, password) == 0){
                    printf("Bakım modune geçildi!\n");
                    status = 4;
                } else {
                    printf("Şifre yanlış!\nBakım modundan çıkmak isterseniz şifre girmeden enter'a basınız!\n");
                    status = 2;
                }
                break;
            case 4:
                if(line_size == 1) {
                    status = last_status;
                } else if(line[0] == '1') {
                    printf("Kasa açıldı\n");
                    print_vallet(vallet);
                    status = 5;
                } else if(line[0] == '2') {
                    print_sold(prd_list);
                }
                break;
            case 5:
                if(line_size == 1){
                    status = 4;
                    print_vallet(vallet);
                    printf("Kasa kapandı!\n");
                }else {
                    int result = cash_retrieve(vallet, line);
                    if(result == 1){
                        printf("Para çekimi başarılı. Kasada kalan coinler aşağıdaki gibidir.\n");
                        print_vallet(vallet);
                    } else if(result == 0){
                        printf("Yanlış formatta giriş yapıldı.\n");
                    } else if(result == -1){
                        printf("Kasada yeterli coin bulunmamakta.\n");
                    }
                        
                }
                    
                break;
     
        }
    }
    printf("Uygulama sonlandı!\n");
    destroy_list(prd_list);
    free(vallet);
    
    return 0;
}
