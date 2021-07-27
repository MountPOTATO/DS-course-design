#ifndef __10_CKX_H__
#define __10_CKX_H__

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <string>
#include <functional>

using std::string;
using std::vector;



/****************************************************************************
* FileName     :assmt_10.h
*
* @Description :
*
* @Editor      :MountPotato
*
* @Date        :
*----------------------------------------------------------------------------
*                            ChangeHistory
*----------------------------------------------------------------------------
* @Date         |
*
* @Version      |
*
* @Editor       |
*
* @Description  |
*
*----------------------------------------------------------------------------
*
*****************************************************************************/


/************************************************************************
* ClassName  :SortCompare
*
* @Description  :排序程序管理类，生成一定个数的随机数并进行相应排序
*
* @Warning      :None
*
* @Editor       : MountPotato
*
*************************************************************************/


class SortCompare {
public:
	//构造与析构函数
	SortCompare() = default;
	~SortCompare() { _randArray.clear(); }

	//运行程序
	void run();
private:
	//存放随机数的指针，动态内存分配
	vector<int> _randArray;
	int _arraySize;
	//生成随机数数组
	void _generateRandNumberArray(int randArraySize);
	//根据对应的排序代码执行对应排序
	void _sortAnalyse(int sortCode);	
	//冒泡排序
	void _bubbleSort(int* ivec,long long& counter);
	//选择排序
	void _selectSort(int* ivec, long long& counter);
	//直接插入排序
	void _directInsertSort(int* ivec, long long& counter);
	//希尔排序
	void _shellSort(int* ivec, long long& counter);
	//快速排序
	void _quickSort(int* ivec, long long& counter);
	void _qSort(int* ivec, int low, int high, long long& counter);
	int _qPartition(int* ivec, int low, int high, long long& counter);
	//堆排序
	void _heapSort(int* ivec, long long& counter);
	void _maintainHeap(int* ivec, int top, int end, long long& counter);
	//归并排序
	void _mergeSort(int* ivec, long long& counter);
	void _mSort(int* ivec, int* tmp,int lo,int hi, long long &counter);
	void _merge(int* ivec, int* tmp,int lo,int mid,int hi, long long& counter);
	//基数排序
	void _radixSort(int* ivec, long long& counter);

};



#endif //__10_CKX_H__