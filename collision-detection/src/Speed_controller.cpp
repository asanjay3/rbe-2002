#include <Romi32U4.h>
#include "Encoders.h"
#include  "Speed_controller.h"

Romi32U4Motors motors;
Encoder MagneticEncoder; 

void SpeedController::Init(void)
{
    MagneticEncoder.Init();
}

void SpeedController::Run(float target_velocity_left, float target_velocity_right)
{
    if(MagneticEncoder.UpdateEncoderCounts()){
        float e_left = target_velocity_left - MagneticEncoder.ReadVelocityLeft();
        float e_right = target_velocity_right - MagneticEncoder.ReadVelocityRight();

        E_left += e_left;
        E_right += e_right;

        float u_left = Kp*e_left + Ki*E_left;
        float u_right = Kp*e_right + Ki*E_right;

        motors.setEfforts(u_left,u_right);
    }
}

boolean SpeedController::Turn(int degree, int direction)
{
    motors.setEfforts(0, 0);
    int turns = counts*(degree/180.0); //assignment 1: convert degree into counts
    Serial.println(turns);
    int count_turn = MagneticEncoder.ReadEncoderCountLeft();

    while(abs(abs(count_turn) - abs(MagneticEncoder.ReadEncoderCountLeft())) <= turns)
    {
        if(!direction) Run(50,-50);
        else Run(-50,50);
    }
    motors.setEfforts(0, 0);
    return 1;
}

boolean SpeedController::Reverse(int target_velocity, int distance) //in mm/s and cm
{
    motors.setEfforts(0, 0);
    
    uint32_t duration = 1000*((distance*10)/(float)target_velocity); //in ms
    unsigned long now = millis();

    //Serial.print(duration);
    //Serial.print('\t');
    //Serial.println(now);

    while ((unsigned long)(millis() - now) <= duration){
        Run(-target_velocity,-target_velocity);
    }
    motors.setEfforts(0, 0);
    return 1;
}

void SpeedController::Stop()
{
    motors.setEfforts(0,0);
}