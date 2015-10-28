//
//  Robot.cpp
//  Robotics Navigation
//
//  Created by James Landess on 10/24/15.
//  Copyright © 2015 James Landess. All rights reserved.
//

#include "Robot.hpp"
namespace Robotics
{
    Robot::Robot(const glm::vec2 & location):Robot()
    {
        this->CurrentLocation = location;
    }
    
    void Robot::SetSpeed(const float &speed)
    {
        this->Speed = speed;
    }
    
    const float & Robot::GetSpeed() const
    {
        return this->Speed;
    }
    
    void Robot::SetLocation(const glm::vec2 &location)
    {
        this->CurrentLocation = location;
    }
    
    Robot::Robot():UltrasonicResolution(0.11811),InfaredResolution(0.11811)
    {
        //i'm going to aribrarily assign them for now, but later on we'll coorelate each index with the valid pin number or address
        
        //the first sensor shall be the one facing the northern wall
        UltrasonicSensors[0].SetDirection({0,0,1});
        
        //the second sensor shall be the one facing the southern wall
        UltrasonicSensors[1].SetDirection({0,0,-1});
        
        //the third sensor shall be the one facing the right wall
        UltrasonicSensors[2].SetDirection({1,0,0});
        
        //the fourth sensor shall be the one facing the left wall
        UltrasonicSensors[3].SetDirection({-1,0,0});
        
        
        InfaredSensors[0].SetDirection({0,0,1});
        InfaredSensors[1].SetDirection({0,0,-1});
        InfaredSensors[2].SetDirection({1,0,0});
        InfaredSensors[3].SetDirection({-1,0,0});
        
        InfaredSensors[0].SetResolution(this->InfaredResolution);
        InfaredSensors[1].SetResolution(this->InfaredResolution);
        InfaredSensors[2].SetResolution(this->InfaredResolution);
        InfaredSensors[3].SetResolution(this->InfaredResolution);
        
        //based upon the specs of the HC SR04 Ultrasonic Sensor the resolution is set to 0.3 cm
        //0.3 cm -> 0.11811 inches
        UltrasonicSensors[0].SetResolution(this->UltrasonicResolution);
        UltrasonicSensors[1].SetResolution(this->UltrasonicResolution);
        UltrasonicSensors[2].SetResolution(this->UltrasonicResolution);
        UltrasonicSensors[3].SetResolution(this->UltrasonicResolution);
        
        //this->CurrentLocation = {87,5};
        
    }
    
    const glm::vec2 & Robot::GetCurrentLocation() const
    {
        return this->CurrentLocation;
    }
    
    void Robot::SetInfaredResolution(const float &resolution)
    {
        this->InfaredResolution = resolution;
        
        InfaredSensors[0].SetResolution(this->InfaredResolution);
        InfaredSensors[1].SetResolution(this->InfaredResolution);
        InfaredSensors[2].SetResolution(this->InfaredResolution);
        InfaredSensors[3].SetResolution(this->InfaredResolution);
    }
    
    void Robot::SetUltrasonicResolution(const float &resolution)
    {
        this->UltrasonicResolution = resolution;
        
        UltrasonicSensors[0].SetResolution(this->UltrasonicResolution);
        UltrasonicSensors[1].SetResolution(this->UltrasonicResolution);
        UltrasonicSensors[2].SetResolution(this->UltrasonicResolution);
        UltrasonicSensors[3].SetResolution(this->UltrasonicResolution);
    }
    
    const float & Robot::GetUltrasonicResolution() const
    {
        return this->UltrasonicResolution;
    }
    
    const float & Robot::GetInfaredResolution() const
    {
        return this->InfaredResolution;
    }
    
    
    Robot & Robot::Translate(const glm::vec2 &translation)
    {
        
        float theta = glm::acos(glm::dot(this->CurrentLocation, translation)/(glm::length(this->CurrentLocation)*glm::length(translation)));
        this->CurrentLocation+=translation;
        return (*this);
    }
    
    
    
}