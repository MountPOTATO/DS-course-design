#ifndef __8_CKX__
#define __8_CKX__

/****************************************************************************
* FileName     :assmt_8.h
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
#include <cfloat>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>


using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

template<class Name, class Weight>
class MinSpanTree;
class EletricityNetworkSimulator;

/************************************************************************
* ClassName  :	template<class Name, class Weight>  struct Edge
*
* @Description  :表示领接表形式图的边，Name为点的数据类型
*
* @Warning      :None
*
* @Editor       : MountPotato
*
*************************************************************************/

template<class Name, class Weight>
struct Edge {
	int destination;			//目的边结点的定义
	Weight cost;				//权值
	Edge<Name, Weight>* next;	//下一条边


	Edge() :next(nullptr) {}
	Edge(int n, Weight weight) :destination(n), cost(weight), next(nullptr) {}

	bool operator !=(const Edge<Name, Weight>& rhs)const { return destination != rhs.destination; }
	bool operator ==(const Edge<Name, Weight>& rhs)const { return destination == rhs.destination; }
};

/************************************************************************
* ClassName  :	template<class Name, class Weight>  struct Point
*
* @Description  :表示领接表形式图的点，Name为点的数据类型，包括Edge类型指针域
*				 表示邻接的边
*
* @Warning      :None
*
* @Editor       : MountPotato
*
*************************************************************************/

template<class Name, class Weight>
struct Point {
	Name data;							//名字域
	Edge<Name, Weight>* edgeList;		//边的头指针域
};

/************************************************************************
* ClassName  :	template<class Name, class Weight>  struct Graph
*
* @Description  :领接表图类，实现了添加点，添加边的操作
*				 
* @Warning      :None
*
* @Editor       : MountPotato
*
*************************************************************************/

template<class Name, class Weight>
class Graph {
public:
	//构造与析构函数
	Graph(int sz);
	~Graph();

	//信息获取:点，边权重
	Name getPointData(int i) { return (i >= 0 && i <= _currPointNum) ? _pointArr[i].data : "NONE"; }
	Weight getEdgeWeight(int v1, int v2);
	//int getFirstNeigbor(int i);
	//int getNextNeigbor(int v, int w);
	int getPointPos(const Name& pointData);
	int getCurrPointNum()const { return _currPointNum; }

	//插入删除点边操作
	bool insertPoint(const Name& pointData);
	//bool removePoint(int v);
	bool insertEdge(int v1, int v2, Weight const);
	//bool removeEdge(int v1, int v2);

private:
	Point<Name, Weight>* _pointArr;		//点的指针域（动态数组）
	int _maxPointNum;
	int _currEdgeNum;
	int _currPointNum;

};

/************************************************************************
* ClassName  :	template<class Name, class Weight> class EdgeNode
*
* @Description  :最小生成树的边结点
*
* @Warning      :None
*
* @Editor       : MountPotato
*
*************************************************************************/


template<class Name, class Weight>
class EdgeNode {
	friend class MinSpanTree<Name,Weight>;
	friend class EletricityNetworkSimulator;
	
private:
	Name tail, head;
	Weight cost;
};

/************************************************************************
* ClassName  :	template<class Name, class Weight> class MinSpanTree
*
* @Description  :最小生成树类
*
* @Warning      :None
*
* @Editor       : MountPotato
*
*************************************************************************/

template<class Name,class Weight>
class MinSpanTree {
public:
	MinSpanTree() :_maxNodeSize(0), _currNodeSize(0), nodeVec(nullptr) {}
	MinSpanTree(int capacity) :
		_maxNodeSize(capacity), _currNodeSize(0), nodeVec(new EdgeNode<Name,Weight>[_maxNodeSize]){ assert(nodeVec); }

	void resize(int newcap)
	{
		_maxNodeSize=newcap;
		_currNodeSize = 0;
		delete[] nodeVec; 
		nodeVec = new EdgeNode<Name, Weight>[newcap];
	}

	void print()const;

	bool insert(EdgeNode<Name, Weight>& item);

private:
	int _maxNodeSize;
	int _currNodeSize;

	EdgeNode<Name, Weight>* nodeVec;
};

/************************************************************************
* ClassName  :	EletricityNetworkSimulator
*
* @Description  :电网模拟系统类
*
* @Warning      :None
*
* @Editor       : MountPotato
*
*************************************************************************/

class EletricityNetworkSimulator {
public:
	EletricityNetworkSimulator() :adjList(nullptr),mst(new MinSpanTree<string, double>()) {}
	
	void prim(const string& startPoint);
	void run();

private:
	Graph<string, double>* adjList;	//领接表图类
	MinSpanTree<string,double>* mst; //最小生成树
};






#endif //__8_CKX__