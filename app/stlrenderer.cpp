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


void StlRenderer::paintObject()
{
    program1.enableAttributeArray(normalAttr1);
    program1.enableAttributeArray(vertexAttr1);
    program1.enableAttributeArray(alphaAttr1);
    program1.enableAttributeArray(colorAttr1);
    program1.setAttributeArray(vertexAttr1, vertices.constData());
    program1.setAttributeArray(normalAttr1, normals.constData());
    program1.setAttributeArray(alphaAttr1, alpha.constData(), 1);
    program1.setAttributeArray(colorAttr1, colors.constData());
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    program1.disableAttributeArray(normalAttr1);
    program1.disableAttributeArray(vertexAttr1);
    program1.disableAttributeArray(alphaAttr1);
    program1.disableAttributeArray(colorAttr1);
}


void StlRenderer::initialize()
{
    initializeOpenGLFunctions();

    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);

    const char *vsrc1 =
            "attribute highp vec4 vertex;\n"
            "attribute mediump vec3 normal;\n"
            "attribute highp float alpha_channel;\n"
            "attribute mediump vec3 col;\n"
            "uniform mediump mat4 worldToView;\n"
            "uniform mediump mat4 modelToWorld;\n"
            "varying mediump vec4 color;\n"
            "void main(void)\n"
            "{\n"
            "    vec3 toLight = normalize(vec3(0.0, 0.3, 1.0));\n"
            "    float angle = max(dot(normal, toLight), 0.0);\n"
            "    color = vec4(col * 0.2 + col * 0.8 * angle, alpha_channel);\n"
            "    color = clamp(color, 0.0, 1.0);\n"
            "    if (alpha_channel == 1.0)\n"
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
    colorAttr1 = program1.attributeLocation("col");
    u_modelToWorld = program1.uniformLocation("modelToWorld");
    u_worldToView = program1.uniformLocation("worldToView");


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

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
    projectionMatrix.perspective(30, float(viewportSize[2]) / viewportSize[3], 0.01, 11*diff_max);
    const QMatrix4x4 viewProjectionMatrix = projectionMatrix * viewMatrix.toMatrix();


    program1.bind();
    program1.setUniformValue(u_modelToWorld, modelMatrix.toMatrix());
    program1.setUniformValue(u_worldToView, viewProjectionMatrix);
    paintObject();
    program1.release();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
}

void StlRenderer::setGeometry(const StlLoader::Triangles &tri)
{
    vertices.clear();
    normals.clear();
    colors.clear();
    alpha.clear();
    diff_max = std::numeric_limits<float>::lowest();

    float xmax, ymax, zmax;
    float xmin, ymin, zmin;

    xmax = ymax = zmax = std::numeric_limits<float>::lowest();
    xmin = ymin = zmin = std::numeric_limits<float>::max();

    for (StlLoader::Triangles::const_iterator it = tri.begin(); it != tri.end(); ++it)
    {
        StlLoader::Triangle tri = *it;

        if (tri.v1.x > xmax)
        {
            xmax = tri.v1.x;
        }

        if (tri.v1.y > ymax)
        {
            ymax = tri.v1.y;
        }

        if (tri.v1.z > zmax)
        {
            zmax = tri.v1.z;
        }

        if (tri.v2.x > xmax)
        {
            xmax = tri.v2.x;
        }

        if (tri.v2.y > ymax)
        {
            ymax = tri.v2.y;
        }

        if (tri.v2.z > zmax)
        {
            zmax = tri.v2.z;
        }

        if (tri.v3.x > xmax)
        {
            xmax = tri.v3.x;
        }

        if (tri.v3.y > ymax)
        {
            ymax = tri.v3.y;
        }

        if (tri.v3.z > zmax)
        {
            zmax = tri.v3.z;
        }

        if (tri.v1.x < xmin)
        {
            xmin = tri.v1.x;
        }

        if (tri.v1.y < ymin)
        {
            ymin = tri.v1.y;
        }

        if (tri.v1.z < zmin)
        {
            zmin = tri.v1.z;
        }

        if (tri.v2.x < xmin)
        {
            xmin = tri.v2.x;
        }

        if (tri.v2.y < ymin)
        {
            ymin = tri.v2.y;
        }

        if (tri.v2.z < zmin)
        {
            zmin = tri.v2.z;
        }

        if (tri.v3.x < xmin)
        {
            xmin = tri.v3.x;
        }

        if (tri.v3.y < ymin)
        {
            ymin = tri.v3.y;
        }

        if (tri.v3.z < zmin)
        {
            zmin = tri.v3.z;
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
    }

    float diff_x, diff_y, diff_z, diff_yz;
    diff_x = std::abs(xmax - xmin);
    diff_y = std::abs(ymax - ymin);
    diff_z = std::abs(zmax - zmin);
    diff_yz = (diff_y > diff_z) ? diff_y : diff_z;
    diff_max = (diff_x > diff_yz) ? diff_x : diff_yz;

    modelMatrix.setOffset(-xmin, -ymin, -zmin);

    int volumex, volumey, volumez;
    volumex = GCodeGenerator::get_instance().getVolumeX();
    volumey = GCodeGenerator::get_instance().getVolumeY();
    volumez = GCodeGenerator::get_instance().getVolumeZ();

    QVector3D color;
    if (diff_x > volumex || diff_y > volumey || diff_z > volumez)
    {
        color = QVector3D(1.0, 0.0, 0.0);
    }
    else
    {
        color = QVector3D(0.4, 1.0, 0.0);
    }

    for (int i = 0; i < vertices.size(); ++i)
    {
        colors << color;
    }

    GCodeGenerator::get_instance().setDistance(3);
    GCodeGenerator::get_instance().setOffset(-xmin, -ymin, -zmin);
}

void StlRenderer::setCamera(int az, float di, int el)
{
    viewMatrix.setAzimuth(az);
    viewMatrix.setElevation(el);
    viewMatrix.setDistance(di * diff_max);
}

void StlRenderer::setVolume(int x, int y, int z)
{
    setWorkingVolume(x, y, z, 0.3);
}

void StlRenderer::setWorkingVolume(int x, int y, int z, float a)
{
    viewMatrix.setCenter(QVector3D(x/2, y/2, z/2));

    QVector3D color = QVector3D(0.4, 1.0, 0.0);

    normals << QVector3D(0, 0, 1);
    vertices << QVector3D(0, y, z);
    normals << QVector3D(0, 0, 1);
    vertices << QVector3D(x, 0, z);
    normals << QVector3D(0, 0, 1);
    vertices << QVector3D(x, y, z);
    alpha << a;
    alpha << a;
    alpha << a;

    colors << color;
    colors << color;
    colors << color;

    normals << QVector3D(0, 0, 1);
    vertices << QVector3D(x, 0, z);
    normals << QVector3D(0, 0, 1);
    vertices << QVector3D(0, y, z);
    normals << QVector3D(0, 0, 1);
    vertices << QVector3D(0, 0, z);
    alpha << a;
    alpha << a;
    alpha << a;

    colors << color;
    colors << color;
    colors << color;

    normals << QVector3D(0, 0, -1);
    vertices << QVector3D(0, 0, 0);
    normals << QVector3D(0, 0, -1);
    vertices << QVector3D(x, y, 0);
    normals << QVector3D(0, 0, -1);
    vertices << QVector3D(x, 0, 0);
    alpha << a;
    alpha << a;
    alpha << a;

    colors << color;
    colors << color;
    colors << color;

    normals << QVector3D(0, 0, -1);
    vertices << QVector3D(x, y, 0);
    normals << QVector3D(0, 0, -1);
    vertices << QVector3D(0, 0, 0);
    normals << QVector3D(0, 0, -1);
    vertices << QVector3D(0, y, 0);
    alpha << a;
    alpha << a;
    alpha << a;

    colors << color;
    colors << color;
    colors << color;

    normals << QVector3D(0, -1, 0);
    vertices << QVector3D(0, 0, 0);
    normals << QVector3D(0, -1, 0);
    vertices << QVector3D(x, 0, z);
    normals << QVector3D(0, -1, 0);
    vertices << QVector3D(0, 0, z);
    alpha << a;
    alpha << a;
    alpha << a;

    colors << color;
    colors << color;
    colors << color;

    normals << QVector3D(0, -1, 0);
    vertices << QVector3D(x, 0, z);
    normals << QVector3D(0, -1, 0);
    vertices << QVector3D(0, 0, 0);
    normals << QVector3D(0, -1, 0);
    vertices << QVector3D(x, 0, 0);
    alpha << a;
    alpha << a;
    alpha << a;

    colors << color;
    colors << color;
    colors << color;

    normals << QVector3D(1, 0, 0);
    vertices << QVector3D(x, 0, z);
    normals << QVector3D(1, 0, 0);
    vertices << QVector3D(x, y, 0);
    normals << QVector3D(1, 0, 0);
    vertices << QVector3D(x, y, z);
    alpha << a;
    alpha << a;
    alpha << a;

    colors << color;
    colors << color;
    colors << color;

    normals << QVector3D(1, 0, 0);
    vertices << QVector3D(x, y, 0);
    normals << QVector3D(1, 0, 0);
    vertices << QVector3D(x, 0, z);
    normals << QVector3D(1, 0, 0);
    vertices << QVector3D(x, 0, 0);
    alpha << a;
    alpha << a;
    alpha << a;

    colors << color;
    colors << color;
    colors << color;

    normals << QVector3D(0, 1, 0);
    vertices << QVector3D(x, y, 0);
    normals << QVector3D(0, 1, 0);
    vertices << QVector3D(0, y, z);
    normals << QVector3D(0, 1, 0);
    vertices << QVector3D(x, y, z);
    alpha << a;
    alpha << a;
    alpha << a;

    colors << color;
    colors << color;
    colors << color;

    normals << QVector3D(0, 1, 0);
    vertices << QVector3D(0, y, z);
    normals << QVector3D(0, 1, 0);
    vertices << QVector3D(x, y, 0);
    normals << QVector3D(0, 1, 0);
    vertices << QVector3D(0, y, 0);
    alpha << a;
    alpha << a;
    alpha << a;

    colors << color;
    colors << color;
    colors << color;

    normals << QVector3D(-1, 0, 0);
    vertices << QVector3D(0, 0, 0);
    normals << QVector3D(-1, 0, 0);
    vertices << QVector3D(0, y, z);
    normals << QVector3D(-1, 0, 0);
    vertices << QVector3D(0, y, 0);
    alpha << a;
    alpha << a;
    alpha << a;

    colors << color;
    colors << color;
    colors << color;

    normals << QVector3D(-1, 0, 0);
    vertices << QVector3D(0, y, z);
    normals << QVector3D(-1, 0, 0);
    vertices << QVector3D(0, 0, 0);
    normals << QVector3D(-1, 0, 0);
    vertices << QVector3D(0, 0, z);
    alpha << a;
    alpha << a;
    alpha << a;

    colors << color;
    colors << color;
    colors << color;
}

