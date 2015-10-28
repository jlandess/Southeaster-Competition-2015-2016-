

#include "Navigator.hpp"
#include "RayTracing.h"

/*
 The MIT License (MIT)
 
 Copyright (c) [2015] [James L. Landess]
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

namespace Robotics
{
    Navigator::Navigator(Robotics::Matrix<char> & map, Robot & robot):Map(map),CurrentRobot(robot),CurrentTime(0)
    {
        
    }
    
    void Navigator::SetDestination(const glm::vec2 &destination)
    {
        this->CurrentTime = 0;
        this->Destination = destination;
        this->Curve.Clear();
        
        
        PDP::Physics::RayTracing tracer;
        
        tracer.FindRoute(this->Map, this->CurrentRobot.GetCurrentLocation(), destination);
        
        const std::vector<glm::vec3> & route = tracer.GetRoute();
        //calculate the distance
        float routeSize = 0;
        
        for (int n = 0; n<route.size()-1 ; ++n)
        {
            glm::vec3 p0 = route[n];
            glm::vec3 p1 = route[n+1];
            
            routeSize += Physics::Utility<float>::Distance(p1, p0);
        }
        
        float totalTime= routeSize/CurrentRobot.GetSpeed();
        
        float timeDifferential = 1.0f/totalTime;
        
        
        
        float time = 0;
        
        for (int n = 0; n<route.size(); ++n)
        {
            this->Curve.AddPoint(route[n], time);
            time+=timeDifferential;
            
        }
        this->Curve.AddPoint(glm::vec3(destination.x,destination.y,0), time);
        //generates the actual bezier curve in this step
        this->Curve.Generate();
        
    }

    void Navigator::Step(const float & dt)
    {
        glm::vec3 position = this->Curve.GetPosition(this->CurrentTime);
        
        
        glm::vec2 delta;
        
        delta.x = position.x - CurrentRobot.GetCurrentLocation().x;
        delta.y = position.y - CurrentRobot.GetCurrentLocation().y;
        
        
        this->CurrentRobot.Translate(delta);
        
        this->CurrentTime+=(dt);
    }
    
    bool Navigator::HasMoreSteps() const
    {
        
        glm::vec3 p0 = {this->CurrentRobot.GetCurrentLocation().x,this->CurrentRobot.GetCurrentLocation().y,0};
        glm::vec3 p1 = {this->Destination.x,this->Destination.y,0};
        return Physics::Utility<float>::Distance(p0, p1) > 0;
        
    }
}