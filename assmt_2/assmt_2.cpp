#include "assmt_2.h"


/****************************************************************************
* FileName     :assmt_2.cpp
*
* @Description :结点类Node,简单链表类SimpleList,程序运行类FindIntersection成员
*				函数的声明定义
*
* @Editor      :MountPotato
*
* @Date        :2020 09 26
*----------------------------------------------------------------------------
*                              FunctionList
*----------------------------------------------------------------------------
* void SimpleList::inputList();
* void SimpleList::printList()const;
* inline void SimpleList::addNodeToTail(Node* node)
* inline void SimpleList::deleteFirstNodeWithElement()
* 
* 
* void FindIntersection::input()
* SimpleList* FindIntersection::generateIntersectionList()
*----------------------------------------------------------------------------
*
*****************************************************************************/


/************************************************************************
* FunctionName  :void SimpleList::inputList()
*
* @Description  :输入数据生成链表，以-1结尾
*
* @Parameter    :None
*
* @ReturnValue  :None
*
* @Warning      :异常处理：1.内存分配错误时，退出程序
*						  2.如果不按题目要求乱序输入，本函数会进行自动排序
*							确保输出的链表是非降序链表
*
* @Editor       : MountPotato
*
*************************************************************************/

template<class T>
void SimpleList<T>::inputList()
{
	T nodeData;
	bool hasInserted = false;	/*表示该节点是以插入而非尾后连接的形式添加的，说明输入是乱序*/
	while (true)
	{
		std::cin >> nodeData;
		hasInserted = false;
		
		if (nodeData == -1)
		{
			break;
		}
		else
		{
			Node<T>* newNode = new Node<T>(nodeData), * pLinker = _pTop;

			if (!newNode)
			{
				std::cerr << "错误：分配内存失败，将退出程序" << std::endl;
				exit(1);
			}

			while (pLinker->next)
			{
				/*遍历链表,正序情况下pLinker会遍历到最后一个元素，以执行尾后连接*/
				if (pLinker->next->data < nodeData)
				{
					pLinker = pLinker->next;					
				}
				/*当出现需要插入的情况（乱序）时，进行链表的插入操作*/
				else
				{
					newNode->next = pLinker->next;
					pLinker->next = newNode;
					/*标识插入的情况*/
					hasInserted = true;

					break;
				}
			}			
			/*正常情况下，如果节点是依次正序输入，则执行尾后连接程序*/
			if (!hasInserted)
			{
				addNodeToTail(newNode);								
			}

		}
	}
}


/************************************************************************
* FunctionName  :void SimpleList::printList()const
*
* @Description  :输出链表，若为空输出NULL
*
* @Parameter    :None
*
* @ReturnValue  :None
*
* @Warning      :None
*
* @Editor       :MountPotato
*
*************************************************************************/

template<class T>
void SimpleList<T>::printList()const
{
	if (!_pTop->next)
	{
		std::cout << "NULL" << std::endl;
	}
	else {
		Node<T>* pTraversal = _pTop->next;
		while (pTraversal != _tail)
		{
			std::cout << pTraversal->data << " ";
			pTraversal = pTraversal->next;
		}
		std::cout << pTraversal->data << std::endl;
	}
}


/************************************************************************
* FunctionName  :void SimpleList::addNodeToTail
*
* @Description  :链表的添加元素操作，在本方案中链表只从尾部插入，故设立尾结点指针
*
* @Parameter    :Node类指针node 表示需要插入的链表
*
* @ReturnValue  :None
*
* @Warning      :None
*
* @Editor       : MountPotato
*
*************************************************************************/

template<class T>
inline void SimpleList<T>::addNodeToTail(Node<T>* node)
{
	_tail->next = node;
	_tail = node;
	_tail->next = nullptr;
	
}


/************************************************************************
* FunctionName  :SimpleList::deleteFirstNodeWithElement
*
* @Description  :删除第一个有实值的元素（即附加头结点的下一个链表单元)
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
inline void SimpleList<T>::deleteFirstNodeWithElement()
{
	Node<T>* pTemp = _pTop->next;
	_pTop->next = pTemp->next;
	delete pTemp;
	
}


/************************************************************************
* FunctionName  :void FindIntersection::input
*
* @Description  :对FindIntersection类的两个成员链表的输入
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
void FindIntersection<T>::input()
{
	_list1->inputList();
	_list2->inputList();
}


/************************************************************************
* FunctionName  :SimpleList* FindIntersection::generateIntersectionList
*
* @Description  :根据两个链表逐步生成交集链表的同时逐步清空原来的两个链表
*
* @Parameter    :None
*
* @ReturnValue  :SimpleList类指针，表示生成的交集链表
*
* @Warning      :None
*
* @Editor       :MountPotato
*
*************************************************************************/
template<class T>
SimpleList<T>* FindIntersection<T>::generateIntersectionList()
{
	SimpleList<T>* list3 = new SimpleList<T>();
	
	Node<T>* pCheck1 = _list1->_pTop->next,* pCheck2 = _list2->_pTop->next;

	/*遍历两个链表，pCheck1和pCheck2为遍历链表使用的指针*/
	while (pCheck1 && pCheck2)
	{
		/*对当前值较小的链表单元，推进遍历指针并删除该单元*/
		if (pCheck1->data < pCheck2->data)
		{
			pCheck1 = pCheck1->next;
			_list1->deleteFirstNodeWithElement();
		}
		else if (pCheck1->data > pCheck2->data)
		{
			pCheck2 = pCheck2->next;
			_list2->deleteFirstNodeWithElement();
		}
		else
		{
			/*当pCheck1和pCheck2的值相等时，即取到交集元素*/
			/*此时如果交集链表中的尾部没有该元素，此时才插入元素*/
			if (pCheck1->data != list3->_tail->data)
			{
				Node<T>* pLinker = new Node<T>(pCheck1->data);
				if (!pLinker)
				{
					std::cerr << "错误：分配内存失败，将退出程序" << std::endl;
					exit(1);
				}
				list3->addNodeToTail(pLinker);
				
			}
			
			/*推进遍历链表并删除之前的单元*/
			pCheck1 = pCheck1->next;
			_list1->deleteFirstNodeWithElement();
			
			pCheck2 = pCheck2->next;
			_list2->deleteFirstNodeWithElement();
		
		}
	}

	/*遍历结束，生成交集链表，原来的两个链表清空*/
	list3->_tail->next = nullptr;
	
	return list3;
}


int main()
{
	FindIntersection<int> testClass;
	testClass.input();
	SimpleList<int>* plist = testClass.generateIntersectionList();
	plist->printList();
}

