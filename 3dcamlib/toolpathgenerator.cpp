#include "toolpathgenerator.h"

ToolPathGenerator::ToolPathGenerator(const Polyhedron &P) : tree(faces(P).first, faces(P).second, P)
{

}

std::list<Point3> ToolPathGenerator::getRayIntersections(float y)
{
    std::map<float, Point> punti;
    std::list<Point> risultato;

    std::list<Segment> listaSegmenti = getBoundarySegments(y);

    if (listaSegmenti.size() > 0)
    {
        float max_x = volume_x;

        for (auto s : listaSegmenti)
        {
            float sx = s.source().x();
            float sy = s.source().y();
            float sz = s.source().z();

            float tx = s.target().x();
            float ty = s.target().y();
            float tz = s.target().z();

            Point p(sx, sy, 2048);

            Point point = getIntersection(p);

            if (point.z() < sz)
            {
                point = Point(sx, sy, sz);
            }

            if (punti.count(sx) > 0)
            {
                if (punti[sx].z() < point.z())
                {
                    punti[sx] = point;
                }
            }
            else
            {
                punti[sx] = point;
            }

            p = Point(tx, ty, 2048);
            point = getIntersection(p);

            if (point.z() < tz)
            {
                point = Point(tx, ty, tz);
            }

            if (punti.count(tx) > 0)
            {
                if (punti[tx].z() < point.z())
                {
                    punti[tx] = point;
                }
            }
            else
            {
                punti[tx] = point;
            }
        }

        for (auto point : punti)
        {
            if (risultato.size() >= 2)
            {
                std::list<Point>::reverse_iterator rIt = risultato.rbegin();
                Point end = *rIt;
                rIt++;
                Point start = *rIt;
                Segment test(start, end);
                Segment temp(end, point.second);
                if (test.direction() == temp.direction())
                {
                    risultato.pop_back();
                }

            }
            Point pminus = getIntersection(Point(point.second.x()-0.0001, point.second.y(), 2048));
            Point pplus = getIntersection(Point(point.second.x()+0.0001, point.second.y(), 2048));
            if (pminus.z() == 0)
            {
                risultato.push_back(Point(point.second.x(), point.second.y(), 0));
            }

            risultato.push_back(point.second);

            if (pplus.z() == 0)
            {
                risultato.push_back(Point(point.second.x(), point.second.y(), 0));
            }
        }

        Point first = *risultato.begin();
        Point last = *risultato.rbegin();

        if (first.z() != 0)
        {
            risultato.push_front(Point(first.x(), first.y(), 0));
        }

        if (*risultato.begin() != Point(0, risultato.begin()->y(), 0))
        {
            risultato.push_front(Point(0, risultato.begin()->y(), 0));
        }

        if (last.z() != 0)
        {
            risultato.push_back(Point(last.x(), last.y(), 0));
        }

        if (*risultato.rbegin() != Point(max_x, risultato.rbegin()->y(), 0))
        {
            risultato.push_back(Point(max_x, risultato.rbegin()->y(), 0));
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
                    float tx = point.x();
                    float ty = point.y();
                    float tz = point.z();
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
