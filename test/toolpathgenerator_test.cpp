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

/**
 * \brief The class to perform unit tests
 *
 * Each private slot is a test
 */
class ToolPathGenerator_Test : public QObject
{
    Q_OBJECT

private slots:

    void testNoIntersections()
    {
        StlLoader loader(":/cube");

        VerticesAndFacesGenerator vfg(loader.triangles());
        TriangularMeshGenerator tmg(vfg.vertices(), vfg.faces());

        Point punti[] = {Point(0, 2, 0), Point(1, 2, 0)};

        ToolPathGenerator tpg(tmg.polyhedron(), 0.1, 0);
        tpg.setVolume(1, 2, 2);
        std::list<Point> listaPunti = tpg.getToolPath(2);
        bool test = true;
        int i = 0;

        QVERIFY(listaPunti.size() == 2);
        for (auto p : listaPunti)
        {
            if(p != punti[i])
            {
                test = false;
                break;
            }
            i++;
        }
        QVERIFY(test);
    }

    void testBorder()
    {
        StlLoader loader(":/cube");

        Point punti[] = {Point(0, 0, 0), Point(0, 0, 1),
                         Point(1, 0, 1), Point(1, 0, 0)};

        VerticesAndFacesGenerator vfg(loader.triangles());
        TriangularMeshGenerator tmg(vfg.vertices(), vfg.faces());

        ToolPathGenerator tpg(tmg.polyhedron(), 1, 0);
        tpg.setVolume(1, 1, 2);
        std::list<Point> listaPunti = tpg.getToolPath(0);
        bool test = true;
        int i = 0;

        QVERIFY(listaPunti.size() == 4);
        for (auto p : listaPunti)
        {
            if(p != punti[i])
            {
                test = false;
                break;
            }
            i++;
        }
        QVERIFY(test);
    }

    void testToolThicknessBefore()
    {
        StlLoader loader(":/cube");

        Point punti[] = {Point(0, 0, 0), Point(0, 0, 1),
                         Point(1, 0, 1), Point(1, 0, 0)};

        VerticesAndFacesGenerator vfg(loader.triangles(), 0, 1, 0);
        TriangularMeshGenerator tmg(vfg.vertices(), vfg.faces());

        ToolPathGenerator tpg(tmg.polyhedron(), 1, 2);
        tpg.setVolume(1, 4, 2);
        std::list<Point> listaPunti = tpg.getToolPath(0);
        bool test = true;
        int i = 0;

        QVERIFY(listaPunti.size() == 4);
        for (auto p : listaPunti)
        {
            if(p != punti[i])
            {
                test = false;
                break;
            }
            i++;
        }
        QVERIFY(test);
    }

    void testToolThicknessAfter()
    {
        StlLoader loader(":/cube");

        Point punti[] = {Point(0, 2, 0), Point(0, 2, 1),
                         Point(1, 2, 1), Point(1, 2, 0)};

        VerticesAndFacesGenerator vfg(loader.triangles());
        TriangularMeshGenerator tmg(vfg.vertices(), vfg.faces());

        ToolPathGenerator tpg(tmg.polyhedron(), 1, 2);
        tpg.setVolume(1, 4, 2);
        std::list<Point> listaPunti = tpg.getToolPath(2);
        bool test = true;
        int i = 0;

        QVERIFY(listaPunti.size() == 4);
        for (auto p : listaPunti)
        {
            if(p != punti[i])
            {
                test = false;
                break;
            }
            i++;
        }
        QVERIFY(test);
    }

    void testWorkingVolume()
    {
        StlLoader loader(":/cube");

        Point punti[] = {Point(0, 1, 0), Point(0.9, 1, 0),
                         Point(1, 1, 1), Point(2, 1, 1),
                         Point(2.1, 1, 0), Point(3, 1, 0)};

        VerticesAndFacesGenerator vfg(loader.triangles(), 1, 1, 0);
        TriangularMeshGenerator tmg(vfg.vertices(), vfg.faces());

        ToolPathGenerator tpg(tmg.polyhedron(), 0.1, 0);
        tpg.setVolume(3, 2, 2);
        std::list<Point> listaPunti = tpg.getToolPath(1);
        bool test = true;
        int i = 0;

        QVERIFY(listaPunti.size() == 6);
        for (auto p : listaPunti)
        {
            if(p != punti[i])
            {
                test = false;
                break;
            }
            i++;
        }
        QVERIFY(test);
    }
};

QTEST_MAIN(ToolPathGenerator_Test)
#include "toolpathgenerator_test.moc"
