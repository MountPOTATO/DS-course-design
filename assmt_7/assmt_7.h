#ifndef __7_CKX_H__
#define __7_CKX_H__

/****************************************************************************
* FileName     :assmt_7.h
*
* @Description :优先队列类的声明与 内置一个优先队列的哈夫曼树WPL计算器类的声明
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

#include <iostream>
#include <vector>
#include <assert.h>

typedef int Index;
typedef int Number;

using std::vector;


/************************************************************************
* ClassName  : PriorQueue
*
* @Description  :优先队列（最小堆）
*
* @Warning      :None
*
* @Editor       : MountPotato
*
*************************************************************************/


//最小堆实现的优先队列

template<class T>
class PriorQueue {
public:
	//构造与析构函数
	PriorQueue() :_size(0) {}
	PriorQueue(int capacity) :_dataVec(new T[capacity+2]),_size(0) {}
	~PriorQueue() { delete[] _dataVec; }


	//元素操作
	void push(T& data);	//将元素推入优先队列
	void pop();				//退出栈顶元素
	inline bool empty()const { return _size == 0; }	//查空
	inline T top()const { assert(_size > 0); return _dataVec[0]; }	//获取栈顶元素


private:
	T* _dataVec;	//动态数组
	int _size;	//当前堆中元素数量

	//交换_dataVec[i]与_daaVec[j]的值
	inline void _swap(Index i, Index j);

	//下沉
	void _sink(Number startNumber);
	//上浮
	void _floating(Number startNumber);
};

/************************************************************************
* ClassName  : HuffmanTreeWPLCalculator
*
* @Description  :哈夫曼树WPL计算器
*
* @Warning      :None
*
* @Editor       : MountPotato
*
*************************************************************************/


class HuffmanTreeWPLCalculator {
public:
	//构造
	HuffmanTreeWPLCalculator(vector<double> woodVec);

	//获得WPL
	double getWeightedPathLength()const { return _WPL; }
	
private:
	double _WPL;
};



#endif