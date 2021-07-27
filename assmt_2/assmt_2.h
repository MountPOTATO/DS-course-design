#ifndef __2_CKX_H__
#define __2_CKX_H__

//尾节点
//链表铰接



/****************************************************************************
* FileName     :assmt_2.h
*
* @Description :结点类Node,简单链表类SimpleList,程序运行类FindIntersection的定义
*
* @Editor      :MountPotato
*
* @Date        :2020 09 26
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

template<class T>
class FindIntersection;



/************************************************************************
* structName	: Node
*
* @Description  : 简单链表的结点类，包含默认构造函数和含值的构造函数
*
* @Warning      : None
*
* @Editor       : MountPotato
*
*************************************************************************/

template<class T>
struct Node{
	
	Node() :next(nullptr) {}					//构造函数
	Node(const T& nodeData) :data(nodeData) {}	//值初始化构造函数

	
	T data;										//数据成员

	Node<T>* next;									//链接指针
};

/************************************************************************
* className	: SimpleList
*
* @Description  : 简单链表类，包含头指针和尾指针，除输入输出外，应题目要求设计了
*				  结点连接尾指针，删除第一个元素的操作
*
* @Warning      : None
*
* @Editor       : MountPotato
*
*************************************************************************/

template<class T>
class SimpleList {
	friend class FindIntersection<T>;
public:
	
	SimpleList() :_pTop(new Node<T>(-99999)), _tail(_pTop) {}
	

	
	void inputList();			//输入元素构建连，包含自动排序程序
	void printList()const;			//输出链表

	
	inline void addNodeToTail(Node<T>* node);
	inline void deleteFirstNodeWithElement();
	
private:
	Node<T>* _pTop;			//附加头结点
	Node<T>* _tail;			//尾指针，指向尾元素
};




/************************************************************************
* className	: FindIntersection
*
* @Description  : 内含两个链表，输入时分别输入两个链表，存储在对象中，使用
*				  generateIntersectionList函数生成交集链表，同时删除原链表
* 
* @Warning      : None
*
* @Editor       : MountPotato
*
*************************************************************************/

template<class T>
class FindIntersection {
public:
	
	FindIntersection() :_list1(new SimpleList<T>), _list2(new SimpleList<T>) {}//初始构造函数

	
	void input();								//输入
	SimpleList<T>* generateIntersectionList();  //生成交集链表

private:
	SimpleList<T>* _list1;
	SimpleList<T>* _list2;
};

#endif //__2_CKX_H__