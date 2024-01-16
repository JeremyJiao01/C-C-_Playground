#include "Func.h"

//通讯录
//1>通讯录初始化后，能存放3个人的信息
//2>当我们空间的存放满的时候，我们增加2个信息

//每个人的信息：

//2. 增加人的信息
//3. 删除指定人的信息
//4. 修改指定人的信息
//5. 查找指定人的信息
//6. 排序通讯录的信息

void menu(){
    printf("*************************************\n");
    printf("********1. ADD  2. DEL***************\n");
    printf("********3. MOD  4. FIND**************\n");
    printf("********5. PRINT 0. EXIT*************\n");
    printf("*************************************\n");
}

enum Option {
    EXIT,
    ADD,
    DEL,
    MOD,
    FIND,
    PRINT
};

int main() {
    int input = 0;
    Con Con;
    Init_con(&Con);
    do {
        menu();
        printf("CHOOSE MODE\n");
        scanf("%d", &input);
        switch (input) {
            case ADD:
                Add(&Con);
                break;
            case DEL:
                Del(&Con);
                break;
            case MOD:
                Mod(&Con);
                break;
            case FIND:
                Find(&Con);
                break;
            case PRINT:
                Print(&Con);
                break;
            case EXIT:
                return 0;
        }
    } while (input);
    return 0;
}
