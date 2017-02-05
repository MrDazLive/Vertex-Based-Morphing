#pragma once

class Time final {
public:
	static void		Initialise		();
	static void		OnUpdate		();

	static double	getTime			();
	static double	getDeltaTime	();
private:
					Time			() = delete;

	static double	m_time;
	static double	m_deltaTime;
};