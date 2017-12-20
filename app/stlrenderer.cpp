#include "stlrenderer.h"
#include <QPainter>
#include <QPaintEngine>
#include <math.h>
#include <QtMath>


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
            "uniform mediump mat4 worldToView;\n"
            "uniform mediump mat4 modelToWorld;\n"
            "varying mediump vec4 color;\n"
            "void main(void)\n"
            "{\n"
            "    vec3 toLight = normalize(vec3(0.0, 0.3, 1.0));\n"
            "    float angle = max(dot(normal, toLight), 0.0);\n"
            "    vec3 col = vec3(0.40, 1.0, 0.0);\n"
            "    color = vec4(col * 0.2 + col * 0.8 * angle, 1.0);\n"
            "    color = clamp(color, 0.0, 1.0);\n"
            "    gl_Position = worldToView * modelToWorld * vertex;\n"
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
    u_modelToWorld = program1.uniformLocation("modelToWorld");
    u_worldToView = program1.uniformLocation("worldToView");


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

//    modelMatrix.setRotation(90.f, 0.0f, 0.0f, 1.0f);
//    modelMatrix.rotate(90, 1.0f, 0.0f, 0.0f);
    viewMatrix.setTranslation(0.0f, 3.0f, 0.0f);
    viewMatrix.setRotation(-90.0f, 1.0f, 0.0f, 0.0f);
    //    viewMatrix.setRotation(45.0f, 1.0, 0.0, 0.0);
    createGeometry();


}

void StlRenderer::render()
{
    QOpenGLFunctions *functions = QOpenGLContext::currentContext()->functions();

    glDepthMask(true);

    glClearColor(0.5f, 0.5f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glFrontFace(GL_CW);
    glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    QMatrix4x4 projectionMatrix;

    GLint viewportSize[4];
    functions->glGetIntegerv(GL_VIEWPORT, viewportSize);
    projectionMatrix.perspective(30, float(viewportSize[2]) / viewportSize[3], 0.01, 1000);
    const QMatrix4x4 viewProjectionMatrix = projectionMatrix * viewMatrix.toMatrix();


    program1.bind();
    program1.setUniformValue(u_modelToWorld, modelMatrix.toMatrix());
    program1.setUniformValue(u_worldToView, viewProjectionMatrix);
    paintQtLogo();
    program1.release();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    modelMatrix.rotate(1.0f, QVector3D(1.0f, 0.0f, 0.0f));
//    modelMatrix.rotate(1.0f, QVector3D(0.0f, 1.0f, 0.0f));
//    modelMatrix.rotate(1.0f, QVector3D(0.0f, 0.0f, 1.0f));
//    modelMatrix.translate(0.01f, 0.0f, 0.0f);
//    modelMatrix.translate(0.0f, 0.01f, 0.0f);
//    modelMatrix.translate(0.0f, 0.0f, 0.01f);
//    viewMatrix.translate(0.0f, 0.0f, 0.0f);
//    viewMatrix.rotate(1.0f, 0.0f, 0.0f, 1.0f);
}

void StlRenderer::createGeometry()
{
    vertices.clear();
    normals.clear();
    float uno = 0.5f;
    float zero = -0.5f;
    float menouno = -0.5f;
    float menozero = -0.5f;

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
}

