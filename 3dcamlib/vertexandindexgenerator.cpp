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

#include "vertexandindexgenerator.h"

VertexAndIndexGenerator::VertexAndIndexGenerator(const StlLoader::Triangles& triangles)
    : m_vertices()
    , m_faces()
{
    for (auto i = 0u; i < triangles.size(); ++i) {
        const auto& t = triangles[i];

        m_vertices.push_back(vertexFromVec3(t.v1));
        m_vertices.push_back(vertexFromVec3(t.v2));
        m_vertices.push_back(vertexFromVec3(t.v3));

        m_faces.push_back(Face(i * 3, i * 3 + 1, i * 3 + 2));
    }
}

VertexAndIndexGenerator::Vertex VertexAndIndexGenerator::vertexFromVec3(const StlLoader::Vec3& v) const
{
    Vertex vertex;

    vertex.x = v.x;
    vertex.y = v.y;
    vertex.z = v.z;

    return vertex;
}
