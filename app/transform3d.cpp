#include "transform3d.h"

Transform3D::Transform3D() :
    dirty(true),
    scale(1.0f, 1.0f, 1.0f)
{

}

//transformations
void Transform3D::translate(const QVector3D &dt)
{
    dirty = true;
    translation += dt;
}

void Transform3D::getScale(const QVector3D &ds)
{
    dirty = true;
    scale *= ds;
}

void Transform3D::rotate(const QQuaternion &dr)
{
    dirty = true;
    rotation = dr * rotation;
}

void Transform3D::grow(const QVector3D &ds)
{
    dirty = true;
    scale += ds;
}

//setters
void Transform3D::setTranslation(const QVector3D &t)
{
    dirty = true;
    translation = t;
}

void Transform3D::setOffset(const QVector3D &o)
{
    dirty = true;
    offset = o;
}

void Transform3D::setScale(const QVector3D &s)
{
    dirty = true;
    scale = s;
}

void Transform3D::setRotation(const QQuaternion &r)
{
    dirty = true;
    rotation = r;
}

const QMatrix4x4 &Transform3D::toMatrix()
{
    if (dirty)
    {
        dirty = false;
        world.setToIdentity();
        world.translate(translation);
        world.translate(offset);
        world.rotate(rotation);
        world.scale(scale);
    }

    return world;
}

//overloading for transformation methods
void Transform3D::translate(float dx, float dy,float dz)
{
    translate(QVector3D(dx, dy, dz));
}

void Transform3D::getScale(float dx, float dy,float dz)
{
    getScale(QVector3D(dx, dy, dz));
}

void Transform3D::getScale(float factor)
{
    getScale(QVector3D(factor, factor, factor));
}

void Transform3D::rotate(float angle, const QVector3D &axis)
{
    rotate(QQuaternion::fromAxisAndAngle(axis, angle));
}

void Transform3D::rotate(float angle, float ax, float ay,float az)
{
    rotate(QQuaternion::fromAxisAndAngle(ax, ay, az, angle));
}

void Transform3D::grow(float dx, float dy, float dz)
{
    grow(QVector3D(dx, dy, dz));
}

void Transform3D::grow(float factor)
{
    grow(QVector3D(factor, factor, factor));
}

//overloading for setters
void Transform3D::setTranslation(float x, float y, float z)
{
    setTranslation(QVector3D(x, y, z));
}

void Transform3D::setOffset(float x, float y, float z)
{
    setOffset(QVector3D(x, y, z));
}

void Transform3D::setScale(float x, float y, float z)
{
    setScale(QVector3D(x, y, z));
}

void Transform3D::setScale(float k)
{
    setScale(QVector3D(k, k, k));
}

void Transform3D::setRotation(float angle, const QVector3D &axis)
{
    setRotation(QQuaternion::fromAxisAndAngle(axis, angle));
}

void Transform3D::setRotation(float angle, float ax, float ay, float az)
{
    setRotation(QQuaternion::fromAxisAndAngle(ax, ay, az, angle));
}

//getters
const QVector3D& Transform3D::getTranslation() const
{
    return translation;
}

const QVector3D& Transform3D::getScale() const
{
    return scale;
}

const QQuaternion& Transform3D::getRotation() const
{
    return rotation;
}
