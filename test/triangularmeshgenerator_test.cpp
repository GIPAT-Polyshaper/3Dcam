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
#include "triangularmeshgenerator.h"

// NOTES AND TODOS
//

/**
 * \brief The class to perform unit tests
 *
 * Each private slot is a test
 */
class TriangularMeshGenerator_Test : public QObject
{
	Q_OBJECT

private slots:
    void return_empty_polyhedron_when_initialized_with_empy_triangles()
    {
        TriangularMeshGenerator t(VerticesAndFacesGenerator::Vertices{}, VerticesAndFacesGenerator::Faces{});

        QVERIFY(t.polyhedron().empty());
	}

    void return_polyhedron_with_one_triangle()
    {
        VerticesAndFacesGenerator::Vertices v{
            V(0, 0, 0, Fi{0}, Fi{}, Fi{}),
            V(0, 1, 0, Fi{}, Fi{0}, Fi{}),
            V(0, 0, 1, Fi{}, Fi{}, Fi{0}),
        };
        VerticesAndFacesGenerator::Faces f{
            F(0, 1, 2)
        };

        TriangularMeshGenerator t(v, f);

        QVERIFY(t.polyhedron().is_pure_triangle());
        QCOMPARE(t.polyhedron().size_of_vertices(), 3ul);
        QCOMPARE(t.polyhedron().size_of_facets(), 1ul);
        QVERIFY(t.polyhedron().is_valid(true, 0));
    }

    void return_polyhedron_with_a_tetrahedron()
    {
        VerticesAndFacesGenerator::Vertices v{
            V(0, 0, 0, Fi{0, 1, 2}, Fi{}, Fi{}),
            V(0, 1, 0, Fi{3}, Fi{0}, Fi{1}),
            V(0, 0, 1, Fi{}, Fi{2}, Fi{0, 3}),
            V(1, 0, 0, Fi{}, Fi{1, 3}, Fi{2})
        };
        VerticesAndFacesGenerator::Faces f{
            F(0, 1, 2),
            F(0, 3, 1),
            F(0, 2, 3),
            F(1, 3, 2)
        };

        TriangularMeshGenerator t(v, f);

        QVERIFY(t.polyhedron().is_pure_triangle());
        QCOMPARE(t.polyhedron().size_of_vertices(), 4ul);
        QCOMPARE(t.polyhedron().size_of_facets(), 4ul);
        QVERIFY(t.polyhedron().is_valid(true, 0));
    }

    void return_polyhedron_with_two_separated_tetrahedrons()
    {
        VerticesAndFacesGenerator::Vertices v{
            // first tetrahedron
            V(0, 0, 0, Fi{0, 1, 2}, Fi{}, Fi{}),
            V(0, 1, 0, Fi{3}, Fi{0}, Fi{1}),
            V(0, 0, 1, Fi{}, Fi{2}, Fi{0, 3}),
            V(1, 0, 0, Fi{}, Fi{1, 3}, Fi{2}),

            // second tetrahedron
            V(10, 0, 0, Fi{4, 5, 6}, Fi{}, Fi{}),
            V(10, 1, 0, Fi{3}, Fi{4}, Fi{5}),
            V(10, 0, 1, Fi{}, Fi{6}, Fi{4, 7}),
            V(11, 0, 0, Fi{}, Fi{5, 7}, Fi{6})
        };
        VerticesAndFacesGenerator::Faces f{
            // first tetrahedron
            F(0, 1, 2),
            F(0, 3, 1),
            F(0, 2, 3),
            F(1, 3, 2),

            // second tetrahedron
            F(4, 5, 6),
            F(4, 7, 5),
            F(4, 6, 7),
            F(5, 7, 6)
        };

        TriangularMeshGenerator t(v, f);

        QVERIFY(t.polyhedron().is_pure_triangle());
        QCOMPARE(t.polyhedron().size_of_vertices(), 8ul);
        QCOMPARE(t.polyhedron().size_of_facets(), 8ul);
        QVERIFY(t.polyhedron().is_valid(true, 0));
    }

private:
    using Fi = std::vector<unsigned int>;

    VerticesAndFacesGenerator::Vertex V(double x, double y, double z, Fi&& f1, Fi&& f2, Fi&& f3) const
    {
        VerticesAndFacesGenerator::Vertex v;

        v.x = x;
        v.y = y;
        v.z = z;
        v.faces[0] = std::move(f1);
        v.faces[1] = std::move(f2);
        v.faces[2] = std::move(f3);

        return v;
    }

    VerticesAndFacesGenerator::Face F(unsigned int v1, unsigned int v2, unsigned int v3) const
    {
        VerticesAndFacesGenerator::Face f;

        f.v1 = v1;
        f.v2 = v2;
        f.v3 = v3;

        return f;
    }
};

QTEST_MAIN(TriangularMeshGenerator_Test)
#include "triangularmeshgenerator_test.moc"
