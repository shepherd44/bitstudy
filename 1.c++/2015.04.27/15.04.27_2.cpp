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

//unnamed namespace 전역 변수, 전역 함수
namespace
{
	void foo(){cout<<"unname::foo"<<endl;}
	void koo(){cout<<"unname::koo"<<endl;}
	int a = 10;
}

void foo() {cout<<"global::foor"<<endl;}
//int a = 20;

//Namespace 안의 함수는 다음과 같은 방법으로 호출
//1.namespace_name::식별자 ==> one::goo();
//2.using 지시어를 사용하면 이름 공간안의 특정 symbol을 바로 사용할 수 있다.
//	using one::goo;
//3. using지시어를 사용, 이름 공간안의 모든 symbol을 바로 사용
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