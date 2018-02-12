#include "toolpathgenerator.h"


ToolPathGenerator::ToolPathGenerator(const Polyhedron &P, double step, int diam) : tree(faces(P).first, faces(P).second, P)
{
    stepSize = step;
    diameter = diam;
}

std::list<Point> ToolPathGenerator::getToolPath(double y)
{
    std::list<Point> result;

    QFuture<std::vector<Point>> futureMinus = QtConcurrent::run(this, &ToolPathGenerator::getRayIntersections, y - (diameter / 2.0));
    QFuture<std::vector<Point>> futureMinusmed = QtConcurrent::run(this, &ToolPathGenerator::getRayIntersections, y - (diameter / 4.0));
    QFuture<std::vector<Point>> futurePlusmed = QtConcurrent::run(this, &ToolPathGenerator::getRayIntersections, y + (diameter / 4.0));
    QFuture<std::vector<Point>> futurePlus = QtConcurrent::run(this, &ToolPathGenerator::getRayIntersections, y + (diameter / 2.0));
    QFuture<std::vector<Point>> futurePath = QtConcurrent::run(this, &ToolPathGenerator::getRayIntersections, y);

    futureMinus.waitForFinished();
    futureMinusmed.waitForFinished();
    futurePlusmed.waitForFinished();
    futurePlus.waitForFinished();
    futurePath.waitForFinished();

    std::vector<Point> pathMinusmed = futureMinusmed.result();
    std::vector<Point> pathPlusmed = futurePlusmed.result();
    std::vector<Point> pathPlus = futurePlus.result();
    std::vector<Point> pathMinus = futureMinus.result();
    std::vector<Point> path = futurePath.result();

    for (int i = 0; i< path.size(); ++i)
    {
        //        std::cout << "Y is " << y << std::endl;
        Point compare1 = (pathMinus[i].z() > pathPlus[i].z()) ? pathMinus[i] : pathPlus[i];
        //        std::cout << "compare " << pathMinus[i] << " and " << pathPlus[i] << " winner is " << compare1 << std::endl;
        Point compare2 = (pathMinusmed[i].z() > pathPlusmed[i].z()) ? pathMinusmed[i] : pathPlusmed[i];
        //        std::cout << "compare " << pathMinusmed[i] << " and " << pathPlusmed[i] << " winner is " << compare2 << std::endl;
        Point compare = (compare1.z() > compare2.z()) ? compare1 : compare2;
        //        std::cout << "compare " << compare1 << " and " <<compare2 << " winner is " << compare << std::endl;
        Point right = (compare.z() > path[i].z()) ? Point(compare.x(), y, compare.z()) : Point(path[i].x(), y, path[i].z());
        //        std::cout << "compare " << compare << " and " << path[i] << " winner is " << right << std::endl;
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
    int steps = (int) round(sizemm / stepSize);


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
                    double tx = point.x();
                    double ty = point.y();
                    double tz = point.z();
                    temp = Point(tx, ty, tz);
                }
            }
        }
        point = temp;
    }
    return point;
}

void ToolPathGenerator::setVolume(int x, int y, int z)
{
    volume_x = x;
    volume_y = y;
    volume_z = z;
}
