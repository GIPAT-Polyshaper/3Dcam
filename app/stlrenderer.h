#ifndef STLRENDERER_H
#define STLRENDERER_H


#include <QtGui/qvector3d.h>
#include <QtGui/qmatrix4x4.h>
#include <QtGui/qopenglshaderprogram.h>
#include <QtGui/qopenglfunctions.h>
#include "transform3d.h"
#include "camera3d.h"



#include <QTime>
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
    void createGeometry();
//    void quad(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3, qreal x4, qreal y4);
//    void extrude(qreal x1, qreal y1, qreal x2, qreal y2);

    QVector<QVector3D> vertices;
    QVector<QVector3D> normals;
    QOpenGLShaderProgram program1;
    int vertexAttr1;
    int normalAttr1;
    int u_modelToWorld;
    int u_worldToView;
    Transform3D modelMatrix;
    Camera3D viewMatrix;
};

#endif // STLRENDERER_H
