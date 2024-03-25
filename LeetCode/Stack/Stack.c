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

// # 496 下一个更大的元素
// 倒序遍历 nums2，并用单调栈中维护当前位置右边的更大的元素列表，
// 从栈底到栈顶的元素是单调递减的，得到每个元素右边的第一个更大元素值
// 使用哈希表存储以上得到的结果
int* nextGreaterElement(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    *returnSize = nums1Size;
    int* res = (int*)malloc(sizeof(int) * nums1Size);
    
    // Simulate the stack with a dynamic array
    int* stack = (int*)malloc(sizeof(int) * nums2Size);
    int stackSize = 0;
    
    // The "map" will be a 2D array with the first column being the number from nums2
    // and the second column being the next greater element for that number
    int** map = (int**)malloc(sizeof(int*) * nums2Size);
    for (int i = 0; i < nums2Size; ++i) {
        map[i] = (int*)malloc(sizeof(int) * 2);
    }

    for (int i = nums2Size - 1; i >= 0; --i) {
        while (stackSize > 0 && nums2[i] >= stack[stackSize - 1]) {
            --stackSize; // Simulating pop operation
        }
        map[i][0] = nums2[i];
        map[i][1] = stackSize == 0 ? -1 : stack[stackSize - 1];
        stack[stackSize++] = nums2[i]; // Simulating push operation
    }
    
    // Simulate the get operation from the map
    for (int i = 0; i < nums1Size; ++i) {
        for (int j = 0; j < nums2Size; ++j) {
            if (map[j][0] == nums1[i]) {
                res[i] = map[j][1];
                break;
            }
        }
    }
    return res;
}

// 使用栈来保存元素下标
// 当新的元素入栈时，弹出所有值小于当前元素的下标
// 整个遍历大小为numsSize * 2 - 1，只需对其取模即可
int* nextGreaterElements(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    if(numsSize == 0){
        return NULL;
    }
    int* returnArr = (int*)malloc(sizeof(int) * numsSize);
    memset(returnArr, -1, sizeof(int) * numsSize);
    int stack[numsSize * 2 - 1], stackTop = 0;
    for(int i = 0; i < numsSize * 2 - 1; i++){
        while(stackTop > 0 && nums[stack[stackTop - 1]] < nums[i % numsSize]){
            returnArr[stack[stackTop - 1]] = nums[i % numsSize];
            stackTop--;
        }
        stack[stackTop++] = i % numsSize;
    }
    return returnArr;
}








