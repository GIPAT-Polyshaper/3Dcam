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

#include "triangularmeshgenerator.h"
#include <CGAL/Polyhedron_incremental_builder_3.h>

namespace {
    // Code to generate the polyhedron is adapted from http://doc.cgal.org/latest/Polyhedron/index.html#title14

    class BuildFromVerticesAndFaces : public CGAL::Modifier_base<Polyhedron::HalfedgeDS>
    {
    public:
        BuildFromVerticesAndFaces(const VerticesAndFacesGenerator::Vertices &vertices, const VerticesAndFacesGenerator::Faces &faces)
            : m_vertices(vertices)
            , m_faces(faces)
        {
        }

        void operator()(Polyhedron::HalfedgeDS& hds)
        {
            // The flag is whether the build process should be verbose or not. Set to false in production
            CGAL::Polyhedron_incremental_builder_3<Polyhedron::HalfedgeDS> b(hds, false);
            b.begin_surface(m_vertices.size(), m_faces.size());

            using Vertex = Polyhedron::HalfedgeDS::Vertex;
            using Point = Vertex::Point;

            for (const auto& v: m_vertices) {
                b.add_vertex(Point(v.x, v.y, v.z));
            }
            for (const auto& f: m_faces) {
                b.begin_facet();
                b.add_vertex_to_facet(f.v1);
                b.add_vertex_to_facet(f.v2);
                b.add_vertex_to_facet(f.v3);
                b.end_facet();
            }
            b.end_surface();
        }

    private:
        const VerticesAndFacesGenerator::Vertices &m_vertices;
        const VerticesAndFacesGenerator::Faces &m_faces;
    };

    Polyhedron generatePolyhedron(const VerticesAndFacesGenerator::Vertices &vertices, const VerticesAndFacesGenerator::Faces &faces)
    {
        Polyhedron p;

        BuildFromVerticesAndFaces b(vertices, faces);
        p.delegate(b);

        return p;
    }
}

TriangularMeshGenerator::TriangularMeshGenerator(const VerticesAndFacesGenerator::Vertices &vertices, const VerticesAndFacesGenerator::Faces &faces)
    : m_polyhedron(generatePolyhedron(vertices, faces))
{
}
