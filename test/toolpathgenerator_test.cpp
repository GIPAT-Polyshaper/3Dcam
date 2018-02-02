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
#include <QFile>
#include <QString>
#include "toolpathgenerator.h"
#include "stlloader.h"
#include "triangularmeshgenerator.h"

// NOTES AND TODOS
//
// This is just an empty file, created as template for unit tests

/**
 * \brief The class to perform unit tests
 *
 * Each private slot is a test
 */
class ToolPathGenerator_Test : public QObject
{
    Q_OBJECT

private slots:

    void testDoubleCube()
    {
        StlLoader loader(":/double_cube");

        Point punti[] = {Point(0, 0, 0), Point(0, 0, 1),
                         Point(1, 0, 2), Point(1, 0, 0),
                         Point(2, 0, 0), Point(2, 0, 1),
                         Point(3, 0, 1), Point(3, 0, 0)};

        VerticesAndFacesGenerator vfg(loader.triangles());
        TriangularMeshGenerator tmg(vfg.vertices(), vfg.faces());

        ToolPathGenerator tpg(tmg.polyhedron());
        tpg.setVolume(3, 1, 2);
        std::list<Point> listaPunti = tpg.getRayIntersections(0);
        bool test = true;
        int i = 0;

        QEXPECT_FAIL("", "Will fix in a future release", Continue);
        QVERIFY(listaPunti.size() == 8);
        for (std::list<Point>::iterator it = listaPunti.begin(); it != listaPunti.end(); it++)
        {
            Point p = *it;
            if(p != punti[i])
            {
                test = false;
                break;
            }
            i++;
        }
        QEXPECT_FAIL("", "Will fix in a future release", Continue);
        QVERIFY(test);
    }

    void testSlope()
    {
        StlLoader loader(":/slope");

        Point punti[] = {Point(0, 0, 0), Point(0, 0, 1),
                         Point(1, 0, 2), Point(1, 0, 0)};

        VerticesAndFacesGenerator vfg(loader.triangles());
        TriangularMeshGenerator tmg(vfg.vertices(), vfg.faces());

        ToolPathGenerator tpg(tmg.polyhedron());
        tpg.setVolume(1, 1, 2);
        std::list<Point> listaPunti = tpg.getRayIntersections(0);
        bool test = true;
        int i = 0;

        QVERIFY(listaPunti.size() == 4);
        for (std::list<Point>::iterator it = listaPunti.begin(); it != listaPunti.end(); it++)
        {
            Point p = *it;
            if(p != punti[i])
            {
                test = false;
                break;
            }
            i++;
        }
//        QEXPECT_FAIL("", "Will fix in a future release", Continue);
        QVERIFY(test);
    }
};

QTEST_MAIN(ToolPathGenerator_Test)
#include "toolpathgenerator_test.moc"
