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

#ifndef STLLOADER_H
#define STLLOADER_H

#include <exception>
#include <QObject>

/**
 * \brief The exception type thrown by StlLoader
 */
class StlLoaderExceptions : public std::exception
{
public:
    /**
     * \brief Constructor
     *
     * \param reason the exception reason. The buffer for this is at most 256
     *               characters (including the '\0' terminator)
     */
    StlLoaderExceptions(const char* reason) noexcept
    {
        strncpy(m_reason, reason, 256);
        m_reason[255] = '\0';
        sprintf(m_errorMessage, "Could not load stl file, reason: \"%s\"", m_reason);
        m_errorMessage[511] = '\0';
    }

    /**
     * \brief Copy constructor
     *
     * \param other the exception to copy
     */
    StlLoaderExceptions(const StlLoaderExceptions& other) noexcept
        : std::exception(other)
    {
        strncpy(m_reason, other.m_reason, 256);
        m_reason[255] = '\0';
        strncpy(m_errorMessage, other.m_errorMessage, 512);
        m_errorMessage[511] = '\0';
    }

    /**
     * \brief Copy operator
     *
     * \param other the exception to copy
     */
    StlLoaderExceptions& operator=(const StlLoaderExceptions& other) noexcept
    {
        if (&other == this) {
            return *this;
        }

        std::exception::operator=(other);
        strncpy(m_reason, other.m_reason, 256);
        m_reason[255] = '\0';
        strncpy(m_errorMessage, other.m_errorMessage, 512);
        m_errorMessage[511] = '\0';

        return *this;
    }

    /**
     * \brief Returns a C string describing the exception
     *
     * \return a C string describing the exception
     */
    virtual const char *what() const noexcept
    {
        return m_errorMessage;
    }

private:
    char m_reason[256];
    char m_errorMessage[512];
};

/**
 * \brief The class loading an STL file
 */
class StlLoader
{
public:
    StlLoader();
};

#endif // STLLOADER_H
