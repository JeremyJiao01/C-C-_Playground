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

// # 316 去除重复字幕
char* removeDuplicateLetters(char* s) {
    int hash[26], visit[26];
    memset(hash, 0, sizeof(hash));
    memset(visit, 0, sizeof(visit));

    int n = strlen(s);
    for(int i = 0; i < n; i++){
    	hash[s[i] - 'a']++;
    }
    char* returnChar = (char*)malloc(sizeof(char)*27);
    int stackTop = 0;
    for(int i = 0; i < n; i++){
    	if(!visit[s[i] - 'a']){ // 如果没有访问过这个元素
    		while(stackTop > 0 && returnChar[stackTop - 1] > s[i]){
    		// 若前一个元素字典序大于当前
    			if(hash[returnChar[stackTop - 1] - 'a'] > 0){
    			// 若该元素在后面还会出现
    				visit[returnChar[--stackTop] - 'a'] = 0;
    				// 在栈中删去该元素	
    			} else {
    				// 如果后续没出现，则保留该元素
    				break;
    			}
    		}
    		visit[s[i] - 'a'] = 1;
    		returnChar[stackTop++] = s[i];
    		// 在栈中加入该元素
    	}
    	hash[s[i] - 'a'] -= 1;
    	// 元素在后续数量减一
    }
    returnChar[stackTop] = '\0';
    return returnChar;    
}

char* removeDuplicateLetters(char* s) {
    int hash[26], visit[26];
    memset(hash, 0, sizeof(hash));
    memset(visit, 0, sizeof(visit));

    int n = strlen(s);
    for(int i = 0; i < n; i++){
    	hash[s[i] - 'a']++;
    }
    char* returnChar = (char*)malloc(sizeof(char)*27);
    int stackTop = 0;
    for(int i = 0; i < n; i++){
    	if(!visit[s[i] - 'a']){ // 如果没有访问过这个元素
    		while(stackTop > 0 && returnChar[stackTop - 1] > s[i]){
    		// 若前一个元素字典序大于当前
    			if(hash[returnChar[stackTop - 1] - 'a'] > 0){
    			// 若该元素在后面还会出现
    				visit[returnChar[--stackTop] - 'a'] = 0;
    				// 在访问列表中删去该元素	
    			} else {
    				// 如果访问过该元素则直接跳过
    				break;
    			}
    		}
    		visit[s[i] - 'a'] = 1;
    		returnChar[stackTop++] = s[i];
    		// 在栈中加入该元素
    	}
    	hash[s[i] - 'a'] -= 1;
    	// 元素在后续数量减一
    }
    returnChar[stackTop] = '\0';
    return returnChar;    
}

// # 739 每日温度
int* dailyTemperatures(int* temperatures, int temperaturesSize, int* returnSize) {
    *returnSize = temperaturesSize;
    int* ans = (int*)malloc(sizeof(int) * temperaturesSize);

    for (int i = 0; i < temperaturesSize; ++i) {
        ans[i] = 0; // Initialize the answer array with 0
    }
    // We will use a dynamically-allocated array to simulate a stack.
    // stack is used to storage the subscript of temperatiures element
    int* stack = (int*)malloc(sizeof(int) * temperaturesSize);
    int stackTop = 0;

    for (int i = 0; i < temperaturesSize; ++i) {
        while (stackTop > 0 && temperatures[i] > temperatures[stack[stackTop - 1]]) {
            int prevIndex = stack[--stackTop]; // Simulating pop operation
            ans[prevIndex] = i - prevIndex;
        }
        // when temperatures element's value less than the previous elements' value 
        stack[stackTop++] = i; // Simulating push operation
    }
    return ans;
}
