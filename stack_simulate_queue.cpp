#include<stdio.h>
#include<stack>
using namespace std;

template <class T>
class my_queue
{
    public:
        my_queue();
        int size();
	bool empty();
	void push(T value);
        T front();
	void pop();

    private:
        stack<T> s1, s2;
};

template <class T>
my_queue<T>::my_queue()
{
    printf("my_queue construct!\n");
}
template <class T>
int my_queue<T>::size()
{
    return s1.size() + s2.size();
}
template <class T>
bool my_queue<T>::empty()
{
    if (size() == 0)
        return true;
    else
	return false;
}
template <class T>
void my_queue<T>::push(T value)
{
    s2.push(value);
}
template <class T>
T my_queue<T>::front()
{
    if (!s1.empty())
        return s1.top();
    else
    {
       while (!s2.empty())
       {
           s1.push(s2.top());
	   s2.pop();
       }
       return s1.top();
    }
}
template <class T>
void my_queue<T>::pop()
{
    if (s1.empty())
    {
        while(!s2.empty())
	{
	    s1.push(s2.top());
	    s1.pop();
	}
    }
    s1.pop();
}
int main()
{
    my_queue<int> queue;
    for (int i = 0; i < 10; i++)
    {
        queue.push(i);
    }
    printf("the size of queue is %d\n", queue.size());

    while (!queue.empty())
    {
        printf("%d ", queue.front());
        queue.pop();
    }
    printf("\n");
    return 0;
}
