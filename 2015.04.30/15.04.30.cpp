#if 0
#include<iostream>

using namespace std;
//������ ȣ�� ����
//1. �޸� �Ҵ�
//2. �θ��� ������ ȣ��
//3. �ڽ��� ������ ȣ��
//4. �ڽ��� �Ҹ��� ȣ��
//5. �θ��� �Ҹ��� ȣ��
class Base{
	int x;
public:
	Base() {cout<<"Base::Base()"<<endl;}
	Base(int n)
	{
		x = n;
		cout<<"Base::Base(int)"<<endl;
	}
	~Base()
	{
		cout<<"Base::~Base()"<<endl;
	}
	void show(){cout<<x<<endl;}
};

class D : public Base {
public:
	int y;
	D(){cout<<":D:D()"<<endl;}
	D(int n):Base(n){
		//Base::Base(n);
		cout<<"D:D(int)"<<endl;
	}
	~D()
	{
		cout<<"D::~D()"<<endl;
	}
};
void main()
{
	//D d(3);
	D d;
	d.show();
	d.y = 10;
}

#endif

#if 0
#include <iostream>
//�θ��� �����ʹ� �ڽ��� �ּҰ��� ���� �� �ִ�.
using namespace std;

class Animal{
public:
	void Cry(){cout<<"Animal::Cry()"<<endl;}
};

class Dog: public Animal
{
public:
	void Cry(){cout<<"Dog::Cry()"<<endl;}
};



void main()
{
	Animal animal;
	Dog dog;
	Animal* pa = &dog;

	animal.Cry();
	dog.Cry();
	pa->Cry();
	((Dog *)pa)->Cry();
}
#endif

#if 0
#include <iostream>
//virtual
using namespace std;

class Animal{
public:
	virtual void Cry(){cout<<"Animal::Cry()"<<endl;}
};

class Dog: public Animal
{
public:
	void Cry(){cout<<"Dog::Cry()"<<endl;}
};

class Cat: public Animal{
public:
	void Cry(){cout<<"Cat::Cry()"<<endl;}
};


void main()
{
	Animal animal;
	Dog dog;
	Cat cat;
	Animal* pa = &dog;

	animal.Cry();
	dog.Cry();
	//((Dog *)pa)->Cry();
	pa->Cry();
	pa = &cat;
	pa->Cry();
}
#endif

#if 0
#include<iostream>
using namespace std;

class A{
public:
	int x;
	A():x(10){}
};

class B : public A{
public:
	int y;
	B():y(20){}
};

void foo(A* p, int s)
{
	for(int i=0;i<s;i++)
	{
		cout<<p[i].x<<endl;
	}
}

void main()
{
	B b[10];
	for(int i=0; i<10; i++)
	{
		cout<<b[i].x<<endl;
	}
	cout<<"========================================"<<endl;
	foo(b, 10);
}

#endif

#if 0
#include<iostream>
using namespace std;
//binding: �Լ� ȣ��� ���� �Լ��� �����ϴ� ���
//1. static binding(Compile-Time Binding, Early Binding)
//	: ������ �ð��� ȣ��� �Լ� ����, ��ü�� type�� ���� ����
//2. Dynamic binding(Run-Time Binding, Late Binding)
//3. C++�� �⺻������ static binding�� �����Ѵ�.
//4. Dynamic binding�� �����Ϸ��� virtual Ű���� ���

//dynamic binding�� �����ϴ� ��ü�� ù��° ����� �����Լ����̺�(vfptr)�� �����ȴ�.
//�ش� class�� ��ӹ޴� class�� �̿��� ��ü ���� vfptr ����
//�� ���̺� ������ �޸� ������� �߻�
class AAA {
public:
	int x;
	AAA():x(10){}
	virtual void foo(){cout<<"AAA::foo()"<<endl;}
	virtual void goo(){cout<<"AAA::goo()"<<endl;}
	virtual void hoo(){cout<<"AAA::hoo()"<<endl;}
	virtual void zoo(){cout<<"AAA::zoo()"<<endl;}
};

class BBB: public AAA {
public:
	int y;
	BBB():y(10){}
	void foo(){cout<<"BBB::foo()"<<endl;}
	void zoo(){cout<<"BBB::goo()"<<endl;}
	void test(){cout<<"BBB::test()"<<endl;}
};

void main()
{
	AAA* p1 = new AAA;
	AAA* p2 = new BBB;
	AAA p3;

	cout<<sizeof(AAA)<<", "<<sizeof(p1)<<endl;
	cout<<sizeof(BBB)<<", "<<sizeof(p2)<<endl;
	cout<<sizeof(p3)<<endl;

	p1->foo();
	p1->goo();
	p1->hoo();
	p1->zoo();

	p2->foo();
	p2->goo();
	p2->hoo();
	p2->zoo();

}

#endif

#if 0
#include<iostream>
using namespace std;

//�߻�Ŭ����
// �߻�Ŭ������ ��üȭ �Ұ���(=���� ���� �Ұ�)
class Shape{
public:
	int x;
	virtual void Draw() = 0;	//���� �����Լ�
	void foo(){}
};

class Rect: public Shape
{
public:
	int y;
	virtual void Draw()
	{
		cout<<"Draw Rect..."<<endl;
	}
};

void main()
{
	Shape *p = new Rect;
	p->Draw();
}

#endif

#if 0
#include<iostream>
using namespace std;

//dynamic ���ε� �� �켱 
//������ ���� ���ε��̱� ������ a=10�� ���õǼ� �Ѿ��.
class AAA{
public:
	virtual void foo(int a=10)	
	{
		cout<<"AAA:foo("<<a<<")"<<endl;
	}
};

class BBB: public AAA{
public:
	virtual void foo(int a=20)
	{
		cout<<"BBB::foo("<<a<<")"<<endl;
	}
};

void Test(AAA v, AAA & r, AAA *p)
{
	v.foo();
	r.foo();
	p->foo();
}

void main()
{
	BBB b;
	Test(b, b, &b);
}

#endif

#if 0
#include<iostream>
using namespace std;

class Horse{
public:
	virtual void Run(void){ cout<<"���� �޸���..."<<endl;}
	virtual ~Horse(){}
};

class Pegasus: public Horse
{
public:
	virtual void Fly(void){cout<<"�䰡������ ����..."<<endl;}
	void Run(void){cout<<"�䰡������ �޸���..."<<endl;}
	~Pegasus(){}

};

void main()
{
	Horse *a[5];
	Pegasus *p;
	int choice;

	for(int i = 0; i<5; i++)
	{
		cout<<"�� 1, �䰡������: 2=>";
		cin>>choice;
		if(choice == 1)
			a[i] = new Horse;
		else
			a[i] = new Pegasus;
	}

	for(int i = 0; i<5; i++)
	{
		p = dynamic_cast<Pegasus*> (a[i]);
		if(p)
			p->Fly();
		else
			cout<<"���� ���� �����"<<endl;
	}
	for(int i=0;i<5;i++)
		delete a[i];
}

#endif

#if 0
#include<iostream>
using namespace std;

class Animal {
public:
	int x;
	virtual void Run(void){};
	virtual void Fly(void){};
	virtual ~Animal(){}
};

class Horse: virtual public Animal{

public:
	Horse(){}
	void Run(void) {cout<<"���� �޸���..."<<endl;}
	~Horse(){}
};

class Bird : virtual public Animal{

public:
	Bird(){}
	void Fly(void){cout<<"���� ����..."<<endl;}
	~Bird(){}
};

class Pegasus: public Horse, public Bird
{
public:
	void Fly(void){cout<<"�䰡������ ����..."<<endl;}
	void Run(void){cout<<"�䰡������ �޸���..."<<endl;}
	~Pegasus(){}

};

void main()
{
	Animal *a[3];
	int choice;
	for(int i = 0; i<3; i++)
	{
		cout<<"��: 1 ��:2 �䰡����: 3 => ";
		cin>>choice;
		if(choice == 1)
			a[i] = new Horse;
		else if(choice == 2)
			a[i] = new Bird;
		else if(choice == 3)
			a[i] = new Pegasus;

	}
	for(int i=0; i<3; i++)
	{
		a[i]->Run();
		a[i]->Fly();
	}
	for(int i=0; i<3; i++)
		delete a[i];

}
#endif

#if 0
#include<iostream>
using namespace std;
//�����ڸ� �̿��� �Լ� ȣ��
//�����ڵ� �Լ���.
//User type���� �����ڸ� ����� �� �ִ�.
// + : operator+()

class Int32{

	int data;
public:
	Int32(int n=0):data(n){}
	int GetData()const{return data;}
	Int32(const Int32& r)
	{data = r.data;}
	void show()
	{
		cout<<"data: "<<data<<endl;
	}
	const Int32 operator+(const Int32& r)
	{
		return Int32(data+r.data);
	}
	const Int32 operator+(int i)
	{
		return Int32(this->data + i);
	}
	const Int32 operator-(const Int32& r)
	{
		return Int32(data-r.data);
	}
	const Int32 operator*(const Int32& r)
	{
		return Int32(data*r.data);
	}
	const Int32 operator/(const Int32& r)
	{
		return Int32(data/r.data);
	}
	
};

const Int32 operator+(int i, const Int32& r)
{
	return Int32(r.GetData() + i);
}
void main()
{
	Int32 a(10), b(20);
	Int32 c;
	a.show();
	b.show();
	c = a+b;
	c.show();
	c = a-b;
	c.show();
	c = a*b;
	c.show();
	c = a/b;
	c.show();
	c = a+123;
	c.show();
	c = 50 + a;
	c.show();
	c = 100+a;
	c.show();
}
#endif

#if 0
#include<iostream>
using namespace std;
//++a : operator++()
//a++ : operator++(int)

class Int32{

	int data;
public:
	Int32(int n=0):data(n){}
	int GetData()const{return data;}
	Int32(const Int32& r)
	{data = r.data;}
	void show()
	{
		cout<<"data: "<<data<<endl;
	}
	Int32& operator++()
	{
		data++;
		return *this;
	}
	Int32& operator++(int)
	{
		
		Int32 temp(*this);
		data++;
		return temp;
		//data++;
		//return *this;
	
	}
	
};

void main()
{
	Int32 a(10), b(20);
	Int32 c;
	
	a++;//11
	a.show();
	b = ++a;//12,12
	b.show();
	a++;//13
	b = a++;//14,13
	b.show();
	a.show();
	//a++++;//16
	a.show();
	++++a;//18
	a.show();
	//int y =2;
	//cout<<y++++;

}
#endif

#if 0
#include<iostream>
using namespace std;

class complex{
	double real;
	double image;
public:
	complex (double _r=0, double _i=0):real(_r), image(_i){}
	void print()
	{
		cout<<real<<"+"<<image<<"i"<<endl;
	}
	const complex operator+(const complex& b)
	{
		complex temp(real + b.real, image + b.image);
		return temp;
	}

	friend bool operator ==(complex& a, complex& b);
	friend bool operator !=(complex& a, complex& b);
};

bool operator ==(complex& a, complex& b)
{
	if((a.real == b.real) && (a.image == b.image))
		return true;
	else
		return false;
}
bool operator !=(complex& a, complex& b)
{
	if((a.real != b.real) || (a.image != b.image))
		return true;
	else
		return false;
}
void main()
{
	complex c1(1.2, 2.3);
	complex c2(2.3, 3.2);
	complex c3;
	c3 = c1 + c2;
	c3.print();
	if(c1==c2)
		cout<<"t"<<endl;
	else if(c1 != c2)
		cout<<"f"<<endl;
	c2 = c2 + complex(-1.1, -0.9);
	c1.print();
	c2.print();
	if(c1==c2)
		cout<<"t"<<endl;
	else if(c1 != c2)
		cout<<"f"<<endl;
}
#endif

#if 0
//cout ��� ���� ��ȯ
#include<iostream>
using namespace std;

void main()
{
	int c = 'A';
	cout<<hex<<c<<endl;
	cout<<10<<endl;
	cout<<oct<<10<<endl;
}

#endif

#if 0

//������ ostream ����
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

namespace std{
	class ostream{
	public:
		enum Type{DEC, HEX, OCT};
		void SetType(Type t)
		{
			type = t;
		}
		ostream(Type t = DEC):type(t){}
		ostream& operator<<(const char *str)
		{
			if(type == DEC)
				printf("%s", str);
			else if(type == HEX)
			{
				int len = strlen(str);
				for(int i = 0; i<len; i++)
					printf("%x", str[i]);
			}
			else
			{
				int len = strlen(str);
				for(int i=0; i<len; i++)
					printf("%o", str[i]);
			}
			return *this;
		}
		ostream& operator<<(int i)
		{
			if(type == DEC)
				printf("%d", i);
			else if(type == HEX)
				printf("%x", i);
			else
				printf("%o", i);		
			return *this;
		}
		ostream operator<<(ostream& (*fp)(ostream &)) { return fp(*this); }

	private:
		Type type;
	};

	ostream& endl(ostream& out)
	{
		printf("\n");
		return out;
	}
	ostream& dec(ostream& out)
	{
		out.SetType(ostream::DEC);
		return out;
	}
	ostream& hex(ostream& out)
	{
		out.SetType(ostream::HEX);
		return out;
	}
	ostream& oct(ostream& out)
	{
		out.SetType(ostream::OCT);
		return out;
	}

	ostream cout;
}
using namespace std;
void main()
{
	int c = 'A';
	cout<<hex<<c<<endl;
	cout<<dec<<c<<endl;
	cout<<oct<<c<<endl;


}
#endif