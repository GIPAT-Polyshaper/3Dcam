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

#include "stlloader.h"
#include <QFile>
#include <QDataStream>
#include <QTextStream>

StlLoader::StlLoader(const QString& filename)
    : m_triangles()
{
    QFile file(filename);

    if (!file.open(QFile::ReadOnly)) {
        throw StlLoaderExceptions(filename, "could not open file for reading");
    }

    auto fileStart = file.read(5);

    if (fileStart != "solid") {
        readBinaryFile(file);
    } else {
        readAsciiFile(file);
    }
}

void StlLoader::readBinaryFile(QFile& file)
{
    // Skip the header material
    file.read(75);

    QDataStream data(&file);
    data.setByteOrder(QDataStream::LittleEndian);
    data.setFloatingPointPrecision(QDataStream::SinglePrecision);

    // Load the triangle count from the .stl file
    uint32_t triCount;
    data >> triCount;

    if (data.status() != QDataStream::Ok) {
        throw StlLoaderExceptions(file.fileName(), "invalid header while reading binary stl file");
    }

    // Dummy array, because readRawData is faster than skipRawData
    char buffer[sizeof(uint16_t)];

    // Store vertices in the array, processing one triangle at a time.
    for (auto i = 0; i < triCount; i++) {
        Vec3 n, v1, v2, v3;

        // Load face's normal vector
        data >> n.x >> n.y >> n.z;

        // Load vertex data
        data >> v1.x >> v1.y >> v1.z;
        data >> v2.x >> v2.y >> v2.z;
        data >> v3.x >> v3.y >> v3.z;

        if (data.status() != QDataStream::Ok) {
            throw StlLoaderExceptions(file.fileName(), "invalid data while reading binary stl file");
        }

        // Skip face attribute
        auto l = data.readRawData(buffer, sizeof(uint16_t));
        if ((l == -1) || (l != sizeof(uint16_t))) {
            throw StlLoaderExceptions(file.fileName(), "invalid data while reading face attributes binary stl file");
        }

        // Add triangle
        m_triangles.push_back(Triangle(n, v1, v2, v3));
    }

    if (!data.atEnd()) {
        throw StlLoaderExceptions(file.fileName(), "data past expected file end reading binary stl file");
    }
}

void StlLoader::readAsciiFile(QFile& file)
{
    QTextStream text(&file);

    // Skip the solid name
    text.readLine();

    QString s;

    // This checks that the content of the s variable is the expected one and that the stream is valid
    auto checkExpected = [&](QString expected) {
        if (s != expected) {
            throw StlLoaderExceptions(file.fileName(), "expected '" + expected + "', found '" + s + "' while reading ascii stl file");
        }
        if (text.status() != QTextStream::Ok) {
            throw StlLoaderExceptions(file.fileName(), "invalid data while reading ascii stl file");
        }
    };

    while (true) {
        text >> s;
        if (s == "endsolid") {
            break;
        }
        checkExpected("facet");

        Vec3 n, v1, v2, v3;

        // we should have read "facet" now we expect "normal"
        text >> s >> n.x >> n.y >> n.z;; checkExpected("normal");

        // "outer loop"
        text >> s; checkExpected("outer");
        text >> s; checkExpected("loop");

        // three "vertex x y z"
        text >> s >> v1.x >> v1.y >> v1.z; checkExpected("vertex");
        text >> s >> v2.x >> v2.y >> v2.z; checkExpected("vertex");
        text >> s >> v3.x >> v3.y >> v3.z; checkExpected("vertex");

        // "endloop"
        text >> s; checkExpected("endloop");

        // "endfacet"
        text >> s; checkExpected("endfacet");

        // Add triangle
        m_triangles.push_back(Triangle(n, v1, v2, v3));
    }

    // after "endsolid" there is the solid name
    text.readLine();
    text.skipWhiteSpace();

    if (!text.atEnd()) {
        throw StlLoaderExceptions(file.fileName(), "data past expected file end reading ascii stl file");
    }
}
