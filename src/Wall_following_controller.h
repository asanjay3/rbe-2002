#ifndef WALL_FOLLOWING_CONTROLLER
#define WALL_FOLLOWING_CONTROLLER

#include <Romi32U4.h>

class WallFollowingController{
    private:
        const float Kp = 0.9; //Adapt parameters Kp and Kd until your robot consistently drives along a wall
        const float Kd = 2.2;
        float E_left = 0;
        float E_right = 0;
        float E_distance = 0;
        float prev_e_distance = 0;

    public:
        void Init(void);
        float Process(float);
        int Start(int distFromWall);  //in cm
        float MedianFilter(void); 
        float distArray[5]; 
        int i; 
        float medianVal = 0; 
        float sameValTally = 0; 
};

#endif