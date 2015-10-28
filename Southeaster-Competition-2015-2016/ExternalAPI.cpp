//
//  ExternalAPI.cpp
//  Robotics Navigation
//
//  Created by James Landess on 10/26/15.
//  Copyright © 2015 James Landess. All rights reserved.
//

#include "ExternalAPI.hpp"
#include "Robot.hpp"
#include "Matrix.h"
#include "Navigator.hpp"
void * CreateRobot()
{
    return  new Robotics::Robot();
}

void SetRobotLocation(void * robot, int x, int y)
{
    Robotics::Robot * rob = (Robotics::Robot*)robot;
    
    rob->SetLocation(glm::vec2(x,y));
}

void SetRobotSpeed(void * robot, float speed)
{
    Robotics::Robot * rob = (Robotics::Robot*)robot;
    rob->SetSpeed(speed);
}

void DeleteRobot(void * robot)
{
    Robotics::Robot * rob = (Robotics::Robot*)robot;
    delete rob;
}

void * CreateMap(int width, int size)
{
    return new Robotics::Matrix<char>(width,size);
}

char AccessMap(void * map, int x, int y)
{
    Robotics::Matrix<char> * m = (Robotics::Matrix<char>*)map;
    return (*m)[x][y];
}

void SetMap(void * map,int x, int y, char character)
{
    Robotics::Matrix<char> * m = (Robotics::Matrix<char>*)map;
    (*m)[x][y] = character;
}


int GetWidth(void * map)
{
    Robotics::Matrix<char> * m = (Robotics::Matrix<char>*)map;
    return (int)m->ColumnSize();
}
int GetHeight(void * map)
{
    Robotics::Matrix<char> * m = (Robotics::Matrix<char>*)map;
    return (int)m->RowSize();
}

void DeleteMap(void * map)
{
    Robotics::Matrix<char> * m = (Robotics::Matrix<char>*)map;
    delete m;
}

void * CreateNavigator(void * map, void * robot)
{
    Robotics::Matrix<char> * m = (Robotics::Matrix<char>*)map;
    
    Robotics::Robot * rob = (Robotics::Robot*)robot;
    
    Robotics::Navigator * navigator = new Robotics::Navigator(*m,*rob);
    
    return navigator;
}

void SetDestination(void * navigator,int x, int y)
{
    Robotics::Navigator * nav = (Robotics::Navigator*)navigator;
    
    nav->SetDestination(glm::vec2(x,y));
}

void Step(void * navigator, float dt)
{
    Robotics::Navigator * nav = (Robotics::Navigator*)navigator;
    nav->Step(dt);
}

int HasMoreSteps(void * navigator)
{
    Robotics::Navigator * nav = (Robotics::Navigator*)navigator;
    return nav->HasMoreSteps();
}

void DeleteNavigator(void * navigator)
{
    Robotics::Navigator * nav = (Robotics::Navigator*)navigator;
    delete nav;
}

