#include "viewer3d.h"
#include "stlrenderer.h"
#include <QtQuick/QQuickWindow>
#include <QOpenGLFramebufferObject>
#include <qsgsimpletexturenode.h>

class Model3DRenderer : public QQuickFramebufferObject::Renderer
{
public:
    StlRenderer obj;

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
        Viewer3D* v = static_cast<Viewer3D*>(item);

        //if we have a new model to render, or working volume has changed
        if (v->isTriangleDirty() || v->isVolumeDirty())
        {
            obj.setVolume(v->getVolumeX(),
                          v->getVolumeY(),
                          v->getVolumeZ());

            obj.setGeometry(v->getTriangles());
            obj.setCamera(v->getAzimuth(),
                          v->getDistance(),
                          v->getElevation());

            v->setCameraDirty(false);
            v->setTrianglesDirty(false);
            v->setVolumeDirty(false);
        }
        //if camera position has changed
        if (v->isCameraDirty())
        {
            obj.setCamera(v->getAzimuth(),
                          v->getDistance(),
                          v->getElevation());

            v->setCameraDirty(false);
        }
    }

    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) {
        QOpenGLFramebufferObjectFormat format;
        format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        format.setSamples(4);
        return new QOpenGLFramebufferObject(size, format);
    }

    void setGeometry(StlLoader::Triangles triangles)
    {
        obj.setGeometry(triangles);
    }
};

QQuickFramebufferObject::Renderer *Viewer3D::createRenderer() const
{
    return new Model3DRenderer();
}

Viewer3D::Viewer3D()
{
    setMirrorVertically(true);
    ApplicationControl::get_instance().setViewer3D(this);
    volumeX = 100;
    volumeY = 100;
    volumeZ = 100;
    elevation = 20;
    azimuth = 0;
    distance = 3;
}

bool Viewer3D::isCameraDirty() const
{
    return cameraDirty;
}

bool Viewer3D::isTriangleDirty() const
{
    return trianglesDirty;
}

bool Viewer3D::isVolumeDirty() const
{
    return volumeDirty;
}

void Viewer3D::setCameraDirty(bool c)
{
    cameraDirty = c;
    update();
}

void Viewer3D::setTrianglesDirty(bool t)
{
    trianglesDirty = t;
    update();
}

void Viewer3D::setVolumeDirty(bool v)
{
    volumeDirty = v;
    update();
}

void Viewer3D::setAzimuth(int az)
{
    azimuth = az;
    setCameraDirty(true);
    emit azimuthChanged(az);
}

void Viewer3D::setDistance(float d)
{
    distance = d;
    setCameraDirty(true);
    emit distanceChanged(d);
}

void Viewer3D::setElevation(int e)
{
    elevation = e;
    setCameraDirty(true);
    emit elevationChanged(e);
}

int Viewer3D::getAzimuth() const
{
    return azimuth;
}

float Viewer3D::getDistance() const
{
    return distance;
}

int Viewer3D::getElevation() const
{
    return elevation;
}

int Viewer3D::getVolumeX() const
{
    return volumeX;
}

int Viewer3D::getVolumeY() const
{
    return volumeY;
}

int Viewer3D::getVolumeZ() const
{
    return volumeZ;
}

const StlLoader::Triangles &Viewer3D::getTriangles() const
{
    return triangles;
}

void Viewer3D::setGeometry(const StlLoader::Triangles &triangles)
{
    this->triangles.clear();
    this->triangles = triangles;
    setTrianglesDirty(true);
}

void Viewer3D::setVolumeX(int x)
{
    volumeX = x;
    setVolumeDirty(true);
}

void Viewer3D::setVolumeY(int y)
{
    volumeY = y;
    setVolumeDirty(true);
}

void Viewer3D::setVolumeZ(int z)
{
    volumeZ = z;
    setVolumeDirty(true);
}
