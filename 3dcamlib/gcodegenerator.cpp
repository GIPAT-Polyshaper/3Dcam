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
    altezzaUtensile = 40;
    diametroUtensile = 6;
    velocitaUtensile = 1000;
    formaUtensile = Candela;
    overlapPassate = 50;
    setVolumeX(100);
    setVolumeY(100);
    setVolumeZ(100);
    startingOffsetX = 0;
    startingOffsetY = 0;
    startingOffsetZ = 0;
    objectOffsetX = 0;
    objectOffsetY = 0;
}

int GCodeGenerator::getAltezzaUtensile() const
{
    return altezzaUtensile;
}

int GCodeGenerator::getDiametroUtensile() const
{
    return diametroUtensile;
}

int GCodeGenerator::getVelocitaUtensile() const
{
    return velocitaUtensile;
}

QString GCodeGenerator::getFormaUtensile() const
{
    QString forma;
    forma = "Candela";
    return forma;
}

int GCodeGenerator::getOverlapPassate() const
{
    return overlapPassate;
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

int GCodeGenerator::getObjectOffsetX() const
{
    return objectOffsetX;
}

int GCodeGenerator::getObjectOffsetY() const
{
    return objectOffsetY;
}

float GCodeGenerator::getStartingoffsetX() const
{
    return startingOffsetX;
}

float GCodeGenerator::getStartingOffsetY() const
{
    return startingOffsetY;
}

float GCodeGenerator::getStartingOffsetZ() const
{
    return startingOffsetZ;
}

void GCodeGenerator::setStartingOffset(float x, float y, float z)
{
    startingOffsetX = x;
    startingOffsetY = y;
    startingOffsetZ = z;
}

void GCodeGenerator::setAltezza(int a)
{
    if (altezzaUtensile != a)
    {
        altezzaUtensile = a;
        emit altezzaChanged(a);
    }
}

void GCodeGenerator::setDiametro(int d)
{
    if (diametroUtensile != d)
    {
        diametroUtensile = d;
        emit diametroChanged(d);
    }
}

void GCodeGenerator::setVelocita(int v)
{
    if (velocitaUtensile != v)
    {
        velocitaUtensile = v;
        emit velocitaChanged(v);
    }
}

void GCodeGenerator::setForma(QString f)
{
    if (getFormaUtensile().compare(f,Qt::CaseInsensitive) != 0)
    {
        formaUtensile = Candela;
        emit formaChanged(f);
    }
}

void GCodeGenerator::setOverlap(int o)
{
    if (overlapPassate != o)
    {
        overlapPassate = o;
        emit overlapChanged(o);
    }
}

void GCodeGenerator::setVolumeX(int x)
{
    if (volumeXAxis != x)
    {
        volumeXAxis = x;
        emit volumeXChanged(x);
    }
}

void GCodeGenerator::setVolumeY(int y)
{
    if(volumeYAxis != y)
    {
        volumeYAxis = y;
        emit volumeYChanged(y);
    }
}

void GCodeGenerator::setVolumeZ(int z)
{
    if (volumeZAxis != z)
    {
        volumeZAxis = z;
        emit volumeZChanged(z);
    }
}

void GCodeGenerator::setObjectOffsetX(int x)
{
    if (objectOffsetX != x)
    {
        objectOffsetX = x;
        emit objectOffsetXChanged(x);
    }
}

void GCodeGenerator::setObjectOffsetY(int y)
{
    if (objectOffsetY != y)
    {
        objectOffsetY = y;
        emit objectOffsetYChanged(y);
    }
}

QString GCodeGenerator::gCodeGeneration(std::vector<std::list<Point>> p)
{
    QString result;
    QTextStream ts(&result);
    ts.setRealNumberPrecision(3);
    int j = 1;
    ts << "N" << (j) << " G01" << " F" << getVelocitaUtensile() << endl;
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
            if (point.z() - getVolumeZ() > 0 - getAltezzaUtensile())
            {
                ts << "N" << j << " G01" << " X" << point.x() << ycoordinate << " Z" << point.z() - getVolumeZ() << endl;
            }
            else
            {
                ts << "N" << j << " G01" << " X"  << point.x() << ycoordinate << " Z" << 0 - getAltezzaUtensile() << endl;
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
