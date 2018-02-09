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
    }

    void synchronize(QQuickFramebufferObject *item)
    {
        bool camera_dirty = GCodeGenerator::get_instance().isCameraDirty();
        bool triangles_dirty = GCodeGenerator::get_instance().isTrianglesDirty();
        bool volume_dirty = GCodeGenerator::get_instance().isVolumeDirty();
        if (triangles_dirty || volume_dirty)
        {
            obj.setGeometry(GCodeGenerator::get_instance().getTriangles());
            obj.setCamera(GCodeGenerator::get_instance().getAzimuth(), GCodeGenerator::get_instance().getDistance(), GCodeGenerator::get_instance().getElevation());
            obj.setVolume(GCodeGenerator::get_instance().getVolumeX(), GCodeGenerator::get_instance().getVolumeY(), GCodeGenerator::get_instance().getVolumeZ());
            GCodeGenerator::get_instance().cleanVolume();
            GCodeGenerator::get_instance().cleanCamera();
            GCodeGenerator::get_instance().cleanTriangles();
        }
        if (camera_dirty)
        {
            obj.setCamera(GCodeGenerator::get_instance().getAzimuth(), GCodeGenerator::get_instance().getDistance(), GCodeGenerator::get_instance().getElevation());
            GCodeGenerator::get_instance().cleanCamera();
        }
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

