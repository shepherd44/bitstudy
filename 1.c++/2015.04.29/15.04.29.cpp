#if 0
#include<iostream>
#define MAX 100
using namespace std;

typedef struct _stack{
	int stack[MAX];
	int top;

	void init(){top = -1;}
	bool isfull() { return (MAX == top + 1);}
	bool isempty() { return (top == -1); }
	void push(int data) ;
	int pop();
}stack;
void _stack::push(int data)
{
	if(isfull())
	{
		cout<<"Stack is full!"<<endl;
		return;
	}
	stack[++top] = data;
}
int _stack::pop()
{
	if(isempty())
	{
		cout<<"stack is empty!!"<<endl;
		return -1;
	}
	return stack[top--];
}
void main()
{
	stack s;
	s.init();
	s.push(20);
	s.push(20);
	cout<<s.pop()<<endl;
	cout<<s.pop()<<endl;
}

#endif

#if 0
#include <stdio.h>
int main()
{
	int kor, eng, math, total = 0;
	double aver = 0.0f;
	printf("국어, 영어, 수학: ");
	scanf("%d %d %d", &kor, &eng, &math);

	total = kor + eng + math;
	aver = total /3;
	printf("국어 영어 수학 총점 평균 \n");
	printf("%4d %4d %4d %4d %5.2lf \n", kor, eng, math, total, aver);
	return 0;
}
#endif

#if 0
#include <stdio.h>
int main()
{
	int kor[50], eng[50], math[50], total[50] = {0,};
	double aver[50] = {0.0f, };
	int rank[50] ={0, };

	int count, i;
	printf("학생수: ");
	scanf("%d", &count);

	i = 0;
	while(i<count)
	{
		printf("%d번 학생 (국어 영어 수학): ", i+1);
		scanf("%d %d %d", kor+i,eng+i,math+i);
		i++;
	}
	i = 0;
	while(i<count)
	{
		total[i] = kor[i] + eng[i] + math[i];
		aver[i] = total[i] / 3;
		i++;
	}
	for(i=0;i<count;i++)
		for(int j=0;j<count;j++)
			if(aver[i] <= aver[j])
				rank[i]++;
	i=0;
	while(i<count)
	{
		printf("국어 영어 수학 총점 석차 평균[%d] \n", i+1);
		printf("%4d %4d %4d %4d %4d %5.2lf \n", kor[i],eng[i],math[i], total[i], rank[i], aver[i]);
		i++;
	}
	return 0;
}
#endif

#if 0
#include <stdio.h>

void Input_count(int * count)
{
	printf("학생수: ");
	scanf("%d", count);
}
void Input_score(int *count, int *kor, int *eng, int *math)
{
	int i = 0;
	while(i<*count)
	{
		printf("%d번 학생 (국어 영어 수학): ", i+1);
		scanf("%d %d %d", kor+i,eng+i,math+i);
		i++;
	}
}
void calc_total(int *count, int *kor, int *eng, int *math, int *total, double* aver)
{
	int i = 0;
	while(i < *count)
	{
		total[i] = kor[i] + eng[i] + math[i];
		aver[i] = total[i] / 3;
		i++;
	}
}
void calc_rank(int *count, int *total, double * aver, int *rank)
{
	for(int i=0;i<*count;i++)
		for(int j=0;j<*count;j++)
			if(aver[i] <= aver[j])
				rank[i]++;
}
void display(int *count, int *kor, int *eng, int *math, int *total, double *aver, int *rank)
{
	int i=0;
	while(i<*count)
	{
		printf("국어 영어 수학 총점 석차 평균[%d] \n", i+1);
		printf("%4d %4d %4d %4d %4d %5.2lf \n", kor[i],eng[i],math[i], total[i], rank[i], aver[i]);
		i++;
	}
}
int main()
{
	int kor[50], eng[50], math[50], total[50] = {0,};
	double aver[50] = {0.0f, };
	int rank[50] ={0, };
	int count;

	Input_count(&count);
	Input_score(&count, kor, eng, math);
	calc_total(&count, kor, eng, math, total, aver);
	calc_rank(&count, total, aver, rank);
	display(&count, kor, eng, math, total, aver, rank);
	return 0;
}
#endif

#if 0
#include <stdio.h>
#include <windows.h>

#define MAX 50
typedef struct _Student {
	int kor, eng, math, total;
	double aver;
	int rank;

} Student, *PStudent;

void init(Student *stu, int *count)
{
	int i = 0;
	memset(stu, 0, sizeof(Student)*(*count));
}
void Input_count(Student* &stu, int *count)
{
	printf("학생수: ");
	scanf("%d", count);
	stu = (Student *)malloc(sizeof(Student)*(*count));
	//stu = (Student *)calloc(count, sizeof(Student)); // calloc으로 초기화 가능
	init(stu, count);
}
void Input_score(Student *stu, int *count)
{
	int i = 0;
	while(i < *count)
	{
		printf("%d번 학생 (국어 영어 수학): ", i+1);
		scanf("%d %d %d", &((stu+i)->kor),&((stu+i)->eng),&((stu+i)->math));
		i++;
	}
}
void calc_total(Student *stu, int *count)
{
	int i = 0;
	while(i < *count)
	{
		(stu+i)->total = (stu+i)->kor + (stu+i)->eng + (stu+i)->math;
		(stu+i)->aver = (stu+i)->total / 3;
		i++;
	}
}
void calc_rank(Student *stu, int *count)
{
	for(int i=0;i<*count;i++)
		for(int j=0;j<*count;j++)
			if((stu+i)->aver <= (stu+j)->aver)
				(stu+i)->rank++;
}
void display(Student *stu, int *count)
{
	int i=0;
	while(i<*count)
	{
		printf("국어 영어 수학 총점 석차 평균[%d] \n", i+1);
		printf("%4d %4d %4d %4d %4d %5.2lf \n", (stu+i)->kor, (stu+i)->eng, (stu+i)->math, (stu+i)->total, (stu+i)->rank, (stu+i)->aver);
		i++;
	}
}

void delete_stu(Student *s)
{
	free(s);
}
int main()
{
	Student *s;
	int count = 0;

	Input_count(s, &count);
	Input_score(s, &count);
	calc_total(s, &count);
	calc_rank(s, &count);
	display(s, &count);
	delete_stu(stu);
	return 0;
}
#endif

#if 0
#include <stdio.h>
#include <windows.h>

#define MAX 50
typedef struct _Student {
	int kor, eng, math, total;
	double aver;
	int rank;
} Student, *PStudent;

typedef struct _School {
	Student *stu;
	int count;

	void init_student();
	void Input_count();
	void Input_score();
	void calc_total();
	void calc_rank();
	void display();
	void delete_stu();

}School, *pSchool;

int main()
{
	School s;
	int count = 0;

	s.Input_count();
	s.Input_score();
	s.calc_total();
	s.calc_rank();
	s.display();
	s.delete_stu();
	return 0;
}

void _School::init_student()
{
	memset(stu, 0, sizeof(Student)*(count));
}
void _School::Input_count()
{
	printf("학생수: ");
	scanf("%d", &count);
	stu = new Student[count];
	init_student();
	
}
void _School::Input_score()
{
	int i = 0;
	while(i < count)
	{
		printf("%d번 학생 (국어 영어 수학): ", i+1);
		scanf("%d %d %d", &((stu+i)->kor),&((stu+i)->eng),&((stu+i)->math));
		i++;
	}
}
void _School::calc_total()
{
	int i = 0;
	while(i < count)
	{
		(stu+i)->total = (stu+i)->kor + (stu+i)->eng + (stu+i)->math;
		(stu+i)->aver = (stu+i)->total / 3;
		i++;
	}
}
void _School::calc_rank()
{
	for(int i=0;i<count;i++)
		for(int j=0;j<count;j++)
			if((stu+i)->aver <= (stu+j)->aver)
				(stu+i)->rank++;
}
void _School::display()
{
	int i=0;
	while(i<count)
	{
		printf("국어 영어 수학 총점 석차 평균[%d] \n", i+1);
		printf("%4d %4d %4d %4d %4d %5.2lf \n", (stu+i)->kor, (stu+i)->eng, (stu+i)->math, (stu+i)->total, (stu+i)->rank, (stu+i)->aver);
		i++;
	}
}

void _School::delete_stu()
{
	delete stu;
}
#endif

#if 0
#include<iostream>
//version 1
//문제점이 많은 코드
using namespace std;

int buff[10];
int index = 0;

void push(int a){buff[index++] = a;}
int pop() { return buff[--index]; }
int main()
{
	
}

#endif

#if 0

#include<iostream>
//version 2
//타입정의
using namespace std;
typedef struct _Stack{
int buff[10];
int index;
} Stack, *PStack;

void init(Stack *s) { s->index = 0;}
void push(Stack *s, int a){s->buff[s->index++] = a;}
int pop(Stack *s) { return s->buff[--(s->index)]; }
int main()
{
	Stack s;
	
	init(&s);
	push(&s, 10);
	push(&s, 20);
	cout<<pop(&s)<<endl;
	cout<<pop(&s)<<endl;
}

#endif

#if 0

#include<iostream>
//version 3
//함수와 data를 묶어서 type을 만듬
using namespace std;
typedef struct _Stack{
int buff[10];
int index;

void init();
void push(int a);
int pop();
} Stack, *PStack;

void _Stack::init() { index = 0;}
void _Stack::push(int a){buff[index++] = a;}
int _Stack::pop() { return buff[--(index)]; }
int main()
{
	Stack s;
	
	s.init(&s);
	s.push(&s, 10);
	s.push(&s, 20);
	cout<<s.pop(&s)<<endl;
	cout<<s.pop(&s)<<endl;
}

#endif

#if 0

#include<iostream>
//version 4
//외부에서 구조체의 멤버에 쉽게 접근이 가능하므로 위험
//멤버 은닉 필요

using namespace std;

typedef struct _Stack{
private:
	int buff[10];
	int index;
public:
	void init();
	void push(int a);
	int pop();
} Stack, *PStack;

void _Stack::init() { index = 0;}
void _Stack::push(int a){buff[index++] = a;}
int _Stack::pop() { return buff[--(index)]; }

int main()
{
	Stack s;
	
	s.init(&s);
	s.push(&s, 10);
	s.push(&s, 20);
	cout<<s.pop(&s)<<endl;
	cout<<s.pop(&s)<<endl;
}

#endif

#if 0

#include<iostream>
//version 5
//생성자로 초기화

using namespace std;

typedef struct _Stack{
private:
	int buff[10];
	int index;
public:
	_Stack();
	void init();
	void push(int a);
	int pop();
} Stack, *PStack;

_Stack::_Stack()
{
	init();
	cout<<"struct constructor"<<endl;
}
void _Stack::init() { index = 0;}
void _Stack::push(int a){buff[index++] = a;}
int _Stack::pop() { return buff[--(index)]; }

int main()
{
	Stack s;
	
	s.push(10);
	s.push(20);
	cout<<s.pop()<<endl;
	cout<<s.pop()<<endl;
}

#endif

#if 0

#include<iostream>
//version 6
//class로 바꾸기

using namespace std;

typedef class _Stack{
private:
	int buff[10];
	int index;
public:
	_Stack();
	void init();
	void push(int a);
	int pop();
} Stack, *PStack;

_Stack::_Stack()
{
	init();
	cout<<"class constructor"<<endl;
}
void _Stack::init() { index = 0;}
void _Stack::push(int a){buff[index++] = a;}
int _Stack::pop() { return buff[--(index)]; }

int main()
{
	Stack s;
	
	s.push(10);
	s.push(20);
	cout<<s.pop()<<endl;
	cout<<s.pop()<<endl;
}

#endif

#if 0
#include <iostream>

using namespace std;

typedef class _Point{
	int x;
	int y;
public:
	_Point(int x = 0, int y = 0)
	{
		this->x = x;
		this->y = y;
	}
	void Print()
	{
		cout<<"x: "<<x<<" y: "<<y<<endl;
	}
}Point, *PPoint;

void main()
{

}
#endif

#if 0
#include<iostream>
using namespace std;

//1.일반 함수 포인터에 멤버함수의 주소를 담을 수 있는가
//2.일반 함수 포인터에 static 멤버변수를 만들 수 있는가
//3.멤

typedef class _Point{
	int x;
	int y;
public:
	//static int s;
public:
	_Point(int x = 0, int y = 0, int s = 0)
	{
		this->x = x;
		this->y = y;
		//this->s = s;
	}
	void Print()
	{
		cout<<"x: "<<x<<" y: "<<y<<endl;
	}
	void foo()
	{
		cout<<"foo"<<x<<" y: "<<y<<endl;
	}
	static void goo()
	{
		//cout<<"goo"<<s<<endl;
		cout<<"goo"<<endl;
	
	}
}Point, *PPoint;

void g_foo(){cout<<g_foo<<endl;}

void main()
{
	//1
	//Point::goo();
	//Point::foo(); //error
	//2
	Point p;
	p.foo();
	p.goo();
	//3
	void(*fp)() = g_foo;
	fp();

	//static 멤버 함수 함수포인터 사용
	fp = Point::goo;
	fp();
	//일반 멤버 함수는 포인터로 사용 가능?
	void (Point::*fp2)() = &Point::foo;
	//fp = p.foo();
	//fp = Point::foo();
	(p.*fp2)();

}

#endif

#if 0
//callback 함수 호출
#include<iostream>

using namespace std;

class Good;

typedef void(*CALLPROC)(void *param);
typedef void((Good::*CALLPROC2))(void *param);
void setFunction(int n, CALLPROC f, void *param)
{
	for(int i=0;i<n;i++)
	{
		(*f)(param);
	}
}

void foo(void *param)
{
	char *msg = (char *)param;
	cout<<msg<<endl;
}
class Good{
public:
	static void goo(void* param)
	{
		char *msg = (char *)param;
		cout<<msg<<endl;
	}
	void foo(void* param)
	{
		char *msg = (char *)param;
		cout<<msg<<endl;
	}
};
void setFunction2(int n, CALLPROC2 f, void *param)
{
	Good g;
	for(int i=0;i<n;i++)
	{
		(g.*f)(param);
	}
}
void main()
{
	setFunction(5,foo,"Hello");
	cout<<endl;
	setFunction(5,&Good::goo,"Hello");
	cout<<endl;
	//void (Point::*fp2)() = &Point::foo;
	//fp = p.foo();
	//fp = Point::foo();
	//(p.*fp2)();
	setFunction2(5,&Good::foo,"Hello");
}

#endif

#if 0
//상속, 오버라이딩
#include<iostream>
using namespace std;

class Base {

public:
	int xxx;
	void foo(){cout<<"Base::foo()"<<endl;}
	void show(){cout<<"xxx: "<<xxx<<endl;}
};

class D: public Base
{
public:
	int yyy;
	void goo(){cout<<"D::goo()"<<endl;}
	void show(){
		Base::show();
		cout<<"yyy: "<<yyy<<endl;}

};

void main()
{
	D d;
	d.xxx = 10;
	d.yyy = 20;
	d.show();
	d.foo();
	d.goo();
}
#endif

#if 1
//	상속방식		private		protected		public
//접근 지정자	
//private			--			--				--
//protected			private		protected		protected
//public			private		protected		public

#include<iostream>
using namespace std;

class Base {

private:
	int one;
protected: 
	int two;
public:	
	int three;
};

class D: public Base
{
public:
	int d;
	void foo()
	{
		//one; // error private
		two;
		three;
	}
};

class E : public D
{
public:
	int e;
	void set()
	{
		d = 3;
		two = 5;
		three = 5;
	}
};

void main()
{
	E e;
	e.three = 4;
	//e.two = 7;	//error protected
}
#endif