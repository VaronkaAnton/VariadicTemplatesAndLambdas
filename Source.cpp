//Understanding lambda functions and variadic templates in C++ 11

#include <iostream>
#include <tuple>
#include <string>
#include <sstream>
using namespace std;

// a variadic template for calculating the sum of arguments (the number of them is arbitrary) 
template <typename First>
auto accumulate(First n) { return n; } //case of 1 argument as a basic case

template <typename First, typename ...Rest>
auto accumulate(First fst, Rest... rst)
{
	auto func = [](auto a, auto b) { return a + b; };
	return func(fst, accumulate(rst...));
}
// finding minimal value
template <typename First>
auto minvalue(First n) { return n; }

template <typename First, typename ...Rest>
auto minvalue(First fst, Rest... rst)
{
	auto func = [](auto a, auto b) ->double {
		if (a < b)
			return a;
		else
			return b;
	};
	return func(fst, minvalue(rst...));
}


//creates a tuple, first element of which is the sum of integers (among arguments), the second is the sum of doubles
template <typename First>
tuple<int, double> intdouble(First n) { 
	if ((string)typeid(n).name() == "int")
		return make_tuple(n, 0.);
	else
	{
		if ((string)typeid(n).name() == "double")
			return make_tuple(0, n);
		else
			return make_tuple(0, 0.);
	}
}

template <typename First, typename ...Rest>
tuple<int, double> intdouble(First fst, Rest... rst)
{
	auto func = [](auto a, tuple<int, double> b) -> tuple<int, double> {
		if ((string)typeid(a).name() == "int")
			return make_tuple(get<int>(b) + a, get<double>(b));
		else
		{
			if ((string)typeid(a).name() == "double")
				return make_tuple(get<int>(b), get<double>(b) + a);
			else
				return make_tuple(get<int>(b), get<double>(b));
		}
	};
	return func(fst, intdouble(rst...));
}

//converts the list of arguments into a string with a given separator

template <typename Separator, typename First>
//auto toString(Separator spr, First n) {return to_string(n);} 
string toString(Separator spr, First n) {
	auto func = [](auto a, auto b) {
		stringstream ss;
		ss << b;
		return ss.str();
	};
	return func(spr, n);
}

template <typename Separator, typename First, typename ...Rest>
string toString(Separator spr, First fst, Rest... rst)
{
	auto func = [](auto a, auto b, auto c) {
		stringstream ss;
		ss << b << a << c;
		return ss.str();
	};
	return func(spr, fst, toString(spr, rst...));
}
int main()
{
	/*int x = 18;
	int t = 7;
	auto n = [&x](int t) {return x * x;};
	cout << n(t)<< endl;*/
	short m = 1;
	int n1 = 2, n2 = 3;
	double x = 12.8;
	bool isEvrthnOK = true;
	//long long int ll = 281234858885832;
	cout << accumulate(n1, 4.7, m, 1.5, 10, n2, isEvrthnOK) << endl;
	cout << accumulate(2, 14, 87, m, x) << endl;
	cout << minvalue(n1, 4.7, m + 3, 1.5, 10, n2 * n2, -3.2) << endl;

	tuple<int, double> sums = intdouble(m, n1, n2, 2, 3.14, 'a', 54, 7.03, 5., -10);
	cout << "sum of int: " << get<int>(sums) << endl;
	cout << "sum of double " << get<double>(sums) << endl;

	const string result = toString(' ', 'a', 23, 1.5, x, "duck");
	cout << result << endl;
}