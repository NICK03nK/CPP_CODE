#include <iostream>
#include <map>
#include <string>
#include <mutex>
using namespace std;

// ֻ���ڶ��ϴ����������
class HeapOnly
{
public:
	static HeapOnly* CreateObj()
	{
		return new HeapOnly;
	}

private:
	HeapOnly()
	{}

	HeapOnly(const HeapOnly& ho) = delete;
};

// ֻ����ջ�ϴ����������
class StackOnly
{
public:
	static StackOnly CreateObj()
	{
		return StackOnly();
	}

private:
	StackOnly()
	{}
};

// ������ --- ȫ��ֻ��Ψһһ��ʵ��������
// ����ģʽ
//class Singleton
//{
//public:
//	static Singleton& getInstance()
//	{
//		return _single;
//	}
//
//	// ����Ϊ��Ϥ����ģʽʹ�ã���������������
//	void Insert(string name, int salary)
//	{
//		_info[name] = salary;
//	}
//
//	// ����Ϊ��Ϥ����ģʽʹ�ã���������������
//	void Print()
//	{
//		for (auto& kv : _info)
//		{
//			cout << kv.first << " : " << kv.second << endl;
//		}
//	}
//
//private:
//	Singleton()
//	{}
//
//	Singleton(const Singleton& single) = delete;
//	Singleton& operator=(const Singleton& single) = delete;
//
//	map<string, int> _info;
//
//private:
//	static Singleton _single;
//};
//Singleton Singleton::_single;  // ���ھ�̬�����������ʼ��

// RAIIģʽ����������
template<class Lock>
class LockGuard
{
public:
	LockGuard(Lock& lk)
		:_lk(lk)
	{
		_lk.lock();  // �ڹ������ʱ����
	}

	~LockGuard()
	{
		_lk.unlock();  // ����������ʱ����
	}

private:
	Lock& _lk;  // ���Ա����ʹ�����ã����ý����ⲿ�Ǹ�ȫ�ֵ�����ע�⣺���õĳ�Ա����Ҫ�ڹ��캯����ʼ���б��г�ʼ��
};

// ����ģʽ
class Singleton
{
public:
	//static Singleton& getInstance()
	//{
	//	// ˫������
	//	if (_psingle == nullptr)  // ����new�����Ժ󣬱���ÿ�ζ��������������
	//	{
	//		_mtx.lock();

	//		if (_psingle == nullptr)  // ��֤�̰߳�ȫ����ֻnewһ��
	//		{
	//			_psingle = new Singleton;  // �ڵ�һ�λ�ȡ��������ʱ�Ŵ�������
	//		}

	//		_mtx.unlock();
	//	}
	//	
	//	return *_psingle;  // ����ʱ���ȡ��ֱ�ӷ��ض��󼴿�
	//}

	static Singleton& getInstance()
	{
		LockGuard<mutex> lock(_mtx);

		if (_psingle == nullptr)  // ��֤�̰߳�ȫ����ֻnewһ��
		{
			_psingle = new Singleton;  // �ڵ�һ�λ�ȡ��������ʱ�Ŵ�������
		}

		return *_psingle;  // ����ʱ���ȡ��ֱ�ӷ��ض��󼴿�
	}

	// ����Ϊ��Ϥ����ģʽʹ�ã���������������
	void Insert(string name, int salary)
	{
		_info[name] = salary;
	}

	// ����Ϊ��Ϥ����ģʽʹ�ã���������������
	void Print()
	{
		for (auto& kv : _info)
		{
			cout << kv.first << " : " << kv.second << endl;
		}
	}

private:
	Singleton()
	{}

	Singleton(const Singleton& single) = delete;
	Singleton& operator=(const Singleton& single) = delete;

	map<string, int> _info;

private:
	static Singleton* _psingle;
	static mutex _mtx;
};
Singleton* Singleton::_psingle = nullptr;
mutex Singleton::_mtx;

int main()
{
	//HeapOnly* pho = HeapOnly::CreateObj();

	//StackOnly so = StackOnly::CreateObj();

	Singleton& single = Singleton::getInstance();
	single.Insert("����", 11000);
	single.Insert("����", 15000);
	single.Insert("����", 20000);
	single.Print();

	return 0;
}