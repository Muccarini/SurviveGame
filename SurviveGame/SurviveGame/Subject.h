#pragma once
#include "Observer.h"

class Subject
{
public:
	virtual ~Subject();

	virtual void subscribe(Observer* obs) = 0;
	virtual void unsubscribe(Observer* obs) = 0;

	virtual void notify() = 0;
};

