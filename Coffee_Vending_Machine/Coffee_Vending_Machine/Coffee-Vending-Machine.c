// https://github.com/jaehee22/coffe_machine_cpp/blob/master/coffe_machine.cpp 해당 코드 사용하여 만듦
//헤더파일 및 매크로 상수
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <Windows.h>
#include<string.h>
#include <math.h>


//전역변수
int Coffe[100];                             //커피 이름, 가격, 재고는 전부 필요하니까 전역변수로 선언
int Coffe_Price[6], Coffe_Stock[10];
int Coffe_S[10];                            // 커피의 매출 
int Money = 0;                              // 투입된 돈
int TotalPrice = 0;                         // 주문한 커피 합계 금액
int TotalMoney = 0;                         // 투입된 돈 총액


//함수
int Insert_Money();
void Coffe_Set();
void Menu_List();
void Coffe_List();
void Coffe_Order();
int Return_Change();
void Show_Coffe_Sales();
void Show_Coffe_Stock();
void Coffe_Stock_Plus();
void Coffe_Reset();


//메인함수
int main() {

    Coffe_Set();      //커피 리스트를 미리 세팅한다.
    int n = 0;

    while (n != 7) {

        Menu_List();
        printf("명령어 입력 : ");
        scanf("%d", &n);
        printf("\n\n");
        switch (n) {
        case 1:
            Insert_Money();
            Coffe_Order();
            break;
        case 2:
            Return_Change();
            break;

        case 3:
            Show_Coffe_Sales();
            break;

        case 4:
            Show_Coffe_Stock();
            break;

        case 5:
            Coffe_Stock_Plus();
            break;

        case 6:
            Coffe_Reset();
            break;

        default:
            break;

        }
        system("cls");
    }
    return 0;
}

//커피의 이름/가격/재고/매출을 미리 설정한다.
void Coffe_Set() {
    Coffe[1] = "믹스커피";
    Coffe[2] = "아메리카노";
    Coffe[3] = "카페라떼";
    Coffe[4] = "카라멜라떼";
    Coffe[5] = "모카라떼";
    Coffe_Price[1] = 700;
    Coffe_Price[2] = 2000;
    Coffe_Price[3] = 2500;
    Coffe_Price[4] = 1500;
    Coffe_Price[5] = 3000;

    for (int i = 1; i <= 5; i++) {      //기본 재고는 10개로 한다.
        Coffe_Stock[i] = 10;
        Coffe_S[i] = 0;
    }
}

//초기화면
void Menu_List() {
    printf("=====================\n");
    printf("|=<<<커피자판기>>>==|\n");
    printf("=====================\n");
    printf("|     <<메뉴>>      |\n");
    printf("=====================\n");
    printf("1. 커피 주문하기\n");
    printf("2. 잔돈 반환\n");
    printf("3. 커피 매출 확인\n");
    printf("4. 커피 재고 확인 하기\n");
    printf("5. 커피 재고 입고 하기\n");
    printf("6. 커피 자판기 초기화\n");
    printf("7. 종료하기\n");
    printf("=====================\n");
}


//돈 투입
int Insert_Money()
{
    while (1) {
        printf("     돈을 투입하세요      \n");
        printf("투입액(천원에서 오만원까지 투입가능)>>");
        scanf("%d", &Money);

        if ((Money < 1000) || (Money > 50000)) {
            printf("잘못 투입되었습니다.\n\n");
            continue;
        }
        else {
            printf("%d원 투입되었습니다.\n\n", Money);
            TotalMoney += Money;
            printf("현재까지 투입된 돈 : %d\n\n", TotalMoney);
            return;
        }
    }
}


//커피의 가격 및 재고를 출력한다.
void Coffe_List() {
    int i = 1;
    while (Coffe[i] != NULL) {
        for (int j = 1; j <= 5; j++) {
            printf("%d.  %s   가격:%d   ", i, Coffe[i], Coffe_Price[i]);
            if (Coffe_Stock[i] <= 0) {
                printf("재고 없음\n\n");
            }
            else
                printf("재고:% d\n\n", Coffe_Stock[i]);
            i++;
        }
    }
}


//커피를 주문한다
void Coffe_Order() {
    int Choice = 0, Coffe_N;         //Choice : 커피를 선택, Coffe_N : 커피의 개수
    while (Choice != 9) {
        Coffe_List();
        printf("구입하실 커피의 번호를 선택해주세요. (뒤로가시려면 9번을 누르세요.)\n");
        scanf("%d", &Choice);
        printf("\n\n");
        if (Choice == 9) {
            break;
        }
        else if (Coffe[Choice] <= 6) {
            printf("해당되는 커피는 없습니다.\n");
            continue;
        }
        printf("몇개를 주문하시겠습니까?\n");
        scanf("%d", &Coffe_N);
        printf("\n\n");
        while (Coffe_Stock[Choice] < Coffe_N) {
            printf("죄송합니다. 커피의 수량이 부족합니다. 수량을 조정해주세요\n");
            scanf("%d", &Coffe_N);
            printf("\n\n");
        }
        TotalPrice = Coffe_Price[Choice] * Coffe_N;         //주문된 커피 총액

        if (TotalMoney >= TotalPrice) {
            printf("결제가 완료되었습니다. 제품을 받아주세요\n");
            printf("잔돈은 %d원 입니다.\n\n", TotalMoney - TotalPrice);
            TotalMoney -= TotalPrice;                           //현재 금액에서 커피 금액 빼기
            Coffe_Stock[Choice] -= Coffe_N;                     //커피의 재고 빼기
            Coffe_S[Choice] += Coffe_Price[Choice] * Coffe_N;   //커피의 매출 더하기
        }

        else
            printf("투입된 돈이 없거나 부족합니다. 제품을 수령하실 수 없습니다.\n9번을 눌러 다시 결제를 진행해 주십시오.\n\n");
    }
    Sleep(3000);
    return;
}


//잔돈을 반환합니다.
int Return_Change() {

    printf("잔돈을 반환합니다.\n");
    printf("잔돈은 %d원입니다.\n", TotalMoney);

    Sleep(3000);
    return TotalMoney = 0;
}



//커피 매출을 확인한다
void Show_Coffe_Sales() {
    int Total_Sale = 0, i = 1;
    while (Coffe[i] != NULL) {
        for (int j = 1; j <= 5; j++) {
            printf("%s 매출 : %d원\n", Coffe[i], Coffe_S[i]);
            Total_Sale += Coffe_S[i];
            i++;
        }
    }
    printf("총 매출 : %d원\n\n", Total_Sale);
    Sleep(3000);
}


//자판기를 초기화한다
void Coffe_Reset() {
    int Total_Sale = 0, i = 1;
    while (Coffe[i] != NULL) {
        for (int j = 1; j <= 5; j++) {
            Coffe_Stock[i] = 10;
            Coffe_S[i] = 0;
            i++;
        }
    }
    Sleep(3000);
    return TotalMoney = 0;
}


//커피의 재고를 출력한다
void Show_Coffe_Stock() {
    int i = 1;
    while (Coffe[i] != NULL) {
        for (int j = 1; j <= 5; j++) {
            printf("%d.  %s   ", i, Coffe[i]);
            if (Coffe_Stock[i] <= 0) {
                printf("재고 없음\n\n");
            }
            else
                printf("재고:% d\n\n", Coffe_Stock[i]);
            i++;
        }
    }
    Sleep(3000);
}


//커피재고를 입고한다
void Coffe_Stock_Plus() {
    int Choice = 0, Coffe_N;
    while (Choice != 9) {
        Coffe_List();
        printf("입고하실 커피의 번호를 선택해주세요. (뒤로가시려면 9번을 누르세요.)\n");
        scanf("%d", &Choice);
        printf("\n\n");
        if (Choice == 9)
            break;
        else if (Coffe[Choice] <= 6) {
            printf("해당되는 커피는 없습니다.\n");
            continue;
        }
        printf("몇개를 입고하시겠습니까?\n");
        scanf("%d", &Coffe_N);
        printf("\n");
        printf("커피 번호 %d에 %d개를 입고하였습니다\n", Choice, Coffe_N);
        printf("\n\n");
        Coffe_Stock[Choice] += Coffe_N;
    }
    Sleep(3000);
    return;
}