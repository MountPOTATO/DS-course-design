#ifndef __6_CKX_H__
#define __6_CKX_H__


/****************************************************************************
* FileName     :assmt_6.h
*
* @Description :
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

#include <memory>
#include <iostream>
#include <string>
#include <assert.h>
#include <vector>
using std::string;
using std::vector;





template<class T>
struct TreeNode {
	//数据成员
	T data;
	//左子节点，下一个兄弟节点和前一个兄弟节点,兄弟节点间形成循环双向链表连接
	TreeNode<T>* firstChild, * nextSibling, * preSibling;	
	//记录孩子的数量，在FamilyTree中更新
	int childNumber;


	//方法成员:构造函数
	TreeNode(T value = 0, TreeNode<T>* fc = nullptr) :
		data(value), firstChild(fc), nextSibling(nullptr),preSibling(nullptr),childNumber(0) {}

	//遍历所有孩子并打印
	void printChildrenName()const;

	
};



class FamilyTree {
public:
	//构造函数析构函数
	FamilyTree() :_root(nullptr), _current(nullptr) {}
	~FamilyTree();
	//根节点初始化
	void createRoot(string name) { _root = _current = new TreeNode<string>(name); assert(_root); }

	//类的运行
	void systemRun();

	//可视
	void printFamilyTree(TreeNode<string>* subRoot)const;  //以subRoot为根节点打印树


private:
	//成员：根节点与当前节点
	TreeNode<string>* _root;
	TreeNode<string>* _current;

	//设置方法：
	inline bool setCurrentAsRoot();	//设置当前节点为子节点，使用于所有的查找函数中

	//运行子办法
	void initFamilyTreeWithAncestor();	//用ancestorName初始化家谱树
	void A_updateFamilyTree();			//操作A：完善家谱树
	void B_addFamilyMember();			//操作B: 添加家庭成员
	void C_dismissFamilySubTree();		//操作C: 解散局部家庭
	void D_changePersonName();			//操作D: 修改成员名字

	//查找办法:当前节点的第一个子节点与最后一个子节点
	TreeNode<string>* currentFirstChild()const { return _current->firstChild; }
	TreeNode<string>* currentLastChild()const { return _current->firstChild->preSibling; }


	//_current节点的操作：添加孩子，删除孩子（所有子孙）
	bool currentAddChildren(vector<string>& childVec);
	void currentDeleteChildren(TreeNode<string>* pTempRoot);

	//查找并更新当前节点的操作
	bool findCurrentFirstChild();								//查找当前节点的长子节点并更新当前节点为长子节点
	bool findCurrentNextSibling();								//查找当前节点的下一个兄弟节点并更新当前节点为下一个兄弟节点
	bool findPerson(string name);								//查找特定名字的家庭成员
	bool findPerson(TreeNode<string>* pTempRoot, string name);	//以pTempRoot为根节点查找家庭成员
};







#endif //__6_CKX_H__