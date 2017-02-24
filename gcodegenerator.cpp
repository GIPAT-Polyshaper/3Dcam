#include "gcodegenerator.h"
#include <iostream>
#include <QFile>
#include <QDataStream>

GCodeGenerator::GCodeGenerator()
{

}

void GCodeGenerator::readAndGenerate()
{
    //std::cout << "a soreta" << std::endl;

    // cambiare il path assoluto per chi fa prove
    QFile file("/Users/flavioprattico/Desktop/a.stl");
    file.open(QIODevice::ReadOnly);


    if( !file.exists() )
      {
        std::cout << "Il file non c'è" << std::endl;
      }

    // Skip the rest of the header material
    file.read(75);

    QDataStream data(&file);
    data.setByteOrder(QDataStream::LittleEndian);
    data.setFloatingPointPrecision(QDataStream::SinglePrecision);

    // Load the triangle count from the .stl file
    uint32_t tri_count;
    data >> tri_count;

    std::cout << tri_count << std::endl;

    // Extract vertices into an array of xyz, unsigned pairs
    //QVector<Vec3i> verts(tri_count*3);







}
