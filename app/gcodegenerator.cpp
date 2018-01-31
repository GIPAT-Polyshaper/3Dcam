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

#include "toolpathgenerator.h"
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
        getPolyhedron(out);
    }
    //insert gcode generation and call writeFile
    //    writeFile();
    if (file.isOpen())
    {
        file.close();
    }
}

void GCodeGenerator::writeFile()
{
    QFile file(fileWritePath);
    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&file);
        out << "Placeholder" << endl;
    }
    if (file.isOpen())
    {
        file.close();
    }
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

float GCodeGenerator::getAzimuth() const
{
    return azimuth;
}

float GCodeGenerator::getElevation() const
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

void GCodeGenerator::setAzimuth(float az)
{
    if (azimuth != az)
    {
        azimuth = az;
        emit azimuthChanged(az);
        camera_dirty = true;
    }
}

void GCodeGenerator::setElevation(float el)
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

void GCodeGenerator::getPolyhedron(QTextStream& ts)
{
    VerticesAndFacesGenerator v(getTriangles(), offset_x, offset_y, offset_z);
    TriangularMeshGenerator t(v.vertices(), v.faces());
    polyhedron = t.polyhedron();
    toolPathGeneration(ts);
}

void GCodeGenerator::toolPathGeneration(QTextStream& ts)
{
    ToolPathGenerator tg;
    tg.setVolume(getVolumeX(), getVolumeY(), getVolumeZ());
    float currentY = 0.0;
    std::list<std::list<Point>> toolPath;

    ts << "inizio le passate" << endl;
    while(currentY <= getVolumeY())
    {
        toolPath.push_back(tg.getRayIntersections(currentY, polyhedron));
        currentY += getDiametroUtensile()/100 * (1 - getOverlapPassate()/100);
        for (std::list<Point>::iterator it = toolPath.rbegin()->begin(); it != toolPath.rbegin()->end(); it++)
        {
            Point p = *it;
            ts << "punto: " << p.x() << " "  << p.y() << " " << p.z() << endl;

        }
        ts << endl;
        ts << "passata " << toolPath.size() << " finita" << endl;
    }

    ts << "numero passate: " << toolPath.size() << endl;
}
