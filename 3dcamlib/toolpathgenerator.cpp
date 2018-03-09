#include "toolpathgenerator.h"


ToolPathGenerator::ToolPathGenerator(const Polyhedron &P, double step, int diam) : tree(faces(P).first, faces(P).second, P)
{
    stepSize = step;
    diameter = diam;
}

std::list<Point> ToolPathGenerator::getToolPath(double y)
{
    std::list<Point> result;

    QFuture<std::vector<Point>> futureMinus = QtConcurrent::run(this,
                                                                &ToolPathGenerator::getRayIntersections,
                                                                y - (diameter / 2.0));

    QFuture<std::vector<Point>> futurePlus = QtConcurrent::run(this,
                                                               &ToolPathGenerator::getRayIntersections,
                                                               y + (diameter / 2.0));
    QFuture<std::vector<Point>> futurePath = QtConcurrent::run(this,
                                                               &ToolPathGenerator::getRayIntersections,
                                                               y);

    std::vector<Point> pathPlus = futurePlus.result();
    std::vector<Point> pathMinus = futureMinus.result();
    std::vector<Point> path = futurePath.result();

    for (int i = 0; i< path.size(); ++i)
    {
        Point compare = (pathMinus[i].z() > pathPlus[i].z()) ? pathMinus[i] : pathPlus[i];
        Point right = (compare.z() > path[i].z()) ?
                    Point(compare.x(), y, compare.z()) :
                    Point(path[i].x(), y, path[i].z());

        if(result.size() < 2)
        {
            result.push_back(right);
        }
        else
        {
            std::list<Point>::reverse_iterator rIt = result.rbegin();
            Point end = *rIt;
            rIt++;
            Point start = *rIt;
            Segment test(start, end);
            Segment temp(end, right);

            if (test.direction() == temp.direction())
            {
                result.pop_back();
            }
            result.push_back(right);
        }
    }

    if (*result.begin() != Point(0, result.begin()->y(), 0))
    {
        result.push_front(Point(0, result.begin()->y(), 0));
    }

    if (*result.rbegin() != Point(volume_x, result.rbegin()->y(), 0))
    {
        result.push_back(Point(volume_x, result.rbegin()->y(), 0));
    }
    return result;
}

std::vector<Point> ToolPathGenerator::getRayIntersections(double Y)
{
    int sizemm = volume_x;
    int steps = (int) ceil(sizemm / stepSize);


    std::vector<Point> punti;
    for (int i = 0; i <= steps; i++)
    {
        double j = stepSize * i;
        Point p(j, Y, 2048);
        Point point = getIntersection(p);

        punti.push_back(point);
    }
    return punti;
}

Point ToolPathGenerator::getIntersection(Point p)
{
    Vector v (0, 0, -1);
    Ray ray(p, v);

    Point point;
    double tx, ty, tz;

    std::list<Object_and_primitive_id> intersections;

    tree.all_intersections(ray,std::back_inserter(intersections));

    if (intersections.empty())
    {
        tx = p.x();
        ty = p.y();
        tz = 0;
    }
    else
    {
        tx = ty = tz = 0;
        for(auto op : intersections)
        {
            CGAL::Object object = op.first;

            if(CGAL::assign(point,object))
            {
                if (point.z() >= tz)
                {
                    tx = point.x();
                    ty = point.y();
                    tz = point.z();
                }
            }
        }
    }
    if (tx > volume_x)
    {
        tx = volume_x;
    }
    return Point(tx, ty, tz);
}

void ToolPathGenerator::setVolume(int x, int y, int z)
{
    volume_x = x;
    volume_y = y;
    volume_z = z;
}
