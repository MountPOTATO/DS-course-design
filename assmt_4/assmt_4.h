#ifndef __4_CKX_H__
#define __4_CKX_H__



/****************************************************************************
* FileName     : assmt_4.h
*
* @Description : 对模板链表节点结构体LinkNode,模板链表栈类LinkStack,以及功能实现
*				 类Calculator的声明
*
* @Editor      : MountPotato
*
* @Date        : 2020.10.4
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
#include <assert.h>
#include <vector>
#include <sstream>
#include <cmath>
#include <cfloat>

using std::string;
using std::vector;


/************************************************************************
* StructName  : LinkNode<T>
*
* @Description  : 模板链表结点结构体，包含T类型数据以及下一个结点的指针类
*				  支持默认构造与值初始化构造
*
* @Warning      : None
*
* @Editor       : MountPotato
*
*************************************************************************/

template <class T>
struct LinkNode {
	//数据成员
	T data;
	LinkNode<T>* nextNode;

	//构造函数
	LinkNode() :nextNode(nullptr) {}
	LinkNode(const T& value) :data(value), nextNode(nullptr) {}

};


/************************************************************************
* ClassName  : LinkStack<T>
*
* @Description  : 模板链表栈类，包含与实现任务基本功能相关的操作如push,pop,clear
*				  等操作
* 
* @Warning      : None
*
* @Editor       : MountPotato
*
*************************************************************************/

template <class T>
class LinkStack {
public:
	//构造与析构函数
	LinkStack():_pTop(nullptr){}
	~LinkStack() { clear(); };

	//内容获取
	bool empty()const { return stackSize == 0; }
	LinkNode<T>* top() { return _pTop; }


	//链表单元操作
	void push(const T& x);	
	void pop();

	//链表操作
	void clear();

private:
	LinkNode<T>* _pTop;
	size_t stackSize;
};



/************************************************************************
* ClassName  : Calculator
*
* @Description  : 计算器类，为程序任务运行主要类，包含double类链表栈与char类链
*				  表栈各一个，分别存放操作符与数字。支持加减乘除乘方取余，括号，
*				  以及简单的浮点运算
* 
* @Warning      : None
*
* @Editor       : MountPotato
*
*************************************************************************/

class Calculator {
public:
	//运行程序
	void run();


private:
	LinkStack<double> operandStack;		//操作数栈，存放表达式中的式子
	LinkStack<char> operatorStack;		//操作符栈，存放操作符并按优先级出栈入栈



	int prior(const char ch)const;		//获取各个操作符的优先级

	bool inputInfixExpression(string& infix);	//输入中缀表达式并初步检查合法性

	bool processInfixExpression(const string& infixExpression);	//将每个数字分解入栈


	bool processOperator(const string& infixExpression, int index); //处理双目运算符以及括号等

	bool process2Operands();	//从数字栈顶弹出两个数字，符号栈顶弹出一个符号，计算，放回数字栈

	double getAnswer(double a, char b, double c)const;	

	bool calculateResult();		//对分解后的两个栈进行计算得到最终结果
};


bool isExpressionOperator(const char& c);
bool isUnary(const string& s, int index);

#endif //__4_CKX_H__