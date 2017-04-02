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
#include "undersquare.h"

// NOTES AND TODOS
//

/**
 * \brief The class to perform unit tests
 *
 * Each private slot is a test
 */
class Undersquare_Test : public QObject
{
    Q_OBJECT

private slots:
    void return_empty_tool_path_for_empty_inputs()
    {
        Undersquare u({}, {});

        QVERIFY(u.toolY().size() == 0);
        QVERIFY(u.toolZ().size() == 0);
    }

    void return_tool_path_triangle()
    {
        Undersquare u({1, 2, 3}, {1, 2, 1});

        auto toolY = std::vector<double>{1, 2, 3};
        auto toolZ = std::vector<double>{1, 2, 1};

        QVERIFY(u.toolY() == toolY);
        QVERIFY(u.toolZ() == toolZ);
    }
    void return_tool_path_triangle_middle_point()
    {
        Undersquare u({1, 2, 3, 2}, {1, 2, 1, 1});

        auto toolY = std::vector<double>{1, 2, 3};
        auto toolZ = std::vector<double>{1, 2, 1};

        QVERIFY(u.toolY() == toolY);
        QVERIFY(u.toolZ() == toolZ);
    }
    void return_tool_path_triangle_starting_from_any_point()
    {

         // the geometry strats from any point different from 1

        Undersquare u({2, 3, 2, 1}, {2, 1, 1, 1});

        auto toolY = std::vector<double>{1, 2, 3};
        auto toolZ = std::vector<double>{1, 2, 1};

        QVERIFY(u.toolY() == toolY);
        QVERIFY(u.toolZ() == toolZ);
    }

};

QTEST_MAIN(Undersquare_Test)
#include "undersquare_test.moc"
