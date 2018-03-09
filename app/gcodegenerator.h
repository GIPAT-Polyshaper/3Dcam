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

#ifndef GCODEGENERATOR_H
#define GCODEGENERATOR_H

#include <QObject>
#include <QTextStream>
#include "stlloader.h"
#include "triangularmeshgenerator.h"

class GCodeGenerator : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int altezzaUt READ getAltezzaUtensile NOTIFY altezzaChanged)
    Q_PROPERTY(int diametroUt READ getDiametroUtensile NOTIFY diametroChanged)
    Q_PROPERTY(int velocitaUt READ getVelocitaUtensile NOTIFY velocitaChanged)
    Q_PROPERTY(QString formaUt READ getFormaUtensile  NOTIFY formaChanged)
    Q_PROPERTY(int overlap READ getOverlapPassate NOTIFY overlapChanged)
    Q_PROPERTY(int volumeX READ getVolumeX NOTIFY volumeXChanged)
    Q_PROPERTY(int volumeY READ getVolumeY NOTIFY volumeYChanged)
    Q_PROPERTY(int volumeZ READ getVolumeZ NOTIFY volumeZChanged)
    Q_PROPERTY(int azimuthCam READ getAzimuth WRITE setAzimuth NOTIFY azimuthChanged)
    Q_PROPERTY(int elevationCam READ getElevation WRITE setElevation NOTIFY elevationChanged)
    Q_PROPERTY(float distanceCam READ getDistance WRITE setDistance NOTIFY distanceChanged)
    Q_PROPERTY(int objectOffsetX READ getObjectOffsetX NOTIFY objectOffsetXChanged)
    Q_PROPERTY(int objectOffsetY READ getObjectOffsetY NOTIFY objectOffsetYChanged)

public:
    enum Forma
    {
        Sferica,
        Candela
    };

    //Assicuriamoci che ci sia una sola istanza di GCodeGenerator
    static GCodeGenerator& get_instance()
    {
        static GCodeGenerator instance;
        return instance;
    }

    int getAltezzaUtensile() const;
    int getDiametroUtensile() const;
    int getVelocitaUtensile() const;
    QString getFormaUtensile() const;
    int getOverlapPassate() const;
    int getVolumeX() const;
    int getVolumeY() const;
    int getVolumeZ() const;
    int getAzimuth() const;
    int getElevation() const;
    int getObjectOffsetX() const;
    int getObjectOffsetY() const;
    float getDistance() const;
    void setStartingOffset(float x, float y, float z);

    void cleanTriangles();
    void cleanCamera();
    void cleanVolume();

    bool isTrianglesDirty() const;
    bool isCameraDirty() const;
    bool isVolumeDirty() const;

    QString getPath() const;
    const StlLoader::Triangles& getTriangles() const;

    void toolPathGeneration(QTextStream &ts);
    const Polyhedron& getPolyhedron();

signals:
    void altezzaChanged(int newAltezza);
    void diametroChanged(int newDiametro);
    void velocitaChanged(int newVelocita);
    void formaChanged(QString newForma);
    void overlapChanged(int newOverlap);
    void volumeXChanged(int newVolumeX);
    void volumeYChanged(int newVolumeY);
    void volumeZChanged(int newVolumeZ);
    void azimuthChanged(int newAzimuth);
    void objectOffsetXChanged(int newObjectOffX);
    void objectOffsetYChanged(int newObjectOffY);
    void elevationChanged(int newElevation);
    void distanceChanged(float newDistance);

public slots:
    void setAltezza(int a);
    void setDiametro(int d);
    void setVelocita(int v);
    void setForma(QString f);
    void setOverlap(int o);
    void setVolumeX(int x);
    void setVolumeY(int y);
    void setVolumeZ(int z);
    void setAzimuth(int az);
    void setElevation(int el);
    void setDistance(float di);
    void setObjectOffsetX(int x);
    void setObjectOffsetY(int y);
    void openFile(QString path);
    void createFile(QString path);
    void generateCode();

protected:
    GCodeGenerator();

private:
    void readAndGenerate3DModel();
    QString filePath;
    QString fileWritePath;
    int altezzaUtensile;
    int diametroUtensile;
    int velocitaUtensile;
    Forma formaUtensile;
    int overlapPassate;
    int volumeXAxis;
    int volumeYAxis;
    int volumeZAxis;
    int azimuth;
    float distance;
    int elevation;
    Polyhedron polyhedron;

    float startingOffsetX;
    float startingOffsetY;
    float startingOffsetZ;

    int objectOffsetX;
    int objectOffsetY;

    bool trianglesDirty;
    bool cameraDirty;
    bool volumeDirty;

    StlLoader::Triangles triangles;
    GCodeGenerator(const GCodeGenerator&) = delete;
    void operator= (const GCodeGenerator&) = delete;
};

#endif // GCODEGENERATOR_H
