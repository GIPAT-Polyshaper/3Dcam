#ifndef TOOLPATHGENERATOR_H
#define TOOLPATHGENERATOR_H

#include "cgaldefs.h"
#include <CGAL/AABB_tree.h>
#include <CGAL/AABB_traits.h>
#include <CGAL/boost/graph/graph_traits_Polyhedron_3.h>
#include <CGAL/AABB_halfedge_graph_segment_primitive.h>
#include <CGAL/AABB_face_graph_triangle_primitive.h>
#include <vector>
#include <CGAL/Timer.h>

#include <CGAL/Cartesian.h>
#include <CGAL/MP_Float.h>
#include <CGAL/Quotient.h>
#include <CGAL/Arr_segment_traits_2.h>
#include <CGAL/Arrangement_2.h>

typedef Kernel::Point_3 Point;
typedef Kernel::Plane_3 Plane;
typedef Kernel::Vector_3 Vector;
typedef Kernel::Segment_3 Segment;
typedef Kernel::Direction_3 Direction_3;
typedef Kernel::FT FT;

typedef CGAL::Quotient<CGAL::MP_Float> Number_type;
typedef CGAL::Arr_segment_traits_2<Kernel> Traits_2;
typedef Traits_2::Point_2 Point_2;
typedef Traits_2::X_monotone_curve_2 Segment_2;
typedef CGAL::Arrangement_2<Traits_2> Arrangement_2;

typedef CGAL::AABB_face_graph_triangle_primitive<Polyhedron> Primitive;
typedef CGAL::AABB_traits<Kernel, Primitive> Traits;
typedef CGAL::AABB_tree<Traits> Tree;

class ToolPathGenerator
{
public:
    ToolPathGenerator();
    void generate_boundary_segments(const Polyhedron &P);

    std::list<Segment> orderSegments(std::list<Segment> &list);
    void generate_ray_intersections(const Polyhedron &P);
    std::list<Segment> getBoundarySegments(float y, Tree &tree);
    std::list<Point> getRayIntersections(float y, const Polyhedron &P);
private:
    Point getIntersection(Point r, Tree &tree);
};

#endif // TOOLPATHGENERATOR_H
