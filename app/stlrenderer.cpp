#include "stlrenderer.h"
#include <QPainter>
#include <QPaintEngine>
#include <math.h>

StlRenderer::StlRenderer()
{
}

StlRenderer::~StlRenderer()
{
}


void StlRenderer::paintQtLogo()
{
    program1.enableAttributeArray(normalAttr1);
    program1.enableAttributeArray(vertexAttr1);
    program1.setAttributeArray(vertexAttr1, vertices.constData());
    program1.setAttributeArray(normalAttr1, normals.constData());
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    program1.disableAttributeArray(normalAttr1);
    program1.disableAttributeArray(vertexAttr1);
}


void StlRenderer::initialize()
{
    initializeOpenGLFunctions();

    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);

    const char *vsrc1 =
            "attribute highp vec4 vertex;\n"
            "attribute mediump vec3 normal;\n"
            "uniform mediump mat4 matrix;\n"
            "varying mediump vec4 color;\n"
            "void main(void)\n"
            "{\n"
            "    vec3 toLight = normalize(vec3(0.0, 0.3, 1.0));\n"
            "    float angle = max(dot(normal, toLight), 0.0);\n"
            "    vec3 col = vec3(0.40, 1.0, 0.0);\n"
            "    color = vec4(col * 0.2 + col * 0.8 * angle, 1.0);\n"
            "    color = clamp(color, 0.0, 1.0);\n"
            "    gl_Position = matrix * vertex;\n"
            "}\n";

    const char *fsrc1 =
            "varying mediump vec4 color;\n"
            "void main(void)\n"
            "{\n"
            "    gl_FragColor = color;\n"
            "}\n";

    program1.addCacheableShaderFromSourceCode(QOpenGLShader::Vertex, vsrc1);
    program1.addCacheableShaderFromSourceCode(QOpenGLShader::Fragment, fsrc1);
    program1.link();

    vertexAttr1 = program1.attributeLocation("vertex");
    normalAttr1 = program1.attributeLocation("normal");
    matrixUniform1 = program1.uniformLocation("matrix");

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    m_fAngle = 20;
    m_fScale = 0.7;
    createGeometry();
}

void StlRenderer::render()
{
    glDepthMask(true);

    glClearColor(0.5f, 0.5f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glFrontFace(GL_CW);
    glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    QMatrix4x4 modelview;
    modelview.rotate(m_fAngle, 0.0f, 1.0f, 0.0f);
    modelview.rotate(m_fAngle, 1.0f, 0.0f, 0.0f);
    modelview.rotate(m_fAngle, 0.0f, 0.0f, 1.0f);
    modelview.scale(m_fScale);
//        modelview.translate(0.0f, 0.2f, 0.0f);
        QVector3D eye = QVector3D (0.5f, 0.5f, 1.0f);
        QVector3D center = QVector3D(0.5f, 0.5f, 0.5f);
        QVector3D up = QVector3D(0.0f, 0.2f, 1.0f);
        modelview.lookAt(eye, center, up);

    program1.bind();
    program1.setUniformValue(matrixUniform1, modelview);
    paintQtLogo();
    program1.release();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    m_fAngle += 1.0f;
}

void StlRenderer::createGeometry()
{
    vertices.clear();
    normals.clear();
    float uno = 1.0f;
    float zero = 0.0f;
    float menouno = -1.0f;
    float menozero = -0.0f;

    vertices << QVector3D(zero, uno, uno);
    vertices << QVector3D(uno, zero, uno);
    vertices << QVector3D(uno,uno,uno);

    normals << QVector3D(menozero, zero, uno);
    normals << QVector3D(menozero, zero, uno);
    normals << QVector3D(menozero, zero, uno);

    vertices << QVector3D(uno, zero, uno);
    vertices << QVector3D(zero, uno, uno);
    vertices << QVector3D(zero,zero,uno);

    normals << QVector3D(zero, zero, uno);
    normals << QVector3D(zero, zero, uno);
    normals << QVector3D(zero, zero, uno);

    vertices << QVector3D(zero, zero, zero);
    vertices << QVector3D(uno, uno, zero);
    vertices << QVector3D(uno, zero, zero);

    normals << QVector3D(zero, zero, menouno);
    normals << QVector3D(zero, zero, menouno);
    normals << QVector3D(zero, zero, menouno);

    vertices << QVector3D(uno, uno, zero);
    vertices << QVector3D(zero, zero, zero);
    vertices << QVector3D(zero,uno,zero);

    normals << QVector3D(menozero, zero, menouno);
    normals << QVector3D(menozero, zero, menouno);
    normals << QVector3D(menozero, zero, menouno);

    vertices << QVector3D(zero, zero, zero);
    vertices << QVector3D(uno, zero, uno);
    vertices << QVector3D(zero,zero,uno);

    normals << QVector3D(zero, menouno, zero);
    normals << QVector3D(zero, menouno, zero);
    normals << QVector3D(zero, menouno, zero);

    vertices << QVector3D(uno, zero, uno);
    vertices << QVector3D(zero, zero, zero);
    vertices << QVector3D(uno,zero,zero);

    normals << QVector3D(zero, menouno, menozero);
    normals << QVector3D(zero, menouno, menozero);
    normals << QVector3D(zero, menouno, menozero);

    vertices << QVector3D(uno, zero, uno);
    vertices << QVector3D(uno, uno, zero);
    vertices << QVector3D(uno,uno,uno);

    normals << QVector3D(uno, menozero, zero);
    normals << QVector3D(uno, menozero, zero);
    normals << QVector3D(uno, menozero, zero);

    vertices << QVector3D(uno, uno, zero);
    vertices << QVector3D(uno, zero, uno);
    vertices << QVector3D(uno,zero,zero);

    normals << QVector3D(uno, zero, zero);
    normals << QVector3D(uno, zero, zero);
    normals << QVector3D(uno, zero, zero);

    vertices << QVector3D(uno, uno, zero);
    vertices << QVector3D(zero, uno, uno);
    vertices << QVector3D(uno,uno,uno);

    normals << QVector3D(zero, uno, menozero);
    normals << QVector3D(zero, uno, menozero);
    normals << QVector3D(zero, uno, menozero);



    vertices << QVector3D(zero, uno, uno);
    vertices << QVector3D(uno, uno, zero);
    vertices << QVector3D(zero,uno,zero);

    normals << QVector3D(zero, uno, zero);
    normals << QVector3D(zero, uno, zero);
    normals << QVector3D(zero, uno, zero);


    vertices << QVector3D(zero, zero, zero);
    vertices << QVector3D(zero, uno, uno);
    vertices << QVector3D(zero,uno,zero);

    normals << QVector3D(menouno, zero, zero);
    normals << QVector3D(menouno, zero, zero);
    normals << QVector3D(menouno, zero, zero);

    vertices << QVector3D(zero, uno, uno);
    vertices << QVector3D(zero, zero, zero);
    vertices << QVector3D(zero,zero,uno);

    normals << QVector3D(menouno, menozero, zero);
    normals << QVector3D(menouno, menozero, zero);
    normals << QVector3D(menouno, menozero, zero);
    //    qreal x1 = +0.06f;
    //    qreal y1 = -0.14f;
    //    qreal x2 = +0.14f;
    //    qreal y2 = -0.06f;
    //    qreal x3 = +0.08f;
    //    qreal y3 = +0.00f;
    //    qreal x4 = +0.30f;
    //    qreal y4 = +0.22f;

    //    quad(x1, y1, x2, y2, y2, x2, y1, x1);
    //    quad(x3, y3, x4, y4, y4, x4, y3, x3);

    //    extrude(x1, y1, x2, y2);
    //    extrude(x2, y2, y2, x2);
    //    extrude(y2, x2, y1, x1);
    //    extrude(y1, x1, x1, y1);
    //    extrude(x3, y3, x4, y4);
    //    extrude(x4, y4, y4, x4);
    //    extrude(y4, x4, y3, x3);

    //    const qreal Pi = 3.14159f;
    //    const int NumSectors = 10;

    //    for (int i = 0; i < NumSectors; ++i) {
    //        qreal angle1 = (i * 2 * Pi) / NumSectors;
    //        qreal x5 = 0.30 * sin(angle1);
    //        qreal y5 = 0.30 * cos(angle1);
    //        qreal x6 = 0.20 * sin(angle1);
    //        qreal y6 = 0.20 * cos(angle1);

    //        qreal angle2 = ((i + 1) * 2 * Pi) / NumSectors;
    //        qreal x7 = 0.20 * sin(angle2);
    //        qreal y7 = 0.20 * cos(angle2);
    //        qreal x8 = 0.30 * sin(angle2);
    //        qreal y8 = 0.30 * cos(angle2);

    //        quad(x5, y5, x6, y6, x7, y7, x8, y8);

    //        extrude(x6, y6, x7, y7);
    //        extrude(x8, y8, x5, y5);
    //    }

    //    for (int i = 0;i < vertices.size();i++)
    //        vertices[i] *= 2.0f;
}

//void StlRenderer::quad(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3, qreal x4, qreal y4)
//{
//    vertices << QVector3D(x1, y1, -0.05f);
//    vertices << QVector3D(x2, y2, -0.05f);
//    vertices << QVector3D(x4, y4, -0.05f);

//    vertices << QVector3D(x3, y3, -0.05f);
//    vertices << QVector3D(x4, y4, -0.05f);
//    vertices << QVector3D(x2, y2, -0.05f);

//    QVector3D n = QVector3D::normal
//            (QVector3D(x2 - x1, y2 - y1, 0.0f), QVector3D(x4 - x1, y4 - y1, 0.0f));

//    normals << n;
//    normals << n;
//    normals << n;

//    normals << n;
//    normals << n;
//    normals << n;

//    vertices << QVector3D(x4, y4, 0.05f);
//    vertices << QVector3D(x2, y2, 0.05f);
//    vertices << QVector3D(x1, y1, 0.05f);

//    vertices << QVector3D(x2, y2, 0.05f);
//    vertices << QVector3D(x4, y4, 0.05f);
//    vertices << QVector3D(x3, y3, 0.05f);

//    n = QVector3D::normal
//            (QVector3D(x2 - x4, y2 - y4, 0.0f), QVector3D(x1 - x4, y1 - y4, 0.0f));

//    normals << n;
//    normals << n;
//    normals << n;

//    normals << n;
//    normals << n;
//    normals << n;
//}

//void StlRenderer::extrude(qreal x1, qreal y1, qreal x2, qreal y2)
//{
//    vertices << QVector3D(x1, y1, +0.05f);
//    vertices << QVector3D(x2, y2, +0.05f);
//    vertices << QVector3D(x1, y1, -0.05f);

//    vertices << QVector3D(x2, y2, -0.05f);
//    vertices << QVector3D(x1, y1, -0.05f);
//    vertices << QVector3D(x2, y2, +0.05f);

//    QVector3D n = QVector3D::normal
//            (QVector3D(x2 - x1, y2 - y1, 0.0f), QVector3D(0.0f, 0.0f, -0.1f));

//    normals << n;
//    normals << n;
//    normals << n;

//    normals << n;
//    normals << n;
//    normals << n;
//}

