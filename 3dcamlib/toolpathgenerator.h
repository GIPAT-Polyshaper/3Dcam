#ifndef TOOLPATHGENERATOR_H
#define TOOLPATHGENERATOR_H

#include "cgaldefs.h"
#include <CGAL/AABB_tree.h>
#include <CGAL/AABB_traits.h>
#include <CGAL/AABB_face_graph_triangle_primitive.h>

using Point = Kernel::Point_3;
using Plane = Kernel::Plane_3;
using Vector = Kernel::Vector_3;
using Segment = Kernel::Segment_3;
using Ray = Kernel::Ray_3;

using Primitive = CGAL::AABB_face_graph_triangle_primitive<Polyhedron>;
using Traits = CGAL::AABB_traits<Kernel, Primitive>;
using Tree = CGAL::AABB_tree<Traits>;
using Object_and_primitive_id = Tree::Object_and_primitive_id;

class ToolPathGenerator
{
public:
    ToolPathGenerator(const Polyhedron& P);
    std::list<Segment> getBoundarySegments(float y);
    std::list<Point> getRayIntersections(float y);
    void setVolume(float x, float y, float z);

private:
    float volume_x;
    float volume_y;
    float volume_z;

    Tree tree;

    Point getIntersection(Point r);
};

#endif // TOOLPATHGENERATOR_H
