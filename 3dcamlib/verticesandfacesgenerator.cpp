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
#include <QDebug>

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

    VerticesAndFacesGenerator::Vertices extractVertices(const StlLoader::Triangles& triangles)
    {
        VerticesAndFacesGenerator::Vertices vertices;

        for (auto i = 0u; i < triangles.size(); ++i) {
            const auto& t = triangles[i];

            vertices.push_back(vertexFromVec3AndFaceIndex(t.v1, i, 0));
            vertices.push_back(vertexFromVec3AndFaceIndex(t.v2, i, 1));
            vertices.push_back(vertexFromVec3AndFaceIndex(t.v3, i, 2));
        }

        return vertices;
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

VerticesAndFacesGenerator::VerticesAndFacesGenerator(const StlLoader::Triangles& triangles)
    : m_vertices(extractVertices(triangles))
    , m_faces(generateFaces(m_vertices, triangles.size()))
{
}
