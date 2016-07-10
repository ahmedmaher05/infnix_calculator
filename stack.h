#include <assert.h>
const int maxstacksize=1000;
template <class stackelemtype>
class Stack
{
    private:

        stackelemtype stackarray[maxstacksize];


    public:
        int topindex;
        Stack();
        void push(stackelemtype e);
        stackelemtype pop();
        stackelemtype top();
        bool isempty();
        bool isfull();
};

template <class stackelemtype>
Stack<stackelemtype>::Stack()

{
	topindex=-1;
}

template <class stackelemtype>
void Stack<stackelemtype>::push(stackelemtype e)
{
	++topindex;
	assert(topindex<maxstacksize);
    stackarray[topindex]=e;
}

template <class stackelemtype>
stackelemtype Stack <stackelemtype>::pop()
{
    assert(topindex>=0);
    int temp=topindex;
    --topindex;
    return stackarray[temp];
}

template <class stackelemtype>
stackelemtype Stack <stackelemtype>::top()
{
    assert(topindex>=0);
    return stackarray[topindex];
}

template <class stackelemtype>
bool Stack <stackelemtype>::isempty()
{
    if(topindex==-1)
        return true;
    else
        return false;
}

template <class stackelemtype>
bool Stack <stackelemtype>::isfull()
{
    if(topindex==maxstacksize-1)
        return true;
    else
        return false;
}






