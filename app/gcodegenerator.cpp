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
    triangles_dirty = false;
    camera_dirty = false;
    volume_dirty = true;
    volumeXAxis = 100;
    volumeYAxis = 100;
    volumeZAxis = 100;
    setAzimuth(0);
    setElevation(20);
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

void GCodeGenerator::setOffset(float x, float y, float z)
{
    offset_x = x;
    offset_y = y;
    offset_z = z;
}

bool GCodeGenerator::isTrianglesDirty() const
{
    return triangles_dirty;
}

bool GCodeGenerator::isCameraDirty() const
{
    return camera_dirty;
}

bool GCodeGenerator::isVolumeDirty() const
{
    return volume_dirty;
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
        volume_dirty = true;
    }
}

void GCodeGenerator::setVolumeY(int y)
{
    if(volumeYAxis != y)
    {
        volumeYAxis = y;
        emit volumeYChanged(y);
        volume_dirty = true;
    }
}

void GCodeGenerator::setVolumeZ(int z)
{
    if (volumeZAxis != z)
    {
        volumeZAxis = z;
        emit volumeZChanged(z);
        volume_dirty = true;
    }
}

void GCodeGenerator::setAzimuth(int az)
{
    if (azimuth != az)
    {
        azimuth = az;
        emit azimuthChanged(az);
        camera_dirty = true;
    }
}

void GCodeGenerator::setElevation(int el)
{
    if (elevation != el)
    {
        elevation = el;
        emit elevationChanged(el);
        camera_dirty = true;
    }
}

void GCodeGenerator::setDistance(float di)
{
    if (distance != di)
    {
        distance = di;
        emit distanceChanged(di);
        camera_dirty = true;
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
    triangles_dirty = true;
}

void GCodeGenerator::clean_camera()
{
    camera_dirty = false;
}

void GCodeGenerator::clean_triangles()
{
    triangles_dirty = false;
}

void GCodeGenerator::clean_volume()
{
    volume_dirty = false;
}

void GCodeGenerator::generateCode(QTextStream& ts)
{
    VerticesAndFacesGenerator v(getTriangles(), offset_x, offset_y, offset_z);
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
        currentY += roundFloat(getDiametroUtensile() * (1 - getOverlapPassate()/100));
        ts << "N" << j << "Y" << currentY << endl;
        ++j;
    }
    ts << "N" << j << "G01" << "Z" << 0.100 << endl;
    ++j;
    ts << "N" << j << "G00" << "X" << 0.0 << "Y" << 0.0 << endl;
}
