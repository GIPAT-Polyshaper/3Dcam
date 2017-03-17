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

#ifndef STLLOADER_H
#define STLLOADER_H

#include <exception>
#include <QObject>
#include <QFile>
#include <QString>
#include <vector>

/**
 * @brief The exception type thrown by StlLoader
 */
class StlLoaderExceptions : public std::exception
{
public:
    /**
     * @brief Constructor
     *
     * @param filename the name of the file to load
     * @param reason the exception reason. The buffer for this is at most 256
     *               characters (including the '\0' terminator)
     */
    StlLoaderExceptions(QString filename, QString reason) noexcept
    {
        strncpy(m_filename, filename.toLatin1().data(), 256);
        m_filename[255] = '\0';
        strncpy(m_reason, reason.toLatin1().data(), 256);
        m_reason[255] = '\0';
        sprintf(m_errorMessage, "Could not load stl file \"%s\", reason: \"%s\"", m_filename, m_reason);
        m_errorMessage[511] = '\0';
    }

    /**
     * @brief Copy constructor
     */
    StlLoaderExceptions(const StlLoaderExceptions& other) noexcept
        : std::exception(other)
    {
        strncpy(m_filename, other.m_filename, 256);
        m_filename[255] = '\0';
        strncpy(m_reason, other.m_reason, 256);
        m_reason[255] = '\0';
        strncpy(m_errorMessage, other.m_errorMessage, 512);
        m_errorMessage[511] = '\0';
    }

    /**
     * @brief Copy operator
     */
    StlLoaderExceptions& operator=(const StlLoaderExceptions& other) noexcept
    {
        if (&other == this) {
            return *this;
        }

        std::exception::operator=(other);
        strncpy(m_filename, other.m_filename, 256);
        m_filename[255] = '\0';
        strncpy(m_reason, other.m_reason, 256);
        m_reason[255] = '\0';
        strncpy(m_errorMessage, other.m_errorMessage, 512);
        m_errorMessage[511] = '\0';

        return *this;
    }

    /**
     * @brief Returns a C string describing the exception
     */
    virtual const char *what() const noexcept
    {
        return m_errorMessage;
    }

private:
    char m_filename[256];
    char m_reason[256];
    char m_errorMessage[768];
};

/**
 * @brief The class loading an STL file
 */
class StlLoader
{
public:
    /**
     * @brief A simple structure representing a point in 3D space
     */
    struct Vec3 {
        Vec3()
        {
        }

        Vec3(float xx, float yy, float zz)
            : x(xx)
            , y(yy)
            , z(zz)
        {
        }

        float x;
        float y;
        float z;
    };

    /**
     * @brief A triangle loaded from an stl file, with normal and vertices
     */
    struct Triangle {
        Triangle(Vec3 n, Vec3 vv1, Vec3 vv2, Vec3 vv3)
            : normal(n)
            , v1(vv1)
            , v2(vv2)
            , v3(vv3)
        {
        }

        Vec3 normal;
        Vec3 v1;
        Vec3 v2;
        Vec3 v3;
    };

public:
    /**
     * @brief Constructor
     *
     * This throws an exception in case loading fails
     * @param filename the stl file to load
     */
    StlLoader(const QString& filename);

    /**
     * @brief Returns the list of triangles loaded from the stl file
     */
    const std::vector<Triangle>& triangles() const
    {
        return m_triangles;
    }

private:
    void readBinaryFile(QFile& file);
    void readAsciiFile(QFile& file);

    std::vector<Triangle> m_triangles;
};

#endif // STLLOADER_H
