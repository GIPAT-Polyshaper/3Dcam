/**************************************************************************
 * PolyShaper 3D Cam                                                      *
 * Copyright (C) 2017                                                     *
 * Flavio Prattico <????>                                                 *
 * Carmine Gianfagna <???>                                                *
 * Tomassino Ferrauto <tomassino.ferrauto@gmail.com>                      *
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

#include <QtTest/QtTest>
#include <iostream>
#include <CGAL/Simple_cartesian.h>

// NOTES AND TODOS
//
// This file contains tests and experiments with cgal

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 Point_2;
typedef Kernel::Segment_2 Segment_2;

/**
 * \brief The class to perform unit tests
 *
 * Each private slot is a test
 */
class CGAL_Test : public QObject
{
    Q_OBJECT

private slots:
    void dummy()
    {
        Point_2 p(1,1), q(10,10);
        std::cout << "p = " << p << std::endl;
        std::cout << "q = " << q.x() << " " << q.y() << std::endl;
        std::cout << "sqdist(p,q) = "
                  << CGAL::squared_distance(p,q) << std::endl;

        Segment_2 s(p,q);
        Point_2 m(5, 9);

        std::cout << "m = " << m << std::endl;
        std::cout << "sqdist(Segment_2(p,q), m) = "
                  << CGAL::squared_distance(s,m) << std::endl;
        std::cout << "p, q, and m ";
        switch (CGAL::orientation(p,q,m)){
        case CGAL::COLLINEAR:
          std::cout << "are collinear\n";
          break;
        case CGAL::LEFT_TURN:
          std::cout << "make a left turn\n";
          break;
        case CGAL::RIGHT_TURN:
          std::cout << "make a right turn\n";
          break;
        }
        std::cout << " midpoint(p,q) = " << CGAL::midpoint(p,q) << std::endl;
    }
};

QTEST_MAIN(CGAL_Test)
#include "cgal_test.moc"
