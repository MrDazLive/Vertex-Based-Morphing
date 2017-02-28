#pragma once

class Time final {
public:
    static void     Initialise      ();
    static void     OnUpdate        ();

    static float    getTime         ();
    static float    getDeltaTime    ();
private:
                    Time            () = delete;

    static float    m_time;
    static float    m_deltaTime;
};