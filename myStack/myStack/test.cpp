#include "myStack.h"

int main()
{
	myStack::stack<int> st;

	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);
	st.push(5);

	cout << "size = " << st.size() << endl;

	while (!st.empty())
	{
		int val = st.top();
		st.pop();

		cout << val << " ";
	}
	cout << endl;

	return 0;
}