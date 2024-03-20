// # 71 简化路径
// 去掉'/'
char** split(char* s, char delim, int* returnSize){
    int n = strlen(s);
    char** ans = (char**)malloc(sizeof(char*) * n);
    // 因为可能出现 .. 这种两个字符的情况，因此需要二维数组
    int pos = 0;
    int cur = 0;
    int len = 0;

    while(pos < n){
        while(pos < n && s[pos] == delim){
            ++pos;
            // 找到不是'/'的位置
        }
        cur = pos;
        while(pos < n && s[pos] != delim){
            ++pos;
            // 找到是'/'的位置
        }
        if(cur < n){
            ans[len] = (char*)malloc(sizeof(char) * (pos - cur + 1));
            // 每行存读到的一种元素
            strncpy(ans[len], s + cur, pos - cur);
            // 存入元素，从 s+cur开始，一共传输pos-cur个元素
            ans[len][pos - cur] = '\0';
            ++len;
        }
    }
    *returnSize = len;
    return ans;
}

char* simplifyPath(char* path) {
    int namesSize = 0;
    int n = strlen(path);
    char** names = split(path, '/', &namesSize);
    char** stack = (char**)malloc(sizeof(char*) * namesSize);
    int stackSize = 0;
    for(int i = 0; i < namesSize; ++i){
        if(!strcmp(names[i], "..")){
            if(stackSize > 0){
                --stackSize;
            }
        }else if(strcmp(names[i], ".")){
            stack[stackSize] = names[i];
            ++stackSize;
        }
    }
    char* ans = (char*)malloc(sizeof(char) * (n+1));
    int cur = 0;
    if(stackSize == 0){
        ans[cur] = '/';
        ++cur;
    }else{
        for(int i = 0; i < stackSize; i++){
            ans[cur] = '/'; // 出栈
            ++cur;
            strcpy(ans + cur, stack[i]);
            cur += strlen(stack[i]);
        }
    }
    ans[cur] = '\0';
    for(int i = 0; i < namesSize; i++){
        free(names[i]);
    }
    free(names);
    free(stack);
    return ans;
}
