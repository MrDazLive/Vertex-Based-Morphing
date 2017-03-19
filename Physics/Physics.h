#pragma once

class Physics final {
public:
    static void         Initialise  (int*, char*[]);
    static void         Loop        ();
    static void         Quit        ();
private:
                        Physics     () = delete;
};