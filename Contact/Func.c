#include "Func.h"

static void CheckStraoge(Con *data){
    if(data->size == data->storage)
    {
        PerInfo *ptr = (PerInfo*)realloc(data->p, (data->storage + ADD_NUM)*sizeof(PerInfo) ) ;
        if(ptr != NULL)
        {
            data->p = ptr;
            data->storage += ADD_NUM;
            printf("Adding Storage Succeed\n");
        }
        else
        {
            printf("Adding Storage Failed\n");
            return;
        }
    }
}

void Init_con(Con *data){
    data->p = (PerInfo *)calloc(Default,sizeof(PerInfo));
    if (data->p == NULL)
        return;
    data->size = 0;
    data->storage = Default;
    LoadFile(data);
}

void LoadFile(Con *data){
    FILE *pf = fopen("Contact.dat", "r");
    if(pf == NULL){
        perror("Contact.dat");
        return;
    }
    PerInfo tmp = {0};
    while(fread(&tmp, sizeof(PerInfo), 1, pf)){
        CheckStraoge(data);
        data->p[data->size] = tmp;
        data->size++;
    }
    fclose(pf);
    pf = NULL;
}

void Add(Con *data){
    CheckStraoge(data);
    printf("Enter Name\n");
    scanf("%s", data->p[data->size].name);
    printf("Enter Sexual\n");
    scanf("%s", data->p[data->size].sex);
    printf("Enter Age\n");
    scanf("%d",&(data->p[data->size].age));
    printf("Enter Address\n");
    scanf("%s", data->p[data->size].addr);
    printf("Enter Telephone\n");
    scanf("%s", data->p[data->size].tele);
    data->size++;
    printf("Adding Contact Succeed\n");
}

void Print(Con *data){
    if(data->size == 0) {
        printf("Contact No Data\n");
        return;
    }
    printf("%s\t %s\t %s\t %s\t %s\t\n", "Name", "Sexual", "Age", "Addr", "Telephone");
    int i = 0;
    for(i = 0; i < data->size; i++){
        printf("%s\t %s\t %6d\t %6s\t %8s\t\n", data->p[i].name, data->p[i].sex, data->p[i].age, data->p[i].addr, data->p[i].tele);
    }
}

int Search(Con *data, char name[]) {
    int i = 0;
    for (i = 0; i < data->size; i++) {
        if (strcmp(data->p[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void Find(Con *data){
    if(data->size == 0) {
        printf("Contact No Data\n");
        return;
    }
    char input[Max_name] = {0};
    printf("Enter Name\n");
    scanf("%s", input);
    int i = Search(data, input);
    if(i != -1 ){
        printf("The Person You Find is:\n");
        printf("%s\t %s\t %s\t %s\t %s\t\n", "Name", "Sexual", "Age", "Addr", "Telephone");
        printf("%s\t %s\t %6d\t %6s\t %8s\t\n", data->p[i].name, data->p[i].sex, data->p[i].age, data->p[i].addr, data->p[i].tele);
        return;
    }
    printf("The Person You Find Isn't In Contact Data \n");

}

void Del(Con *data){
    if(data->size == 0) {
        printf("Contact No Data\n");
        return;
    }
    char input[Max_name] = {0};
    printf("Enter Name To Delete\n");
    scanf("%s", input);
    int i = Search(data, input);
    if(i != -1){
        int j = 0;
        for(j = i; j < (data->size)-1; j++){
            data->p[i] = data->p[i+1];
        }
        data->size--;
        printf("Delete Succeed\n");
        return;
    }
    printf("Not Find\n");
}

void Mod(Con *data){
    if(data->size == 0) {
        printf("Contact No Data\n");
        return;
    }
    char input[Max_name] = {0};
    printf("Enter Name To Modify\n");
    scanf("%s", input);
    int i = Search(data, input);
    if(i != -1){
        printf("Enter Name\n");
        scanf("%s", data->p[i].name);
        printf("Enter Sexual\n");
        scanf("%s", data->p[i].sex);
        printf("Enter Age\n");
        scanf("%d",&(data->p[i].age));
        printf("Enter Address\n");
        scanf("%s", data->p[i].addr);
        printf("Enter Telephone\n");
        scanf("%s", data->p[i].tele);
        printf("Modify Contact Succeed\n");
    }
}

void Destroy(Con *data){
    free(data->p);
    data->p = NULL;
    data->size = 0;
    data->storage = 0;
}

void SaveContact(Con *data){
    FILE* pf = fopen("Contact.dat","w");
	if (pf == NULL)
	{
		perror("SaveContact");
		return;
	}
    int i = 0;
    for(i = 0; i < data->size; i++){
        fwrite(data->p+i, sizeof(PerInfo), 1, pf);
    }
    fclose(pf);
    pf = NULL;
}