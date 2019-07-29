#pragma once
#include "Observer.h"
class Subject {
	virtual ~Subject() {};


	virtual void subscribe(Observer * o) = 0;
	virtual void unsuscribe(Observer * o) = 0;

	virtual void notify() = 0;

};

