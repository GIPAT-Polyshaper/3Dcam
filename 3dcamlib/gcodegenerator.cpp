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
#include <fstream>
#include <QTextStream>


GCodeGenerator::GCodeGenerator(const std::vector<SinglePath>& paths, double speed, double zSafe)
    : m_paths(paths)
    , m_speed(speed)
    , m_zSafe(zSafe)
{

}

void GCodeGenerator::readAndGenerate(QTextStream& stream)
{






stream << "F" << m_speed << "\n";

if (!m_paths.empty())
{
    //std::cout << m_paths[0].y[2] << std::endl;


    for (auto j = 0; j < m_paths.size(); ++j){

        for (auto i = 0; i < m_paths[j].y.size(); ++i){

            stream << "G01 X" << m_paths[j].x << " Y" << m_paths[j].y[i] << " Z" << m_paths[j].z[i] <<"\n";

        }
    }

}

stream << "G00 Z" << m_zSafe << "\nG00 X0 Y0 Z0";


}
