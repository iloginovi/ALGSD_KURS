#include <iostream>
#include<string>

#define pi 3.14159265 
#define e 2.718281
using namespace std;

template <class T>
class Stack
{
private:
	class elem
	{
	public:
		elem(T data, elem* next = NULL) :data(data), next(next) {}
		~elem() = default;
		void setNext(elem* newnext) { next = newnext; }
		elem* getNext() { return next; }
		T getData() { return data; }
	private:
		T data;
		elem* next;
	};

	elem* head;
public:
	Stack() {
		head = NULL;
	};

	~Stack() {
		while (!empty())
		{
			pop();
		}
	};

	void pop() {//delete
		if (empty())
		{
			throw out_of_range("No more elements");
		}
		else
		{
			elem* tmp = head;
			head = head->getNext();
			delete tmp;
		}
	};

	void push(T data) {//add
		elem* tmp = new elem(data);
		elem* cur = head;
		head = tmp;
		head->setNext(cur);

	};

	bool empty() {
		return head == nullptr;
	};

	T top() {//first element
		if (empty())
		{
			throw out_of_range("Empty");
		}
		else
		{
			return head->getData();
		}

	};
};
void check_for_correct_input(string str)
{
	bool check_for_bracekts = 1;
	int posL, posR;
	string str_check_for_brackets = str;
	string Lbracket = "(";
	string Rbracket = ")";
	while (check_for_bracekts)
	{
		posL = str_check_for_brackets.find(Lbracket);
		posR = str_check_for_brackets.find(Rbracket);
		if ((posL != -1) && (posR != -1) && (posL < posR))
		{
			str_check_for_brackets.erase(posL, 1);
			check_for_bracekts = 1;
			str_check_for_brackets.erase(posR - 1, 1);
		}
		else
			check_for_bracekts = 0;
	}

	if (posL != posR) { throw invalid_argument("wrong string"); }

};
void check_for_wrong_commands(string str)
{
	bool check = 1;
	int pos;
	pos = str.find(".");
	if (pos != -1 && (str[pos - 1] > 57 || str[pos - 1] < 48)) { throw invalid_argument("wrong number"); }

	pos = str.find("*");
	if (pos != -1 && (str[pos - 1] == '(' || str[pos + 1] == ')')) { throw invalid_argument("wrong arithmetics"); }

	pos = str.find("+");
	if (pos != -1 && (str[pos - 1] == '(' || str[pos + 1] == ')')) { throw invalid_argument("wrong arithmetics"); }

	pos = str.find("-");
	if (pos != -1 && str[pos + 1] == ')') { throw invalid_argument("wrong arithmetics"); }

	pos = str.find("/");
	if (pos != -1 && ((str[pos + 1] == ')') || str[pos - 1] == '(')) { throw invalid_argument("wrong arithmetics"); }

	pos = str.find("^");
	if (pos != -1 && str[pos - 1] == '(') { throw invalid_argument("wrong arithmetics"); }
};

string check_for_unarity(string str)
{	//sqrt,sgn,sin,cos,log,ln,tg,ctg	g,n,s,t
		//string str = "((2.2+1.0*4.4*1.0)*5.5)/6.6+(-cos(6.2832)*2.0+sin(0.0))^2.0+sgn(-5.0)+ln(e)+ln(1.0)";
	//add (str)
		//( ((2.2+1.0*4.4*1.0)*5.5)/6.6+(cos(6.2832)*2.0+sin(0.0))^2.0+sgn(-5.0)+ln(e)+ln(1.0) )

	for (int i = 1; i < str.length() - 1; i++)
	{
		if (str[i] == '(' && str[i + 1] == '-' && (str[i - 1] != 'g' && str[i - 1] != 'n' && str[i - 1] != 's' && str[i - 1] != 't'))
		{
			str.replace(i, 1, "(0.0");
		}
	}
	return str;
};

/*void stack_brackets_check(string str)
{
	Stack<char> stck;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '(') { stck.push(str[i]); }
		if (str[i] == ')') { stck.pop(); }
	}
	if (stck.empty() == 0) { throw invalid_argument("wrong string"); }
};*/
void transform_inf_to_stack(Stack<string>* stck, string str)
{
	stck->push(")");
	string tmp_str;
	int pos, j;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '(') { stck->push(")"); }
		else
			if (str[i] == ')') { stck->push("("); }
			else
				//sqrt,sgn,sin,cos,log,ln,tg,ctg
				if (str[i] == 's' && str[i + 1] == 'q')
				{
					pos = str.find(")", i); tmp_str.assign(str, i, pos - i + 1); stck->push(tmp_str); tmp_str = "\0"; i = pos;
				}//sqrt
				else
					if (str[i] == 's' && str[i + 1] == 'g')
					{
						pos = str.find(")", i); tmp_str.assign(str, i, pos - i + 1); stck->push(tmp_str); tmp_str = "\0"; i = pos;
					}//sgn
					else
						if (str[i] == 's' && str[i + 1] == 'g')
						{
							pos = str.find(")", i); tmp_str.assign(str, i, pos - i + 1); stck->push(tmp_str); tmp_str = "\0"; i = pos;
						}//sgn
						else
							if (str[i] == 's' && str[i + 1] == 'i')
							{
								pos = str.find(")", i); tmp_str.assign(str, i, pos - i + 1); stck->push(tmp_str); tmp_str = "\0"; i = pos;
							}//sin
							else
								if (str[i] == 'c' && str[i + 1] == 'o')
								{
									pos = str.find(")", i); tmp_str.assign(str, i, pos - i + 1); stck->push(tmp_str); tmp_str = "\0"; i = pos;
								}//cos
								else
									if (str[i] == 't' && str[i + 1] == 'g')
									{
										pos = str.find(")", i); tmp_str.assign(str, i, pos - i + 1); stck->push(tmp_str); tmp_str = "\0"; i = pos;
									}//tg
									else
										if (str[i] == 'c' && str[i + 1] == 't')
										{
											pos = str.find(")", i); tmp_str.assign(str, i, pos - i + 1); stck->push(tmp_str); tmp_str = "\0"; i = pos;
										}//ctg
										else
											if (str[i] == 'l' && str[i + 1] == 'o')
											{
												pos = str.find(")", i); tmp_str.assign(str, i, pos - i + 1); stck->push(tmp_str); tmp_str = "\0"; i = pos;
											}//log
											else
												if (str[i] == 'l' && str[i + 1] == 'n')
												{
													pos = str.find(")", i); tmp_str.assign(str, i, pos - i + 1); stck->push(tmp_str); tmp_str = "\0";	i = pos;
												}//ln
												else
													//double
													if (str[i] >= 48 && str[i] <= 57) //check from table ASCII if string's symbol is between numbers
													{
														j = i; while (str[i] == 46 || (str[i] >= 48 && str[i] <= 57)) { i++; }
														tmp_str.assign(str, j, i - j); stck->push(tmp_str); tmp_str = "\0"; i--;
													}
													else
														// + * - / ^ 
														if (str[i] == '+') { stck->push("+"); }
														else
															if (str[i] == '*') { stck->push("*"); }
															else
																if (str[i] == '-') { stck->push("-"); }
																else
																	if (str[i] == '/') { stck->push("/"); }
																	else
																		if (str[i] == '^') { stck->push("^"); }
																		else
																			//pi and e
																			if (str[i] == 'p' && str[i + 1] == 'i') { stck->push("pi"); i++; }
																			else
																				if (str[i] == 'e') { stck->push("e"); i += 2; }

	}

	stck->push("(");
};
int priority(string c)
{
	if (c == "^") { return 3; }
	else if (c == "*" || c == "/") { return 2; }
	else if (c == "+" || c == "-") { return 1; }
	else { return 0; }
}
void prefix_notation_isnt_my_oreintation(Stack<string>* prefix, Stack<string>* str)//turn in prefix
{
	/*
	stack string				| stack operators				|stack prefix
	firstly stack					( + - * / ^						double cos sin tg and e.t.c.

	*/
	Stack<string> operators;
	string tmp;
	while (!str->empty())
	{
		tmp = str->top();
		if (tmp == "(") { operators.push(tmp); str->pop(); }
		else
			if (tmp == ")") { while (tmp != "(") { tmp = operators.top(); if (tmp != "(") { prefix->push(tmp); }operators.pop(); } str->pop(); }
			else
				if (tmp == "*") {
					while (priority(tmp) <= priority(operators.top())) { prefix->push(operators.top()); operators.pop(); }operators.push(str->top()); str->pop();
				}
				else
					if (tmp == "+") {
						while (priority(tmp) <= priority(operators.top())) { prefix->push(operators.top()); operators.pop(); } operators.push(str->top()); str->pop();
					}
					else
						if (tmp == "-") {
							while (priority(tmp) <= priority(operators.top())) { prefix->push(operators.top()); operators.pop(); }operators.push(str->top()); str->pop();
						}
						else
							if (tmp == "/") {
								while (priority(tmp) <= priority(operators.top())) { prefix->push(operators.top()); operators.pop(); } operators.push(str->top()); str->pop();
							}
							else
								if (tmp == "^") {
									while (priority(tmp) <= priority(operators.top())) { prefix->push(operators.top()); operators.pop(); } operators.push(str->top()); str->pop();
								}
								else
									if (tmp != "*" && tmp != "+" && tmp != "-" && tmp != "/" && tmp != "^" && tmp != "(" && tmp != ")")
									{
										prefix->push(tmp); str->pop();
									}
	}
	while (!operators.empty()) { operators.pop(); }
	while (!str->empty()) { str->pop(); }
};
/*
1) Create empty stack for saving operators
2)check calculation from right to left
if token is operant- add him to the ioutput list
if token is left bracket take out from stack all symbols to right bracket and add them to the output list
if token is operator- delete all operators from stack ( while will see operator with lower proirity)
and add them to the output list if only operators proirity on top of stack >= prority of current operator(token)
then add token in stack
otherway add token in stack firstly
3) if after searching all elements some operators left in stack-> add to output
*/

string transform_log_and_CO(string str)//count log tg sin and e.t.c.as it is simple function of 1 element
{
	string tmp_str, tmp2_str;
	int  left_point, right_point, i, j, pos_ar;//pos_ar- position of artihmetic left/right_point is for borders of double
	double tmp_d1, tmp_d2;
	//firstly find e or pi in case it can be in ln or sin or e.t.c.
	if (str.find("e") != -1)
	{
		i = str.find("e");//find index of 'e'
		j = i;
		tmp_str = to_string(e);
		str.replace(i, j - i + 1, tmp_str);
	}
	if (str.find("pi") != -1)
	{
		i = str.find("pi");//find index of 'p'
		j = str.find("i", i);
		tmp_str = to_string(pi);
		str.replace(i, j - i + 1, tmp_str);
	}
	if (str.find("cos(") != -1)
	{
		i = str.find("cos(");//find index of 'c'
		j = str.find(")", i);
		tmp_str.assign(str, i + 4, j - (i + 4));
		tmp_d1 = std::stod(tmp_str);
		tmp_d2 = cos(tmp_d1);
		tmp_str = to_string(tmp_d2);
		str.replace(i, j - i + 1, tmp_str);
	}
	if (str.find("sin(") != -1)
	{
		i = str.find("sin(");//find index of 's'
		j = str.find(")", i);
		tmp_str.assign(str, i + 4, j - (i + 4));
		tmp_d1 = std::stod(tmp_str);
		tmp_d2 = sin(tmp_d1);
		tmp_str = to_string(tmp_d2);
		str.replace(i, j - i + 1, tmp_str);
	}
	if (str.find("sgn(") != -1)
	{
		i = str.find("sgn(");//find index of 's'
		j = str.find(")", i);
		tmp_str.assign(str, i + 4, j - (i + 4));
		tmp_d1 = std::stod(tmp_str);
		if (tmp_d1 > 0) tmp_d2 = 1;
		if (tmp_d1 < 0) tmp_d2 = -1;
		if (tmp_d1 == 0) tmp_d2 = 0;
		tmp_str = to_string(tmp_d2);
		str.replace(i, j - i + 1, tmp_str);
	}
	if (str.find("log(") != -1)
	{
		i = str.find("log(");//find index of 'l'
		j = str.find(")", i);
		tmp_str.assign(str, i + 4, j - (i + 4));
		tmp_d1 = std::stod(tmp_str);
		if (tmp_d1 <= 0) {
			throw invalid_argument("wrong number under logartihm");
		}
		tmp_d2 = log2(tmp_d1);
		tmp_str = to_string(tmp_d2);
		str.replace(i, j - i + 1, tmp_str);
	}
	if (str.find("ln(") != -1)
	{
		i = str.find("ln(");//find index of 'l'
		j = str.find(")", i);
		tmp_str.assign(str, i + 3, j - (i + 3));
		tmp_d1 = std::stod(tmp_str);
		if (tmp_d1 <= 0) {
			throw invalid_argument("wrong number under logartihm");
		}
		tmp_d2 = log(tmp_d1);
		tmp_str = to_string(tmp_d2);
		str.replace(i, j - i + 1, tmp_str);
	}
	if (str.find("ctg(") != -1)
	{
		i = str.find("ctg(");//find index of 'c'
		j = str.find(")", i);
		tmp_str.assign(str, i + 4, j - (i + 4));
		tmp_d1 = std::stod(tmp_str);
		tmp_d2 = 1 / (tan(tmp_d1));
		tmp_str = to_string(tmp_d2);
		str.replace(i, j - i + 1, tmp_str);
	}
	if (str.find("tg(") != -1)
	{
		i = str.find("tg(");//find index of 't'
		j = str.find(")", i);
		tmp_str.assign(str, i + 3, j - (i + 3));
		tmp_d1 = std::stod(tmp_str);
		tmp_d2 = tan(tmp_d1);
		tmp_str = to_string(tmp_d2);
		str.replace(i, j - i + 1, tmp_str);
	}
	if (str.find("sqrt(") != -1)
	{
		i = str.find("sqrt(");//find index of 's'
		j = str.find(")", i);
		tmp_str.assign(str, i + 5, j - (i + 5));
		tmp_d1 = std::stod(tmp_str);
		if (tmp_d1 < 0) { throw invalid_argument("wrong number under logartihm"); }
		tmp_d2 = sqrt(tmp_d1);
		tmp_str = to_string(tmp_d2);
		str.replace(i, j - i + 1, tmp_str);
	}
	return str;
}
double calculation(Stack<string>* rev_pref)
{//the final count of our prefix
	Stack<string> calc;
	string tmp1, tmp_calc1, tmp_calc2;
	char operation;
	double tmp_d1, tmp_d2;
	while (!rev_pref->empty())
	{
		tmp1 = rev_pref->top();
		if (tmp1 == "*" || tmp1 == "+" || tmp1 == "-" || tmp1 == "/" || tmp1 == "^")
		{
			/*	create "empty stack"
				scan from right to left(reverse stack)
				if tmp=stack.top()==operator(numbers or log or some else)=> put in "epmty stack"
				if tmp=stack.top()==operand(+ - * / sqrt ^)				 =>take two string from "empty stack" make arithmetics and add back to stack*/

			if (tmp1 == "+")
			{
				tmp_calc1 = calc.top(); calc.pop();
				tmp_calc2 = calc.top(); calc.pop();
				tmp_d1 = std::stod(tmp_calc1);
				tmp_d2 = std::stod(tmp_calc2);
				tmp_d1 = tmp_d1 + tmp_d2;
				calc.push(to_string(tmp_d1));
			}
			else
				if (tmp1 == "*")
				{
					tmp_calc1 = calc.top(); calc.pop(); tmp_calc2 = calc.top(); calc.pop(); tmp_d1 = std::stod(tmp_calc1); tmp_d2 = std::stod(tmp_calc2);
					tmp_d1 = tmp_d1 * tmp_d2; calc.push(to_string(tmp_d1));
				}
				else
					if (tmp1 == "-")
					{
						tmp_calc1 = calc.top(); calc.pop(); tmp_calc2 = calc.top(); calc.pop(); tmp_d1 = std::stod(tmp_calc1); tmp_d2 = std::stod(tmp_calc2);
						tmp_d1 = tmp_d1 - tmp_d2; calc.push(to_string(tmp_d1));
					}
					else
						if (tmp1 == "/")
						{
							tmp_calc1 = calc.top(); calc.pop(); tmp_calc2 = calc.top(); calc.pop(); tmp_d1 = std::stod(tmp_calc1); tmp_d2 = std::stod(tmp_calc2);
							tmp_d1 = tmp_d1 / tmp_d2; calc.push(to_string(tmp_d1));
						}
						else
							if (tmp1 == "^")
							{
								tmp_calc1 = calc.top(); calc.pop(); tmp_calc2 = calc.top(); calc.pop(); tmp_d1 = std::stod(tmp_calc1); tmp_d2 = std::stod(tmp_calc2);
								tmp_d1 = pow(tmp_d1, tmp_d2); calc.push(to_string(tmp_d1));
							}
		}
		//if its double/e/pi/log
		if (tmp1.rfind("c") != -1 || tmp1.rfind("s") != -1 || tmp1.rfind("e") != -1 || tmp1.rfind("p") != -1 || tmp1.rfind("l") != -1 || tmp1.rfind("t") != -1)
			//				cos				sin,sgn,sqrt					e						pi					log,ln				tg,ctg
		{
			tmp1 = transform_log_and_CO(tmp1); calc.push(tmp1);
		}
		else if (tmp1.rfind(".") != -1) { calc.push(tmp1); }
		rev_pref->pop();
	}
	double	result = std::stod(calc.top());
	return result;
};
int main(){
	Stack<string> prefix_stack;
	Stack<string> from_str;
	Stack<string> reverse_prefix;
	//string str = "(((-2.2)+1.0*4.4*1.0)*5.5)/6.6+(cos(6.2832)*2.0+sin(0.0))^2.0+sgn(-5.0)+ln(e)+ln(1.0)";
	//string str ="(cos(pi)+sin(pi))^2.0"; //another variant 
	string str = "(-1.0)+5.2";
	double result;
	cout << "our txt is :\n" << str << endl;
	str = "(" + str + ")";
	str = check_for_unarity(str);
	cout << "our txt is :\n" << str << endl;
	check_for_wrong_commands(str);
	check_for_correct_input(str);
	transform_inf_to_stack(&from_str, str);
	prefix_notation_isnt_my_oreintation(&prefix_stack, &from_str);
	cout << "\nprefix form:\n";
	while (!prefix_stack.empty()) { cout << prefix_stack.top(); reverse_prefix.push(prefix_stack.top()); prefix_stack.pop(); }
	cout << endl;
	result = calculation(&reverse_prefix);//9.5
	cout << "result=" << result;
	//by internet(online calculator)
	//+/*+2.2*1.1*4.41.05.56.6+^+*cos0.1238912982.0sin0.02.0+sgn-5.0+logelog1.0
    return 0;
}
