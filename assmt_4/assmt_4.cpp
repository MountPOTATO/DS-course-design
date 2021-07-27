#include "assmt_4.h"


/************************************************************************
* FunctionName  :isExpressionOperator(const char& c)
*
* @Description  :判断当前的char字符是否是属于运算符
*
* @Parameter    :const char& c表示当前接收判断的字符
*
* @ReturnValue  : 如果是'+','-','*','/','百分号','^','(',')'则返回真
*				  反之返回假
*
* @Warning      : none
*
* @Editor       : MountPotato
*
*************************************************************************/


bool isExpressionOperator(const char& c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^' || c == '(' || c == ')')
	{
		return true;
	}
	return false;
}


/************************************************************************
* FunctionName  :bool isUnary(const string& s, int index)
*
* @Description  :判断当前的字符s[index]是否为单目运算符
*
* @Parameter    :const string&s 表示传入的字符串，int index表示字符索引
*
* @ReturnValue  :如果是单目运算符(在s[0]处或前面一个字符是(，则返回真，
*				 反之返回加
*
* @Warning      : None
*
* @Editor       : MountPotato
*
*************************************************************************/


bool isUnary(const string& s, int index)
{
	//如果index不在范围内，返回假
	if (index < 0 || index >= s.size())
	{
		return false;
	}
	else		
	{
		//如果符号不是+或-，返回假
		if (s[index] != '+' && s[index] != '-')
		{
			return false;
		}
		else
		{
			//首字符，真
			if (index == 0) return true;
			else
			{
				//前一个字符为(,真
				char chFront = s.at(index - 1);

				switch (chFront)
				{
					case ')':return false;
					case '(':return true;
					default:return false;
				}
			}
		}
	}
}


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
	if (_pTop)
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
* FunctionName  :int Calculator::prior(const char ch)const
*
* @Description  :计算各个运算符号的优先级
*
* @Parameter    :const char ch 表示当前符号的优先级
*
* @ReturnValue  :如下所示
*
* @Warning      :此函数需要在判明ch为字母后再进行使用
*
* @Editor       : MountPotato
*
*************************************************************************/


int Calculator::prior(const char ch)const
{
	switch (ch)
	{
	case '+':
	case '-':return 1; break;	//+- 优先级为1
	case '*':
	case '/':
	case '%':return 2; break;	//* / mod 优先级为2	
	case '^':return 3; break;
	default:return 0; break;
	}
}

/************************************************************************
* FunctionName  :double Calculator::getAnswer(double a, char c, double b)const
*
* @Description  :输入两个浮点数a，b 通过符号c对应的操作进行计算，返回计算结果
*
* @Parameter    :double a，b表示两个操作数,char c表示运算符号
*
* @ReturnValue  :根据对应的符号与操作数，返回相应的计算成果
*
* @Warning      :由于浮点数不能直接取余，所以使用库内置方法fmod计算两个浮点数的取余
*
* @Editor       : MountPotato
*
*************************************************************************/

double Calculator::getAnswer(double a, char c, double b)const
{
	switch (c)
	{
		case '+': return b + a; break;
		case '-': return b - a; break;
		case '*': return b * a; break;
		case '/': return b / a; break;
		case '%': return fmod(b, a); break;
		case '^': return pow(b, a); break;
		default:assert(false);
	}
}


/************************************************************************
* FunctionName  :void Calculator::run()
*
* @Description  :主函数运行程序
*
* @Parameter    :None
*
* @ReturnValue  :None
*
* @Warning      :
*
* @Editor       : MountPotato
*
*************************************************************************/


void Calculator::run()
{
	string infixExpression;
	char chCommand;

	while (true)
	{
		std::cout << "输入表达式:" << std::endl;
		if (!inputInfixExpression(infixExpression))	//输入表达式
		{
			continue;
		}
		
		if (!processInfixExpression(infixExpression))	//将表达式数字与符号放入栈中
		{
			std::cerr << "错误：表达式非法,请重新";
			continue;
		}
		if (!calculateResult())	//根据栈中的情况计算结果
		{
			std::cerr << "错误：表达式非法,请重新";
			continue;
		}

		if (isfinite(operandStack.top()->data))	//若除数为0时用_finite函数判断是否在有理数范围内
		{
			std::cout << operandStack.top()->data << std::endl;	//合法，正常输出
		}
		else
		{
			std::cerr << "错误：表达式非法,出现除数为0的非法运算,请重新";
			continue;
		}


		std::cout << "是否继续(y,n)? " << std::endl;
		std::cin >> chCommand;
		while (true)
		{
			if (chCommand == 'n')
			{
				std::cout << "计算器程序结束，感谢使用" << std::endl;
				return;
			}
			else if (chCommand != 'y')
			{
				std::cin.clear();
				std::cin.ignore();
				std::cout << "错误：请重新输入'y'或'n'" << std::endl;
				std::cin >> chCommand;
			}
			else
			{
				break;
			}

		}
	}
}



/************************************************************************
* FunctionName  :bool Calculator::calculatePostfix()
*
* @Description  :在中缀转后缀的函数完成后运行，将栈中结果进行运算
*				 运行结果：在operandStack中留下最终的一个结果
*				 返回值：如果成功，返回true，如果中间因表达式出
*				 错导致其中一个栈提前为空，则返回false
*
* @Parameter    :None
*
* @ReturnValue  :返回值：如果成功，返回true，如果中间因表达式出
*				 错导致其中一个栈提前为空，则返回false，表示式子
*				 有误
*
* @Warning      : 需在Calculator::infixToPostfix()函数完成后进行
*
* @Editor       : MountPotato
*
*************************************************************************/


bool Calculator::calculateResult()
{
	while (!operatorStack.empty())
	{
		if (!process2Operands())
		{
			return false;
		}
	}
	return true;
}




/************************************************************************
* FunctionName  :bool Calculator::infixToPostfix(const string& infixExpression)
*
* @Description  :输入中缀表达式，并将后缀表达式的式子放入操作符栈与操作数栈中
*				 同时进行输入检查，判断中缀表达式是否合法
*
* @Parameter    :const string& infixExpression，表示输入的中缀表达式
*
* @ReturnValue  :成功转换，返回true，转换失败，返回false
*
* @Warning      :异常处理
*
* @Editor       : MountPotato
*
*************************************************************************/


bool Calculator::processInfixExpression(const string& infixExpression)
{
	operandStack.clear();//预处理，清空两个栈
	operatorStack.clear();

	bool isNegative = false;
	for (int i = 0; i < infixExpression.size() - 1; i++)
	{
		auto currentChar = infixExpression.at(i);

		if (!isExpressionOperator(currentChar))
		{
			string number;
			double data;
			//处理浮点数，用stringstream方法将浮点数字符串转化为浮点数double
			while (!isExpressionOperator(currentChar) && i < infixExpression.size() - 1)
			{
				number.push_back(currentChar);
				currentChar = infixExpression.at(++i);
			}
			--i;
			std::stringstream stringToDouble;
			stringToDouble << number;
			stringToDouble >> data;
			if (isNegative)
			{
				//对负数的处理
				operandStack.push(-data);
				isNegative = false;
			}
			else
			{
				operandStack.push(data);
			}
			number.clear();
		}
		else
		{
			//单目运算符+ -的处理方式
			if (currentChar == '-' && isUnary(infixExpression, i))
			{
				isNegative = true;
			}
			else if (currentChar == '+' && isUnary(infixExpression, i))
			{
				continue;
			}
			else
			{
				//处理双目运算符
				if (!processOperator(infixExpression, i))
				{
					return false;
				}
			}
		}
	}
	return true;
}



/************************************************************************
* FunctionName  :bool Calculator::processBinaryOperator
					(const string& infixExpression, int index)
*
* @Description  :当infixExpression[index]为双目运算符时，进行判断与处理
*
* @Parameter    :const string& infixExpression, int index
*				 表示infixExpression[index]代表的字符
*
* @ReturnValue  :若表达式非法导致提前栈空，返回false，正常则返回true
*
* @Warning      :见下
*
* @Editor       : MountPotato
*
*************************************************************************/


bool Calculator::processOperator(const string& infixExpression, int index)
{
	auto curChar = infixExpression.at(index);

	//直接入栈条件：1.运算符栈空，2.当前为左括号 3.当前栈顶为左括号但当前不为右括号，4.栈顶元素优先级小于当前运算符优先级
	if (operatorStack.empty())
	{
		operatorStack.push(curChar);
	}
	else if (	curChar == '(' 
				|| (operatorStack.top()->data == '('&&curChar!=')')
				|| (prior(curChar) > prior(operatorStack.top()->data))
			)
	{
		operatorStack.push(curChar);
	}
	//当前符号为右括号时：1.如果括号中只有数（符号栈顶为左括号） 2.否则，直到栈顶为左括号之前进行运算处理
	else if (curChar == ')')
	{
		char ctop = operatorStack.top()->data;
		
		if (ctop == '(')
		{
			operatorStack.pop();
		}
		else
		{
			while (ctop != '(')
			{
				if (!process2Operands())
				{
					return false;
				}
				ctop = operatorStack.top()->data;
			}
			operatorStack.pop();
		}
	}
	//当前符号优先级小于栈顶优先级时
	else
	{		
		while (true)
		{
			if (operatorStack.empty()) break;
			else if ((prior(operatorStack.top()->data) >= prior(curChar)))
			{
				char ctop = operatorStack.top()->data;
				if (!process2Operands())
				{
					return false;
				}
			}
			else break;
		}
		operatorStack.push(curChar);
	}
	return true;
}


/************************************************************************
* FunctionName  :bool Calculator::process2Operands()
*
* @Description  : 从符号栈中取出1个双目运算符，从数字栈中取出2个数字，运算后放回
*				  数字栈
*
* @Parameter    :None
*
* @ReturnValue  :若表达式非法导致提前栈空，返回false，正常则返回true
*
* @Warning      :
*
* @Editor       : MountPotato
*
*************************************************************************/


bool Calculator::process2Operands()
{
	double num1, num2;
	char ctop;
	bool isRightExpression = true;
	if (!operandStack.empty())
	{
		num1 = operandStack.top()->data;
		operandStack.pop();
	}
	else
	{
		isRightExpression = false;
	}
	if (!operandStack.empty())
	{
		num2 = operandStack.top()->data;
		operandStack.pop();
	}
	else
	{
		isRightExpression = false;
	}
	if (!operatorStack.empty())
	{
		ctop = operatorStack.top()->data;
		operatorStack.pop();
	}
	else
	{
		isRightExpression = false;
	}
	if (isRightExpression)
	{
		operandStack.push(getAnswer(num1, ctop, num2));
	}
	else
	{
		operandStack.clear();
		operatorStack.clear();
		return false;
	}
	return true;
}



/************************************************************************
* FunctionName  :bool Calculator::inputInfixExpression(string& infix)
*
* @Description  :对表达式的预处理与检查，从符号正确性，括号匹配性等方面检查
*
* @Parameter    :string& infix 表示输入的字符
*
* @ReturnValue  :若表达式在符号正确性，括号匹配性不正确返回false，反之返回true
*
* @Warning      :None
*
* @Editor       : MountPotato
*
*************************************************************************/


bool Calculator::inputInfixExpression(string& infix)
{

	std::cin >> infix;
	int bracketCounter = 0;

	for (int i =0; i < infix.size(); i++)
	{
		char ch = infix.at(i);
		if (!(isExpressionOperator(ch) || (ch >= '0' && ch <= '9')||ch=='.'))
		{
			if (ch != '=' || (ch == '=' && i < infix.size() - 1))
			{
				std::cerr << "错误：出现非法字符,请重新";
				return false;
			}
			
		}
		
		if (ch == '(') bracketCounter++;
		if (ch == ')')bracketCounter--;

	}

	if (bracketCounter != 0)
	{
		std::cerr << "错误：括号不匹配,请重新";
		return false;
	}

	if (*(infix.end()-1) != '=')
	{
		infix.push_back('=');
	}
	

	if (infix.at(0) == '-')
		infix.insert(infix.begin(), '0');
	return true;
}






int main(int argc, char* argv[])
{
	Calculator cal;
	cal.run();
	return 0;
}