// mergeSort （优化）
// 使用递归的方法，不断将数组分为两个有序的部分
// 在对数组进行有序合并

#define INSERTION_SORT_THRESHOLD = 47 // 当列表大小小于47时使用插入排序
				      // 此参数应当是超参数，但是为方便设为47

void mergeSort(int* nums, int numsSize, int left, int right, int* tmp){
	if(left == right){
		return;
	}
	if(right - left <= INSERTION_SORT_THRESHOLD){
		insertionSort(nums, left, right);
		return;
	} // 优化1：小区间内使用插入排序
	int mid = (left + right) / 2;
	mergeSort(nums, left, mid, tmp);
	mergeSort(nums, mid + 1, right, tmp);

	mergeTwoArr(nums, numsSize, left, mid, right, tmp);
}

void mergeTwoArr(int* nums, int numsSize, int left, int mid, int right, int* tmpArr){
	int len = right - left + 1;
	int i = left;
	int j = mid + 1;
	int k = 0;
	// 判断指针下标是否越界
	while(i <= mid && j <= right){
		if(nums[i] <= nums[j]){
			tempArr[k++] = nums[i++];
		}else{
			tempArr[k++] = nums[j++];
		}
	}
	// 剩下的直接将数组中的值复制进去
	while(i <= mid){
		tempArr[k++] = nums[i++];
	}
	while(j <= right){
		tempArr[k++] = nums[j++];
	}
	// 重新排列原数组
	int b = 0; 
	for(int a = left; a <= right; a++){
		nums[a] = temp[b++];
	}
}

int* sortArr(int* nums, int numsSize){
	int* tmp = (int*)malloc(numsSize * sizeof(int));
	// 优化3：全局使用同一个临时数组
	mergeSort(nums, numsSize, 0, len - 1, tmp);
	return nums;
}

// ---------------------题目---------------------------
// # 189 轮转数组
// 思路：
// 方法一：使用额外的数组
// 用 n 表示数组的长度，遍历原数组
// 将数组下标为 i 的元素放到新数组的 (i + k) mod n 的位置
// 然后拷贝新数组到原数组上

// 方法二：环状替代（原地操作）
// 通过方法一的 (i + k) mod n 的操作
// 我们可知这本身就是一个环状循环，因此我们只需要以下步骤
//    1. 从 0 开始，最初令 tmp = nums[0]
//       根据规则，位置 0 应该放在 (0 + k) mod n处
//    2. 此时令 x = (0 + k) mod n 再交换nums[0] 和 nums[x]
//    3. 不断进行上述过程，知道回到初始位置0
// 在遍历过程中，我们每一趟遍历不一定能全部遍历完
// 因此我们的目标是求的最小的遍历次数
// 现在有几个参数： n 数组长度， k 间隔数， 
//               a 需要遍历几次， b 总共遍历的几个元素
// 因为 a = n / b，b = 最小公倍数(n, k) / k
// 所以 a = 最大公约数(n, k)

int gcd(int a, int b){
    return b ? gcd(b, a % b) : a;
}

void swap(int* a, int* b){
    int t = *a;
    *a = *b;
    *b = t;
}

void rotate(int* nums, int numsSize, int k) {
    k = k % numsSize;
    // 目的是将k值固定在小于numsSize中
    int count = gcd(k, numsSize);
    for(int i = 0; i < count; ++i){
        int cur = i; // 当前位置
        int prev = nums[i];
        do{
            int next = (cur + k) % numsSize; 
            // 下一个间隔后的位置
            swap(&nums[next], &prev);
            cur = next;
        }while(i != cur); // 循环到初始位置就结束
    }
}

// 方法三：
// 翻转数组也可以理解为：先将所有的元素翻转
// 这样尾部 k mod n 个元素就被移动到数组头部
// 然后在翻转[0, k mod (n - 1)]和[k mod n, n - 1]即可
void swap(int* a, int* b){
    int t = *a;
    *a = *b;
    *b = t;
}

void reverse(int* nums, int start, int end){
    while(start < end){
        swap(&nums[start], &nums[end]);
        start += 1;
        end -= 1;
    }
}

void rotate(int* nums, int numsSize, int k){
    k = k % numsSize;
    reverse(nums, 0, numsSize - 1);
    reverse(nums, 0, k - 1);
    reverse(nums, k, numsSize - 1);
}

// # 170 求逆序数（困难）
// 思路：
// 使用归并排序分而治之的思想
int mergingTwoArr(int* record, int left, int mid, int right, int* tmp){
    int len = right - left + 1;
    int i = left;
    int j = mid + 1;
    int count = 0;
    int k = 0;
    while(i <= mid && j <= right){
        if(record[i] <= record[j]){
            tmp[k++] = record[i++];
        }else{
            tmp[k++] = record[j++];
            count += (mid - i + 1);
            // 这里取 mid - i + 1的意思是
            // mid位于左边一组中，若左边的元素i大于右边的元素j
            // 则mid到i之间所有数都大于右边的元素j
        }
    }
    while(i <= mid){
        tmp[k++] = record[i++];
    }
    while(j <= right){
        tmp[k++] = record[j++];
    }
    int b = 0;
    for(int i = left; i <= right; i++){
        record[i] = tmp[b++];
    }
    return count;
}

int dividePairs(int* record, int left, int right, int* tmp){
    if(left == right){
        return 0;
    }
    int mid = left + (right - left) / 2;
    int leftParis = dividePairs(record, left, mid, tmp);
    int rightParis = dividePairs(record, mid + 1, right, tmp);

    if(record[mid] <= record[mid + 1]){
        return leftParis + rightParis;
    }
    int acrossParis = mergingTwoArr(record, left, mid, right, tmp);
    return leftParis + rightParis + acrossParis;
}


int reversePairs(int* record, int recordSize) {
    if(recordSize < 2){
        return 0;
    }
    int* tmp = (int*)malloc(recordSize * sizeof(int));
    return dividePairs(record, 0, recordSize - 1, tmp);
}
