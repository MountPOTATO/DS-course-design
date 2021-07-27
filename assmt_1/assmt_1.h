#ifndef __1_CKX_H__
#define __1_CKX_H__


/****************************************************************************
* FileName     :assmt_1.h
*
* @Description :考试报名系统的制作:类的定义
*
* @Editor      :MountPotato
*
* @Date        :2020 09 22
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

using std::string;


class StudentList;	//链表类前向声明



/************************************************************************
* className		: StudentNode
*
* @Description  : 考试系统链表的结点类
*
* @Warning      : None
*
* @Editor       : MountPotato
*
*************************************************************************/


class StudentNode {

	friend class StudentList;

public:
	
	//构造，析构函数
	StudentNode() :_next(nullptr) {}
	~StudentNode() = default;

	
	inline void inputStudentInfo();						//学生信息的操作：输入(修改),输出
	inline void printStudentInfo()const;

	
	bool operator==(const StudentNode& rhs);			//重载运算符:==,!=
	bool operator!=(const StudentNode& rhs);

private:
	int _candidateNumber;	//考号
	string _name;			//名字
	string _gender;			//性别
	int _age;				//年龄
	string _examType;		//考试类别

	//链表单元
	StudentNode* _next;	
};


/************************************************************************
* className		: StudentList
*
* @Description  : 考试系统链表的主体链表类
*
* @Warning      : None
*
* @Editor       : MountPotato
*
*************************************************************************/

class StudentList {
public:

	/*类运行程序*/
	void inputList();										//初始构造链表
	void printList()const;									//打印链表内容
	void runClassProgram();									//执行输入指令的操作

//异常处理
	void correctStudentInfo(StudentNode* student);			//对StudentNode类指针所指的student

//构造析构函数
	StudentList() :_header(new StudentNode()), _length(0) {}
	~StudentList() { clear(); }

	//链表操作输入指令
	void inputAndInsert();									//输入学生信息，插入链表
	void inputAndDelete();									//输入学生信息，从链表中删除
	void inputFindAndPrintStudent()const;					//输入学生信息，从链表中查找，并打印学生信息
	void inputAndModify();									//输入学生信息，从链表中查找并修改

	//链表单元层面上的操作
	StudentNode* findFront(int candNumber)const;			//根据考号查找，返回对应考号学生节点的前一个节点（用于删除、查找、修改）
	

	//链表层面操作
	void clear();											//清空，释放内存，在程序结束时使用



private:
	StudentNode* _header;	//附加的头结点
	int _length;			//链表存储的StudentNode个数
};


#endif //__1_CKX_H__

