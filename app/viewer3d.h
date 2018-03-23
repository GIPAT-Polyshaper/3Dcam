#ifndef VIEWER3D_H
#define VIEWER3D_H

#include <QtQuick/QQuickFramebufferObject>
#include "stlrenderer.h"
#include "applicationcontrol.h"

class Viewer3D : public QQuickFramebufferObject
{
    Q_OBJECT

    Q_PROPERTY(int azimuthCam READ getAzimuth NOTIFY azimuthChanged)
    Q_PROPERTY(int elevationCam READ getElevation NOTIFY elevationChanged)
    Q_PROPERTY(float distanceCam READ getDistance NOTIFY distanceChanged)

public:
    Renderer *createRenderer() const;
    Viewer3D();

    bool isCameraDirty() const;
    bool isTriangleDirty() const;
    bool isVolumeDirty() const;

    void setCameraDirty(bool c);
    void setTrianglesDirty(bool t);
    void setVolumeDirty(bool v);

    void setAzimuth(int az);
    void setDistance(float d);
    void setElevation(int e);

    int getAzimuth() const;
    float getDistance() const;
    int getElevation() const;

    int getVolumeX() const;
    int getVolumeY() const;
    int getVolumeZ() const;

    const StlLoader::Triangles& getTriangles() const;
    void setGeometry(const StlLoader::Triangles &triangles);

public slots:
    void setVolumeX(int x);
    void setVolumeY(int y);
    void setVolumeZ(int z);

signals:
    void azimuthChanged(int newAzimuth);
    void elevationChanged(int newElevation);
    void distanceChanged(float newDistance);

private:
    bool cameraDirty = false;
    bool trianglesDirty = false;
    bool volumeDirty = false;

    int azimuth;
    float distance;
    int elevation;

    int volumeX;
    int volumeY;
    int volumeZ;

    StlLoader::Triangles triangles;
};

#endif // VIEWER3D_H
