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

// NOTES AND TODOS
//
// This is just an empty file, created as placeholder for unit tests

/**
 * \brief The class to perform unit tests
 *
 * Each private slot is a test
 */
class Dummy_Test : public QObject
{
	Q_OBJECT

private slots:
	void dummy()
	{
	}
};

QTEST_MAIN(Dummy_Test)
#include "dummy_test.moc"