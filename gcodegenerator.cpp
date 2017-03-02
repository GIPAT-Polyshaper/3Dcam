#include "gcodegenerator.h"
#include <iostream>
#include <QFile>
#include <QDataStream>
#include <QVector>
#include <typeinfo>
//#include <algorithm> per la funzione sort

struct Vec3
{
    float x, y, z;
};

struct Vec3i {
    Vec3 first;
    uint second;

    bool operator<(const Vec3i& other) const {
        return first.x < other.first.x;
    }

    //bool operator==(const Vec3i& other) const {
    //    return first.x == other.first.x;
    //}
};

//typedef std::pair<Vec3, uint> Vec3i;

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

    // Skip the header material
    file.read(80);

    QDataStream data(&file);
    data.setByteOrder(QDataStream::LittleEndian);
    data.setFloatingPointPrecision(QDataStream::SinglePrecision);

    // Load the triangle count from the .stl file
    uint32_t tri_count;
    data >> tri_count;

    //std::cout << typeid(data).name() << std::endl;

    // Extract vertices into an array of xyz, unsigned pairs
    QVector<Vec3i> verts(tri_count*3);

    // Dummy array, because readRawData is faster than skipRawData
    char buffer[sizeof(float)*3];

    // Store vertices in the array, processing one triangle at a time.
    for (auto v=verts.begin(); v != verts.end(); v += 3)
    {
        // Skip face's normal vector
        data.readRawData(buffer, 3*sizeof(float));

        // Load vertex data from .stl file into vertices
        data >> v[0].first.x >> v[0].first.y >> v[0].first.z;
        data >> v[1].first.x >> v[1].first.y >> v[1].first.z;
        data >> v[2].first.x >> v[2].first.y >> v[2].first.z;

        // Skip face attribute
        data.readRawData(buffer, sizeof(uint16_t));
    }

    // Save indicies as the second element in the array
    // (so that we can reconstruct triangle order after sorting)
    for (size_t i=0; i < tri_count*3; ++i)
    {
        verts[i].second = i;
    }


    // da qui in poi procedo per la mia strada (finalmente)

    std::sort(verts.begin(), verts.end());

    // odio le strutture quindi mi costruisco i tre vettori xx, yy, zz e ind

    float xx[verts.length()];
    float yy[verts.length()];
    float zz[verts.length()];
    float ind[verts.length()];

    for (int i=0; i < verts.length(); i++)
    {
        //std::cout << verts[i].first.x << " - " << verts[i].first.y << std::endl;

        xx[i] = verts[i].first.x;
        yy[i] = verts[i].first.y;
        zz[i] = verts[i].first.z;
        ind[i] = i;
    }


// discretization as a function of the tool dimension

    float toolD = 0.2;

    int xxd[verts.length()];

//    std::cout << *std::min_element(xx,xx+verts.length()) << '\n';
//    std::cout << *std::max_element(xx,xx+verts.length()) << '\n';

    float x_min = *std::max_element(xx,xx+verts.length());
    float x_max = *std::max_element(xx,xx+verts.length());

    /*
    for (int i=0; i < verts.length(); i++)
    {
        //std::cout << verts[i].first.x << std::endl;



    }
*/






}
