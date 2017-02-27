#include "gcodegenerator.h"
#include <iostream>
#include <QFile>
#include <QDataStream>
#include <QVector>
#include <typeinfo>



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

    //std::cout << typeid(data).name() << std::endl;

    // Extract vertices into an array of xyz, unsigned pairs
    QVector<uint> verts(1000*3);  //al posto di 1000 ci dovrebbe essere tri_count e al posto di unit Vec3i che è definita dopo la struttura comenatta sotto

    /*struct Vec3
{
    GLfloat x, y, z;
    bool operator!=(const Vec3& rhs) const
    {
        return x != rhs.x || y != rhs.y || z != rhs.z;
    }
    bool operator<(const Vec3& rhs) const
    {
        if      (x != rhs.x)    return x < rhs.x;
        else if (y != rhs.y)    return y < rhs.y;
        else if (z != rhs.z)    return z < rhs.z;
        else                    return false;
    }
};

typedef std::pair<Vec3, GLuint> Vec3i;

*/





}
