#pragma once
#include <queue>
#include <stack>
#include <iostream>
#include <string>

using namespace std;
//公式类//目前只支持整型变量
template<class VarT = int>
class Formula
{
	enum sign
	{
		equal,
		pules, minus,
		multiply, divide,
		absolute
	};

	struct OperateObject
	{
		//整数 浮点数 变量 一元运算符 二元运算符 括号 未知
		enum OperateType { i, f, v, monadic, dyadic, parentheses, unknow } type = unknow;
		string value;
		OperateObject() {};
		OperateObject(char*& exp_ptr)
		{
			//常量
			if (isdigit(*exp_ptr))
			{
				type = OperateObject::i;
				while (isdigit(*exp_ptr)) value += *exp_ptr++;
				if (*exp_ptr == '.')
				{
					type = OperateObject::f;
					value += *exp_ptr;
					exp_ptr++;
					while (isdigit(*exp_ptr)) value += *exp_ptr++;
					//不支持浮点
					type = unknow;
					value = "err";
					cerr << "do not support float" << endl;
				}
			}
			//变量/常数
			else if (isalpha(*exp_ptr))
			{
				type = OperateObject::v;
				while (isalpha(*exp_ptr))value += *exp_ptr++;
				if (isdigit(*exp_ptr))
				{
					while (isdigit(*exp_ptr))value += *exp_ptr++;
				}
			}
			//运算符
			else if (ispunct(*exp_ptr))
			{
				if (*exp_ptr == '+' || *exp_ptr == '-' || *exp_ptr == '*' || *exp_ptr == '/')
					type = OperateObject::dyadic;
				else if (*exp_ptr == '(' || *exp_ptr == ')')
					type = OperateObject::parentheses;
				else
				{
					type = unknow;
					cerr << "Do not support such operation" << endl;
				}
				value = *exp_ptr++;
			}
			else
			{
				type = unknow;
				value = "err";
				cerr << "Unkonwn Object in expression" << endl;
			}
		}
		OperateObject(string str) { char* p = &str[0]; *this = OperateObject(p); };
		OperateObject(VarT var)
		{
			type = OperateObject::i;
			value = to_string(var);
		}
		VarT GetValue()
		{
			//溢出报错
			string i_max = to_string(INT_MAX);
			string i_min = to_string(INT_MIN);
			if (value[0] != '-')
			{
				if (i_max.size() < value.size() ||
					i_max.size() == value.size() && i_max < value)
					cerr << "integer overflow" << endl;
			}
			else if (i_min.size() < value.size() ||
				i_min.size() == value.size() && i_min < value)
				cerr << "integer overflow" << endl;
			return atoi(value.c_str());
		}
	};

	string expression;//原始数据
	queue<OperateObject>Expression;//存储公式
	bool err = false;//错误

	enum priority { p4, p3, p2, p1, p0 };

	int Priority(OperateObject op)
	{
		if (op.type == OperateObject::monadic)
		{
			return p0;
		}
		if (op.value == "*" || op.value == "/")
		{
			return p1;
		}
		if (op.value == "+" || op.value == "-")
		{
			return p2;
		}
		if (op.value == ",")
		{
			return p3;
		}
	}

	void ProcessError(string err_info)
	{
		expression = "err";
		err = true;
		cerr << "Invalid expression : " << err_info << endl;
		while (!Expression.empty())
		{
			Expression.pop();
		}
	}
public:
	bool Check()
	{
		return !err;
	}

	Formula(string exp)
	{
		queue<OperateObject> formula_cache;//原公式缓存
		stack<OperateObject> formula_stack;
		OperateObject prevobj{};//前一对象
		//括号数量检查
		{
			int p_l{};//左括号数量
			int p_r{};//右括号数量
			for (auto c : exp)
			{
				if (c == '(') p_l++;
				else if (c == ')')p_r++;
			}
			if (p_l != p_r)
			{
				ProcessError("parentheses matching fail");
				return;
			}
		}
		char* exp_ptr = &exp[0];
		//翻译成操作对象
		while (*exp_ptr)
		{
			formula_cache.push(OperateObject(exp_ptr));
			//错误处理
			if (formula_cache.back().type == OperateObject::unknow)
			{
				ProcessError("Unknow object");
				return;
			}
		}

		//转化成后缀表达式
		bool infunction = false;
		OperateObject operateObject;
		while (!formula_cache.empty())
		{
			operateObject = formula_cache.front();
			formula_cache.pop();
			//不支持符号
			if (operateObject.type == OperateObject::v)
			{
				ProcessError("do not support symbols");
				return;
			}
			//括号
			if (operateObject.type == OperateObject::parentheses)
			{
				if (operateObject.value == "(")
				{
					formula_stack.push(operateObject);//压入括号
				}
				else if (operateObject.value == ")")
				{
					//错误检查
					while (!formula_stack.empty() && formula_stack.top().value != "(")
					{
						Expression.push(formula_stack.top());//弹出括号里运算
						formula_stack.pop();
					}
					if (formula_stack.empty())
					{
						ProcessError("parentheses matching fail");
						return;
					}
					formula_stack.pop();//弹出括号
					if (infunction)
					{
						Expression.push(formula_stack.top());//输出函数
					}
				}
			}
			//运算符
			else if (operateObject.type == OperateObject::dyadic)
			{
				//负号处理
				if (prevobj.type == OperateObject::unknow|| prevobj.value == "(")
				{
					if (operateObject.value == "-")
					{
						operateObject.type = OperateObject::monadic;
					}
				}
				//优先级低 弹出
				while (!formula_stack.empty() && formula_stack.top().value != "(" && (Priority(operateObject) <= Priority(formula_stack.top())))
				{
					if (formula_stack.top().value != ",")
						Expression.push(formula_stack.top());
					formula_stack.pop();
				}
				//优先级高 入栈
				formula_stack.push(operateObject);
				//错误检查
				if (formula_cache.empty() || formula_cache.front().type == operateObject.type)
				{
					ProcessError("invalid usage of operator");
					return;
				}
			}
			//变量
			else
			{
				Expression.push(operateObject);
				//错误检查//!
				if (!formula_cache.empty())
					if (formula_cache.front().type != OperateObject::dyadic &&
						formula_cache.front().type != OperateObject::monadic &&
						formula_cache.front().value != ")")
					{
						ProcessError("lack of operator");
						return;
					}
			}
			prevobj = operateObject;
		}
		//将栈中剩余的输出
		while (!formula_stack.empty())
		{
			Expression.push(formula_stack.top());
			formula_stack.pop();
		}

		expression = exp;//储存原始数据
	}

	VarT Calculate()
	{
		queue<OperateObject> exp = Expression;
		stack<OperateObject> calculate_stack;
		while (!exp.empty())
		{
			OperateObject obj = exp.front(); exp.pop();
			if (obj.type == OperateObject::i)
			{
				calculate_stack.push(obj);
			}
			else if (obj.type == OperateObject::dyadic)
			{
				VarT value1{};
				VarT value2{};
				VarT result{};
				value1 = calculate_stack.top().GetValue(); calculate_stack.pop();
				value2 = calculate_stack.top().GetValue(); calculate_stack.pop();
				if (obj.value == "+")
				{
					result = value2 + value1;
				}
				else if (obj.value == "-")
				{
					result = value2 - value1;
				}
				else if (obj.value == "*")
				{
					result = value2 * value1;
				}
				else if (obj.value == "/")
				{
					if (value1 == 0)
					{
						ProcessError("division by zero");
						return VarT{};
					}
					result = value2 / value1;
				}
				calculate_stack.push(OperateObject(result));
			}
			else if (obj.type == OperateObject::monadic)
			{
				VarT value = calculate_stack.top().GetValue(); calculate_stack.pop();
				VarT result{};
				if (obj.value == "-")
				{
					result = -value;
				}

				calculate_stack.push(OperateObject(result));
			}
		}
		if (!calculate_stack.empty())
			return calculate_stack.top().GetValue();
		else
		{
			ProcessError("empty expression");
			return VarT{};
		}
	}
};