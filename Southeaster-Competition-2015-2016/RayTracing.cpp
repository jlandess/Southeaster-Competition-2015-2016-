//
//  RayTracing.cpp
//  Foundation
//
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

#include "RayTracing.h"

#define WAVE_SOURCE	2
namespace PDP
{
    namespace Physics
    {
        glm::vec2 RayTracing::FindNear(Robotics::Matrix<char> &map, int x, int y, int n) const
        {
            if ( y > 0 && map[x][y - 1] == n )
                return glm::vec2(x, y - 1);
            else if  ( y < map.ColumnSize() - 1 && map[x][y + 1] == n )//( y < m_BoardSize - 1 && map[x][y + 1] == n )
                return glm::vec2(x, y + 1);
            else if ( x > 0 && map[x - 1][y] == n )
                return glm::vec2(x - 1, y);
            else// if ( x < m_BoardSize - 1 && map[x + 1][y] == n )
                return glm::vec2(x + 1, y);
        }
        bool RayTracing::SetNear(Robotics::Matrix<char> &map, int x, int y, int n) const
        {
            bool bStatus = false;
            if ( y > 0 && map[x][y - 1] == 0 )
            {
                map[x][y - 1] = n;
                bStatus = true;
            }
            if  ( y < map.ColumnSize() - 1 && map[x][y + 1] == 0 )//( y < m_BoardSize - 1 && map[x][y + 1] == 0 )
            {
                map[x][y + 1] = n;
                bStatus = true;
            }
            if ( x > 0 && map[x - 1][y] == 0 )
            {
                map[x - 1][y] = n;
                bStatus = true;
            }
            if ( x < map.RowSize() - 1 && map[x + 1][y] == 0 )//( x < m_BoardSize - 1 && map[x + 1][y] == 0 )
            {
                map[x + 1][y] = n;
                bStatus = true;
            }
            return bStatus;
        }
        bool RayTracing::NearBy(Robotics::Matrix<char> &map, int x, int y, int n, glm::vec2 &pt) const
        {
            if ( y > 0 && map[x][y - 1] == n )
            {
                pt.x = x; pt.y = y - 1;
                return true;
            }
            if ( y < map.ColumnSize() - 1 && map[x][y + 1] == n )//( y < m_BoardSize - 1 && map[x][y + 1] == n )
            {
                pt.x = x; pt.y = y + 1;
                return true;
            }
            if ( x > 0 && map[x - 1][y] == n )
            {
                pt.x = x - 1; pt.y = y;
                return true;
            }
            if ( x < map.RowSize() - 1 && map[x + 1][y] == n )//( x < m_BoardSize - 1 && map[x + 1][y] == n )
            {
                pt.x = x + 1; pt.y = y;
                return true;
            }
            return false;
        }
        
        
        
        bool RayTracing::FindRoute(Robotics::Matrix<char> & m_Board, const glm::vec2 &m_FromCell, const glm::vec2 &m_ToCell)
        {
            int i, j, k = WAVE_SOURCE;
            glm::vec2 pt1, pt2;
            bool isMet = false, isNotFinished = true;
            
            Robotics::Matrix<char> map(m_Board.RowSize(),m_Board.ColumnSize());
            
            for ( int i = 0; i < m_Board.RowSize(); i++ )
                for ( int j = 0; j < m_Board.ColumnSize(); j++ )
                    map[i][j] = m_Board[i][j] ? 1 : 0;
            
            
            // Mark wave sources
            map[m_FromCell.x][m_FromCell.y] = k;
            map[m_ToCell.x][m_ToCell.y] = -k;
            
            // Clear the route
            m_Route.clear();
            for ( ; isNotFinished && !isMet; k++ )
            {
                isNotFinished = false;
                for ( i = 0; i < m_Board.RowSize() && !isMet; i++ )
                {
                    for ( j = 0; j < m_Board.ColumnSize() && !isMet; j++ )
                    {
                        if ( map[i][j] == k )
                        {
                            if ( NearBy(map, i, j, -k, pt2) || NearBy(map, i, j, -k - 1, pt2) )
                            {
                                // Two waves met
                                isMet = true;
                                pt1.x = i;
                                pt1.y = j;
                            }
                            else
                                isNotFinished |= SetNear(map, i, j, k + 1);
                        }
                        
                        else if ( map[i][j] == -k )
                        {
                            if ( NearBy(map, i, j, k, pt1) || NearBy(map, i, j, k + 1, pt1) )
                            {
                                // Two waves met
                                isMet = true;
                                pt2.x = i;
                                pt2.y = j;
                            }
                            else
                            {
                                isNotFinished |= SetNear(map, i, j, -k - 1);
                            }
                        }
                    }
                    
                }
                
                
                
            }
            // Extract route
            if ( isMet )
            {
                
                m_Route.push_back(glm::vec3(pt1.x,pt1.y,0));
                m_Route.push_back(glm::vec3(pt2.x,pt2.y,0));
                while ( map[pt2.x][pt2.y] < -WAVE_SOURCE )
                {
                    pt2 = FindNear(map, pt2.x, pt2.y, map[pt2.x][pt2.y] + 1);
                    m_Route.push_back(glm::vec3(pt2.x,pt2.y,0));
                }
                while ( map[pt1.x][pt1.y] > WAVE_SOURCE )
                {
                    pt1 = FindNear(map, pt1.x, pt1.y, map[pt1.x][pt1.y] - 1);
                    m_Route.insert(m_Route.begin(), glm::vec3(pt1.x,pt1.y,0));
                }
                return true;
            }
            return false;
        }
        const std::vector<glm::vec3> & RayTracing::GetRoute() const
        {
            return this->m_Route;
        }
    }

}