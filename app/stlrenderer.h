#ifndef STLRENDERER_H
#define STLRENDERER_H


#include <QtGui/qvector3d.h>
#include <QtGui/qmatrix4x4.h>
#include <QtGui/qopenglshaderprogram.h>
#include <QtGui/qopenglfunctions.h>
#include "transform3d.h"
#include "camera3d.h"
#include "gcodegenerator.h"
#include <QVector>

class StlRenderer : protected QOpenGLFunctions
{
public:
    StlRenderer();
    ~StlRenderer();

    void render();
    void initialize();

private:

    void paintQtLogo();
//    void createGeometry();
    float max;
    QVector<QVector3D> vertices;
    QVector<GLfloat> alpha;
    QVector<QVector3D> normals;
    QOpenGLShaderProgram program1;
    int alphaAttr1;
    int vertexAttr1;
    int normalAttr1;
    int u_modelToWorld;
    int u_worldToView;
    Transform3D modelMatrix;
    Camera3D viewMatrix;

public slots:
    void setGeometry(const StlLoader::Triangles &t);
};

#endif // STLRENDERER_H
