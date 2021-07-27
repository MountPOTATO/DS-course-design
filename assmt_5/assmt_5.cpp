#include "assmt_5.h"

/****************************************************************************
* FileName     :assmt_5.cpp
*
* @Description :节点单元，队列，窗口系统的成员函数声明
*
* @Editor      :MountPotato
*
* @Date        :2020 10 19
*----------------------------------------------------------------------------
*                              FunctionList
*----------------------------------------------------------------------------
* void LinkQueue::push(CustomerNode* node)
* void LinkQueue::pop()
* void LinkQueue::clear()
* void LinkQueue::printQueue()
*
*
* void BankWindow::inputAndDivide()
* void BankWindow::generateOrderQueue()
* void BankWindow::run()
*----------------------------------------------------------------------------
*
*****************************************************************************/

/************************************************************************
* FunctionName  :void LinkQueue::push(CustomerNode* node)
*
* @Description  :链表队列的入栈（从尾结点进入)
*
* @Parameter    :结点类CustomerNode* node表示需要插入的结点
*
* @ReturnValue  :None
*
* @Warning      :None
*
* @Editor       : MountPotato
*
*************************************************************************/

void LinkQueue::push(CustomerNode* node)
{
	if (node && !node->_next)
	{
		_rear->_next = node;
		_rear = node;
		_rear->_next = nullptr;

		++_size;
	}
}

/************************************************************************
* FunctionName  :void LinkQueue::pop()
*
* @Description  :链表队列的出队列程序（头结点）
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

void LinkQueue::pop()
{
	if (_front->_next)
	{
		CustomerNode* pDelete = _front->_next;
		_front->_next = pDelete->_next;
		delete pDelete;

		--_size;
	}
}


/************************************************************************
* FunctionName  :void LinkQueue::clear()
*
* @Description  :链表队列的清空函数，用于析构
*
* @Parameter    :None
*
* @ReturnValue  :None
*
* @Warning      :清空后链表队列对象回到初始状态
*
* @Editor       : MountPotato
*
*************************************************************************/


void LinkQueue::clear()
{
	while (_front->_next)
	{
		pop();
	}
	_rear = _front;
	_size = 0;
}


/************************************************************************
* FunctionName  :void LinkQueue::printQueue()
*
* @Description  :链表队列的打印程序
*
* @Parameter    :None
*
* @ReturnValue  :None
*
* @Warning      :NOne
*
* @Editor       : MountPotato
*
*************************************************************************/


void LinkQueue::printQueue()
{
	CustomerNode* pTraversal = _front;
	while (pTraversal->_next)
	{
		pTraversal->_next->output();
		std::cout << " ";
		pTraversal = pTraversal->_next;
	}
	
	std::cout << std::endl;
}


/************************************************************************
* FunctionName  :void BankWindow::inputAndDivide()
*
* @Description  :输入顾客人数后，依次输入每个顾客的编号，并根据顾客编号的
*				 奇偶性分到不同的窗口队列
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


void BankWindow::inputAndDivide()
{
	int numberOfCustomer;
	std::cout << "请输入顾客总数N(N<1000):";
	std::cin >> numberOfCustomer;
	while (numberOfCustomer <= 0)
	{
		std::cout << "请重新输入客户数量，要求为正整数:";
		std::cin >> numberOfCustomer;
	}

	std::cout << "请依次输入" << numberOfCustomer << "位顾客的编号。编号为奇数的顾客需要去A窗口办理业务，编号为偶数的顾客需要去B窗口办理业务。数字间以空格分开）:" << std::endl;	
	for (int i = 0; i < numberOfCustomer; i++)
	{
		int mark;
		
		std::cin >> mark;

		CustomerNode* customer = new CustomerNode(mark);
		if (!customer)
		{
			std::cerr << "错误，内存分配失败，将退出程序" << std::endl;
			exit(1);
		}


		if (customer->isOdd())
		{
			_windowA.push(customer);
		}
		else
		{
			_windowB.push(customer);
		}
	}
}


/************************************************************************
* FunctionName  :void BankWindow::generateOrderQueue()
*
* @Description  :根据两个窗口队列，生成顾客顺序队列（即为结果)
*
* @Parameter    :None
*
* @ReturnValue  :None
*
* @Warning      :需要在调用inputAndDivide()后使用
*
* @Editor       : MountPotato
*
*************************************************************************/


void BankWindow::generateOrderQueue()
{
	while (!_windowA.empty() || !_windowB.empty())
	{
		if (_windowA.top())
		{
			CustomerNode* customer1 = new CustomerNode(_windowA.top());
			_orderQueue.push(customer1);
			_windowA.pop();
		}

		if (_windowA.top())
		{
			CustomerNode* customer2 = new CustomerNode(_windowA.top());
			_orderQueue.push(customer2);
			_windowA.pop();
		}
		if (_windowB.top())
		{
			CustomerNode* customer3 = new CustomerNode(_windowB.top());
			_orderQueue.push(customer3);
			_windowB.pop();
		}
	}
}


/************************************************************************
* FunctionName  :void BankWindow::run()
*
* @Description  :运行程序。包括：输入，生成，打印三个步骤，封装整个任务执行过程
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


void BankWindow::run()
{
	inputAndDivide();
	generateOrderQueue();
	std::cout << "顾客业务完成的顺序为：" << std::endl;
	_orderQueue.printQueue();
}



int main()
{
	BankWindow bank;
	bank.run();
}