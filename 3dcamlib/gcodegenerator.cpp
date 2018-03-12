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
//#include <QVector>
#include <typeinfo>
#include <climits>

GCodeGenerator::GCodeGenerator()
{
    toolHeight = 40;
    toolWidth = 6;
    toolSpeed = 1000;
    toolShape = Candela;
    volumeXAxis = 100;
    volumeYAxis = 100;
    volumeZAxis = 100;
}

GCodeGenerator::GCodeGenerator(int tHeight, int tWidth, int tSpeed, int x, int y, int z)
{
    toolHeight = tHeight;
    toolWidth = tWidth;
    toolSpeed = tSpeed;
    volumeXAxis = x;
    volumeYAxis = y;
    volumeZAxis = z;
    toolShape = Candela;
}

int GCodeGenerator::getToolHeight() const
{
    return toolHeight;
}

int GCodeGenerator::getToolWidth() const
{
    return toolWidth;
}

int GCodeGenerator::getToolSpeed() const
{
    return toolSpeed;
}

QString GCodeGenerator::getToolShape() const
{
    QString forma;
    forma = "Candela";
    return forma;
}

int GCodeGenerator::getVolumeX() const
{
    return volumeXAxis;
}

int GCodeGenerator::getVolumeY() const
{
    return volumeYAxis;
}

int GCodeGenerator::getVolumeZ() const
{
    return volumeZAxis;
}

void GCodeGenerator::setToolHeight(int a)
{
    if (toolHeight != a)
    {
        toolHeight = a;
    }
}

void GCodeGenerator::setToolWidth(int d)
{
    if (toolWidth != d)
    {
        toolWidth = d;
    }
}

void GCodeGenerator::setToolSpeed(int v)
{
    if (toolSpeed != v)
    {
        toolSpeed = v;
    }
}

void GCodeGenerator::setToolShape(QString f)
{
    if (getToolShape().compare(f,Qt::CaseInsensitive) != 0)
    {
        toolShape = Candela;
    }
}

QString GCodeGenerator::gCodeGeneration(std::vector<std::list<Point>> p)
{
    QString result;
    QTextStream ts(&result);
    ts.setRealNumberPrecision(3);
    int j = 1;
    ts << "N" << (j) << " G01" << " F" << getToolSpeed() << endl;
    ++j;
    ts << "N" << (j) << " G01 Z0" << endl;
    ++j;
    ts << "N" << (j) << " G92 X0 Y0 Z0" << endl;
    ++j;
    for (int i = 0; i < p.size(); ++i)
    {
        auto toolPath = p[i];
        bool reverse = false;
        bool first = true;
        if (i % 2 != 0)
        {
            reverse = true;
        }
        for (auto it = (reverse) ? --toolPath.rbegin().base() : toolPath.begin(); it != toolPath.end(); (reverse) ? --it : ++it)
        {
            auto point = *it;
            QString ycoordinate = "";
            if (first)
            {
                ycoordinate = " Y" + QString::number(point.y(), 'g', 3);
            }
            if (point.z() - getVolumeZ() > 0 - getToolHeight())
            {
                ts << "N" << j << " G01" << " X" << point.x() << ycoordinate << " Z" << point.z() - getVolumeZ() << endl;
            }
            else
            {
                ts << "N" << j << " G01" << " X"  << point.x() << ycoordinate << " Z" << 0 - getToolHeight() << endl;
            }
            first = false;
            ++j;
            if (reverse && it == toolPath.begin())
            {
                break;
            }
        }
    }

    ts << "N" << j << " G00" << " Z" << 0.500 << endl;
    ++j;
    ts << "N" << j << " G00" << " X" << 0.0 << " Y" << 0.0 << endl;
    return result;
}
