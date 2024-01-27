// # 875 线性相关二分搜索
// 思路：
// 限制时间为 h
// 吃香蕉需要的时间为 piles[i] / k 向上取整
// 每个小时选一堆
// k 的取值范围是 1～max(piles)
// 当吃完时间总和大于 h 时，left = mid + 1
// 当吃完时间小于等于 h 时，right = mid

int Max(int arr, int x){
    if(arr < x){
        return x;
    }else{
        return arr;
    }
}

int caculate(int* arr, int arrSize, int k){
    int cnt = 0;
    int i = 0;
    for(i = 0; i < arrSize; i++){
        cnt += (arr[i] + k - 1) / k;
        // 向上取整的写法
    }
    return cnt;
}

int minEatingSpeed(int* piles, int pilesSize, int h) {
    int i = 0;
    int max = 0;
    for(i = 0; i < pilesSize; i++){
        max = Max(piles[i], max);
    }
    int left = 1;
    int right = max;
    while(left < right){
        int mid = (left + right) / 2;
        if(caculate(piles, pilesSize, mid) > h){
            left = mid + 1;
        }else{
            right = mid;
        }
    }
    return left;
}


// # 410 分割数组的最大值
// 思路：
// 将分组 M 作为二分查找的判断
// M 的取值范围是 1～numsSize
// 二分搜索的值为前n项和a，当小于a的值为一个组
// 使用二分搜索，如果二分搜索得出的分组数大于题目给的k
// left = mid + 1

int Max(int a, int b){
    if(a > b){
        return a;
    }else{
        return b;
    }
}

int split(int* nums,int numsSize, int k){
    int splits = 1;
    // 当前区间的和
    int curIntervalSum = 0;
    int i = 0;
    for (i = 0; i < numsSize; i++) {
        // 尝试加上当前遍历的这个数
        // 如果加上去超过了「子数组各自的和的最大值」
        // 就不加这个数，另起炉灶
        if (curIntervalSum + nums[i] > k) {
            curIntervalSum = 0;
            splits++;
        }
        curIntervalSum += nums[i];
    }
    return splits;
}

int splitArray(int* nums, int numsSize, int k) {
    int max = 0;
    int sum = 0;
    int i = 0;
    for(i = 0; i < numsSize; i++){
        max = Max(nums[i], max);
        sum += nums[i];
    }
    int left = max;
    int right = sum;
    while(left < right){
        int mid = (left + right) >> 1;
        int splits = split(nums, numsSize, mid);
        if(splits > k){
            left = mid + 1;
        }else{
            right = mid;
        }
    } 
    return left;
}
