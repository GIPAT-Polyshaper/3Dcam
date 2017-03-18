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
#include "vertexandindexgenerator.h"

// NOTES AND TODOS
//
// Wait to have an intermediate representation before writing this (vertex and indices to vertices)

/**
 * \brief The class to perform unit tests
 *
 * Each private slot is a test
 */
class VertexAndIndexGenerator_Test : public QObject
{
    Q_OBJECT

    using T = StlLoader::Triangle;
    using V = StlLoader::Vec3;

private slots:
    void return_empty_list_of_vertices_and_faces_when_the_list_of_triangles_is_empty()
    {
        VertexAndIndexGenerator v(StlLoader::Triangles{});

        QVERIFY(v.vertices().size() == 0);
        QVERIFY(v.faces().size() == 0);
    }

    void return_correct_result_for_one_triangle()
    {
        StlLoader::Triangles t{
            T(V(0, 0, 0), V(0, 0, 0), V(0, 1, 0), V(0, 0, 1))
        };

        VertexAndIndexGenerator v(t);

        QVERIFY(v.vertices().size() == 3);
        QVERIFY(checkVertex(v.vertices()[0], 0, 0, 0));
        QVERIFY(checkVertex(v.vertices()[1], 0, 1, 0));
        QVERIFY(checkVertex(v.vertices()[2], 0, 0, 1));
        QVERIFY(v.faces().size() == 1);
        QVERIFY(checkFace(v.faces()[0], 0, 1, 2));
    }

private:
    bool checkVertex(const VertexAndIndexGenerator::Vertex& v, double x, double y, double z)
    {
        return (v.x == x) && (v.y == y) && (v.z == z);
    }

    bool checkFace(const VertexAndIndexGenerator::Face& f, unsigned int v1, unsigned int v2, unsigned int v3)
    {
        return (f.v1 == v1) && (f.v2 == v2) && (f.v3 == v3);
    }
};

QTEST_MAIN(VertexAndIndexGenerator_Test)
#include "vertexandindexgenerator_test.moc"
