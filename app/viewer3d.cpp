#include "viewer3d.h"
#include "stlrenderer.h"
#include <QtQuick/QQuickWindow>
#include <QOpenGLFramebufferObject>
#include <qsgsimpletexturenode.h>

class Model3DRenderer : public QQuickFramebufferObject::Renderer
{
public:
    Model3DRenderer()
    {
        obj.initialize();
    }

    void render()
    {
        obj.render();
        update();
    }

    void synchronize(QQuickFramebufferObject *item)
    {
        obj.setGeometry(GCodeGenerator::get_instance().getTriangles());
    }

    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) {
        QOpenGLFramebufferObjectFormat format;
        format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        format.setSamples(4);
        return new QOpenGLFramebufferObject(size, format);
    }
    StlRenderer obj;
};

QQuickFramebufferObject::Renderer *Viewer3D::createRenderer() const
{
    return new Model3DRenderer();
}

Viewer3D::Viewer3D()
{
    setMirrorVertically(true);
}
  /*
   * here only for reference
   */
//class FbItemRenderer : public QQuickFramebufferObject::Renderer
//{
//    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size)
//    {
//        QOpenGLFramebufferObjectFormat format;
//        format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
//        // optionally enable multisampling by doing format.setSamples(4);
//        return new QOpenGLFramebufferObject(size, format);
//    }

//    void render()
//    {
//        // Called with the FBO bound and the viewport set.
//        ... // Issue OpenGL commands.
//    }
//    ...
//}

//class FbItem : public QQuickFramebufferObject
//{
//    QQuickFramebufferObject::Renderer *createRenderer() const
//    {
//        return new FbItemRenderer;
//    }
//    ...
//}

//int main(int argc, char **argv)
//{
//    ...
//    qmlRegisterType("fbitem", 1, 0, "FbItem");
//    ...
//}

