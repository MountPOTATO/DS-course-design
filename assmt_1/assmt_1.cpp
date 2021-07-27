#include "assmt_1.h"

/****************************************************************************
* FileName     :assmt_1.cpp
*
* @Description :StudentNode,StudentList类中成员函数的定义
*
* @Editor      :MountPotato
*
* @Date        :2020 09 24
*----------------------------------------------------------------------------
*                            FunctionList
*----------------------------------------------------------------------------
* void StudentNode::inputStudentInfo()
* void StudentNode::printStudentInfo()
* bool StudentNode::operator==(const StudentNode& rhs)
* bool StudentNode::operator!=(const StudentNode& rhs)
*
* void StudentList::inputList();										
* void StudentList::printList()const;									
* void StudentList::runClassProgram();									
* void StudentList::correctStudentInfo(StudentNode* student)
* void StudentList::inputAndInsert();
* void StudentList::inputAndDelete();									
* void StudentList::inputFindAndPrintStudent()const;					
* void StudentList::inputAndModify();									
* StudentNode* StudentList::findFront(int candNumber)const;
* void StudentList::clear();
*----------------------------------------------------------------------------
*
*****************************************************************************/


/************************************************************************
* FunctionName  :void StudentNode::inputStudentInfo
*
* @Description  :依次输入学生的考号，姓名，性别，年龄，考试类别，存储到类中
*
* @Parameter    :None（函数内输入）
*
* @ReturnValue  :None
*
* @Warning      :如果输入错误的、重复的信息，数据依然会储存在该节点中。信息
*				 检查的容错操作程序在链表类StudentList中correctStudentInfo
*				 中，故在inputStudentInfo后应马上运行correctStudentInfo函数
*
* @Editor       : MountPotato
*
*************************************************************************/
inline void StudentNode::inputStudentInfo()
{
	std::cin >> _candidateNumber >> _name >> _gender >> _age >> _examType;
	
}



/************************************************************************
* FunctionName  :void StudentNode::printStudentInfo
*
* @Description  :依次输出学生的考号，姓名，性别，年龄，考试类别
*
* @Parameter    :None（函数内输入）
*
* @ReturnValue  :None
*
* @Warning      :None
*
* @Editor       :MountPotato
*
*************************************************************************/

inline void StudentNode::printStudentInfo()const
{
	std::cout << _candidateNumber << "\t"
		<< _name << "\t" << _gender << "\t"
		<< _age << "\t" << _examType << std::endl;
}


/************************************************************************
* Overload operator :
*	bool StudentNode::operator==(const StudentNode& rhs)
*	bool StudentNode::operator!=(const StudentNode& rhs)
*************************************************************************/

bool StudentNode::operator==(const StudentNode& rhs)
{
	if (_candidateNumber == rhs._candidateNumber
		&& _name == rhs._name
		&& _gender == rhs._gender
		&& _age == rhs._age
		&& _examType == rhs._examType)
	{
		return true;
	}
	else
	{
		return false;
	}

}
bool StudentNode::operator!=(const StudentNode& rhs)
{
	return !(*this == rhs);
}



/************************************************************************
* FunctionName  :void StudentList::inputList
*
* @Description  :类的初始输入程序,输入考生人数并按照考生人数依次输入考生,并在每
*			   	 输入一个考生后检查考生信息格式是否正确,对不正确的进行重输入修正
*
* @Parameter    :None（函数内输入）
*
* @ReturnValue  :None
*
* @Warning      :异常处理：1.考生人数应为正整数
*						  2.若分配内存失败，结束程序并退出
*
* @Editor       :MountPotato
*
*************************************************************************/
void StudentList::inputList()
{
	int initStudentNumber;
	std::cout << "首先建立考生信息系统" << std::endl;
	std::cout << "请输入考生人数" << std::endl;
	std::cin >> initStudentNumber;

	while (initStudentNumber <= 0)
	{
		std::cout << "考生人数应为正整数，请重新输入：";
		std::cin >> initStudentNumber;
	}

	std::cout << "请依次输入考生考号，姓名，性别，年龄及报考类别！" << std::endl;
	
	StudentNode* pLinker = _header;		//用于连接的指针
	for (int i = 0; i < initStudentNumber; i++)
	{
		StudentNode* student = new StudentNode;

		//分配失败，student为空时的异常处理
		if (!student)
		{
			std::cerr << "错误：分配内存失败，将退出输入程序" << std::endl;
			exit(1);
		}
		student->inputStudentInfo();
		correctStudentInfo(student);

		//连接过程
		pLinker->_next = student;
		pLinker = pLinker->_next;
		

		++_length;
		
	}
	
}


/************************************************************************
* FunctionName  :void StudentList::printList
*
* @Description  :打印表列
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

void StudentList::printList()const
{
	StudentNode* pCheck = _header->_next;
	std::cout << "考号" << "    " << "姓名" << "    " << "性别" << "    "
		<< "年龄" << "    " << "报考类别" << std::endl;
	while (pCheck)
	{
		pCheck->printStudentInfo();
		pCheck = pCheck->_next;
	}
}
/************************************************************************
* FunctionName  :void StudentList::runClassProgram
*
* @Description  :类的运行程序:按照io指示输入各种操作的对应指令:1为插入,2为删除
*				 3为查找，4为修改，5为统计，0为取消操作退出程序,并根据输入的指令
*				 进入对应的操作模块
*			
* @Parameter    :None（函数内输入）
*
* @ReturnValue  :None
*
* @Warning      :异常处理：1.对不在0-5内的操作指令,进行提示并要求重新输入
*
* @Editor       : MountPotato
*
*************************************************************************/


void StudentList::runClassProgram()
{
	
	
	std::cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << std::endl;
	while (true)
	{
		//命令代号:1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作
		int commandCode;
		//空一行
		std::cout << std::endl;
		std::cout << "请选择您要进行的操作:";
		std::cin >> commandCode;

		switch (commandCode)
		{
		case 1:
			//进行插入操作 打印表
			inputAndInsert();
			printList();
			break;
		case 2:
			//进行删除操作 打印表
			inputAndDelete();
			printList();
			break;
		case 3:
			//进行查找考号操作,打印查找的学生信息
			inputFindAndPrintStudent();
			break;
		case 4:
			//进行修改操作，打印表
			inputAndModify();
			printList();
			break;
		case 5:
			//统计，打印表
			printList();
			break;
		case 0:
			std::cout << "结束操作，已退出考试报名系统程序，感谢您的使用" << std::endl;
			clear();
			return;
		default:
			std::cout << "无效的操作序号（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << std::endl;
			break;
		}
	}
}



/************************************************************************
* FunctionName  :void StudentList::correctStudentInfo
*
* @Description  :传入所要检查的学生节点参数，检查所输入的学生考号是否重复，性别
*				 输入是否正确，若不正确，提示有误的信息并重新输入，直到学生信息
*				 无误后，退出函数
*
* @Parameter    :StudentNode类指针student，代表所要检查的学生节点
*
* @ReturnValue  :None
*
* @Warning      :异常处理:由于考试类别未给出，且考虑重名的情况，仅对性别，考号进行
*				 纠错，排除考号重复与性别格式有误（不是"男"或"女")的情况
*
* @Editor       :MountPotato
*
*************************************************************************/
void StudentList::correctStudentInfo(StudentNode* student)
{
	if (!student)
	{
		return;
	}
	while (true)
	{
		//指示考号是否正常，性别是否格式正确的布尔变量
		bool rightCandidateNumber = true;
		bool rightGender = true;

		
		//检查性别输入
		if (student->_gender != "男" && student->_gender != "女")
		{
			rightGender = false;
		}

		//遍历链表，检查考号是否重复
		StudentNode* pCheck = _header->_next;
		while (pCheck)
		{
			if (pCheck->_candidateNumber == student->_candidateNumber && *pCheck != *student)
			{
				rightCandidateNumber = false;
				break;
			}
			else
			{
				pCheck = pCheck->_next;
			}
		}

		//错误清算
		if (rightGender && rightCandidateNumber)
		{
			//无误，退出修正函数
			return;
		}
		else
		{
			std::cout << "考生信息有误:";
			if (!rightCandidateNumber)
			{
				std::cout << "考号已被使用  ";
			}
			if (!rightGender)
			{
				std::cout << "性别格式有误（应输入男/女)";
			}
			std::cout << std::endl;
			std::cout << "请重新输入考生信息，依次依次输入考生考号，姓名，性别，年龄及报考类别：" << std::endl;
			student->inputStudentInfo();
		}
	}

}


/************************************************************************
* FunctionName  :void StudentList::inputAndInsert
*
* @Description  :输入插入的位置与学生信息，随后插入链表并打印表显示插入后状态
*
* @Parameter    :None(函数内输入)
*
* @ReturnValue  :None
*
* @Warning      :异常处理:1.对输入有误的考生信息（性别格式有误，考号重复）,提示
*				 错误并要求重新输入直到输入格式正确为止;2.插入的考生位置如为不符
*				 合要求的索引，提示插入位置有误
*
* @Editor       :MountPotato
*
*************************************************************************/
void StudentList::inputAndInsert()
{
	int insertIndex = 0;
	std::cout << "请输入你要插入的考生位置:";
	std::cin >> insertIndex;

	//检查索引,确保正确输入的索引在正确范围内
	while (insertIndex<1 || insertIndex>_length + 1)
	{
		if (_length)
		{
			std::cout << "插入的位置有误，请重新输入一个1到" << _length + 1 << "之间的整数:";
		}
		else
		{
			std::cout << "链表为空，若要插入请输入1:";
		}
		std::cin >> insertIndex;
	}

	StudentNode* newStudent = new StudentNode(), * pCheck = _header;
	std::cout << "请依次输入考生考号，姓名，性别，年龄及报考类别！" << std::endl;
	newStudent->inputStudentInfo();

	correctStudentInfo(newStudent);

	for (int i = 1; i < insertIndex; i++)
	{
		if (!pCheck) break;
		pCheck = pCheck->_next;
	}

	if (!pCheck)
	{
		std::cerr << "错误：索引溢出" << std::endl;
		
	}
	else
	{
		newStudent->_next = pCheck->_next;
		pCheck->_next = newStudent;
		++_length;
	}

}



/************************************************************************
* FunctionName  :StudentNode* StudentList::find
*
* @Description  :输入所要查找的考号，遍历链表，如果找到了与所查找考号相同的学生，
*				 输出该学生信息；反之，输出nullptr
*
* @Parameter    :整型变量candNumber,表示所要查找的考号
*
* @ReturnValue  :StudentNode类指针，如果有对应学生则指向它，反之返回nullptr
*
* @Warning      :None
*
* @Editor       : MountPotato
*
*************************************************************************/
StudentNode* StudentList::findFront(int candNumber)const
{
	StudentNode* pCheckNumber = _header;
	while (pCheckNumber->_next)
	{
		if (pCheckNumber->_next->_candidateNumber == candNumber)
		{
			break;
		}
		pCheckNumber = pCheckNumber->_next;
	}
	return (pCheckNumber) ? pCheckNumber : nullptr;
}


/************************************************************************
* FunctionName  :void StudentList::inputAndDelete
*
* @Description  :输入需要删除的学生考号，从链表中删除
*
* @Parameter    :None
*
* @ReturnValue  :None
*
* @Warning      :异常处理:1.对输入有误的考生信息（性别格式有误，考号重复）,提示
*				 错误并要求重新输入直到输入格式正确为止;2.删除的考生若不存在，
*				 提示考生不存在
*
* @Editor       :MountPotato
*
*************************************************************************/

void StudentList::inputAndDelete()
{

	//删除的目标考号
	int targetCandidateNumber;

	std::cout << "请输入要删除的考生的考号：" << std::endl;
	std::cin >> targetCandidateNumber;

	//找到对应学号的学生节点的前一个节点
	StudentNode* pFindFront = findFront(targetCandidateNumber);
	if (!pFindFront->_next)
	{
		std::cout << "抱歉，您要删除的学生不存在" << std::endl;
	}
	else
	{
		std::cout << "你删除的考生信息是：";

		StudentNode* pDelete = pFindFront->_next;
		pDelete->printStudentInfo();

		pFindFront->_next = pDelete->_next;
		delete pDelete;

		--_length;
	}
}


/************************************************************************
* FunctionName  :void StudentList::inputFindAndPrintStudent
*
* @Description  :输入需要查找的学生序号
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


void StudentList::inputFindAndPrintStudent()const
{
	//查找的目标考号
	int targetCandidateNumber;

	std::cout << "请输入要查找的考生的考号：" << std::endl;
	std::cin >> targetCandidateNumber;

	//找到查找到的
	StudentNode* pFindFront = findFront(targetCandidateNumber);
	if (!pFindFront->_next)
	{
		std::cout << "抱歉，您要查找的学生不存在" << std::endl;
	}
	else
	{
		std::cout << "你查找的考生信息是：";

		pFindFront->_next->printStudentInfo();

	}
}


/************************************************************************
* FunctionName  :void StudentLIst::inputAndModify()
*
* @Description  :输入要修改的学生信息，查找并修改，打表
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

void StudentList::inputAndModify()
{
	//查找的目标考号
	int targetCandidateNumber;

	std::cout << "请输入要修改的考生的考号：" << std::endl;
	std::cin >> targetCandidateNumber;

	//找到查找到的
	StudentNode* pFindFront = findFront(targetCandidateNumber);
	if (!pFindFront->_next)
	{
		std::cout << "抱歉，您要修改的学生不存在" << std::endl;
	}
	else
	{
		std::cout << "请依次输入考生考号，姓名，性别，年龄及报考类别！" << std::endl;

		pFindFront->_next->inputStudentInfo();

		correctStudentInfo(pFindFront->_next);

	}
}



/************************************************************************
* FunctionName  :void StudentList::clear
*
* @Description  :清空链表操作
*
* @Parameter    :None
*
* @ReturnValue  :None
*
* @Warning      :注意,清空后的链表_header为空,长度_length为0
*
* @Editor       :MountPotato
*
*************************************************************************/

void StudentList::clear()
{
	StudentNode* pCheck;
	while (_header->_next)
	{
		pCheck = _header->_next;
		_header->_next = pCheck->_next;
		delete pCheck;
	}
	_length = 0;

}

///////////////////////////////////////////////////////////主函数//////////////////////////////////////////////////////////////

int main(int argc,char* argv[])
{
	StudentList slist;
	slist.inputList();
	slist.printList();
	slist.runClassProgram();
}
