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
    program1.enableAttributeArray(alphaAttr1);
    program1.setAttributeArray(vertexAttr1, vertices.constData());
    program1.setAttributeArray(normalAttr1, normals.constData());
    program1.setAttributeArray(alphaAttr1, alpha.constData(), 1);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    program1.disableAttributeArray(normalAttr1);
    program1.disableAttributeArray(vertexAttr1);
    program1.disableAttributeArray(alphaAttr1);
}


void StlRenderer::initialize()
{
    initializeOpenGLFunctions();

    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);

    const char *vsrc1 =
            "attribute highp vec4 vertex;\n"
            "attribute mediump vec3 normal;\n"
            "attribute highp float alpha_channel;\n"
            "uniform mediump mat4 worldToView;\n"
            "uniform mediump mat4 modelToWorld;\n"
            "varying mediump vec4 color;\n"
            "void main(void)\n"
            "{\n"
            "    vec3 toLight = normalize(vec3(0.0, 0.3, 1.0));\n"
            "    float angle = max(dot(normal, toLight), 0.0);\n"
            "    vec3 col = vec3(0.40, 1.0, 0.0);\n"
            "    color = vec4(col * 0.2 + col * 0.8 * angle, alpha_channel);\n"
            "    color = clamp(color, 0.0, 1.0);\n"
            "    if (alpha_test == 1.0)\n"
            "    gl_Position = worldToView * modelToWorld * vertex;\n"
            "    else"
            "    gl_Position = worldToView * vertex;\n"
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

    alphaAttr1 = program1.attributeLocation("alpha_channel");
    vertexAttr1 = program1.attributeLocation("vertex");
    normalAttr1 = program1.attributeLocation("normal");
    u_modelToWorld = program1.uniformLocation("modelToWorld");
    u_worldToView = program1.uniformLocation("worldToView");


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    viewMatrix.setRotation(-90.0f, 1.0f, 0.0f, 0.0f);
}
void StlRenderer::render()
{
    QOpenGLFunctions *functions = QOpenGLContext::currentContext()->functions();

    glDepthMask(true);

    glClearColor(0.5f, 0.5f, 0.7f, 1.0f);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

void StlRenderer::setGeometry(const StlLoader::Triangles &tri)
{
    vertices.clear();
    normals.clear();
    alpha.clear();
    max = std::numeric_limits<float>::min();
    float min = std::numeric_limits<float>::max();

//    std::cout << "\nStampa dei triangoli letti in STLRENDERER:\n";
//    int i = 1;
    for (StlLoader::Triangles::const_iterator it = tri.begin(); it != tri.end(); ++it)
    {
        StlLoader::Triangle tri = *it;
        if (std::abs(tri.v1.x) > max)
        {
            max = std::abs(tri.v1.x);
        }

        if (std::abs(tri.v1.y) > max)
        {
            max = std::abs(tri.v1.y);
        }

        if (std::abs(tri.v1.z) > max)
        {
            max = std::abs(tri.v1.z);
        }

        if (std::abs(tri.v2.x) > max)
        {
            max = std::abs(tri.v2.x);
        }

        if (std::abs(tri.v2.y) > max)
        {
            max = std::abs(tri.v2.y);
        }

        if (std::abs(tri.v2.z) > max)
        {
            max = std::abs(tri.v2.z);
        }

        if (std::abs(tri.v3.x) > max)
        {
            max = std::abs(tri.v3.x);
        }

        if (std::abs(tri.v3.y) > max)
        {
            max = std::abs(tri.v3.y);
        }

        if (std::abs(tri.v3.z) > max)
        {
            max = std::abs(tri.v3.z);
        }

        vertices << QVector3D(tri.v1.x, tri.v1.y, tri.v1.z);
        alpha << 1.0f;
        normals << QVector3D(tri.normal.x, tri.normal.y, tri.normal.z);
        vertices << QVector3D(tri.v2.x, tri.v2.y, tri.v2.z);
        alpha << 1.0f;
        normals << QVector3D(tri.normal.x, tri.normal.y, tri.normal.z);
        vertices << QVector3D(tri.v3.x, tri.v3.y, tri.v3.z);
        alpha << 1.0f;
        normals << QVector3D(tri.normal.x, tri.normal.y, tri.normal.z);

//            std::cout << std::endl << "Triangolo " << i << ":" << std::endl;
//            std::cout << "Normale.x:   \t" << tri.normal.x << "\t normale.y: \t" << tri.normal.y << "\t normale.z: \t" << tri.normal.z << std::endl;
//            std::cout << "Vertice 1.x: \t" << tri.v1.x << "\t vertice 1.y: \t" << tri.v1.y << "\t vertice 1.z: \t" << tri.v1.z << std::endl;
//            std::cout << "Vertice 2.x: \t" << tri.v2.x << "\t vertice 2.y: \t" << tri.v2.y << "\t vertice 2.z: \t" << tri.v2.z << std::endl;
//            std::cout << "Vertice 3.x: \t" << tri.v3.x << "\t vertice 3.y: \t" << tri.v3.y << "\t vertice 3.z: \t" << tri.v3.z << std::endl;
//            ++i;

    }

    viewMatrix.setTranslation(0.0f, max * 5, 0.0f);
}

//void StlRenderer::createGeometry()
//{
//    vertices.clear();
//    normals.clear();
//    float uno = 0.5f;
//    float zero = -0.5f;
//    float menouno = -0.5f;
//    float menozero = -0.5f;

//    vertices << QVector3D(zero, uno, uno);
//    vertices << QVector3D(uno, zero, uno);
//    vertices << QVector3D(uno,uno,uno);

//    normals << QVector3D(menozero, zero, uno);
//    normals << QVector3D(menozero, zero, uno);
//    normals << QVector3D(menozero, zero, uno);

//    vertices << QVector3D(uno, zero, uno);
//    vertices << QVector3D(zero, uno, uno);
//    vertices << QVector3D(zero,zero,uno);

//    normals << QVector3D(zero, zero, uno);
//    normals << QVector3D(zero, zero, uno);
//    normals << QVector3D(zero, zero, uno);

//    vertices << QVector3D(zero, zero, zero);
//    vertices << QVector3D(uno, uno, zero);
//    vertices << QVector3D(uno, zero, zero);

//    normals << QVector3D(zero, zero, menouno);
//    normals << QVector3D(zero, zero, menouno);
//    normals << QVector3D(zero, zero, menouno);

//    vertices << QVector3D(uno, uno, zero);
//    vertices << QVector3D(zero, zero, zero);
//    vertices << QVector3D(zero,uno,zero);

//    normals << QVector3D(menozero, zero, menouno);
//    normals << QVector3D(menozero, zero, menouno);
//    normals << QVector3D(menozero, zero, menouno);

//    vertices << QVector3D(zero, zero, zero);
//    vertices << QVector3D(uno, zero, uno);
//    vertices << QVector3D(zero,zero,uno);

//    normals << QVector3D(zero, menouno, zero);
//    normals << QVector3D(zero, menouno, zero);
//    normals << QVector3D(zero, menouno, zero);

//    vertices << QVector3D(uno, zero, uno);
//    vertices << QVector3D(zero, zero, zero);
//    vertices << QVector3D(uno,zero,zero);

//    normals << QVector3D(zero, menouno, menozero);
//    normals << QVector3D(zero, menouno, menozero);
//    normals << QVector3D(zero, menouno, menozero);

//    vertices << QVector3D(uno, zero, uno);
//    vertices << QVector3D(uno, uno, zero);
//    vertices << QVector3D(uno,uno,uno);

//    normals << QVector3D(uno, menozero, zero);
//    normals << QVector3D(uno, menozero, zero);
//    normals << QVector3D(uno, menozero, zero);

//    vertices << QVector3D(uno, uno, zero);
//    vertices << QVector3D(uno, zero, uno);
//    vertices << QVector3D(uno,zero,zero);

//    normals << QVector3D(uno, zero, zero);
//    normals << QVector3D(uno, zero, zero);
//    normals << QVector3D(uno, zero, zero);

//    vertices << QVector3D(uno, uno, zero);
//    vertices << QVector3D(zero, uno, uno);
//    vertices << QVector3D(uno,uno,uno);

//    normals << QVector3D(zero, uno, menozero);
//    normals << QVector3D(zero, uno, menozero);
//    normals << QVector3D(zero, uno, menozero);



//    vertices << QVector3D(zero, uno, uno);
//    vertices << QVector3D(uno, uno, zero);
//    vertices << QVector3D(zero,uno,zero);

//    normals << QVector3D(zero, uno, zero);
//    normals << QVector3D(zero, uno, zero);
//    normals << QVector3D(zero, uno, zero);


//    vertices << QVector3D(zero, zero, zero);
//    vertices << QVector3D(zero, uno, uno);
//    vertices << QVector3D(zero,uno,zero);

//    normals << QVector3D(menouno, zero, zero);
//    normals << QVector3D(menouno, zero, zero);
//    normals << QVector3D(menouno, zero, zero);

//    vertices << QVector3D(zero, uno, uno);
//    vertices << QVector3D(zero, zero, zero);
//    vertices << QVector3D(zero,zero,uno);

//    normals << QVector3D(menouno, menozero, zero);
//    normals << QVector3D(menouno, menozero, zero);
//    normals << QVector3D(menouno, menozero, zero);
//}

