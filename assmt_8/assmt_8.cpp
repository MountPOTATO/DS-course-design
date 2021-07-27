#include "assmt_8.h"


/************************************************************************
* FunctionName  :Graph<Name, Weight>::Graph(int sz)
*
* @Description  :Graph<Name,Weight>的构造函数，传入size
*
* @Parameter    :int sz,表示初始化的点大小（最大存储点数）
*
* @ReturnValue  :None
*
* @Warning      :None
*
* @Editor       : MountPotato
*
*************************************************************************/

template<class Name, class Weight>
Graph<Name, Weight>::Graph(int sz) :
	_maxPointNum(sz),
	_currPointNum(0),
	_currEdgeNum(0)
{
	_pointArr = new Point<Name, Weight>[_maxPointNum];
	//初始化参数：最大点数更新为sz，当前点边数都是0
	assert(_pointArr);
	for (int i = 0; i < _maxPointNum; i++)
	{
		//指针置空防止野指针出现
		_pointArr[i].data = "NONE";
		_pointArr[i].edgeList = nullptr;
	}
}


/************************************************************************
* FunctionName  :Graph<Name, Weight>::~Graph()
*
* @Description  :Graph<Name,Weight>的析构函数
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


template<class Name, class Weight>
Graph<Name, Weight>::~Graph()
{
	//对当前所有的点
	for (int i = 0; i < _currPointNum; i++)
	{
		Edge<Name, Weight>* pTemp = _pointArr[i].edgeList;
		while (pTemp)
		{
			//删除以该点为入度的所有边
			_pointArr[i].edgeList = pTemp->next;
			delete pTemp;
			pTemp = _pointArr[i].edgeList;
		}
	}

	delete[] _pointArr;
}


/************************************************************************
* FunctionName  :int Graph<Name, Weight>::getPointPos(const Name& pointName)
*
* @Description  :查找名字为pointName的点在图中的索引
*
* @Parameter    :const Name& pointName。表示节点的名字
*
* @ReturnValue  :成功，返回索引值；未找到，返回-1
*
* @Warning      :None
*
* @Editor       : MountPotato
*
*************************************************************************/


template<class Name, class Weight>
int Graph<Name, Weight>::getPointPos(const Name& pointName)
{
	for (int i = 0; i < _currPointNum; i++)
	{
		if (_pointArr[i].data == pointName) return i;
	}
	return -1;
}



/************************************************************************
* FunctionName  :Weight Graph<Name, Weight>::getEdgeWeight(int index1, int index2)
*
* @Description  :找到(index1,index2)边的权值
*
* @Parameter    :int index1 表示入点位置，int index2表示出点位置
*
* @ReturnValue  :如果找得到边，返回p->cost当前权值；找不到，返回DBL_MAX、
*				 表示浮点数范围最大值（权值无限大)
*
* @Warning      :None
*
* @Editor       : MountPotato
*
*************************************************************************/


template<class Name, class Weight>
Weight Graph<Name, Weight>::getEdgeWeight(int index1, int index2)
{
	//越界判断
	if (index1 < 0 || index1 >= _maxPointNum)
	{
		return DBL_MAX;
	}
	else
	{
		//初始指针p指向第一个邻接index1点的边
		Edge<Name, Weight>* p = _pointArr[index1].edgeList;
		while (p)
		{
			if (p->destination != index2) p = p->next;
			else break;
		}
		//如p为空返回DBL_MAX，不为空返回p所指向的边的权值
		return p ? p->cost : DBL_MAX;
	}
	return DBL_MAX;
}


/************************************************************************
* FunctionName  :bool Graph<Name, Weight>::insertPoint(const Name& pointName)
*
* @Description  :插入以pointName为值的点
*
* @Parameter    :const Name& pointName表示插入的点的值	
*
* @ReturnValue  :插入成功返回true，如果图已满，返回false
*
* @Warning      :
*
* @Editor       : MountPotato
*
*************************************************************************/


template<class Name, class Weight>
bool Graph<Name, Weight>::insertPoint(const Name& pointName)
{
	if (_currPointNum == _maxPointNum)  return false;
	_pointArr[_currPointNum++].data = pointName;
	return true;
}



/************************************************************************
* FunctionName  :bool Graph<Name, Weight>::insertEdge
*				(int index1, int index2,Weight weight)
*
* @Description  :在index1，index2处插入weight权重边
*
* @Parameter    :int index1,int index2表示要接边的两点，Weight weight为权重
*
* @ReturnValue  :插入成功返回true，不成功返回false
*
* @Warning      :异常处理：1.索引越界，返回false的基础上要求重新输入，具体实现
*				 在系统类run()函数中实现;2.若边已存在，返回false，提示已存在边
*
* @Editor       : MountPotato
*
*************************************************************************/



template<class Name,class Weight>
bool Graph<Name, Weight>::insertEdge(int index1, int index2,Weight weight)
{
	if (index1 < 0 || index1 >= _currPointNum || index2 < 0 || index2 >= _currPointNum)
	{
		cout << "错误：顶点位置越界，请重新输入" << endl;
		return false;
	}
	else
	{
		Edge<Name, Weight>* pInsert, * pFind = _pointArr[index1].edgeList;
		//找到(index1,index2)找得到即返回假
		while (pFind)
		{
			if (pFind->destination == index2)
			{
				cout << "当前需要插入的边已存在，无需重复插入" << endl;
				return false;
			}
			else
			{
				pFind = pFind->next;
			}
		}
		pFind = new Edge<Name, Weight>;
		pInsert = new Edge<Name, Weight>;//准备后续插入
		//index1 插入新边
		pFind->destination = index2;
		pFind->cost = weight;
		//插入头部
		pFind->next = _pointArr[index1].edgeList;	
		_pointArr[index1].edgeList = pFind;

		//index2插入新边
		pInsert->destination = index1;
		pInsert->cost = weight;
		//插入头部
		pInsert->next = _pointArr[index2].edgeList;
		_pointArr[index2].edgeList = pInsert;

		_currEdgeNum++;
	}
}



/************************************************************************
* FunctionName  :bool MinSpanTree<Name, Weight>::insert
					(EdgeNode<Name, Weight>& item)
*
* @Description  :最小生成树插入item边
*
* @Parameter    :EdgeNode<Name, Weight>& item 表示需要插入的边结点
*
* @ReturnValue  : 成功，返回true;已满，返回false
*
* @Warning      :None
*
* @Editor       : MountPotato
*
*************************************************************************/


template<class Name, class Weight>
bool MinSpanTree<Name, Weight>::insert(EdgeNode<Name, Weight>& item)
{
	if (_currNodeSize == _maxNodeSize)
	{
		cout << "最小生成树已满" << endl;
		return false;
	}
	nodeVec[_currNodeSize++] = item;
	return true;
}


/************************************************************************
* FunctionName  :void MinSpanTree<Name, Weight>::print()const
*
* @Description  :打印最小生成树（遍历所有EdgeNode并打印）
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


template<class Name, class Weight>
void MinSpanTree<Name, Weight>::print()const
{
	for (int i = 0; i < _currNodeSize; i++)
	{
		cout << nodeVec[i].head << "-(" << nodeVec[i].cost << ")->" << nodeVec[i].tail << "\t";
	}
}



/************************************************************************
* FunctionName  :void EletricityNetworkSimulator::run()
*
* @Description  :系统类运行程序，根据输入指令执行对应操作:
*				 A --- 创建电网顶点
*				 B --- 添加电网的边
*				 C --- 构造最小生成树 
*				 D --- 显示最小生成树
*				 E --- 退出程序
*
* @Parameter    :None
*
* @ReturnValue  :None(退出函数即完成任务）
*
* @Warning      :None
*
* @Editor       : MountPotato
*
*************************************************************************/


void EletricityNetworkSimulator::run()
{
	
	char order;
	cout << "**           电网造价模拟系统           **" << endl;
	cout << "==========================================" << endl;
	cout << "**           A --- 创建电网顶点         **" << endl;
	cout << "**           B --- 添加电网的边         **" << endl;
	cout << "**           C --- 构造最小生成树       **" << endl;
	cout << "**           D --- 显示最小生成树       **" << endl;
	cout << "**           E --- 退出程序             **" << endl;
	cout << "==========================================" << endl << endl;
	
	
	while (true)
	{
		cout << "请选择操作：";
		cin >> order;
		
		if (order == 'A')
		{
			
			int pointNum;
			cout << "请输入顶点的个数：";
			cin >> pointNum;
			while (pointNum <= 1)
			{
				cout << "输入非法，请重新输入一个大于1的正整数：";
				cin >> pointNum;
			}

			adjList = new Graph<string, double>(pointNum);

			cout << "请依次输入各顶点的名称：";
			string pointName;
			vector<string> pointVec;
			string* nameVec = new string[pointNum];
			while (true)
			{
				bool error = false;
				for (int i = 0; i < pointNum; i++)
				{
					cin >> pointName;
					if (std::find(pointVec.begin(), pointVec.end(), pointName) != pointVec.end())
					{
						
						cout << "错误：输入了两个以上一样的顶点名字，请重新输入各顶点的名称";
						error = true;
						break;
					}
					else
					{
						pointVec.push_back(pointName);
					}
				}
				if (error) {pointVec.clear();continue;}
				else break;
			}

			for (auto& i : pointVec)
			{
				adjList->insertPoint(i);
			}
			cout << "已经建立含" << pointNum << "个顶点的邻接表图" << endl;
			cout << endl;
		}

		else if (order == 'B')
		{
			string name1, name2;
			double weight;
			while (true)
			{
				cout << "请输入两个顶点及边(边权值为负结束操作)：";
				cin >> name1 >> name2 >> weight;
				if (weight < 0)
				{
					break;
				}

				int index1 = adjList->getPointPos(name1);
				int index2 = adjList->getPointPos(name2);
				if (!adjList->insertEdge(index1, index2, weight))
				{
					continue;
				}

			}
			cout << endl;
		}

		else if (order == 'C')
		{
			string start;
			cout << "请输入起始起点" << endl;
			cin >> start;
			while (adjList->getPointPos(start) == -1)
			{
				cout << "您输入的起点并不存在于图中,请重新输入";
				cin >> start;
			}

			prim(start);
			cout << "生成最小生成树" << endl;
			cout << endl;
		}

		else if (order == 'D')
		{
			cout << "最小生成树的顶点及边:" << endl;
			mst->print();
			cout << endl;
		}

		else if (order == 'E')
		{
			break;
		}
		else
		{
			cout<<"输入不合法的操作码（应为A,B,C,D或E)，请重新输入"<<endl;
		}
	}

	cout << "程序已成功退出" << endl;
}


/************************************************************************
* FunctionName  :void EletricityNetworkSimulator::prim(const string& startPoint)
*
* @Description  :系统类输入C时执行的算法操作：生成Prim最小生成树
*
* @Parameter    :const string& startPoint，起点名称
*
* @ReturnValue  :None
*
* @Warning      :None
*
* @Editor       :MountPotato
*
*************************************************************************/


void EletricityNetworkSimulator::prim(const string& startPoint)
{
	int startIndex = adjList->getPointPos(startPoint), pointSum = adjList->getCurrPointNum();
	double* lowcost = new double[pointSum];
	int* nearPoint = new int[pointSum];
	mst->resize(pointSum - 1);
	//初始化lowcost与nearPoint数组
	for (int i = 0; i < pointSum; i++)
	{
		//lowcost[i]为索引i的点到startIndex点的边的权值（无边时为DBL_MAX）
		lowcost[i] = (i == startIndex) ? 0 : adjList->getEdgeWeight(startIndex, i);
		//nearPoint[i]为生成树集合中距离索引i的点最近的点
		nearPoint[i] = (i == startIndex) ? -1 : startIndex;

	}

	EdgeNode<string, double> e;
	for (int i = 1; i < pointSum; i++)
	{
		double minCost = DBL_MAX;
		int newPointIndex = -1, lastIndex = pointSum - 1;
		//对不在集合中的点，查找距离集合中的点权值最小的点并获取该边的权值
		for (int j = 0; j < pointSum; j++)
		{
			if (nearPoint[j] != -1 && lowcost[j] < minCost)
			{
				newPointIndex = j; minCost = lowcost[j];
			}
		}
		if (newPointIndex != -1)
		{
			//若找得到
			string name1 = adjList->getPointData(nearPoint[newPointIndex]);
			string name2 = adjList->getPointData(newPointIndex);
			e.head = name1;
			e.tail = name2;
			e.cost = minCost;
			//边加入最小生成树
			mst->insert(e);
			//置目前的点为-1，加入集合
			nearPoint[newPointIndex] = -1;
			for (int j = 0; j < pointSum; j++)
			{
				if (nearPoint[j] != -1 && adjList->getEdgeWeight(newPointIndex, j) < lowcost[j])
				{
					//更新lowcost的最小权值与nearPoint邻近点
					lowcost[j] = adjList->getEdgeWeight(newPointIndex, j);
					nearPoint[j] = newPointIndex;
				}
			}
		}
	}
	
}

/**************************************主函数*********************************************/
int main()
{
	EletricityNetworkSimulator el;
	el.run();
}