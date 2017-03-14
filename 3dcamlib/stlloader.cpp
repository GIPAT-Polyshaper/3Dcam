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

StlLoader::StlLoader(const QString& filename)
    : m_triangles()
{
    QFile file(filename);

    if (!file.open(QFile::ReadOnly)) {
        throw StlLoaderExceptions(filename.toLatin1().data(), "could not open file for reading");
    }

    // Skip the header material
    file.read(80);

    QDataStream data(&file);
    data.setByteOrder(QDataStream::LittleEndian);
    data.setFloatingPointPrecision(QDataStream::SinglePrecision);

    // Load the triangle count from the .stl file
    uint32_t triCount;
    data >> triCount;

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

        // Skip face attribute
        data.readRawData(buffer, sizeof(uint16_t));

        // Add triangle
        m_triangles.push_back(Triangle(n, v1, v2, v3));
    }
}
