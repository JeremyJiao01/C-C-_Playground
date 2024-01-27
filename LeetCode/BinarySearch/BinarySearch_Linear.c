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
