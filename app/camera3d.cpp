#include "camera3d.h"
#include <QtMath>

Camera3D::Camera3D() : dirty(true), center(0, 0, 0)
{

}

//getters
const QMatrix4x4 &Camera3D::toMatrix()
{
    if (dirty)
    {
        dirty = false;
        camera.setToIdentity();
        const float azimuthInRadians = qDegreesToRadians(azimuth);
        const float elevationInRadians = qDegreesToRadians(elevation);
        const QVector3D eye(std::cos(elevationInRadians) * std::cos(azimuthInRadians),
                            std::sin(azimuthInRadians) * std::cos(elevationInRadians),
                            std::sin(elevationInRadians));


                QVector3D up = QVector3D(-std::cos(azimuthInRadians) * std::sin(elevationInRadians), -std::sin(elevationInRadians)*std::sin(azimuthInRadians), std::cos(elevationInRadians));

        camera.lookAt(eye * distance, QVector3D(0, 0, 0),up);
        camera.translate(-center.x(), -center.y(), -center.z());
    }
    return camera;
}

void Camera3D::setAzimuth(float a)
{
    dirty = true;
    azimuth = a;
}

void Camera3D::setDistance(float d)
{
    dirty = true;
    distance = d;
}

void Camera3D::setElevation(float e)
{
    dirty = true;
    elevation = e;
}

void Camera3D::setCenter(QVector3D c)
{
    dirty = true;
    center = c;
}

const float Camera3D::getAzimuth()
{
    return azimuth;
}

const float Camera3D::getElevation()
{
    return elevation;
}

const float Camera3D::getDistance()
{
    return distance;
}
