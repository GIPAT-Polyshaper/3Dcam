#include "polyhedroncuttest.h"
#include <cmath>

const double EPSILON = 0.00000001;

double roundDouble(double d)
{
    double num = d * 10000;
    num = round(num);
    return num/10000;
}

bool isRealSegment(Segment s)
{
    return  (std::abs(s.source().x() - s.target().x()) > EPSILON) ||
            (std::abs(s.source().y() - s.target().y()) > EPSILON) ||
            (std::abs(s.source().z() - s.target().z()) > EPSILON);
}

bool pointsAreEqual(Point3 p1, Point3 p2)
{
    return  (std::abs(p1.x() - p2.x()) < EPSILON) &&
            (std::abs(p1.y() - p2.y()) < EPSILON) &&
            (std::abs(p1.z() - p2.z()) < EPSILON);
}

//bool isTwin(Segment t, std::list<Segment> &list)
//{
//    for (std::list<Segment>::iterator sit = list.begin(); sit != list.end(); sit++)
//    {
//        Segment s = *sit;
//        if (pointsAreEqual(s.target(), t.source()) && pointsAreEqual(s.source(), t.target()))
//        {
//            return true;
//        }
//    }
//    return false;
//}

bool isNotBackward(Segment s1, Segment s2)
{
    return !pointsAreEqual(s1.source(), s2.target());
}

bool isContiguous(Segment s1, Segment s2)
{
    if (pointsAreEqual(s1.target(), s2.source()))
    {
        return isNotBackward(s1, s2);
    }
    return false;
}

PolyhedronCutTest::PolyhedronCutTest()
{

}

void PolyhedronCutTest::generate_ray_intersections(const Polyhedron& P)
{
    typedef Kernel::Ray_3 Ray;

    typedef Tree::Object_and_primitive_id Object_and_primitive_id;
    typedef boost::optional<Tree::Intersection_and_primitive_id<Ray>::Type> Ray_intersection;

    double stepSize = 0.01;
    int sizemm = 100;
    int steps = (int) round(sizemm / stepSize);

    std::cout << steps << std::endl;

    std::cout << "Construct AABB tree...";
    Tree tree(faces(P).first,faces(P).second,P);
    std::cout << "done." << std::endl;
    std::list<Point> punti;
    for (int i = 1; i <= steps; i++)
    {
        double j = roundDouble(stepSize * i);
        Point p(j, 0.5, 2048);
        Vector v (0, 0, -1);
        Ray ray(p, v);
        std::cout << j << std::endl;
        std::list<Object_and_primitive_id> intersections;
        Point point;
        tree.all_intersections(ray,std::back_inserter(intersections));
        if (intersections.empty())
        {
            std::cout << "doesn't intersect" << std::endl;
            Point temp(j, 0.5, 0);
            point = temp;
        }
        else
        {
            std::list<Object_and_primitive_id>::iterator it;
            Point temp(0, 0, 0);
            for(it = intersections.begin(); it != intersections.end(); it++)
            {
                Object_and_primitive_id op = *it;
                CGAL::Object object = op.first;

                if(CGAL::assign(point,object))
                {
                    if (point.z() > temp.z())
                    {
                        double x = roundDouble(point.x());
                        double y = roundDouble(point.y());
                        double z = roundDouble(point.z());
                        temp = Point(x,y,z);
                    }
                }
            }
            point = temp;
            std::cout << point << std::endl;
        }

        if(punti.size()<2)
        {
            punti.push_back(point);
        }
        else
        {
            std::list<Point>::reverse_iterator rIt = punti.rbegin();
            Point end = *rIt;
            rIt++;
            Point start = *rIt;
            Segment test(start, end);
            Segment temp(end, point);
            Direction_3 dir1(roundDouble(test.direction().hdx()), roundDouble(test.direction().hdy()), roundDouble(test.direction().hdz()));
            Direction_3 dir2(roundDouble(temp.direction().hdx()), roundDouble(temp.direction().hdy()), roundDouble(temp.direction().hdz()));
            if (dir1 == dir2)
            {
                std::cout << "stessa direzione" << std::endl;
                punti.pop_back();
            }
            else
            {
                std::cout << "direzione 1: " << test.direction() << " direzione 2: " << temp.direction() << std::endl;
            }
            punti.push_back(point);
        }
        //        Ray_intersection intersection = tree.first_intersection(ray);

        //        if(intersection)
        //        {
        //            if(boost::get<Point>(&(intersection->first)))
        //            {
        //                const Point* p =  boost::get<Point>(&(intersection->first) );
        //                std::cout <<  *p << std::endl;
        //            }
        //        }
        //        else
        //        {
        //            std::cout << "doesn't intersect"<<std::endl;
        //        }
    }
    //    Point s1(0, 0, 0);
    //    Point e1(0, 0, 1);
    //    Segment seg1(s1, e1);
    //    Point s2(0, 0, 3);
    //    Point e2(0, 0, 5);
    //    Segment seg2(s2,e2);
    //    std::cout << "direzione 1: " << seg1.direction() << std::endl;
    //    std::cout << "direzione 2: " << seg2.direction() << std::endl;
    //    if (seg1.direction() == seg2.direction())
    //    {
    //        std::cout << "stessa direzione" << std::endl;
    //    }
    //    else
    //    {
    //        std::cout << "direzione diversa" << std::endl;
    //    }
    int i = 1;
    for (std::list<Point>::iterator pIt = punti.begin(); pIt != punti.end(); pIt++)
    {
        std::cout << "punto " << i << ": " << *pIt << std::endl;
        ++i;
    }
}

std::list<Point3> PolyhedronCutTest::getRayIntersections(double y, const Polyhedron& P)
{
    y = roundDouble(y);
    std::list<Point> punti;
    std::cout << "Construct AABB tree...";
    Tree tree(faces(P).first,faces(P).second,P);
    std::cout << "done." << std::endl;

//    tree.bbox();

    std::list<Segment> listaSegmenti = getBoundarySegments(y, tree);

    if (listaSegmenti.size() > 0){
        double max_x = 2048;

        //    punti.push_back(Point(0, y, 0));
        for (std::list<Segment>::iterator it = listaSegmenti.begin(); it != listaSegmenti.end(); it++)
        {
            Segment s = *it;
            double sx = roundDouble(s.source().x());
            double sy = roundDouble(s.source().y());
            double sz = roundDouble(s.source().z());

            double tx = roundDouble(s.target().x());
            double ty = roundDouble(s.target().y());
            double tz =  roundDouble(s.target().z());

            Point p(sx, sy, 2048);


            Point point = getIntersection(p, tree);

            if (point.z() < sz)
            {
                point = Point(sx, sy, sz);
            }
            punti.push_back(point);

            p = Point(tx, ty, 2048);
            point = getIntersection(p, tree);

            if (point.z() < tz)
            {
                point = Point(tx, ty, tz);
            }
            punti.push_back(point);
        }

        int i = 1;
        for (std::list<Point>::iterator pIt = punti.begin(); pIt != punti.end(); pIt++)
        {
            std::cout << "punto " << i << ": " << *pIt << std::endl;
            ++i;
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
        i = 1;
        for (std::list<Point>::iterator pIt = punti.begin(); pIt != punti.end(); pIt++)
        {
            std::cout << "punto " << i << ": " << *pIt << std::endl;
            ++i;
        }
    }
    return punti;
}

Point PolyhedronCutTest::getIntersection(Point p, Tree& tree)
{

    typedef Tree::Object_and_primitive_id Object_and_primitive_id;
    typedef Kernel::Ray_3 Ray;
    typedef boost::optional<Tree::Intersection_and_primitive_id<Ray>::Type> Ray_intersection;

    Vector v (0, 0, -1);
    Ray ray(p, v);

    std::list<Object_and_primitive_id> intersections;

    Point point;

    tree.all_intersections(ray,std::back_inserter(intersections));

    if (intersections.empty())
    {
        std::cout << "doesn't intersect" << std::endl;
        point = Point(p.x(), p.y(), 0);
    }
    else
    {
        std::list<Object_and_primitive_id>::iterator it;
        Point temp(0, 0, 0);
        for(it = intersections.begin(); it != intersections.end(); it++)
        {
            Object_and_primitive_id op = *it;
            CGAL::Object object = op.first;

            if(CGAL::assign(point,object))
            {
                if (point.z() >= temp.z())
                {
                    double tx = roundDouble(point.x());
                    double ty = roundDouble(point.y());
                    double tz = roundDouble(point.z());
                    temp = Point(tx, ty, tz);
                }
            }
        }
        point = temp;
    }
    return point;
}

std::list<Segment> PolyhedronCutTest::getBoundarySegments(double y, Tree& tree)
{
    typedef Tree::Object_and_primitive_id Object_and_primitive_id;

    CGAL::Timer timer;
    timer.start();
    std::cout << "Generate boundary segments" << std::endl;
    Vector normal(0, 1, 0);

    std::list<Segment> m_segments;

    Point p(0, y, 0);

    Plane plane(p,normal);

    std::list<Object_and_primitive_id> intersections;

    if (tree.number_of_intersected_primitives(plane) > 0)
    {
        std::cout << "si interseca qualcosa " << std::endl;
        tree.all_intersections(plane,std::back_inserter(intersections));


        std::list<Object_and_primitive_id>::iterator it;
        for(it = intersections.begin(); it != intersections.end(); it++)
        {
            Object_and_primitive_id op = *it;
            CGAL::Object object = op.first;
            Segment segment;
            if(CGAL::assign(segment,object))
                m_segments.push_back(segment);
        }
        int j=1;
        for (std::list<Segment>::iterator sit = m_segments.begin(); sit != m_segments.end(); sit++)
        {
            Segment s = *sit;
            std::cout<<"Segmento numero "<<j<<":"<<std::endl<<"inizio: "<<s.source()<<std::endl<<"fine: "<<s.target()<<std::endl;
            ++j;
        }
    }
    else
    {
        std::cout << "non si interseca nulla" << std::endl;
    }
    return m_segments;
}

void PolyhedronCutTest::generate_boundary_segments(const Polyhedron& P)
{
    typedef Tree::Object_and_primitive_id Object_and_primitive_id;

    std::cout << "Construct AABB tree...";
    Tree tree(faces(P).first,faces(P).second,P);
    std::cout << "done." << std::endl;

    CGAL::Timer timer;
    timer.start();
    std::cout << "Generate boundary segments" << std::endl;

    Vector normal((FT)0.0,(FT)1.0,(FT)0.0);
    unsigned int i;

    const double dy = 1 - 0;
    int nb_slices = 3;
    std::list<Segment> m_segments[nb_slices+1];

    for(i=0; i<=nb_slices; i++)
    {
        FT y = 0 + (FT)i / (FT)nb_slices * dy;
        Point p((FT)0.0, y, (FT)0.0);
        Plane plane(p,normal);

        std::list<Object_and_primitive_id> intersections;
        tree.all_intersections(plane,std::back_inserter(intersections));


        std::list<Object_and_primitive_id>::iterator it;
        for(it = intersections.begin();
            it != intersections.end();
            it++)
        {
            Object_and_primitive_id op = *it;
            CGAL::Object object = op.first;
            Segment segment;
            if(CGAL::assign(segment,object))
                m_segments[i].push_back(segment);
        }
    }

    int j = 1;
    std::cout <<"finito: " << timer.time() << " s." << std::endl;


    for (int i = 0; i<=nb_slices; ++i)
    {
        for (std::list<Segment>::iterator sit = m_segments[i].begin(); sit != m_segments[i].end(); sit++)
        {
            Segment s = *sit;
            std::cout<<"Segmento numero "<<j<<":"<<std::endl<<"inizio: "<<s.source()<<std::endl<<"fine: "<<s.target()<<std::endl;
            ++j;
        }
    }

    std::list<Segment> m_segments2[nb_slices+1];

    for (int i = 0; i <= nb_slices; ++i)
    {
        std::cout << "giro " << (i+1) << " dimensione cv: " << m_segments[i].size() << std::endl;
        Arrangement_2 arr;
        Segment_2 cv[m_segments[i].size()+1];

        j = 0;
        for (std::list<Segment>::iterator sit = m_segments[i].begin(); sit != m_segments[i].end(); sit++)
        {
            Segment s3 = *sit;
            Point_2 start (roundDouble(s3.source().x()), roundDouble(s3.source().z()));
            Point_2 end (roundDouble(s3.target().x()), roundDouble(s3.target().z()));
            cv[j] = Segment_2 (start, end);
            std::cout << "insert segment 2: " << (j+1) << " " << cv[j] << std::endl;
            j++;
        }
        Point_2 start(1,0);
        Point_2 end(2,0);
        Segment_2 ss3 (start, end);
        cv[m_segments[i].size()] = ss3;

        CGAL::insert (arr, &cv[0], &cv[m_segments[i].size()+1]);
        std::cout << "giro " << (i+1) << " dimensione arr: " << arr.number_of_edges() << std::endl;
        Arrangement_2::Halfedge_handle he = arr.edges_begin()->next()->prev();
        Arrangement_2::Halfedge_handle temp = he;
        int k=1;
        do
        {
            Point3 source (temp->source()->point().x(), roundDouble(m_segments[i].begin()->source().y()), temp->source()->point().y());
            Point3 target (temp->target()->point().x(), roundDouble(m_segments[i].begin()->target().y()), temp->target()->point().y());
            Segment s3 (source, target);
            //            if (isRealSegment(s3) && (m_segments2[i].size()==0 || isContiguous((*m_segments2[i].rbegin()), s3)))
            //            {
            std::cout << "insert segment 3: " << (k) << " " << s3 << std::endl;
            m_segments2[i].push_back(s3);
            //            }
            k++;
            temp = temp->next();
        } while (temp != he /*&& k <= arr.number_of_edges()*/);
    }

    j = 1;
    std::cout <<"finito di nuovo: " << timer.time() << " s." << std::endl;
    for (int i = 0; i<=nb_slices; ++i)
    {
        for (std::list<Segment>::iterator sit = m_segments2[i].begin(); sit != m_segments2[i].end(); sit++)
        {
            Segment s = *sit;
            std::cout << "segmento " << j << " source:\t" << s.source().x() << "\t" << s.source().y() << "\t" << s.source().z()
                      << "\t target: \t" << s.target().x() << "\t" << s.target().y() << "\t" << s.target().z() << std::endl;
            ++j;
        }
    }
}



//this goes in gcodegenerator
//void GCodeGenerator::getPolyhedron()
//{
//    VerticesAndFacesGenerator v(getTriangles());
//    TriangularMeshGenerator t(v.vertices(), v.faces());
//    PolyhedronCutTest p;
//    p.generate_boundary_segments(t.polyhedron());
//}
