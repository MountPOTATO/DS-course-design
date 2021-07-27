
#include <iostream>
#include <vector>
#include <assert.h>
#include <numeric>


/****************************************************************************
* FileName     :assmt_3.h
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


//默认的宏定义char
#define START 'S'
#define ROUTE 'X'
#define END 'E'

const int directionX[4] = { -1,0,1,0 };
const int directionY[4] = { 0,-1,0,1 };

using std::vector;

typedef std::pair<int, int> point;



/************************************************************************
* StructName  :Point
*
* @Description  : DFS表示二维坐标的结构体,内含有
*
* @Warning      : 默认构造的情况下x=-1,y=-1
*				  方向指示为0,1,2,3分别代表DFS的四个方向,超过3后无效
*
* @Editor       : MountPotato
*
*************************************************************************/


struct Point {
	Point() :x(-1), y(-1), direction(0) {}							//默认构造函数
	Point(int a, int b) :x(a), y(b), direction(0) {}				//值初始化构造函数
	Point(const Point& pt) :x(pt.x), y(pt.y), direction(0) {}		//复制构造函数

	bool operator==(const Point& rhs) { return x == rhs.x && y == rhs.y; }	//重载==
	friend std::ostream& operator<<(std::ostream& os, const Point& pt)		//重载<<
	{
		os << "<" << pt.x << " " << pt.y << ">";
		return os;
	}

	//坐标数组
	int x; int y;

	//方向
	int direction;
};

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
	LinkStack() = default;
	~LinkStack() { clear(); };

	//内容获取
	bool empty()const { return stackSize == 0; }
	T getTopData() { return _pTop->data; }
	LinkNode<T>* getTop() { return _pTop; }

	//链表单元操作
	void push(const T& x);
	void pop();
	void printFromTop()const;
	size_t getSize()const{return stackSize;}

	//链表操作
	void clear();

private:
	//栈顶指针
	LinkNode<T>* _pTop;
	//元素个数
	int stackSize;
};


/************************************************************************
* ClassName  : MazeSolver
*
* @Description  : 迷宫管理类，包含解决迷宫路径的非递归DFS方法以及一些必要的数据
*				  成员，方法包括：输入迷宫，打印迷宫，dfs解决迷宫并输出路径
*
* @Warning      : None
*
* @Editor       : MountPotato
*
*************************************************************************/


class MazeSolver {
public:
	//构造函数与析构函数
	MazeSolver() :_mazeMap(nullptr), _currentRow(0), _currentColumn(0), _startCoord(-1, -1), _endCoord(-1, -1) {}
	~MazeSolver();

	//输入迷宫
	void inputMaze();
	//展示迷宫
	void showMaze()const;

	//从start到end使用非递归方法解决dfs问题
	void dfsSolveMaze(Point start, Point end);

	//程序运行程序
	void run();

private:
	char** _mazeMap;			//表示迷宫的二维动态指针
	bool** _markMap;			//表示迷宫回溯标记的二维动态指针,可走时为true，不可走时为false
	int _currentRow;			//当前迷宫的行数，为空时设为-1
	int _currentColumn;			//当前迷宫的列数，为空时设为-1

	Point _startCoord;			//起始坐标，为空时设为(-1,-1)
	Point _endCoord;			//终止坐标，为空时设为(-1,-1)

	LinkStack<Point> _dfsStack;	//dfs栈，节点为Point类型
};




/****************************************************************************
* FileName     :3_1951724_陈垲昕.cpp
*
* @Description :坐标信息类Point,结点类LinkNode,链表栈类LinkStack,程序运行类'
*				MazeSolver成员函数的声明定义
*
* @Editor      :MountPotato
*
* @Date        :2020 10 18
*----------------------------------------------------------------------------
*                              FunctionList
*----------------------------------------------------------------------------
* void LinkStack<T>::push(const T& x)
* void LinkStack<T>::pop()
* void LinkStack<T>::clear()
* void LinkStack<T>::printFromTop()const
*
*
* void MazeSolver::inputMaze()
* SimpleList* FindIntersection::generateIntersectionList()
*----------------------------------------------------------------------------
*
*****************************************************************************/

/************************************************************************
* FunctionName  :void LinkStack<T>::push(const T& x)
*
* @Description  :入栈操作（输入栈值，链表栈顶插入元素为x的结点
*
* @Parameter    :const T& x 表要插入的值
*
* @ReturnValue  :None
*
* @Warning      :None
*
* @Editor       : MountPotato
*
*************************************************************************/


template <class T>
void LinkStack<T>::push(const T& x)
{
	LinkNode<T>* newNode = new LinkNode<T>(x);
	assert(newNode);
	if (_pTop!=nullptr)
	{
		newNode->nextNode = _pTop;
		_pTop = newNode;
	}
	else
	{
		_pTop = newNode;
	}
	
	++stackSize;
}


/************************************************************************
* FunctionName  :void LinkStack<T>::pop()
*
* @Description  :出栈操作
*
* @Parameter    :None
*
* @ReturnValue  :None
*
* @Warning      :当栈为空时，pop()操作直接退出
*
* @Editor       : MountPotato
*
*************************************************************************/


template <class T>
void LinkStack<T>::pop()
{
	if (!_pTop)
	{
		return;
	}
	LinkNode<T>* pDelete = _pTop;
	_pTop = _pTop->nextNode;

	delete pDelete;
	--stackSize;
}


/************************************************************************
* FunctionName  :void LinkStack<T>::clear()
*
* @Description  :清空栈，用于析构
*
* @Parameter    :None
*
* @ReturnValue  :NOne
*
* @Warning      :None
*
* @Editor       : MountPotato
*
*************************************************************************/


template<class T>
void LinkStack<T>::clear()
{
	LinkNode<T>* pDelete;
	while (_pTop)
	{
		pDelete = _pTop;
		_pTop = _pTop->nextNode;
		delete pDelete;
	}
	stackSize = 0;
}


/************************************************************************
* FunctionName  :void LinkStack<T>::printFromTop()const
*
* @Description  :从栈顶到栈底的元素打印，间隔符为"->"
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
void LinkStack<T>::printFromTop()const
{
	LinkNode<T>* temp = _pTop;
	
	int sz=getSize();
	for(int i=0;i<sz;i++)
	{
		std::cout << temp->data;
		if (i!=sz-1)
		{
			temp = temp->nextNode;
			std::cout << "->";
		}
	}
}


/************************************************************************
* FunctionName  :void MazeSolver::inputMaze()
*
* @Description  :输入迷宫
*
* @Parameter    : None（函数内输入）
*
* @ReturnValue  : None
*
* @Warning      :进行了异常检查:1.迷宫行列数合法性检测，2.迷宫内容合法性检测
*
* @Editor       : MountPotato
*
*************************************************************************/


void MazeSolver::inputMaze()
{
	std::cout << "请输入迷宫的行数与列数:" << std::endl;
	int row, column;

	std::cin >> row >> column;

	//行数合法性检测
	while (row <= 0 || column <= 0)
	{
		if (row <= 0)  std::cout << "行数";
		if (column <= 0)  std::cout << "列数";
		std::cout << "不能小于1，请重新输入两个正整数:";
		std::cin >> row >> column;
	}

	//通过合法性检测后，初始化MazeSolver数据成员
	//记录当前row和column，并根据row和column动态分配两个指针
	_currentRow = row;
	_currentColumn = column;
	_mazeMap = new char* [_currentRow+1]; 
	_markMap = new bool* [_currentRow+1];


	for (int i = 0; i < _currentColumn; i++)
	{
		_mazeMap[i] = new char[_currentColumn+1];
		_markMap[i] = new bool[_currentColumn+1];
	}

	
	while (true)
	{
		//迷宫输入
		int startCount = 0, endCount = 0;
		std::cout << "请输入迷宫(" << START << "为起点," << END << "为终点," << ROUTE << "为通路,其余为墙):" << std::endl;
		for (int i = 0; i < _currentRow; i++)
		{
			for (int j = 0; j < _currentColumn; j++)
			{
				std::cin >> _mazeMap[i][j];
				//当_mazeMap[i][j]为START，标记为起点；为END，标记未终点；为ROUTE，标记为路径
				switch (_mazeMap[i][j]) {
					case START:_startCoord.x = i; _startCoord.y = j;  _markMap[i][j] = true; ++startCount; break;
					case END:_endCoord.x = i; _endCoord.y = j; _markMap[i][j] = true; ++endCount; break;
					case ROUTE:_markMap[i][j] = true; break;
					default:_markMap[i][j] = false; break;
				}
			}
		}
		//起点与终点个数合法性检查
		if (startCount!=1||endCount!=1)
		{
			std::cout << "错误：输入了含有" << startCount << "个起点和含有" << endCount << "个终点的迷宫" << std::endl;
			std::cout << "请重新输入含有1个起点" << START << "与1个终点" << END << "的迷宫" << std::endl;
			std::cout << std::endl;
		}
		else
		{
			break;
		}
	}

}


/************************************************************************
* FunctionName  :void MazeSolver::showMaze()const
*
* @Description  :打印迷宫地图
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


void MazeSolver::showMaze()const
{
	if (!_mazeMap||_currentRow<=0||_currentColumn<=0)
	{
		std::cout << "没有创建迷宫地图" << std::endl;
		return;
	}

	std::cout << "此迷宫的图样:" << std::endl;
	std::cout << '\t';
	for (int i = 0; i < _currentColumn; i++)
	{
		std::cout << i << "列" << '\t';
	}
	std::cout<<std::endl;

	for (int i = 0; i < _currentRow; i++)
	{
		std::cout << i  << "行" << '\t';
		for (int j = 0; j < _currentColumn; j++)
		{
			std::cout << _mazeMap[i][j] << '\t';
		}
		std::cout << std::endl;
	}
}


/************************************************************************
* FunctionName  : void MazeSolver::dfsSolveMaze(Point start,Point end)
*
* @Description  : 根据已有的地图，根据起点和终点，生成迷宫的一条路径
*
* @Parameter    : Point start 和 Point end 表示起点和终点
*
* @ReturnValue  : None
*
* @Warning      : None
*
* @Editor       : MountPotato
*
*************************************************************************/

void MazeSolver::dfsSolveMaze(Point start,Point end)
{
	//由于打印栈是从栈顶到栈底打印，故从终点开始向起点遍历
	//把终点坐标放入栈中，设该点处不可走
	Point endCoord(end);
	_dfsStack.push(endCoord);
	LinkNode<Point>* p=_dfsStack.getTop();
	p->nextNode=nullptr;
	_markMap[endCoord.x][endCoord.y] = false;
	

	while (!_dfsStack.empty())
	{
		//获取栈顶元素
		LinkNode<Point>* currPointNode=_dfsStack.getTop();
		//判断终止条件，即dfs走到了start（终点）
		if (currPointNode->data == start)
		{
			break;
		}

		//对当前点的四个方向遍历，（0,1,2,3）分别代表dfs的四个方向（上下左右）
		for(;currPointNode->data.direction<4;currPointNode->data.direction++)
		{
			int i = currPointNode->data.direction;
			Point tempPoint(currPointNode->data);
			//边界判断，如果到了边界，则直接处理下一个方向
			if (tempPoint.x + directionX[i] < 0 || tempPoint.x + directionX[i] >= _currentColumn ||
				tempPoint.y + directionY[i] < 0 || tempPoint.y + directionY[i] >= _currentRow)
			{
				continue;
			}
			//若不是边界，获取由目前点的direction得到的下一个点的坐标
			Point nextPoint(tempPoint.x + directionX[i], tempPoint.y + directionY[i]);
			//如果该坐标可走（该点的)_markMap为真，入栈,设为不可走
			if (_markMap[nextPoint.x][nextPoint.y])
			{
				_dfsStack.push(nextPoint);
				_markMap[nextPoint.x][nextPoint.y] = false;
				break;
			}
		}
		//如果当前点的direction为4，说明遍历完了四个方向，走到死路，回退栈并设为可走
		if (currPointNode->data.direction == 4)
		{
			_markMap[currPointNode->data.x][currPointNode->data.y] = true;
			_dfsStack.pop();
			if (!_dfsStack.empty())
			{
				_dfsStack.getTop()->data.direction++;
			}			
		}
	}

	//迷宫最终解处理
	if (_dfsStack.empty())
	{
		std::cout << "该迷宫没有解" << std::endl;
	}
	else
	{
		std::cout << "该迷宫的解为:" << std::endl;
		
		_dfsStack.printFromTop();
	}
}


/************************************************************************
* FunctionName  :MazeSolver::~MazeSolver()
*
* @Description  : 析构函数，清空内存
*
* @Parameter    : None
*
* @ReturnValue  : None
*
* @Warning      : None
*
* @Editor       : MountPotato
*
*************************************************************************/


MazeSolver::~MazeSolver()
{
	_dfsStack.clear();
	for (int i = 0; i < _currentRow; i++)
	{
		delete[] _mazeMap[i];
		delete[] _markMap[i];
		_mazeMap[i] = nullptr;
		_markMap[i] = nullptr;
	}
	delete _mazeMap;
	delete _markMap;
	_mazeMap = nullptr;
	_markMap = nullptr;

	_currentColumn = _currentRow = 0;
	_startCoord.x = -1, _startCoord.y = -1;
	_endCoord.x = -1, _endCoord.y = -1;
}



/************************************************************************
* FunctionName  :void MazeSolver::run()
*
* @Description  :运行程序
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

void MazeSolver::run()
{
	inputMaze();
	showMaze();
	dfsSolveMaze(_startCoord,_endCoord);
}

///////////////////////////////////////////////////////////主函数//////////////////////////////////////////////////////////////

int main()
{
	MazeSolver ms;
	ms.run();
}