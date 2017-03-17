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

// NOTES AND TODOS
//
// This is just an empty file, created as template for unit tests

/**
 * \brief The class to perform unit tests
 *
 * Each private slot is a test
 */
class Dummy_Test : public QObject
{
	Q_OBJECT

private slots:
    void readDummyFile()
	{
        QFile f(":/dummy_file.txt");

        QVERIFY(f.open(QIODevice::ReadOnly | QIODevice::Text));

        QString content = f.readAll();

        QVERIFY(content.startsWith("A test file"));
	}
};

QTEST_MAIN(Dummy_Test)
#include "dummy_test.moc"
