#if 0

#include <iostream>

using std::cout;
using std::endl;

namespace one
{
	void foo(){cout<<"one::foo"<<endl;}
}
namespace two
{
	void foo(){cout<<"two::foo"<<endl;}
	void goo(){cout<<"two::goo"<<endl;}
	int a = 10;
}

//unnamed namespace ���� ����, ���� �Լ�
namespace
{
	void foo(){cout<<"unname::foo"<<endl;}
	void koo(){cout<<"unname::koo"<<endl;}
	int a = 10;
}

void foo() {cout<<"global::foor"<<endl;}
//int a = 20;

//Namespace ���� �Լ��� ������ ���� ������� ȣ��
//1.namespace_name::�ĺ��� ==> one::goo();
//2.using ���þ ����ϸ� �̸� �������� Ư�� symbol�� �ٷ� ����� �� �ִ�.
//	using one::goo;
//3. using���þ ���, �̸� �������� ��� symbol�� �ٷ� ���
//	using namespace one;

void main()
{
	cout<<a<<endl;
	two::foo();
	//using namespace two;
	using two::foo;
	//using one::foo;
	foo();
	//goo();

	//cout<<::a<<endl;
	//foo();
	//goo();

}
#endif

#if 1

#include <iostream>

using std::cout;
using std::endl;

int my_pow(int n)
{
	return n*n;
}
//#define POW(n) ((n)*(n))

inline int POW(int n)
{
	return n*n;
}


void main()
{
	int n = 5;
	int k;
	cout<<my_pow(++n)<<endl;
	cout<<POW(++n)<<endl;
	//k = my_pow(++n);
	//k = POW(++n);
}
#endif