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
#include "verticesandfacesgenerator.h"

// NOTES AND TODOS
//
// Wait to have an intermediate representation before writing this (vertex and indices to vertices)

/**
 * \brief The class to perform unit tests
 *
 * Each private slot is a test
 */
class VerticesAndFacesGenerator_Test : public QObject
{
    Q_OBJECT

    using T = StlLoader::Triangle;
    using V = StlLoader::Vec3;

private slots:
    void return_empty_list_of_vertices_and_faces_when_the_list_of_triangles_is_empty()
    {
        VerticesAndFacesGenerator v(StlLoader::Triangles{});

        QVERIFY(v.vertices().size() == 0);
        QVERIFY(v.faces().size() == 0);
    }

    void return_correct_result_for_one_triangle()
    {
        StlLoader::Triangles t{
            T(V(0, 0, 0), V(0, 0, 0), V(0, 1, 0), V(0, 0, 1))
        };

        VerticesAndFacesGenerator v(t);

        QVERIFY(v.vertices().size() == 3);
        QVERIFY(verifyAllVertices(t, v));
        QVERIFY(verifyAllFaces(t, v));
    }

    void return_correct_result_for_multiple_triangles()
    {
        StlLoader::Triangles t{
            T(V(0, 0, 0), V(0, 0, 0), V(0, 1, 0), V(0, 0, 1)),
            T(V(0, 0, 0), V(1, 0, 0), V(1, 1, 0), V(1, 0, 1)),
            T(V(0, 0, 0), V(2, 0, 0), V(2, 1, 0), V(2, 0, 1)),
        };

        VerticesAndFacesGenerator v(t);

        QVERIFY(v.vertices().size() == 9);
        QVERIFY(verifyAllVertices(t, v));
        QVERIFY(verifyAllFaces(t, v));
    }

    void return_correct_result_with_shared_equal_vertices()
    {
        StlLoader::Triangles t{
            T(V(0, 0, 0), V(0, 0, 0), V(0, 1, 0), V(0, 0, 1)),
            T(V(0, 0, 0), V(0, 1, 0), V(0, 1, 1), V(0, 0, 1)),
            T(V(0, 0, 0), V(0, 1, 0), V(0, 1, 1), V(0, 2, 1)),
        };

        VerticesAndFacesGenerator v(t);

        QVERIFY(false);
        //QUI VERIFICARE CHE VENGANO TOLTI VERTICI DUPLICATI
    }

private:
    // The two following functions work by verifying that vertices and faces in the VerticesAndFacesGenerator correspond to
    // the original ones in Triangles. They are not optimized (verifyAllVertices is O(n^2))

    bool verifyAllVertices(const StlLoader::Triangles& triangles, const VerticesAndFacesGenerator& verticesAndFaces)
    {
        // The bool is to flag whether the vertices has been found or not
        std::vector<std::pair<StlLoader::Vec3, bool>> allVertices;

        // Filling allVertices
        for (const auto& t: triangles) {
            allVertices.push_back(std::pair<StlLoader::Vec3, bool>(t.v1, false));
            allVertices.push_back(std::pair<StlLoader::Vec3, bool>(t.v2, false));
            allVertices.push_back(std::pair<StlLoader::Vec3, bool>(t.v3, false));
        }

        // Matching generated vertices and flagging found vertices in allVertices. This also checks that all generated
        // vertices are found in the original triangles
        for (const auto& g: verticesAndFaces.vertices()) {
            bool found = false;
            for (auto& v: allVertices) {
                if (checkVertex(g, v.first)) {
                    v.second = true;
                    found = true;
                }
            }
            if (!found) {
                return false;
            }
        }

        // Checking that all vertices have been found
        for (const auto& v: allVertices) {
            if (!v.second) {
                return false;
            }
        }

        return true;
    }

    bool verifyAllFaces(const StlLoader::Triangles& triangles, const VerticesAndFacesGenerator& verticesAndFaces)
    {
        if (triangles.size() != verticesAndFaces.faces().size()) {
            return false;
        }

        for (auto i = 0u; i < triangles.size(); ++i) {
            const auto& f = verticesAndFaces.faces();

            if (!checkVertex(verticesAndFaces.vertices()[f[i].v1], triangles[i].v1)) {
                return false;
            }
            if (!checkVertex(verticesAndFaces.vertices()[f[i].v2], triangles[i].v2)) {
                return false;
            }
            if (!checkVertex(verticesAndFaces.vertices()[f[i].v3], triangles[i].v3)) {
                return false;
            }
        }

        return true;
    }

    bool checkVertex(const VerticesAndFacesGenerator::Vertex& g, const StlLoader::Vec3& v)
    {
        return (g.x == v.x) && (g.y == v.y) && (g.z == v.z);
    }
};

QTEST_MAIN(VerticesAndFacesGenerator_Test)
#include "verticesandfacesgenerator_test.moc"
