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
//#include <algorithm> per la funzione sort

struct Vec3
{
    float x, y, z;
};

struct Vec3i {
    Vec3 first;
    uint second;

    bool operator<(const Vec3i& other) const {
        return first.x < other.first.x;
    }

    //bool operator==(const Vec3i& other) const {
    //    return first.x == other.first.x;
    //}
};

//typedef std::pair<Vec3, uint> Vec3i;

GCodeGenerator::GCodeGenerator()
{
    altezzaUtensile = 40;
    diametroUtensile = 6;
    velocitaUtensile = 1000;
    formaUtensile = Sferica;
    overlapPassate = 50;
    volumeXAxis = 100;
    volumeYAxis = 100;
    volumeZAxis = 100;
}

void GCodeGenerator::openFile(QString path)
{
    if (path.contains("file://"))
    {
        filePath = path.mid(7,path.length());
    }
    else
    {
        filePath = path;
    }
    //    emit pathChanged(filePath);
    readAndGenerate();
}


float GCodeGenerator::getAltezzaUtensile() const
{
    return altezzaUtensile;
}

float GCodeGenerator::getDiametroUtensile() const
{
    return diametroUtensile;
}

float GCodeGenerator::getVelocitaUtensile() const
{
    return velocitaUtensile;
}

QString GCodeGenerator::getFormaUtensile() const
{
    QString forma;
    switch (formaUtensile)
    {
    case Sferica:
        forma = "Sferica";
        break;
    case Candela:
        forma = "Candela";
    default:
        break;
    }
    return forma;
}

float GCodeGenerator::getOverlapPassate() const
{
    return overlapPassate;
}

float GCodeGenerator::getVolumeX() const
{
    return volumeXAxis;
}

float GCodeGenerator::getVolumeY() const
{
    return volumeYAxis;
}

float GCodeGenerator::getVolumeZ() const
{
    return volumeZAxis;
}

QString GCodeGenerator::getPath() const
{
    return filePath;
}

void GCodeGenerator::setAltezza(float a)
{
    if (altezzaUtensile != a)
    {
        altezzaUtensile = a;
        emit altezzaChanged(a);
    }
}

void GCodeGenerator::setDiametro(float d)
{
    if (diametroUtensile != d)
    {
        diametroUtensile = d;
        emit diametroChanged(d);
    }
}

void GCodeGenerator::setVelocita(float v)
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
        if (f.toUpper().compare("SFERICA") == 0)
        {
            formaUtensile = Sferica;
        }
        else if (f.toUpper().compare("CANDELA") == 0)
        {
            formaUtensile = Candela;
        }
        emit formaChanged(f);
    }
}

void GCodeGenerator::setOverlap(float o)
{
    if (overlapPassate != o)
    {
        overlapPassate = o;
        emit overlapChanged(o);
    }
}

void GCodeGenerator::setVolumeX(float x)
{
    if (volumeXAxis != x)
    {
        volumeXAxis = x;
        emit volumeXChanged(x);
    }
}

void GCodeGenerator::setVolumeY(float y)
{
    if(volumeYAxis != y)
    {
        volumeYAxis = y;
        emit volumeYChanged(y);
    }
}

void GCodeGenerator::setVolumeZ(float z)
{
    if (volumeZAxis != z)
    {
        volumeZAxis = z;
        emit volumeZChanged(z);
    }
}

const StlLoader::Triangles& GCodeGenerator::getTriangles() const
{
    return triangles;
}

void GCodeGenerator::readAndGenerate()
{
    StlLoader loader(filePath);
    triangles.clear();
    triangles = loader.triangles();
}
