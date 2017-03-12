#include "Time.h"

#include <ctime>

float Time::m_time          = 0.0f;
float Time::m_deltaTime     = 0.0f;

void Time::Initialise() {
    m_time = getTime();
}

void Time::OnUpdate() {
    float now = getTime();
    m_deltaTime = now - m_time;
    m_time = now;
}

float Time::getTime() {
    return ((float)clock())/CLOCKS_PER_SEC;
}

float Time::getDeltaTime() {
    return m_deltaTime;
}