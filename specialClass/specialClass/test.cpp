#include <iostream>
#include <map>
#include <string>
#include <mutex>
using namespace std;

// 只能在堆上创建对象的类
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

// 只能在栈上创建对象的类
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

// 单例类 --- 全局只有唯一一个实例化对象
// 饿汉模式
//class Singleton
//{
//public:
//	static Singleton& getInstance()
//	{
//		return _single;
//	}
//
//	// 仅作为熟悉单例模式使用，无其他特殊意义
//	void Insert(string name, int salary)
//	{
//		_info[name] = salary;
//	}
//
//	// 仅作为熟悉单例模式使用，无其他特殊意义
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
//Singleton Singleton::_single;  // 类内静态对象在类外初始化

// RAII模式的锁管理类
template<class Lock>
class LockGuard
{
public:
	LockGuard(Lock& lk)
		:_lk(lk)
	{
		_lk.lock();  // 在构造对象时加锁
	}

	~LockGuard()
	{
		_lk.unlock();  // 在析构对象时解锁
	}

private:
	Lock& _lk;  // 类成员变量使用引用，引用接收外部那个全局的锁；注意：引用的成员变量要在构造函数初始化列表中初始化
};

// 懒汉模式
class Singleton
{
public:
	//static Singleton& getInstance()
	//{
	//	// 双检查加锁
	//	if (_psingle == nullptr)  // 对象new出来以后，避免每次都加锁，提高性能
	//	{
	//		_mtx.lock();

	//		if (_psingle == nullptr)  // 保证线程安全，且只new一次
	//		{
	//			_psingle = new Singleton;  // 在第一次获取单例对象时才创建对象
	//		}

	//		_mtx.unlock();
	//	}
	//	
	//	return *_psingle;  // 其他时候获取，直接返回对象即可
	//}

	static Singleton& getInstance()
	{
		LockGuard<mutex> lock(_mtx);

		if (_psingle == nullptr)  // 保证线程安全，且只new一次
		{
			_psingle = new Singleton;  // 在第一次获取单例对象时才创建对象
		}

		return *_psingle;  // 其他时候获取，直接返回对象即可
	}

	// 仅作为熟悉单例模式使用，无其他特殊意义
	void Insert(string name, int salary)
	{
		_info[name] = salary;
	}

	// 仅作为熟悉单例模式使用，无其他特殊意义
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
	single.Insert("张三", 11000);
	single.Insert("李四", 15000);
	single.Insert("王五", 20000);
	single.Print();

	return 0;
}