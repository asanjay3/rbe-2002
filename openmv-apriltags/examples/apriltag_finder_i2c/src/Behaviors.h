#ifndef BEHAVIORS
#define BEHAVIORS

#include <Romi32U4.h>

class Behaviors{
    private:
        enum ROBOT_STATE {IDLE, FIND_TAG, FOLLOW_TAG};
        ROBOT_STATE robot_state = IDLE; //initial state: IDLE
         
    public:
        void Init(void); /// a and b
        void Stop(void);
        void Run(void);
};

#endif