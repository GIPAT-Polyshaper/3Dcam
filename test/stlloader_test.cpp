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

#include <QtTest/QtTest>
#include <QFile>
#include <QString>

#include "stlloader.h"

// NOTES AND TODOS
//
// Mettere livello warning alto e standard ansi pedantic
// Validare dati (se numero triangoli è sbagliato lanciare eccezione)
// ABILITARE CPPCHECK IN CMAKE E LANCIARLO SEMPRE!!! (CONTROLLARE ANCHE SUPPORTO DA PARTE DI QTCREATOR)

using Triangle = StlLoader::Triangle;
using Vec3 = StlLoader::Vec3;

/**
 * \brief The class to perform unit tests
 *
 * Each private slot is a test
 */
class StlLoader_Test : public QObject
{
    Q_OBJECT

private slots:
    void throw_exception_if_cannot_open_file()
    {
        QVERIFY_EXCEPTION_THROWN(StlLoader(":/non-exising"), StlLoaderExceptions);
    }

    void load_binary_stl_file()
    {
        StlLoader loader(":/cube_binary.stl");

        const auto& t = loader.triangles();
        QVERIFY(t.size() == 12);
        QVERIFY(compareTriangles(t[0], Triangle(Vec3(0, 0, 1), Vec3(0, 1, 1), Vec3(1, 0, 1), Vec3(1, 1, 1))));
        QVERIFY(compareTriangles(t[1], Triangle(Vec3(0, 0, 1), Vec3(1, 0, 1), Vec3(0, 1, 1), Vec3(0, 0, 1))));
        QVERIFY(compareTriangles(t[2], Triangle(Vec3(0, 0, -1), Vec3(0, 0, 0), Vec3(1, 1, 0), Vec3(1, 0, 0))));
        QVERIFY(compareTriangles(t[3], Triangle(Vec3(0, 0, -1), Vec3(1, 1, 0), Vec3(0, 0, 0), Vec3(0, 1, 0))));
        QVERIFY(compareTriangles(t[4], Triangle(Vec3(0, -1, 0), Vec3(0, 0, 0), Vec3(1, 0, 1), Vec3(0, 0, 1))));
        QVERIFY(compareTriangles(t[5], Triangle(Vec3(0, -1, 0), Vec3(1, 0, 1), Vec3(0, 0, 0), Vec3(1, 0, 0))));
        QVERIFY(compareTriangles(t[6], Triangle(Vec3(1, 0, 0), Vec3(1, 0, 1), Vec3(1, 1, 0), Vec3(1, 1, 1))));
        QVERIFY(compareTriangles(t[7], Triangle(Vec3(1, 0, 0), Vec3(1, 1, 0), Vec3(1, 0, 1), Vec3(1, 0, 0))));
        QVERIFY(compareTriangles(t[8], Triangle(Vec3(0, 1, 0), Vec3(1, 1, 0), Vec3(0, 1, 1), Vec3(1, 1, 1))));
        QVERIFY(compareTriangles(t[9], Triangle(Vec3(0, 1, 0), Vec3(0, 1, 1), Vec3(1, 1, 0), Vec3(0, 1, 0))));
        QVERIFY(compareTriangles(t[10], Triangle(Vec3(-1, 0, 0), Vec3(0, 0, 0), Vec3(0, 1, 1), Vec3(0, 1, 0))));
        QVERIFY(compareTriangles(t[11], Triangle(Vec3(-1, 0, 0), Vec3(0, 1, 1), Vec3(0, 0, 0), Vec3(0, 0, 1))));
    }

    void throw_if_binary_file_has_not_enough_triangles()
    {
        QVERIFY_EXCEPTION_THROWN(StlLoader(":/cube_binary_invalid_triangle_num.stl"), StlLoaderExceptions);
    }

    void throw_if_binary_file_has_invalid_header()
    {
        QVERIFY_EXCEPTION_THROWN(StlLoader(":/cube_binary_invalid_header.stl"), StlLoaderExceptions);
    }

    void throw_if_binary_file_has_data_past_the_end()
    {
        QVERIFY_EXCEPTION_THROWN(StlLoader(":/cube_binary_invalid_data_past_end.stl"), StlLoaderExceptions);
    }

    void throw_if_binary_file_has_last_byte_missing()
    {
        QVERIFY_EXCEPTION_THROWN(StlLoader(":/cube_binary_invalid_missing_last_byte.stl"), StlLoaderExceptions);
    }

    void load_ascii_file()
    {
        StlLoader loader(":/cube_ascii.stl");

        const auto& t = loader.triangles();
        QVERIFY(t.size() == 12);
        QVERIFY(compareTriangles(t[0], Triangle(Vec3(0, 0, 1), Vec3(0, 1, 1), Vec3(1, 0, 1), Vec3(1, 1, 1))));
        QVERIFY(compareTriangles(t[1], Triangle(Vec3(0, 0, 1), Vec3(1, 0, 1), Vec3(0, 1, 1), Vec3(0, 0, 1))));
        QVERIFY(compareTriangles(t[2], Triangle(Vec3(0, 0, -1), Vec3(0, 0, 0), Vec3(1, 1, 0), Vec3(1, 0, 0))));
        QVERIFY(compareTriangles(t[3], Triangle(Vec3(0, 0, -1), Vec3(1, 1, 0), Vec3(0, 0, 0), Vec3(0, 1, 0))));
        QVERIFY(compareTriangles(t[4], Triangle(Vec3(0, -1, 0), Vec3(0, 0, 0), Vec3(1, 0, 1), Vec3(0, 0, 1))));
        QVERIFY(compareTriangles(t[5], Triangle(Vec3(0, -1, 0), Vec3(1, 0, 1), Vec3(0, 0, 0), Vec3(1, 0, 0))));
        QVERIFY(compareTriangles(t[6], Triangle(Vec3(1, 0, 0), Vec3(1, 0, 1), Vec3(1, 1, 0), Vec3(1, 1, 1))));
        QVERIFY(compareTriangles(t[7], Triangle(Vec3(1, 0, 0), Vec3(1, 1, 0), Vec3(1, 0, 1), Vec3(1, 0, 0))));
        QVERIFY(compareTriangles(t[8], Triangle(Vec3(0, 1, 0), Vec3(1, 1, 0), Vec3(0, 1, 1), Vec3(1, 1, 1))));
        QVERIFY(compareTriangles(t[9], Triangle(Vec3(0, 1, 0), Vec3(0, 1, 1), Vec3(1, 1, 0), Vec3(0, 1, 0))));
        QVERIFY(compareTriangles(t[10], Triangle(Vec3(-1, 0, 0), Vec3(0, 0, 0), Vec3(0, 1, 1), Vec3(0, 1, 0))));
        QVERIFY(compareTriangles(t[11], Triangle(Vec3(-1, 0, 0), Vec3(0, 1, 1), Vec3(0, 0, 0), Vec3(0, 0, 1))));
    }

    // For ascii files we don't check all possible errors (there are too many) even if they are checked in code
    void throw_it_ascii_file_is_invalid()
    {
        QVERIFY_EXCEPTION_THROWN(StlLoader(":/cube_ascii_invalid.stl"), StlLoaderExceptions);
    }

private:
    bool compareTriangles(const StlLoader::Triangle& t1, const StlLoader::Triangle& t2)
    {
        return compareVec3(t1.normal, t2.normal) && compareVec3(t1.v1, t2.v1) && compareVec3(t1.v2, t2.v2) && compareVec3(t1.v3, t2.v3);
    }

    bool compareVec3(const StlLoader::Vec3& v1, const StlLoader::Vec3& v2)
    {
        return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z);
    }
};

QTEST_MAIN(StlLoader_Test)
#include "stlloader_test.moc"
