#include "assmt_6.h"

template<class T>
void TreeNode<T>::printChildrenName()const
{
	if (firstChild)
	{
		TreeNode<T>* pTemp = firstChild;
		for (int i = 0; i < childNumber; i++)
		{
			std::cout << pTemp->data << " ";
			pTemp = pTemp->nextSibling;
		}
		std::cout << std::endl;
	}
	else
	{
		std::cout << "没有孩子" << std::endl;
	}
}

FamilyTree::~FamilyTree()
{
	currentDeleteChildren(_root);
	delete _root; 
	_root = nullptr; 
	_current = nullptr;
}

void FamilyTree::initFamilyTreeWithAncestor()
{
	string ancestorName;
	std::cout << "首先建立一个家谱" << std::endl;
	std::cout << "请输入祖先的姓名：";
	std::cin >> ancestorName;
	createRoot(ancestorName);
	std::cout << "此家谱的祖先是：" << ancestorName << std::endl;
}


bool FamilyTree::findCurrentFirstChild()
{
	if (_current && _current->firstChild)
	{
		_current = _current->firstChild;
		return true;
	}
	else
	{
		_current = nullptr;
		return false;
	}
}

bool FamilyTree::findCurrentNextSibling()
{
	if (_current && _current->nextSibling)
	{
		_current = _current->nextSibling;
		return true;
	}
	else
	{
		_current = nullptr;
		return false;
	}
}

bool FamilyTree::currentAddChildren(vector<string>& childrenVec)
{
	if (!_current)
	{
		return false;
	}
	//决定遍历时的起始索引：如果current没有孩子，从0开始，有孩子时从1开始
	int startIndex = (_current->firstChild) ? 0 : 1;

	//current开始没有孩子时，用childrenVec[0]为它添加第一个孩子，此时该孩子的nextSibling与preSibling就是自身
	if (!_current->firstChild&&!childrenVec.empty())
	{
		TreeNode<string>* newFirstChild = new TreeNode<string>(childrenVec.at(0));
		newFirstChild->nextSibling = newFirstChild->preSibling = newFirstChild;
		_current->firstChild = newFirstChild;
	}

	//若current开始已经有孩子了，则从childrenVec[0]为它添加第一个孩子;
	//若current开始已经有孩子了，则从childrenVec[1]为它添加第一个孩子;
	for (int i = startIndex; i < childrenVec.size(); i++)
	{
		TreeNode<string>* newChild = new TreeNode<string>(childrenVec.at(i));
		assert(newChild);
		//直接通过循环链表回退得到当前节点的最后一个子节点，添加在家谱树尾部，并维护双向链表的完整性
		TreeNode<string>* pOriginLast = currentLastChild();
		pOriginLast->nextSibling = newChild;
		newChild->preSibling = pOriginLast;
		
		currentFirstChild()->preSibling = newChild;
		newChild->nextSibling = currentFirstChild();

	}

	//更新current的孩子数目
	_current->childNumber += childrenVec.size();

	return true;
}


bool FamilyTree::findPerson(string name)
{
	if (!_root)
	{
		std::cout << "家谱为空" << std::endl;
		return false;
	}

	else
	{
		return findPerson(_root, name);
	}
}

bool FamilyTree::findPerson(TreeNode<string>* pTempRoot, string name)
{
	bool personFinded = false;
	//找到节点，更新当前节点为所找到的结点
	if (pTempRoot->data == name)
	{	
		personFinded = true;
		_current = pTempRoot;
	}
	else
	{
		TreeNode<string>* pTemp = pTempRoot->firstChild;
		//遍历，循环终止条件为：搜索完所有的子节点，或者对某个子节点搜索时personFinded=true
		int counter = 0;
		while (pTemp && !(personFinded = findPerson(pTemp, name))&&counter!=pTempRoot->childNumber)
		{
			pTemp = pTemp->nextSibling;
			counter++;
		}
		
	}

	return personFinded;

}

void FamilyTree::currentDeleteChildren(TreeNode<string>* pTempRoot)
{
	if (!pTempRoot||!pTempRoot->firstChild)
	{
		return;
	}
	//定位到最后一个子节点
	TreeNode<string>* pRear = pTempRoot->firstChild->preSibling;
	
	for (int i = 0; i < pTempRoot->childNumber-1; i++)
	{
		//从后往前遍历，对每个子节点递归调用删除函数
		pTempRoot->firstChild->preSibling = pRear->preSibling;
		currentDeleteChildren(pRear);
		delete pRear;
		pRear = nullptr;
		pRear = pTempRoot->firstChild->preSibling; 
	}
	//对最后一个子节点的处理:删除，置父节点的孩子数为0
	pTempRoot->firstChild->preSibling = pRear->preSibling;
	currentDeleteChildren(pRear);
	delete pTempRoot->firstChild;
	pTempRoot->firstChild = nullptr;

	pTempRoot->childNumber = 0;
}


void FamilyTree::A_updateFamilyTree()
{
	string parentName, childName;
	std::cout << "请输入要建立家庭的人的姓名：";
	std::cin >> parentName;

	if (!findPerson(parentName))
	{
		std::cout << "目前家谱中找不到该成员" << std::endl;
		return;
	}

	int childNumber;
	std::cout << "请输入" << parentName << "的儿女个数：";
	std::cin >> childNumber;

	while (childNumber <= 0)
	{
		std::cout << "需输入正整数，请重新输入:";
		std::cin >> childNumber;
	}

	std::cout << "请依次输入" << parentName << "的儿女的姓名：";
	vector<string> childrenVec;
	for (int i = 0; i < childNumber; i++)
	{
		std::cin >> childName;
		childrenVec.push_back(childName);
	}

	
	currentAddChildren(childrenVec);
	std::cout << parentName << "的第一代子孙是：";
	_current->printChildrenName();
	return;
}

void FamilyTree::B_addFamilyMember()
{
	string parentName,childName;
	std::cout << "请输入要添加儿子（或女儿）的人的姓名：";
	std::cin >> parentName;

	if (!findPerson(parentName))
	{
		std::cout << "目前家谱中找不到该成员" << std::endl;
		return;
	}

	std::cout << "请输入" << parentName << "新添加的儿子（或女儿）的姓名：";

	vector<string> childVec;
	std::cin >> childName;
	childVec.push_back(childName);
	currentAddChildren(childVec);

	std::cout << parentName << "的第一代子孙是：";
	_current->printChildrenName();
	return;
}

void FamilyTree::C_dismissFamilySubTree()
{
	string parentName;
	std::cout << "请输入要解散的家庭的人的姓名：";
	
	std::cin >> parentName;
	if (!findPerson(parentName))
	{
		std::cout << "目前家谱中找不到该成员" << std::endl;
		return;
	}

	std::cout << "要解散家庭的人是：" << parentName<<std::endl;
	std::cout << parentName << "的第一代子孙是：";
	_current->printChildrenName();

	currentDeleteChildren(_current);
	return;
}


void FamilyTree::D_changePersonName()
{
	string personName, newName;
	std::cout << "请输入要更改姓名的人的目前姓名：";
	std::cin >> personName;

	if (!findPerson(personName))
	{
		std::cout << "目前家谱中找不到该成员" << std::endl;
		return;
	}

	std::cout << "请输入更改后的姓名：";
	std::cin >> newName;

	_current->data = newName;
	std::cout << personName << "已更名为" << _current->data << std::endl;
	return;


}

inline bool FamilyTree::setCurrentAsRoot()
{
	if (_root)
	{
		_current = _root;
		return true;
	}
	else
	{
		_current = nullptr;
		return false;
	}
}

void FamilyTree::printFamilyTree(TreeNode<string>* subRoot)const
{	
	//节点为空，返回
	if (!subRoot)
	{
		return;
	}
	//节点不为空：以“父节点(...所有子节点...)的格式打印树”
	std::cout << subRoot->data;
	if (TreeNode<string>* p=subRoot->firstChild)
	{
		std::cout << " ( ";
		for (int i = 0; i < subRoot->childNumber; i++)
		{
			printFamilyTree(p);
			std::cout << " ";
			p = p->nextSibling;	//遍历
		}
		std::cout << ") ";
	}
}

void FamilyTree::systemRun()
{
	std::cout << "====================================================" << std::endl;
	std::cout << "**		    家谱管理系统                  **" << std::endl;
	std::cout << "====================================================" << std::endl;
	std::cout << "**		 请选择要执行的操作	          **" << std::endl;
	std::cout << "**		   A --- 完善家谱		  **" << std::endl;
	std::cout << "**		   B --- 添加家庭成员		  **" << std::endl;
	std::cout << "**		   C --- 解散局部家庭	          **" << std::endl;
	std::cout << "**		   D --- 更改家庭成员姓名	  **" << std::endl;
	std::cout << "**		   E --- 退出程序		  **" << std::endl;
	std::cout << "====================================================" << std::endl;
	std::cout << std::endl;

	initFamilyTreeWithAncestor();
	while (true)
	{
		std::cout << std::endl;
		std::cout << "请选择需要执行的操作：";
		char operateCode;

		std::cin >> operateCode;
		switch (operateCode)
		{
			case 'A':A_updateFamilyTree(); break;
			case 'B':B_addFamilyMember(); break;
			case 'C':C_dismissFamilySubTree(); break;
			case 'D':D_changePersonName(); break;
			case 'E':std::cout << "程序已退出" << std::endl; return;
			default:std::cout << "无效的操作码，请重新输入" << std::endl; break;
		}

		std::cout << "家谱树简图：";
		printFamilyTree(_root);
		std::cout << std::endl;
	}
}

int main(int argc, char* argv[])
{
	FamilyTree fmlTree;
	fmlTree.systemRun();
	return 0;
}



