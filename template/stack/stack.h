#ifndef __STACK_H_
#define __STACK_H_

template<typename T>
class stack
{
public:
	virtual ~stack() {};
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual T top() const = 0;
	virtual void pop() = 0;
	virtual void push(const T&) = 0;
	virtual void clear() = 0;
};

#endif //__STACK_H_
