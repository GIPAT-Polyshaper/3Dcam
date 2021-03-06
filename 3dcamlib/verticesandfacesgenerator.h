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

#ifndef VERTICESANDFACESGENERATOR_H
#define VERTICESANDFACESGENERATOR_H

#include <vector>
#include <array>
#include "stlloader.h"

/**
 * @brief The class generating faces with vertex indices
 *
 * This class takes a list of StlLoader::Triangles and generates structures
 * that are suitable to be used by TriangularMeshGenerator: a list of all
 * vertices and a list of faces in which each face is defined by the index
 * of its vertices in the list of all vertices
 */
class VerticesAndFacesGenerator
{
public:
    /**
     * @brief A vertex of a face in the 3D space
     */
    struct Vertex {
        double x;
        double y;
        double z;

        // faces[i] is the list of faces for which this vertex is the i-th vertex.
        // This is needed to keep the same vertex order for faces as in the original
        // structure
        std::array<std::vector<unsigned int>, 3> faces;
    };

    /**
     * @brief A face, with its verteices identified by the index in the
     *        vector of vertices
     */
    struct Face {
        unsigned int v1;
        unsigned int v2;
        unsigned int v3;
    };

    /**
     * @brief The type of the list of vertices
     */
    using Vertices = std::vector<Vertex>;

    /**
     * @brief The type of a list of faces
     */
    using Faces = std::vector<Face>;

public:
    /**
     * @brief Constructor
     *
     * @param triangles the list of triangles
     */
    VerticesAndFacesGenerator(const StlLoader::Triangles& triangles, float x_offset = 0, float y_offset = 0, float z_offset = 0);

    /**
     * @brief Returns the list of vertices
     */
    const Vertices& vertices() const
    {
        return m_vertices;
    }

    /**
     * @brief Returns the list of faces
     */
    const Faces& faces() const
    {
        return m_faces;
    }

private:
    const Vertices m_vertices;
    const Faces m_faces;
};

#endif // VERTICESANDFACESGENERATOR_H
