#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main()
{
	string str;
	cin >> str;

	stack<char> st;
	for (auto e : str)
	{
		if (e >= '0' && e <= '9')
		{
			cout << e << " ";
		}
		else if ((st.empty()) && (e == '+' || e == '-' || e == '*' || e == '/'))
		{
			st.push(e);
		}
		else
		{
			if (e == '+' || e == '-')
			{
				while (!st.empty())
				{
					cout << st.top() << " ";
					st.pop();
				}

				st.push(e);
			}
			else if (e == '*' || e == '/')
			{
				while ((!st.empty()) && (st.top() == '*' || st.top() == '/'))
				{
					cout << st.top() << " ";
					st.pop();
				}

				st.push(e);
			}
		}
	}
	while (!st.empty())
	{
		cout << st.top() << " ";
		st.pop();
	}
	cout << endl;

	return 0;
}