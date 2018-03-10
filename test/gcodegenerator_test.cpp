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

#include <QtTest/QtTest>
#include "gcodegenerator.h"

/**
 * \brief The class to perform unit tests
 *
 * Each private slot is a test
 */
class GCodeGenerator_Test : public QObject
{
    Q_OBJECT

private slots:
    void getEmptyGcode()
    {
        GCodeGenerator g;
        g.setAltezza(4);
        g.setVolumeX(10);
        g.setVolumeY(10);
        g.setVolumeZ(4);
        g.setVelocita(300);
        QString verify;
        verify.append("N1 G01 F300\n")
                .append("N2 G01 Z0\n")
                .append("N3 G92 X0 Y0 Z0\n")
                .append("N4 G00 Z0.5\n")
                .append("N5 G00 X0 Y0\n");

        std::vector<std::list<Point>> list;
        QString test = g.gCodeGeneration(list);
        QCOMPARE(test.toStdString(),verify.toStdString());
    }

    void testReverse()
    {
        GCodeGenerator g;
        g.setAltezza(4);
        g.setVolumeX(10);
        g.setVolumeY(10);
        g.setVolumeZ(4);
        g.setVelocita(300);
        QString verify;

        verify.append("N1 G01 F300\n")
                .append("N2 G01 Z0\n")
                .append("N3 G92 X0 Y0 Z0\n")
                .append("N4 G01 X0 Y0 Z-4\n")
                .append("N5 G01 X10 Z-4\n")
                .append("N6 G01 X10 Y2 Z-4\n")
                .append("N7 G01 X0 Z-4\n")
                .append("N8 G00 Z0.5\n")
                .append("N9 G00 X0 Y0\n");

        std::vector<std::list<Point>> list;
        std::list<Point> punti1;
        std::list<Point> punti2;

        punti1.push_back(Point(0, 0, 0));
        punti1.push_back(Point(10, 0, 0));
        punti2.push_back(Point(0, 2, 0));
        punti2.push_back(Point(10, 2, 0));
        list.push_back(punti1);
        list.push_back(punti2);
        QString test = g.gCodeGeneration(list);
        QCOMPARE(test.toStdString(),verify.toStdString());
    }

    void testMaxPenetration()
    {
        GCodeGenerator g;
        g.setAltezza(3);
        g.setVolumeX(10);
        g.setVolumeY(10);
        g.setVolumeZ(5);
        g.setVelocita(300);
        QString verify;

        verify.append("N1 G01 F300\n")
                .append("N2 G01 Z0\n")
                .append("N3 G92 X0 Y0 Z0\n")
                .append("N4 G01 X0 Y0 Z-3\n")
                .append("N5 G01 X2 Z0\n")
                .append("N6 G01 X3 Z-3\n")
                .append("N7 G01 X10 Z-3\n")
                .append("N8 G00 Z0.5\n")
                .append("N9 G00 X0 Y0\n");

        std::vector<std::list<Point>> list;
        std::list<Point> punti;

        punti.push_back(Point(0, 0, 0));
        punti.push_back(Point(2, 0, 5));
        punti.push_back(Point(3, 0, 1));
        punti.push_back(Point(10, 0, 0));
        list.push_back(punti);
        QString test = g.gCodeGeneration(list);
        QCOMPARE(test.toStdString(),verify.toStdString());
    }
};

QTEST_MAIN(GCodeGenerator_Test)
#include "gcodegenerator_test.moc"
