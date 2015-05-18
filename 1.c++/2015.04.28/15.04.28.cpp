#if 0
//namespace 
//�̸� �浹�� �������� ����
//�̸� �浹�� ���ɼ��� ���� �پ���.
//������ ���� ����
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
 int a=30;
}

//unnamed namespace ��������, �����Լ�
namespace
{
 void foo(){cout<<"unnamed::foo"<<endl;}
 void koo(){cout<<"unnamed::koo"<<endl;}
// int a=10;
}
//void foo(){cout<<"global foo"<<endl;}
int a= 20;
//Namespace ���� �Լ��� ������ ���� ������� ȣ��
//1. namespace_name::�ĺ��� ==> one::goo();
//2. using ���þ ����ϸ� �̸� �������� Ư�� symbol�� �ٷ� ����� �� �ִ�.
//    using one::goo;
//3. using ���þ ���, �̸� �������� ��� symbol�� �ٷ� ����� �� �ִ�.
//    using namespace one;
void main()
{
// cout<<a<<endl;
 two::foo();
 //using namespace two;
 using two::foo;
 using one::foo;
 foo();
 koo();

 //cout<<::a<<endl;
 //foo();
 //goo();
}
#endif

#if 0
#include <iostream>
#include <stdlib.h>
using namespace std;
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
 int n=5;
 int k;
 cout<<my_pow(++n)<<endl;
 cout<<POW(++n)<<endl;
 //k=my_pow(++n);
 //k=POW(++n);
}
#endif

#if 0
#include <iostream>
using namespace std;

int main()
{
 cout<<"What is your name? ";
 char name[256];
 int age;
 cin>>name;
 cout<<"Enter the age: ";
 cin>>age;
 cout<<"Hi "<<name <<" age : "<<age<< endl;
 return 0;
}
#endif

#if 0
//Reference
//���� ������ ���� �� �ٸ� �̸�
//������ �޸� ������ ����
//�ݵ�� ����� ���ÿ� �ʱ�ȭ
//&�� �뵵
//���۷��� ������ ���� �� ���(ex : int& r = n);
//��ü(����)�� �ּҸ� ��� ���� ���(ex : cout<<&r;)
#include<iostream>
using namespace std;
void main()
{
 int n=10;
 int *p=&n;
 int& r = n;
 ++r;
 cout<<n<<endl;
 cout<<&n<<endl;
 cout<<r<<endl;
 cout<<&r<<endl;
 cout<<p<<endl;
 cout<<&p<<endl;

}
#endif

#if 0
#include<iostream>
using namespace std;
int square(int x){return x*x;}
int main()
{
 int ar[3] = {1,2,3};
 int (&r_ar)[3] = ar;

 int (&fp1)(int) = square;
 int (*fp2)(int) = square;
 cout<<"ar[0]: "<<ar[0]<<endl;
 r_ar[0]=7;
 cout<<"ar[0]: "<<ar[0]<<endl;
 cout<<"p(ar[2]): "<<fp1(ar[2])<<endl;
 return 0;
}
#endif

#if 0
//������ �ƴ� ����� ���� ���۷����� ����°͵� �����Ѱ�?
//const �̿� �� ����, �����Ϸ��� �޸� ����
#include<iostream>
using namespace std;
int main()
{
 const int &r = 7;
 cout<<&r2<<end;
}
#endif

#if 0

#include <iostream>
using namespace std;
//call by reference
void swap_r(int& x, int& y)
{
 int temp;
 temp = x;
 x=y;
 y=temp;
}
//call by value
void swap_v(int x, int y)
{
 int temp;
 temp = x;
 x=y;
 y=temp;
}
//call by pointer
void swap_p(int* x, int* y)
{
 int temp;
 temp = *x;
 *x=*y;
 *y=temp;
}
void main()
{
 int x=10, y=20;
 swap_v(x,y);
 cout<<"x: "<<x<<"y: "<<y<<endl;
 swap_p(&x,&y);
 cout<<"x: "<<x<<"y: "<<y<<endl;
 swap_r(x,y);
 cout<<"x: "<<x<<"y: "<<y<<endl;

}
#endif

#if 0
#include<iostream>
using namespace std;

typedef struct _People
{
 char name[32];
 char addr[256];
 int age;
}People;
void foo(People p)
{
 char name[] = "ö��";
 strcpy(p.name,name);
 char addr[] = "�����";
 strcpy(p.addr,addr);
 p.age=20;
}
void foo_r(People& p)
{
 char name[] = "ö��";
 strcpy(p.name,name);
 char addr[] = "��⵵";
 strcpy(p.addr,addr);
 p.age=30;
}
void main()
{
 People p={0,};
 foo(p);
 //cout<<"name: "<<p.name<<"  addr: "<<p.addr<<"  age: "<<p.age<<endl;
 foo_r(p);
 //cout<<"name: "<<p.name<<"  addr: "<<p.addr<<"  age: "<<p.age<<endl;
}

#endif

#if 0
#include <iostream>
using namespace std;
int& foo()
{
 int n=10;
 return n;
}
int goo()
{
 int n=50;
 return n;
}
void main()
{
 int& k=foo();
 k=20;
 cout<<"k: "<<k<<endl;
 goo();
 cout<<"k: "<<k<<endl;
}
#endif

#if 0
#include <iostream>
using namespace std;
//new /delete
//c++������ �������� �޸𸮸� �Ҵ��ϱ� ���� new �����ڸ� ���
// (C������ malloc()�Լ� ���)
class AAA
{
public:
 AAA(){cout<<"class AAA"<<endl;}
 ~AAA(){cout<<"bye class AAA"<<endl;}
};
void main()
{
 int *p1;
 int *p2;
 int n=20;
 p1 = new int;      //new type
 p2 = new int[n];   //new type[n]
 delete p1;
 delete [] p2;

 //2. ������ ������ 2�� �̻� delete�ϸ� �ȵ�
 //3. 0������ delete�ϴ� ���� ���ȴ�.
 int *p4 = 0;
 delete p4;

 //4. �������� ������ �迭���·� ��������
 int size;
 cin>>size;
 int* p5 = new int[size];

 delete [] p5;

 //5. ������ �迭 ���·� �Ҵ簡��
 int (*p6)[10] = new int[10][10];
 delete [] p6;

 //6. ������ �迭 �Ҵ翡���� ����
 cin>>size;
 int(*p7)[10] = new int[size][10];
 delete [] p7;
 //p7 = new int[10][size]; --> error
 
 //8.malloc ��� �� ������ ȣ�� �ȵ�
 AAA* p10 = (AAA*)malloc(sizeof(AAA));
 free(p10);

 AAA *p11 = new AAA;
 delete p11;

}
#endif

#if 0
//default parameter
//C++�Լ��� ����Ʈ �Ķ���͸� �����ϴ� ���� �����ϴ�.
//�Ķ������ ���� �������� ���� ��� ����Ʈ �� ����
//����Ʈ �Ķ���͸� ������ ���� �ݵ�� ������ �Ķ���ͺ��� ���ʴ�� ����
#include<iostream>
using namespace std;
void foo(int a, int b=1, int c=2, int d=3);

void main()
{
 foo(10,20,30,40);
 foo(10,20,30);
 foo(10,20);
 foo(10);
}
void foo(int a, int b, int c, int d)
{
 cout<<"a: "<< a<<"\tb: "<< b<< "\tc: "<< c<< "\td: "<< d<< endl;
}
#endif

#if 0
//c: ���� �̸��� ���� �Լ��� �ߺ��ؼ� ���� �� ����.
//c++: ���޵Ǵ� ������ ������ ������ type�� �ٸ��� ���� �̸��� ���� �Լ��� �ߺ��ؼ� ���� �� �ִ�.
#include<iostream>
using namespace std;
int max(int a, int b)
{
 return a>b? a:b;
}
char max(char a, char b)
{
 return a>b? a:b;
}
double max(double a, double b)
{
 return a>b? a:b;
}
int main()
{
 int a=3, b=4; char ca = 'a', cb='b';
 double da = 3.33, db= 4.3;
 cout<<max(a,b)<<endl;
 cout<<max(ca,cb)<<endl;
 cout<<max(da,db)<<endl;
 return 0;
}
#endif

#if 0
#include<iostream>
using namespace std;
//1. value�� reference�� �����ε� ���� ����
//void foo(int a) { cout<<"foo(int)"<<endl;}  //error
//void foo(int &a) { cout<<"foo(int&)"<<endl;} //error

//2. default parameter �� �����ε� �� ����
void foo(int a) { cout<<"foo(int&)"<<endl;}
void foo(int a,int b=5) { cout<<"foo(int,int)"<<endl;}

//3. ���ϰ����δ� �����ε� �� �� ����.
void foo(int a) { cout<<"foo(int&)"<<endl;}
int foo(int a) { cout<<"int foo(int&)"<<endl;}
int main()
{
 int a=10;
 int b=20;
 foo(a,b);
 return 0;
}
#endif

#if 0
#include<iostream>
// Over loading �� �Լ� ã�� ����
//1. Exactly Matching : ���޵� ���ڿ� ��Ȯ�� ��ġ�ϴ� Ÿ���� ã�´�.
//2. Promotion   : Data �ս��� ���� �������� ��ȯ
//3. Standard Conversion : ǥ�غ�ȯ
//4. �������ڸ� ���� �Լ�
using namespace std;
//void foo(int x){cout<<"foo(int x)"<<endl;} //3
//void foo(float x){cout<<"foo(float x)"<<endl;} //1
//void foo(double x){cout<<"foo(double x)"<<endl;} //2
void foo(...){cout<<"foo(...)"<<endl;} //4
void main()
{
 foo(3.4f);
}
#endif

#if 0
//C�� casting�� ����
void main()
{
 double d=3.4;
 int n1 = d;
 int n2 = (int)d;
 n1 = int(d);//�Լ��� typecasting

 int a = 10;
 char *p1 = &a;
 char *p2 = (char *)&a;
 
 const int c = 20;
 int* pc1 = &c;
 int* pc2 = (int*)(&c);
}
#endif

#if 0
#include<iostream>
using namespace std;
//static_cast : �̼����� ĳ��Ʈ�� ����
//reinterpret_cast : ��κ� ����
//const_cast : ��ü�� ��� �Ӽ��� �����Ѵ�
//dynamic_cast : RTTI(Runtime Type Identification)�� ���� ĳ����
int main()
{
 double d = 3.4;
 int n=(int)d;

 int n1=static_cast<int>(d); // Ÿ���� static_cast
 //double *p1=static_cast<double*>(&n); //�ٸ� Ÿ�Ը� ����, ���δٸ� Ÿ���� "������"�� ����
 double *p2=reinterpret_cast<double*>(&n);// �����ʹ� reinterpret_cast
 
 const int c= 10;
 //int *p3 = &c;//error
 int *p4 = const_cast<int*>(&c);

 cout<<"c: "<<c<<endl;
 cout<<"*p4: "<<*p4<<endl;
 cout<<"p4: "<<p4<<" &c: "<<&c<<endl;
 *p4 = 50;
 int i;
 i=c;
 cout<<"c: "<<c<<endl;
 cout<<"*p4: "<<*p4<<endl;
 cout<<"p4: "<<p4<<" &c: "<<&c<<endl;
 cout<<"c: "<<c<<endl;
}
#endif

#if 0
#include<iostream>
using namespace std;

class MyInt{
public:
 int Num;
};
class MyFloat{
private:
 float Real;
 friend ostream& operator<<(ostream& os, const MyFloat& c);
public:
 MyFloat(){ Real = 3.2f; }
};
ostream& operator<<(ostream& os, const MyFloat& c)
{
 return os<<c.Real;
}
int main()
{
 MyInt Num = {7};
 MyFloat Real;
 //Real = static_cast<MyFloat>(Num);
 int i=7;
 char c = 'a';
 cout<<i<<" "<<c<<endl;
 cout<<Real<<endl;
 return 0;
}
#endif

#if 0
#include <iostream>
using namespace std;//����
class MyFloat
{
public:
 float Real1, Real2;
};
class MyInt
{
public:
 int Num1, Num2;
 operator MyFloat(void) //��ȯ ������
 {
  MyFloat Float;
  Float.Real1 = static_cast<float>(Num1);
  Float.Real2 = static_cast<float>(Num2);
  return Float;
 }
};
int main()
{
 MyInt Num = {7,2};
 MyFloat Real = {0.f,};
 Real = static_cast<MyFloat>(Num);
 
 cout<<Real.Real1<<endl;
 cout<<Real.Real2<<endl;
 return 0;
}
//MyInt::operator MyFloat(void)

#endif

#if 0
#include<iostream>
using namespace std;
enum DOORSTATE{OPEN=1, CLOSE, UNKNOWN};
void DoorOpen(DOORSTATE *state)
{
 *state = OPEN;
}
void DoorClose(DOORSTATE *state)
{
 *state = CLOSE;
}
void ShowDoorState(DOORSTATE state)
{
 cout<<"Door is ";
 if(state ==OPEN)
  cout<<"Open "<<endl;
 else if(state ==CLOSE)
  cout<<"Close "<<endl;
 else
  cout<<"Unknown"<<endl;
}
int main()
{
 DOORSTATE door = UNKNOWN;
 ShowDoorState(door);
 DoorOpen(&door);
 ShowDoorState(door);
 DoorClose(&door);
 ShowDoorState(door);
 return 0;
}
#endif

#if 0
#include<iostream>
using namespace std;
struct Door
{
 enum DOORSTATE{OPEN=1, CLOSE, UNKNOWN};
 DOORSTATE state;
 void DoorOpen()
 {
  state = OPEN;
 }
 void DoorClose()
 {f
  state = CLOSE;
 }
 void ShowDoorState()
 {
  cout<<"Door is ";
  if(state ==OPEN)
   cout<<"Open "<<endl;
  else if(state ==CLOSE)
   cout<<"Close "<<endl;
  else
   cout<<"Unknown"<<endl;
 } 
};
int main()
{
 Door d1 = {Door::UNKNOWN};

 d1.ShowDoorState();
 d1.DoorOpen();
 d1.ShowDoorState();
 d1.DoorClose();
 d1.ShowDoorState();
 return 0;
}
#endif

#if 0
#include<stdio.h>
typedef struct _Rect
{
 int left;
 int top;
 int right;
 int bottom;
}Rect;

int GetArea(Rect r)
{
 return (r.right - r.left) *(r.bottom - r.top);
}
bool PtInRect(Rect r, int x, int y)
{
 if(r.left< x && r.right > x && r.top< y && r.bottom > y)
  return true;
 return false;
}
void print(Rect r)
{
 printf("[%d, %d] ~ [%d, %d]\n", r.left,r.top, r.right,r.bottom);
}
void InflateRect(Rect *r, int dx, int dy)
{
 r->right +=dx;
 r->bottom +=dy;
}
void main()
{
 Rect r = {10, 10, 20, 20};
 print(r);
 InflateRect(&r, 10, 10);
 print(r);
 int s = GetArea(r);
 if(PtInRect(r,50,50))
  printf("(15,15) is In \n");
}
#endif

#if 1

#include<iostream>

typedef class _Rect {
	int left,top,right,bottom;
public:
	_Rect();
	_Rect(int left, int top, int right, int bottom);
	int GetArea();
	bool PtInRect(int x, int y);
	void print();
	void InflateRect(int dx, int dy);
}Rect;

_Rect::_Rect()
{
	this->left = 0;
	this->right = 0;
	this->top = 0;
	this->bottom = 0;
}

_Rect::_Rect(int left, int top, int right, int bottom)
{
	this->left = left;
	this->right = right;
	this->top = top;
	this->bottom = bottom;
}

int _Rect::GetArea()
{
	return (right - left) * (bottom - top);
}

bool _Rect::PtInRect(int x, int y)
{
	if(left < x && right > x && top < y && bottom > y)
		return true;
	return false;
}
void _Rect::print()
{
	printf("[%d, %d] ~ [%d, %d]\n", left,top, right,bottom);
}
void _Rect::InflateRect(int dx, int dy)
{
	right += dx;
	bottom += dy;
}

void main()
{
	Rect r(10, 10, 20, 20);
	r.print();
	r.InflateRect(10, 10);
	r.print();
	int s = r.GetArea();
	if(r.PtInRect(15,15))
		printf("(15,15) is In \n");
}

#endif 
