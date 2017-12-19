#include "camera3d.h"

Camera3D::Camera3D() : m_dirty(true)
{

}

//transformations
void Camera3D::translate(const QVector3D &dt)
{
    m_dirty = true;
    m_translation += dt;
}

void Camera3D::rotate(const QQuaternion &dr)
{
    m_dirty = true;
    m_rotation = dr * m_rotation;
}

//setters
void Camera3D::setTranslation(const QVector3D &t)
{
    m_dirty = true;
    m_translation = t;
}

void Camera3D::setRotation(const QQuaternion &r)
{
    m_dirty = true;
    m_rotation = r;
}

//getters
const QMatrix4x4 &Camera3D::toMatrix()
{
    if (m_dirty)
    {
        m_dirty = false;
        m_world.setToIdentity();
        m_world.rotate(m_rotation.conjugate());
        m_world.translate(-m_translation);
    }
    return m_world;
}

//overloading for transformation methods
void Camera3D::translate(float dx, float dy,float dz)
{
    translate(QVector3D(dx, dy, dz));
}

void Camera3D::rotate(float angle, const QVector3D &axis)
{
    rotate(QQuaternion::fromAxisAndAngle(axis, angle));
}

void Camera3D::rotate(float angle, float ax, float ay,float az)
{
    rotate(QQuaternion::fromAxisAndAngle(ax, ay, az, angle));
}

//overloading for setters
void Camera3D::setTranslation(float x, float y, float z)
{
    setTranslation(QVector3D(x, y, z));
}

void Camera3D::setRotation(float angle, const QVector3D &axis)
{
    setRotation(QQuaternion::fromAxisAndAngle(axis, angle));
}

void Camera3D::setRotation(float angle, float ax, float ay, float az)
{
    setRotation(QQuaternion::fromAxisAndAngle(ax, ay, az, angle));
}

//getters
const QVector3D& Camera3D::getTranslation() const
{
    return m_translation;
}

const QQuaternion& Camera3D::getRotation() const
{
    return m_rotation;
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
