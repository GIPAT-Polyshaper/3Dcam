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
#include "toolpathgenerator.h"

class GCodeGenerator : public QObject
{

public:

    GCodeGenerator();
    GCodeGenerator(int tHeight, int tWidth, int tSpeed, int x, int y, int z);
    enum Shape
    {
        Candela
    };

    int getToolHeight() const;
    int getToolWidth() const;
    int getToolSpeed() const;
    QString getToolShape() const;
    int getVolumeX() const;
    int getVolumeY() const;
    int getVolumeZ() const;

    void setToolHeight(int a);
    void setToolWidth(int d);
    void setToolSpeed(int v);
    void setToolShape(QString f);

    QString gCodeGeneration(std::vector<std::list<Point>> p);

private:
    int toolHeight;
    int toolWidth;
    int toolSpeed;
    Shape toolShape;
    int volumeXAxis;
    int volumeYAxis;
    int volumeZAxis;
};

#endif // GCODEGENERATOR_H
