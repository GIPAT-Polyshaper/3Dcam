#ifndef STLRENDERER_H
#define STLRENDERER_H


#include <QtGui/qvector3d.h>
#include <QtGui/qmatrix4x4.h>
#include <QtGui/qopenglshaderprogram.h>
#include <QtGui/qopenglfunctions.h>
#include "transform3d.h"
#include "camera3d.h"
#include "gcodegenerator.h"
#include "stlloader.h"
#include <QVector>

class StlRenderer : protected QOpenGLFunctions
{
public:
    StlRenderer();
    ~StlRenderer();

    void render();
    void initialize();
    void setGeometry(const StlLoader::Triangles &t);
    void setCamera(int az, float di, int el);
    void setVolume(int x, int y, int z);
private:

    void paintObject();
    void setWorkingVolume(int x, int y, int z, float a);
    float diffMax;
    QVector3D center;

    QVector<QVector3D> vertices;
    QVector<GLfloat> alpha;
    QVector<QVector3D> normals;
    QVector<QVector3D> colors;
    QOpenGLShaderProgram program1;

    int alphaAttr1;
    int vertexAttr1;
    int normalAttr1;
    int colorAttr1;

    int uModeltoworld;
    int uWorldtoview;

    Transform3D modelMatrix;
    Camera3D viewMatrix;

    int volume_x;
    int volume_y;
    int volume_z;


};

#endif // STLRENDERER_H
