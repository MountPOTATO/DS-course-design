#include "assmt_10.h"


inline bool less(int numA, int numB)
{
	return numA < numB;
}

void SortCompare::run()
{
	std::cout << "====================================================" << std::endl;
	std::cout << "**		   排序算法比较                   **" << std::endl;
	std::cout << "====================================================" << std::endl;
	std::cout << "**		   1 --- 冒泡排序		  **" << std::endl;
	std::cout << "**		   2 --- 选择排序		  **" << std::endl;
	std::cout << "**		   3 --- 直接插入排序		  **" << std::endl;
	std::cout << "**		   4 --- 希尔排序		  **" << std::endl;
	std::cout << "**		   5 --- 快速排序		  **" << std::endl;
	std::cout << "**		   6 --- 堆排序		  	  **" << std::endl;	
	std::cout << "**		   7 --- 归并排序		  **" << std::endl;
	std::cout << "**		   8 --- 基数排序		  **" << std::endl;
	std::cout << "**		   9 --- 退出程序		  **" << std::endl;
	std::cout << "====================================================" << std::endl;
	std::cout << std::endl;
	std::cout << "请输入要产生的随机数的个数：";
	int randArraySize=0,sortCode=0;
	std::cin >> randArraySize;
	_generateRandNumberArray(randArraySize);
	std::cout << std::endl;

	std::cout << "请选择排序算法：   ";
	std::cin >> sortCode;
	while (sortCode != 9)
	{
		_sortAnalyse(sortCode);
		std::cout << std::endl;
		std::cout << "请选择排序算法：   ";
		std::cin >> sortCode;
	}
	return;
}


void SortCompare::_generateRandNumberArray(int randArraySize)
{
	
	//异常处理，检查生成随机数的数字
	while (randArraySize <= 1)
	{
		std::cerr << "错误：请重新输入一个大于1的正整数（测试样例为100,1000,10000,100000）:  ";
		std::cin >> randArraySize;
	}

	srand(time(NULL));
	for (int i = 0; i < randArraySize; i++)
	{
		_randArray.push_back(rand());
	}

	_arraySize = randArraySize;


}




void SortCompare::_sortAnalyse(int sortCode)
{
	if (_arraySize <= 1||_randArray.size()<=1)
	{
		std::cerr << "错误，请检查数组是否含有两个及以上数据" << std::endl;
	}

	static long long counter = 0;
	string sortName;
	clock_t beginTime = 0, endTime = 0;

	
	counter = 0;
	int* sortArray = new int[_arraySize];
	for (int i = 0; i < _arraySize; i++)
	{
		sortArray[i] = _randArray[i];
	}

	beginTime = clock();
	switch (sortCode)
	{
		case 1:sortName = "冒泡"; _bubbleSort(sortArray, counter); break;
		case 2:sortName = "选择"; _selectSort(sortArray, counter); break;
		case 3:sortName = "直接插入"; _directInsertSort(sortArray, counter); break;
		case 4:sortName = "希尔"; _shellSort(sortArray, counter); break;
		case 5:sortName = "快速"; _quickSort(sortArray, counter); break;
		case 6:sortName = "堆"; _heapSort(sortArray, counter); break;
		case 7:sortName = "归并"; _mergeSort(sortArray,counter); break;
		case 8:sortName = "基数"; _radixSort(sortArray, counter); break;
		default:std::cout<<"无效操作码，请重新输入"<<std::endl;break;
	}
	endTime = clock();

	std::cout << sortName<< "排序所用时间： ";
	std::cout << endTime-beginTime << " ms"<<std::endl;
	std::cout << sortName << "排序"<<((sortCode==7)?"比较":"交换")<<"次数： ";
	std::cout <<  counter << std::endl;


}


///////////////////////////////////////////////////////冒泡排序///////////////////////////////////////////////////////////////
void SortCompare::_bubbleSort(int* ivec, long long& counter)
{
	bool hasExchange = false;
	for (int i=_arraySize-1; i >0; i--)
	{
		hasExchange = false;
		for (int j = 0; j < i; j++)
		{
			
			if (less(ivec[j + 1], ivec[j]))
			{
				
				std::swap(ivec[j], ivec[j + 1]);
				++counter;
				hasExchange = true;
			}
		}
		if (!hasExchange)
		{
			return;
		}
	}
}


///////////////////////////////////////////////////////选择排序///////////////////////////////////////////////////////////////
void SortCompare::_selectSort(int* ivec, long long& counter)
{
	int vecSize = _arraySize;
	for (int i = 0; i < vecSize; i++)
	{
		int minIndex = i;
		for (int j = i + 1; j < vecSize; j++)
		{
			
			if (less(ivec[j], ivec[minIndex]))
			{
				minIndex = j;
			}
		}
		std::swap(ivec[i], ivec[minIndex]);
		++counter;
	}
}

///////////////////////////////////////////////////////插入排序///////////////////////////////////////////////////////////////
void SortCompare::_directInsertSort(int* ivec, long long& counter)
{
	int vecSize = _arraySize;
	for (int i = 1; i < vecSize; i++)
	{
		for (int j = i; j > 0 && less(ivec[j], ivec[j - 1]); j--)
		{
			
			std::swap(ivec[j], ivec[j - 1]);
			++counter;
		}
	}
}

///////////////////////////////////////////////////////希尔排序///////////////////////////////////////////////////////////////
void SortCompare::_shellSort(int* ivec, long long& counter)
{
	int vecSize = _arraySize;
	int groupSize = 1;
	while (groupSize < vecSize / 3) groupSize = 3 * groupSize + 1;
	while (groupSize >= 1)	
	{
		for (int i = groupSize; i < vecSize; i++)
		{
			for (int j = i; j >= groupSize && (less(ivec[j], ivec[j - groupSize])); j -= groupSize)
				std::swap(ivec[j], ivec[j - groupSize]);
			++counter;
		}
		groupSize = groupSize / 3;
	}
}

///////////////////////////////////////////////////////堆排序///////////////////////////////////////////////////////////////
void SortCompare::_heapSort(int* ivec, long long& counter)
{
	int length = _arraySize;
	int lastIndex = length - 1;
	for (int cur = lastIndex/ 2; cur >= 0; --cur)
		_maintainHeap(ivec, cur, lastIndex,counter);
	for (int end = lastIndex; end >= 0; --end)
	{
		std::swap(ivec[0], ivec[end]);
		++counter;
		_maintainHeap(ivec, 0, end - 1, counter);
	}
}

void SortCompare::_maintainHeap(int* ivec, int top, int end, long long& counter)
{
	int topData = ivec[top];
	for (int i = top * 2 + 1; i <= end; i = i * 2 + 1)
	{
		if (i + 1 <= end && ivec[i] < ivec[i + 1])
		{
			++i;
		}

		if (ivec[i] < topData)
		{
			break;
		}
		std::swap(ivec[top], ivec[i]);
		top = i;
		++counter;
		
	}
}

///////////////////////////////////////////////////////归并排序///////////////////////////////////////////////////////////////
void SortCompare::_mergeSort(int* ivec, long long& counter)
{
	int* tmpArr = new int[_arraySize];
	for (int i = 0; i < _arraySize; i++)
	{
		tmpArr[i] = ivec[i];
	}

	_mSort(ivec, tmpArr, 0, _arraySize - 1, counter);
}

void SortCompare::_mSort(int* ivec, int* tmp,int low, int high, long long& counter)
{
	if (high <= low) return;

	int mid = low + (high - low) / 2;
	_mSort(ivec,tmp, low, mid,counter);
	_mSort(ivec,tmp, mid + 1, high, counter);
	_merge(ivec,tmp, low, mid, high, counter);
}

void SortCompare::_merge(int* ivec, int* tmp,int low, int mid, int high, long long &counter)
{
	int i = low, j = mid + 1;
	int t= 0;
	while (i <= mid && j <= high)
	{
		if (ivec[i] < ivec[j])
		{
			tmp[t++] = ivec[i++];
			counter++;
		}
		else
		{
			tmp[t++] = ivec[j++];
			counter++;
		}
	}

	while (i <= mid)  {	tmp[t++] = ivec[i++]; counter++; }
	while (j <= high) { tmp[t++] = ivec[j++]; counter++; }

	t = 0;
	while (low <= high) {ivec[low++] = tmp[t++]; counter++;}
}

///////////////////////////////////////////////////////快速排序///////////////////////////////////////////////////////////////
void SortCompare::_quickSort(int* ivec, long long& counter)
{
	_qSort(ivec, 0, _arraySize - 1, counter);
}

void SortCompare::_qSort(int* ivec, int low, int high, long long& counter)
{
	if (low >= high) return;

	int cut = _qPartition(ivec, low, high, counter);
	_qSort(ivec, low, cut - 1, counter);
	_qSort(ivec, cut+ 1, high,counter);
}
int SortCompare::_qPartition(int* ivec, int low, int high, long long& counter)
{
	//数组切分:ivec[low...i-1],ivec[i],ivec[i+1...high]

	int i = low, j = high + 1;//理解为begin()和end()对应索引

	int x = ivec[low];
	while (true)
	{
		//扫描左右，检查是否结束并交换元素
		while (ivec[++i] < x) if (i == high) break;
		while (x < ivec[--j]) if (j == low) break;
		if (i >= j) break;

		std::swap(ivec[i], ivec[j]);
		++counter;
	}
	std::swap(ivec[low], ivec[j]);
	++counter;
	return j;
}

///////////////////////////////////////////////////////基数排序///////////////////////////////////////////////////////////////
void SortCompare::_radixSort(int* ivec, long long& counter)
{
	//找到最大数
	int length = _arraySize;
	int maxElement = ivec[0];

	for (int i = 1; i < length; i++)
	{
		if (ivec[i] > maxElement)
		{
			maxElement = ivec[i];
		}
	}
	
	int i = 0;

	for (int bit = 1; maxElement / bit > 0; bit *= 10)
	{
		int bucket[10] = { 0 };
		int* sortArr = new int[length];
		for (i = 0; i < length; i++)
		{
			int bitValue = (ivec[i] / bit) % 10;
			bucket[bitValue]++;
		}
		for ( i = 1; i < 10; i++)
		{
			bucket[i] += bucket[i - 1];
		}

		for (i = length - 1; i >= 0; i--)
		{
			int bitValue = (ivec[i] / bit) % 10;
			sortArr[bucket[bitValue] - 1] = ivec[i];
			bucket[bitValue]--;
		}

		for (int i = 0; i < length; i++)
		{
			ivec[i] = sortArr[i];
		}
		delete[]sortArr;

	}
	
}


///////////////////////////////////////////////////////主函数///////////////////////////////////////////////////////////////


int main()
{
	SortCompare testClass;
	testClass.run();
}
