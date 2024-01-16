#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define Max_name 20
#define Max_addr 30
#define Max_tele 12
#define Max_sex 10

#define Default 3
#define ADD_NUM 2


// 初始化通讯录结构体
// 名字+性别+电话+地址
typedef struct PerInfo{
    char name[Max_name];
    int age;
    char addr[Max_addr];
    char tele[Max_tele];
    char sex[Max_sex];
}PerInfo;

typedef struct Con{
    int size;
    int storage;
    PerInfo *p;
}Con;

void Init_con(Con *data);

void Add(Con *data);

void Print(Con *data);

void Find(Con *data);

void Del(Con *data);

void Mod(Con *data);