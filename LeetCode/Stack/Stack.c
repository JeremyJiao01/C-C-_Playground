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

// # 20 有效的括号
char convert(char a){
    if (a == '}') return '{';
    if (a == ']') return '[';
    if (a == ')') return '(';
    return 0;
}

bool isValid(char* s) {
    int n = strlen(s);
    if(n % 2 == 1){
        return false;
    }
    int stack[n + 1];
    int node = 0;
    for(int i = 0; i < n; i++){
        char ch = convert(s[i]);
        if(ch){
            if(node == 0 || stack[node - 1] != ch){
                return false;
            }
            node--;
        }else{
            stack[node] = s[i];
            node++;
        }
    }
    return node == 0;
}

// # 150 逆波兰表达式求值(后缀表达式)

bool isNumber(char* token){
    return strlen(token) > 1 || ('0' <= token[0] && token[0] <= '9');
}

int evalRPN(char** tokens, int tokensSize) {
    int* stack = (int*)malloc(sizeof(int) * tokensSize);
    int node = 0;
    for(int i = 0; i < tokensSize; i++){
        char* token = tokens[i];
        if(isNumber(token)){
            stack[node++] = atoi(token); // 将字符串里的所有数字提取
        }else{
            int num2 = stack[--node];
            int num1 = stack[--node];
            switch(token[0]){
                case'+':
                    stack[node++] = num1 + num2;
                    break;
                case'-':
                    stack[node++] = num1 - num2;
                    break; 
                case'*':
                    stack[node++] = num1 * num2;
                    break;  
                case'/':
                    stack[node++] = num1 / num2;
                    break;                                                     
            }
        }
    }
    return stack[node - 1];
}
