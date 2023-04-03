#include "myQueue.h"

int main()
{
	myQueue::queue<int> q;

	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	q.push(5);

	cout << "size = " << q.size() << endl;

	while (!q.empty())
	{
		int val = q.front();
		q.pop();

		cout << val << " ";
	}
	cout << endl;

	return 0;
}