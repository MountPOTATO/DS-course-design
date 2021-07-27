#include "assmt_7.h"

/****************************************************************************
* FileName     :assmt_7.cpp
*
* @Description :最小堆，以及运行类的成员函数定义
*
* @Editor      :MountPotato
*
* @Date        :2020 10 18
*----------------------------------------------------------------------------
*                            FunctionList
*----------------------------------------------------------------------------
* PriorQueue<T>
*inline void PriorQueue<T>::_swap(Index i, Index j)
*void PriorQueue<T>::push(T& data)
*void PriorQueue<T>::_floating(Number startNumber)
*void PriorQueue<T>::pop()
*void PriorQueue<T>::_sink(Number startNumber)
*
*HuffmanTreeWPLCalculator
*HuffmanTreeWPLCalculator::HuffmanTreeWPLCalculator(vector<double> woodVec)
*double HuffmanTreeWPLCalculator::getWeightedPathLength()const
*----------------------------------------------------------------------------
*
*****************************************************************************/

/************************************************************************
* FunctionName  :void PriorQueue<T>::_swap(Index i, Index j)
*
* @Description  :优先队列类的内联函数,交换_dataVec[i]与_daaVec[j]的值
*
* @Parameter    :Index i, Index j,表示两个交换数所在的数组索引
*
* @ReturnValue  :None
*
* @Warning      :合法的i ，j应大于等于0且小于_size
*
* @Editor       : MountPotato
*
*************************************************************************/

template<class T>
inline void PriorQueue<T>::_swap(Index i, Index j)
{
	if (i >= 0&&i<_size && j >= 0&&j<_size)
	{
		T temp = _dataVec[i];
		_dataVec[i] = _dataVec[j];
		_dataVec[j] = temp;
	}
}


/************************************************************************
* FunctionName  :void PriorQueue<T>::push(int data)
*
* @Description  :优先队列推入数据，并使用上浮函数调整堆
*
* @Parameter    :int data表示数据
*
* @ReturnValue  :None
*
* @Warning      :None
*
* @Editor       : MountPotato
*
*************************************************************************/

template<class T>
void PriorQueue<T>::push(T& data)
{
	

	_dataVec[_size++] = data;

	_floating(_size);
}


/************************************************************************
* FunctionName  :void PriorQueue<T>::_floating(Number startNumber)
*
* @Description  :从起始位置开始，将起始位置处的数据上浮放入堆中
*
* @Parameter    :int startNumber,表示开始的位置
*
* @ReturnValue  :None
*
* @Warning      :None
*
* @Editor       : MountPotato
*
*************************************************************************/


template<class T>
void PriorQueue<T>::_floating(Number startNumber)
{
	if (_size <= 1)
	{
		return;
	}
	for (int i = startNumber; i > 0; i /= 2)
	{
		if (_dataVec[i - 1] < _dataVec[i / 2 - 1])
		{
			_swap(i - 1, i / 2 - 1);
		}
		else
		{
			break;
		}
	}
	return;
}



/************************************************************************
* FunctionName  :void PriorQueue<T>::pop()
*
* @Description  :删除堆顶数据，交换堆顶数据与末尾数据，并从堆顶开始下沉
*
* @Parameter    :None
*
* @ReturnValue  :None
*
* @Warning      :None
*
* @Editor       : MountPotato
*
*************************************************************************/


template<class T>
void PriorQueue<T>::pop()
{
	if (empty())
	{
		return;
	}
	_dataVec[0] = _dataVec[_size - 1];
	_sink(1);
	_size--;
	return;

}


/************************************************************************
* FunctionName  :void PriorQueue<T>::_sink(Number startNumber)
*
* @Description  :从起始位置startNumber开始将数据下沉至堆底
*
* @Parameter    :int startNumber,表示开始的位置
*
* @ReturnValue  :None
*
* @Warning      :None
*
* @Editor       : MountPotato
*
*************************************************************************/


template<class T>
void PriorQueue<T>::_sink(Number startNumber)
{
	int i = startNumber;

	while (i * 2 <= _size)
	{
		int j = 2 * i;
		if (j <= _size && _dataVec[j - 1] > _dataVec[j])	//左节点与右节点比较
		{
			j++;
		}
		if (_dataVec[i - 1] <= _dataVec[j - 1])
		{
			break;
		}
		else
		{
			_swap(i - 1, j - 1);
		}
		i = j;
	}
	
}



/************************************************************************
* FunctionName  :HuffmanTreeWPLCalculator::HuffmanTreeWPLCalculator(vector<double> woodVec)
*
* @Description  :输入一个浮点数组woodVec，并用里面的数据初始化最小堆(double)
*
* @Parameter    :vector<double> woodVec，表示用于初始化堆的数据
*
* @Warning      :None
*
* @Editor       : MountPotato
*
*************************************************************************/

HuffmanTreeWPLCalculator::HuffmanTreeWPLCalculator(vector<double> woodVec)
{
	_WPL = 0;
	PriorQueue<double> priorQueue(woodVec.size());

	for (int i = 0; i < woodVec.size(); i++)
	{
		priorQueue.push(woodVec[i]);
	}

	int operateTimes = woodVec.size() - 1;
	for (int i = 0; i < operateTimes; i++)
	{
		double first = priorQueue.top();
		priorQueue.pop();
		double second = priorQueue.top();
		priorQueue.pop();
		double parent = first + second;
		
		priorQueue.push(parent);

		_WPL += parent;
	}

}




int main(int argc, char* argv[])
{
	
	int woodNumber;
	std::cin >> woodNumber;
	vector<double> woodVec;
	while(woodNumber<=0)
	{
		std::cout<<"错误：请重新输入一个正整数"<<std::endl;
		std::cin >> woodNumber;
	}

	for (int i = 0; i < woodNumber; i++)
	{
		double woodLength;
		std::cin >> woodLength;
		woodVec.push_back(woodLength);
	}

	HuffmanTreeWPLCalculator hftree(woodVec);
	std::cout << hftree.getWeightedPathLength() << std::endl;

}


