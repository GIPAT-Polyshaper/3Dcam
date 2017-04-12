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

#include "gcodegenerator.h"
#include <iostream>
#include <QFile>
#include <QDataStream>
#include <QVector>
#include <typeinfo>
#include <algorithm>
#include <vector>
#include <fstream>


GCodeGenerator::GCodeGenerator()
{

}

void GCodeGenerator::readAndGenerate()
{

//std::cout << "we bello" << std::endl;

float a[10]={1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
float b[10]={4, 2, 3, 4, 5, 6, 7, 8, 9, 10};
float c[10]={7, 2, 3, 4, 5, 6, 7, 8, 9, 10};
float F = 800;

FILE * pFileTXT;

pFileTXT = fopen ("gcode.txt","a");
fprintf (pFileTXT, "F%f\n", F);
fclose (pFileTXT);

 for(auto i=0; i < 10; ++i){

    pFileTXT = fopen ("gcode.txt","a");
    fprintf (pFileTXT, "G01 X%f Y%f Z%f\n", a[i], b[i], c[i]);
    fclose (pFileTXT);


}




}
