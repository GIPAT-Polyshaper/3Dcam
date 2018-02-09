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
#include <climits>

#include "toolpathgenerator.h"
//#include <algorithm> per la funzione sort

const float EPSILON = 0.00000001;

float roundFloat(float d)
{
    float num = d / EPSILON;
    num = round(num);
    return num * EPSILON;
}

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
    trianglesDirty = false;
    cameraDirty = false;
    volumeDirty = true;
    volumeXAxis = 100;
    volumeYAxis = 100;
    volumeZAxis = 100;
    setAzimuth(0);
    setElevation(20);
    setDistance(3);
    startingOffsetX = 0;
    startingOffsetY = 0;
    startingOffsetZ = 0;
    objectOffsetX = 0;
    objectOffsetY = 0;
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
    readAndGenerate3DModel();
}

void GCodeGenerator::createFile(QString path)
{

    std::cout << path.toStdString() << std::endl;
    if (path.contains("file://"))
    {
        fileWritePath = path.mid(7,path.length());
    }
    else
    {
        fileWritePath = path;
    }
    if (!fileWritePath.endsWith(".gcode",Qt::CaseInsensitive))
    {
        fileWritePath = fileWritePath.append(".gcode");
    }
    std::cout << fileWritePath.toStdString() << std::endl;

    QFile file(fileWritePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        generateCode(out);
    }

    if (file.isOpen())
    {
        file.close();
    }
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

int GCodeGenerator::getAzimuth() const
{
    return azimuth;
}

int GCodeGenerator::getElevation() const
{
    return elevation;
}

float GCodeGenerator::getDistance() const
{
    return distance;
}

int GCodeGenerator::getObjectOffsetX() const
{
    return objectOffsetX;
}

int GCodeGenerator::getObjectOffsetY() const
{
    return objectOffsetY;
}

void GCodeGenerator::setStartingOffset(float x, float y, float z)
{
    startingOffsetX = x;
    startingOffsetY = y;
    startingOffsetZ = z;
}

bool GCodeGenerator::isTrianglesDirty() const
{
    return trianglesDirty;
}

bool GCodeGenerator::isCameraDirty() const
{
    return cameraDirty;
}

bool GCodeGenerator::isVolumeDirty() const
{
    return volumeDirty;
}

QString GCodeGenerator::getPath() const
{
    return filePath;
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
        volumeDirty = true;
    }
}

void GCodeGenerator::setVolumeY(int y)
{
    if(volumeYAxis != y)
    {
        volumeYAxis = y;
        emit volumeYChanged(y);
        volumeDirty = true;
    }
}

void GCodeGenerator::setVolumeZ(int z)
{
    if (volumeZAxis != z)
    {
        volumeZAxis = z;
        emit volumeZChanged(z);
        volumeDirty = true;
    }
}

void GCodeGenerator::setObjectOffsetX(int x)
{
    if (objectOffsetX != x)
    {
        objectOffsetX = x;
        emit objectOffsetXChanged(x);
        trianglesDirty = true;
    }
}

void GCodeGenerator::setObjectOffsetY(int y)
{
    if (objectOffsetY != y)
    {
        objectOffsetY = y;
        emit objectOffsetYChanged(y);
        trianglesDirty = true;
    }
}

void GCodeGenerator::setAzimuth(int az)
{
    if (azimuth != az)
    {
        azimuth = az;
        emit azimuthChanged(az);
        cameraDirty = true;
    }
}

void GCodeGenerator::setElevation(int el)
{
    if (elevation != el)
    {
        elevation = el;
        emit elevationChanged(el);
        cameraDirty = true;
    }
}

void GCodeGenerator::setDistance(float di)
{
    if (distance != di)
    {
        distance = di;
        emit distanceChanged(di);
        cameraDirty = true;
    }
}


const StlLoader::Triangles& GCodeGenerator::getTriangles() const
{
    return triangles;
}

void GCodeGenerator::readAndGenerate3DModel()
{
    StlLoader loader(filePath);
    triangles.clear();
    triangles = loader.triangles();
    trianglesDirty = true;
}

void GCodeGenerator::cleanCamera()
{
    cameraDirty = false;
}

void GCodeGenerator::cleanTriangles()
{
    trianglesDirty = false;
}

void GCodeGenerator::cleanVolume()
{
    volumeDirty = false;
}

void GCodeGenerator::generateCode(QTextStream& ts)
{
    VerticesAndFacesGenerator v(getTriangles(), startingOffsetX + objectOffsetX, startingOffsetY + objectOffsetY, startingOffsetZ);
    TriangularMeshGenerator t(v.vertices(), v.faces());
    polyhedron = t.polyhedron();
    toolPathGeneration(ts);
}

const Polyhedron& GCodeGenerator::getPolyhedron()
{
    return polyhedron;
}

void GCodeGenerator::toolPathGeneration(QTextStream& ts)
{
    ToolPathGenerator tg(getPolyhedron());
    tg.setVolume(getVolumeX(), getVolumeY(), getVolumeZ());
    float currentY = 0.0;
    std::list<Point> toolPath;
    int i = 0, j = 1;
    ts << "F" << getVelocitaUtensile() << endl;
    ts << "N" << (j) << "G01" << "X" << 0.0 << "Y" << 0.0 << "Z" << 0.100 << endl;
    ++j;
    while(currentY <= getVolumeY())
    {
        toolPath = tg.getRayIntersections(currentY);

        float startx = 0, endx = getVolumeX();
        if (i % 2 != 0)
        {
            toolPath.reverse();
            startx = endx;
            endx = 0;
        }

        if (toolPath.size() > 0)
        {
            for (auto p : toolPath)
            {
                ts << "N" << j << "X"  << roundFloat(p.x()) << "Z" << roundFloat(p.z() - getVolumeZ()) << endl;
                ++j;
            }
        }
        else
        {
            ts << "N" << j << "X" << roundFloat(startx) << "Z" << roundFloat(0 - getVolumeZ()) << endl;
            ++j;
            ts << "N" << j << "X" << roundFloat(endx) << endl;
            ++j;
        }

        ++i;
        currentY += roundFloat(getDiametroUtensile() * (1 - getOverlapPassate()/100.0));
        ts << "N" << j << "Y" << currentY << endl;
        ++j;
    }
    ts << "N" << j << "G01" << "Z" << 0.100 << endl;
    ++j;
    ts << "N" << j << "G00" << "X" << 0.0 << "Y" << 0.0 << endl;
}
