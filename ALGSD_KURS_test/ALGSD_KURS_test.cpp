#include "pch.h"
#include "CppUnitTest.h"
#include "../ALGSD_KURS/ALGSD_KURS.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ALGSDKURStest
{
	TEST_CLASS(ALGSDKURStest)
	{
	public:
		TEST_METHOD(Test_result)
		{
			Stack<string> prefix_stack;
			Stack<string> from_str;
			Stack<string> reverse_prefix;
			string str1 = "((2.2+1.1*4.4*1.0)*5.5)/6.6+(cos(6.2832)*2.0+sin(0.0))^2.0+sgn(-5.0)+ln(e)+ln(1.0)";
			string str2 = "2.2+2.8";
			double result;
			transform_inf_to_stack(&from_str, str2);
			prefix_notation_isnt_my_oreintation(&prefix_stack, &from_str);
			while (!prefix_stack.empty()) { reverse_prefix.push(prefix_stack.top()); prefix_stack.pop(); }
			result = calculation(&reverse_prefix);
			Assert::AreEqual(5.0, result);

		}
		TEST_METHOD(Test_result2)
		{
			Stack<string> prefix_stack;
			Stack<string> from_str;
			Stack<string> reverse_prefix;
			string str1 = "((2.2+1.0*4.4*1.0)*5.5)/6.6+(cos(6.2832)*2.0+sin(0.0))^2.0+sgn(-5.0)+ln(e)+ln(1.0)";
			double result;
			transform_inf_to_stack(&from_str, str1);
			prefix_notation_isnt_my_oreintation(&prefix_stack, &from_str);
			while (!prefix_stack.empty()) { reverse_prefix.push(prefix_stack.top()); prefix_stack.pop(); }
			result = calculation(&reverse_prefix);
			Assert::AreEqual(9.5, result);
		}
		TEST_METHOD(Test_result3)
		{
			Stack<string> prefix_stack;
			Stack<string> from_str;
			Stack<string> reverse_prefix;
			string str1 = "(cos(pi)+sin(pi))^2.0";
			double result;
			transform_inf_to_stack(&from_str, str1);
			prefix_notation_isnt_my_oreintation(&prefix_stack, &from_str);
			while (!prefix_stack.empty()) { reverse_prefix.push(prefix_stack.top()); prefix_stack.pop(); }
			result = calculation(&reverse_prefix);
			Assert::AreEqual(1.0, result);
		}
		TEST_METHOD(Test_result4)
		{
			Stack<string> prefix_stack;
			Stack<string> from_str;
			Stack<string> reverse_prefix;
			string str1 = "sqrt(4.0+sin(pi))";
			double result;
			transform_inf_to_stack(&from_str, str1);
			prefix_notation_isnt_my_oreintation(&prefix_stack, &from_str);
			while (!prefix_stack.empty()) { reverse_prefix.push(prefix_stack.top()); prefix_stack.pop(); }
			result = calculation(&reverse_prefix);
			Assert::AreEqual(2.0, result);
		}
		TEST_METHOD(Test_breakers)
		{
			Stack<string> prefix_stack;
			Stack<string> from_str;
			Stack<string> reverse_prefix;
			string str1 = "4+sin(pi)";
			double result;
			transform_inf_to_stack(&from_str, str1);
			prefix_notation_isnt_my_oreintation(&prefix_stack, &from_str);
			while (!prefix_stack.empty()) { reverse_prefix.push(prefix_stack.top()); prefix_stack.pop(); }
			bool check = 0;
			try { result = calculation(&reverse_prefix); }
			catch (std::out_of_range) { check = 1; }
			Assert::IsTrue(check);
		}
		TEST_METHOD(Test_breakers2)
		{
			string str1 = "(4.0+sin(pi)";
			bool check = 0;
			try { check_for_correct_input(str1); }
			catch (std::invalid_argument) { check = 1; }
			Assert::IsTrue(check);
		}
		TEST_METHOD(Test_breakers3)
		{
			Stack<string> prefix_stack;
			Stack<string> from_str;
			Stack<string> reverse_prefix;
			string str1 = " .0+sin(pi)";
			string str2 = "s.0+sin(pi)";
			string str3 = "(+sin(pi))";
			string str4 = "(*sin(pi))";
			string str5 = "(/sin(pi))";
			string str6 = "(^sin(pi))";
			string str7 = "(sin(pi)-)";
			bool check = 0;
			try { check_for_wrong_commands(str1); }
			catch (std::invalid_argument) { check = 1; }
			Assert::IsTrue(check);
			check = 0;
			try { check_for_wrong_commands(str2); }
			catch (std::invalid_argument) { check = 1; }
			Assert::IsTrue(check);
			check = 0;
			try { check_for_wrong_commands(str3); }
			catch (std::invalid_argument) { check = 1; }
			Assert::IsTrue(check);
			check = 0;
			try { check_for_wrong_commands(str4); }
			catch (std::invalid_argument) { check = 1; }
			Assert::IsTrue(check);
			check = 0;
			try { check_for_wrong_commands(str5); }
			catch (std::invalid_argument) { check = 1; }
			Assert::IsTrue(check);
			check = 0;
			try { check_for_wrong_commands(str6); }
			catch (std::invalid_argument) { check = 1; }
			Assert::IsTrue(check);
			check = 0;
			try { check_for_wrong_commands(str7); }
			catch (std::invalid_argument) { check = 1; }
			Assert::IsTrue(check);
		}
		TEST_METHOD(Test_rules_of_fucntions)
		{
			Stack<string> prefix_stack;
			Stack<string> from_str;
			string tmp;
			bool check = 0;
			string str1 = "log(-6.66)+ln(-993.0)+sqrt(-25.25)";
			transform_inf_to_stack(&from_str, str1);
			prefix_notation_isnt_my_oreintation(&prefix_stack, &from_str);
			while (!prefix_stack.empty()) {
				tmp = prefix_stack.top();
				if (tmp != "+")
				{
					check = 0;
					try
					{
						transform_log_and_CO(tmp);
					}
					catch (std::invalid_argument) { check = 1; }
					Assert::IsTrue(check);
				}
				prefix_stack.pop();
			}
		}

		TEST_METHOD(Test_for_true_stack)
		{
			Stack<string> prefix_stack;
			Stack<string> from_str;
			string tmp1, tmp2;
			bool check = 0;
			string str1 = "log(6.66)+ln(993.0)+sqrt(25.25)";
			transform_inf_to_stack(&from_str, str1);
			prefix_notation_isnt_my_oreintation(&prefix_stack, &from_str);
			tmp1 = prefix_stack.top(); tmp2 = "+";
			Assert::AreEqual(tmp2, tmp1);
			prefix_stack.pop();	tmp1 = prefix_stack.top();  tmp2 = "log(6.66)";
			Assert::AreEqual(tmp2, tmp1);
			prefix_stack.pop();	tmp1 = prefix_stack.top(); tmp2 = "+";
			Assert::AreEqual(tmp2, tmp1);
			prefix_stack.pop();	tmp1 = prefix_stack.top(); tmp2 = "ln(993.0)";
			Assert::AreEqual(tmp2, tmp1);
			prefix_stack.pop();	tmp1 = prefix_stack.top(); tmp2 = "sqrt(25.25)";
			Assert::AreEqual(tmp2, tmp1);

		}
	};
}
