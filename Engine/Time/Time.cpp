#include "Time.h"

#include <ctime>

double Time::m_time			= 0.0f;
double Time::m_deltaTime	= 0.0f;

void Time::Initialise() {
	m_time = getTime();
}

void Time::OnUpdate() {
	double now = getTime();
	m_deltaTime = now - m_time;
	m_time = now;
}

double Time::getTime() {
	return ((double)clock())/CLOCKS_PER_SEC;
}

double Time::getDeltaTime() {
	return m_deltaTime;
}