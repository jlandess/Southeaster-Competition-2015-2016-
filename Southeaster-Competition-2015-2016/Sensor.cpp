//
//  Sensor.cpp
//  Robotics Navigation
//

#include "Sensor.hpp"
namespace Robotics
{
    namespace Navigation
    {
        Sensor::Sensor():AmbientTemperature(70)
        {
            
        }
        Sensor::Sensor(const glm::vec3 & direction):Direction(direction)
        {
            
        }
        
        void Sensor::SetDirection(const glm::vec3 &direction)
        {
            this->Direction = direction;
        }
        
        const float Sensor::Pulse() const
        {
            return 0;
        }
        
        const glm::vec3 & Sensor::GetDirection() const
        {
            return this->Direction;
        }
        
        const float & Sensor::GetAmbientTemperature() const
        {
            return this->AmbientTemperature;
        }
        
        const float & Sensor::GetResolution() const
        {
            return this->Resolution;
        }
        
        void Sensor::SetResolution(const float &resolution)
        {
            this->Resolution = resolution;
        }
        
        void Sensor::SetAmbientTemperature(const float &ambientTemperature)
        {
            this->AmbientTemperature = ambientTemperature;
        }
    }
}