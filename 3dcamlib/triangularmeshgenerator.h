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

#ifndef TRIANGULARMESHGENERATOR_H
#define TRIANGULARMESHGENERATOR_H

#include <exception>
#include "cgaldefs.h"
#include "verticesandfacesgenerator.h"

/**
 * @brief The class loading an STL file
 */
class TriangularMeshGenerator
{
public:
    /**
     * @brief Constructor
     *
     * @param triangles the list of triangles
     */
    TriangularMeshGenerator(const VerticesAndFacesGenerator::Vertices& vertices, const VerticesAndFacesGenerator::Faces& faces);

    /**
     * @brief Returns the polyhedron built by the constructor
     */
    const Polyhedron& polyhedron() const
    {
        return m_polyhedron;
    }

private:
    const Polyhedron m_polyhedron;
};

#endif // TRIANGULARMESHGENERATOR_H
