#ifndef __5_CKX_H__
#define __5_CKX_H__

#include <iostream>


/****************************************************************************
* FileName     :assmt_5.h
*
* @Description :项目5的问题解决:使用链表队列解决排队问题
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

class LinkQueue;

/************************************************************************
* ClassName  :CustomerNode
*
* @Description  :表示顾客节点的链表节点类，实现包括构造函数，判定奇偶数等操作

* @Warning      :None
*
* @Editor       : MountPotato
*
*************************************************************************/

class CustomerNode {
	friend class LinkQueue;
public:
	//构造函数
	CustomerNode() :_number(-1), _next(nullptr) {}
	CustomerNode(const int& initNumber) :_number(initNumber), _next(nullptr) {}
	CustomerNode(CustomerNode* node) 
	{
		if (node)
		{
			_number = node->_number;
			_next = nullptr;
		}
	}

	//输出函数
	void output(std::ostream& os = std::cout) { os << _number; }

	//判断当前节点的数值是奇数还是偶数
	bool isOdd()const { return _number % 2 == 1; }
	bool isEven()const { return _number % 2 == 0; }
private:
	//数值与后继节点成员
	int _number;
	CustomerNode* _next;

};


/************************************************************************
* ClassName  :LinkQueue
*
* @Description  :表示由CustomerNode类构成的链表队列，实现包括信息获取，出入队列
*				 清空，打印的操作

* @Warning      :None
*
* @Editor       : MountPotato
*
*************************************************************************/


class LinkQueue {
public:
	//构造与析构函数
	LinkQueue() :_front(new CustomerNode(-1)), _rear(_front),_size(0) {}
	~LinkQueue() { clear(); }

	//信息获取
	size_t size()const { return _size; }
	bool empty()const { return size() == 0; }
	//队列单元操作
	void push( CustomerNode* node);
	void pop();
	CustomerNode* top()const { return _front->_next; }

	//队列操作
	void clear();	
	void printQueue();


private:
	//头尾结点指针，方便出栈入栈
	CustomerNode* _front, * _rear;

	
	size_t _size;
};

/************************************************************************
* ClassName  :BackWindow
*
* @Description  :实现任务功能的主类，封装两个链表队列表示窗口A、B，并留出
*				 处理顺序队列代表最终结果

* @Warning      :None
*
* @Editor       : MountPotato
*
*************************************************************************/
class BankWindow {
public:
	//默认构造与析构函数
	BankWindow() = default;
	~BankWindow() { _windowA.clear(); _windowB.clear(); }

	//任务运行函数
	void run();

	void inputAndDivide();		//输入，根据顾客编号分类
	void generateOrderQueue();	//生成顾客顺序队列

private:
	LinkQueue _windowA;			//窗口A队列
	LinkQueue _windowB;			//窗口A队列

	LinkQueue _orderQueue;		//最终生成的队列
};

#endif //__5_CKX_H__