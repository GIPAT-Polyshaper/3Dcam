/**************************************************************************
 * PolyShaper 3D Cam                                                      *
 * Copyright (C) 2017                                                     *
 * Tomassino Ferrauto <tomassino.ferrauto@gmail.com>                      *
 * Flavio Prattico <flavioprattico@gmail.com>                             *
 * Carmine Gianfagna <carmine.gianfagna@gmail.com>                        *
 *                                                                        *
 * This program is free software; you can redistribute it and/or modify   *
 * it under the terms of the GNU General Public License as published by   *
 * the Free Software Foundation; either version 3 of the License, or      *
 * (at your option) any later version.                                    *
 *                                                                        *
 * This program is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 * GNU General Public License for more details.                           *
 *                                                                        *
 * You should have received a copy of the GNU General Public License      *
 * along with this program; if not, write to the                          *
 * Free Software Foundation, Inc.,                                        *
 * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.              *
 **************************************************************************/

#include "gcodegenerator.h"
#include <iostream>
#include <QFile>
#include <QDataStream>
#include <QVector>
#include <typeinfo>
#include <algorithm>
#include <vector>

struct Vec3
{
    float y, z, ind;
};

struct Vec3i {
    Vec3 first;

    bool operator<(const Vec3i& other) const {
        return first.y < other.first.y;
    }

    //bool operator==(const Vec3i& other) const {
    //    return first.x == other.first.x;
    //}
};

//typedef std::pair<Vec3, uint> Vec3i;

GCodeGenerator::GCodeGenerator()
{

}

void GCodeGenerator::readAndGenerate()
{
    //std::cout << "a soreta" << std::endl;

    float indi [11] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    float yi [11]   = {10, 5, 3, 1, 2, 4, 6, 8, 9,  7, 10};
    float zi [11]   = { 1, 1, 2, 2, 4, 6, 7, 5, 3,  2, 2};

    QVector<Vec3i> verts(11);

    /*
    const auto start = 4;

    for (auto i = 0; i < verts.size(); ++i) {
        const auto j = (i + start) % verts.size();

        verts[j]
    }
    */

    for (int i=0; i < verts.length(); i++)
    {
        //std::cout << verts[i].first.x << " - " << verts[i].first.y << std::endl;

        verts[i].first.y = yi[i];
        verts[i].first.z = zi[i];
        verts[i].first.ind = indi[i];
        //std::cout << verts[i].first.y << " - " << verts[i].first.ind << std::endl;
    }

    std::sort(verts.begin(), verts.end());


//show ordered struct

    for (int i=0; i < verts.length(); i++)
    {

       std::cout << verts[i].first.y << " - " << verts[i].first.ind << std::endl;
    }






    // let hypothesize clockwise increment in the yz profile

    std::vector<float> surfy;
    std::vector<float> surfz;
    std::vector<float> surfind;


    float tmp = verts[0].first.ind;

    for (int i=1; i < verts.length(); i++)
    {

        //std::cout << verts[i-1].first.y  << " - " << verts[i].first.y  << std::endl;
        //std::cout << (verts[i-1].first.y > verts[i].first.y) << std::endl;

        if (tmp+1==verts[i].first.ind || verts[i].first.ind==1){

            if (verts[i-1].first.y <= verts[i].first.y){

                surfy.push_back(verts[i].first.y);
                surfz.push_back(verts[i].first.z);
                surfind.push_back(verts[i].first.ind);
                tmp = verts[i].first.ind;

            }
            else if (verts[i-1].first.y > verts[i].first.y){ //non entra qui col punto 10

                surfy.push_back(verts[i-1].first.y);
                surfz.push_back(verts[i].first.z);
                surfind.push_back(verts[i].first.ind);
                tmp = verts[i].first.ind;
            }


        }

    }

    surfy.insert (surfy.begin(), verts[0].first.y);
    surfz.insert (surfz.begin(), verts[0].first.z);
    surfind.insert (surfind.begin(), verts[0].first.ind);



    for (int i=0; i < verts.length(); i++)
    {
        //std::cout << verts[i].first.y << std::endl;

        std::cout << verts[i].first.y << " - " << verts[i].first.ind << std::endl;
    }




}
