#include "camera3d.h"
#include <QtMath>

Camera3D::Camera3D() : m_dirty(true)
{

}

//getters
const QMatrix4x4 &Camera3D::toMatrix()
{
    if (m_dirty)
    {
        m_dirty = false;
        m_world.setToIdentity();
        const float azimuthInRadians = qDegreesToRadians(m_azimuth);
        const float elevationInRadians = qDegreesToRadians(m_elevation);
        const QVector3D eye(std::cos(elevationInRadians) * std::cos(azimuthInRadians),
                            std::sin(azimuthInRadians) * std::cos(elevationInRadians),
                            std::sin(elevationInRadians));

        QVector3D up = QVector3D(-std::cos(azimuthInRadians) * std::sin(elevationInRadians), -std::sin(elevationInRadians)*std::sin(azimuthInRadians), std::cos(elevationInRadians));

        m_world.lookAt(eye * m_distance,QVector3D(0,0,0),up);
    }
    return m_world;
}

void Camera3D::setAzimuth(float a)
{
    m_dirty = true;
    m_azimuth = a;
}

void Camera3D::setDistance(float d)
{
    m_dirty = true;
    m_distance = d;
}

void Camera3D::setElevation(float e)
{
    m_dirty = true;
    m_elevation = e;
}

const float Camera3D::azimuth()
{
    return m_azimuth;
}

const float Camera3D::elevation()
{
    return m_elevation;
}

const float Camera3D::distance()
{
    return m_distance;
}
