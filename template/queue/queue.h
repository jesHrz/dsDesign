#ifndef __QUEUE_H_
#define __QUEUE_H_

template<typename T>
class queue
{
public:
	virtual ~queue() {};
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual T front() const = 0;
	virtual T back() const = 0;
	virtual void pop() = 0;
	virtual void push(const T&) = 0;
	virtual void clear() = 0;
};

#endif //__QUEUE_H_
