#include<iostream>
using namespace std;

class A
{
    public:
	    virtual void fun(int number = 10)
	    {
	        cout << "A::fun with number " << number << endl;
	    }
};

class B:public A
{
    public:
	    virtual void fun(int number = 20)
	    {
	        cout << "B::fun with number " << number << endl;
	    }
};
int main()
{
    B b;
    A &a = b;
    a.fun();

    return 0;
}
