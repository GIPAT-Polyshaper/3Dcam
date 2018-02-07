#include "toolpathgenerator.h"
#include <cmath>

const float EPSILON = 0.00000001;

float roundFloat(float d)
{
    float num = d / EPSILON;
    num = round(num);
    return num * EPSILON;
}

ToolPathGenerator::ToolPathGenerator(const Polyhedron &P) : tree(faces(P).first, faces(P).second, P)
{

}

std::list<Point3> ToolPathGenerator::getRayIntersections(float y)
{
    y = roundFloat(y);
    std::list<Point> punti;
    std::list<Point> risultato;

    std::list<Segment> listaSegmenti = getBoundarySegments(y);

    if (listaSegmenti.size() > 0)
    {
        float max_x = volume_x;

        for (auto s : listaSegmenti)
        {
            float sx = roundFloat(s.source().x());
            float sy = roundFloat(s.source().y());
            float sz = roundFloat(s.source().z());

            float tx = roundFloat(s.target().x());
            float ty = roundFloat(s.target().y());
            float tz = roundFloat(s.target().z());

            Point p(sx, sy, 2048);


            Point point = getIntersection(p);

            if (point.z() < sz)
            {
                point = Point(sx, sy, sz);
            }
            punti.push_back(point);

            p = Point(tx, ty, 2048);
            point = getIntersection(p);

            if (point.z() < tz)
            {
                point = Point(tx, ty, tz);
            }
            punti.push_back(point);
        }

        punti.sort([](const Point &f, const Point &s) { return f.x() < s.x(); });

        Point first = *punti.begin();
        Point last = *punti.rbegin();

        if (first.z() != 0)
        {
            punti.push_front(Point(first.x(), first.y(), 0));
        }
        punti.push_front(Point(0, first.y(), 0));

        if (last.z() != 0)
        {
            punti.push_back(Point(last.x(), last.y(), 0));
        }
        punti.push_back(Point(max_x, last.y(), 0));

        punti.unique();
        for (auto point : punti)
        {
            if (risultato.size() >= 2)
            {
                std::list<Point>::reverse_iterator rIt = risultato.rbegin();
                Point end = *rIt;
                rIt++;
                Point start = *rIt;
                Segment test(start, end);
                Segment temp(end, point);
                if (test.direction() == temp.direction())
                {
                    risultato.pop_back();
                }

            }
            risultato.push_back(point);
        }
    }
    return risultato;
}

Point ToolPathGenerator::getIntersection(Point p)
{
    Vector v (0, 0, -1);
    Ray ray(p, v);

    std::list<Object_and_primitive_id> intersections;

    Point point;

    tree.all_intersections(ray,std::back_inserter(intersections));

    if (intersections.empty())
    {
        point = Point(p.x(), p.y(), 0);
    }
    else
    {
        Point temp(0, 0, 0);
        for(auto op : intersections)
        {
            CGAL::Object object = op.first;

            if(CGAL::assign(point,object))
            {
                if (point.z() >= temp.z())
                {
                    float tx = roundFloat(point.x());
                    float ty = roundFloat(point.y());
                    float tz = roundFloat(point.z());
                    temp = Point(tx, ty, tz);
                }
            }
        }
        point = temp;
    }
    return point;
}

std::list<Segment> ToolPathGenerator::getBoundarySegments(float y)
{
    Vector normal(0, 1, 0);

    std::list<Segment> segments;

    Point p(0, y, 0);

    Plane plane(p,normal);

    std::list<Object_and_primitive_id> intersections;

    if (tree.number_of_intersected_primitives(plane) > 0)
    {
        tree.all_intersections(plane,std::back_inserter(intersections));
        for(auto op : intersections)
        {
            CGAL::Object object = op.first;
            Segment segment;
            if(CGAL::assign(segment,object))
                segments.push_back(segment);
        }
    }
    return segments;
}

void ToolPathGenerator::setVolume(float x, float y, float z)
{
    volume_x = x;
    volume_y = y;
    volume_z = z;
}
