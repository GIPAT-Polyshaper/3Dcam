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

#include "verticesandfacesgenerator.h"
#include <algorithm>

namespace {
    VerticesAndFacesGenerator::Vertex vertexFromVec3AndFaceIndex(const StlLoader::Vec3& v, unsigned int face, unsigned int positionInFace)
    {
        VerticesAndFacesGenerator::Vertex vertex;

        vertex.x = v.x;
        vertex.y = v.y;
        vertex.z = v.z;
        vertex.faces[positionInFace].push_back(face);

        return vertex;
    }

    // Returns true if two vertex are the same
    bool equalVertices(const VerticesAndFacesGenerator::Vertex& v1, const VerticesAndFacesGenerator::Vertex& v2)
    {
        return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z);
    }

    // Returns true if v1 is less than v2. First x is compared, if equal y is compared and if equal x is compared
    bool compareVertices(const VerticesAndFacesGenerator::Vertex& v1, const VerticesAndFacesGenerator::Vertex& v2)
    {
        if (v1.x < v2.x) {
            return true;
        } else if (v1.x > v2.x) {
            return false;
        } else {
            if (v1.y < v2.y) {
                return true;
            } else if (v1.y > v2.y) {
                return false;
            } else {
                return (v1.z < v2.z);
            }
        }
    }

    void addFacesFromOtherVertex(VerticesAndFacesGenerator::Vertex& v1, const VerticesAndFacesGenerator::Vertex& v2)
    {
        v1.faces[0].insert(v1.faces[0].end(), v2.faces[0].begin(), v2.faces[0].end());
        v1.faces[1].insert(v1.faces[1].end(), v2.faces[1].begin(), v2.faces[1].end());
        v1.faces[2].insert(v1.faces[2].end(), v2.faces[2].begin(), v2.faces[2].end());
    }

    VerticesAndFacesGenerator::Vertices extractVertices(const StlLoader::Triangles& triangles, float x_offset = 0, float y_offset = 0, float z_offset = 0)
    {
        VerticesAndFacesGenerator::Vertices vertices;

        // Copying all vertex from triangles into vertices
        for (auto i = 0u; i < triangles.size(); ++i) {
            const auto& t = triangles[i];

            StlLoader::Vec3 v1, v2, v3;

            v1.x = t.v1.x + x_offset;
            v2.x = t.v2.x + x_offset;
            v3.x = t.v3.x + x_offset;

            v1.y = t.v1.y + y_offset;
            v2.y = t.v2.y + y_offset;
            v3.y = t.v3.y + y_offset;

            v1.z = t.v1.z + z_offset;
            v2.z = t.v2.z + z_offset;
            v3.z = t.v3.z + z_offset;

            vertices.push_back(vertexFromVec3AndFaceIndex(v1, i, 0));
            vertices.push_back(vertexFromVec3AndFaceIndex(v2, i, 1));
            vertices.push_back(vertexFromVec3AndFaceIndex(v3, i, 2));
        }

        // Sorting vertices
        std::sort(vertices.begin(), vertices.end(), compareVertices);

        // Excluding repeated vertices. They are sorted, so equal vertices will be near to each other
        VerticesAndFacesGenerator::Vertices uniqueVertices;
        if (vertices.size() != 0) {
            uniqueVertices.push_back(vertices.front());
            for (auto it = vertices.begin() + 1; it != vertices.end(); ++it) {
                auto& last = uniqueVertices.back();
                if (equalVertices(last, *it)) {
                    addFacesFromOtherVertex(last, *it);
                } else {
                    uniqueVertices.emplace_back(*it);
                }
            }
        }

        return uniqueVertices;
    }

    // The number of faces is equal to the number of triangles in the list passed to VerticesAndFacesGenerator constructor
    VerticesAndFacesGenerator::Faces generateFaces(const VerticesAndFacesGenerator::Vertices& vertices, unsigned int numFaces)
    {
        VerticesAndFacesGenerator::Faces faces(numFaces);

        for (auto i = 0u; i < vertices.size(); ++i) {
            const auto& v = vertices[i];

            for (auto f: v.faces[0]) {
                faces[f].v1 = i;
            }
            for (auto f: v.faces[1]) {
                faces[f].v2 = i;
            }
            for (auto f: v.faces[2]) {
                faces[f].v3 = i;
            }
        }

        return faces;
    }
}

VerticesAndFacesGenerator::VerticesAndFacesGenerator(const StlLoader::Triangles& triangles, float x_offset, float y_offset, float z_offset)
    : m_vertices(extractVertices(triangles, x_offset, y_offset, z_offset))
    , m_faces(generateFaces(m_vertices, triangles.size()))
{
}
