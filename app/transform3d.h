#ifndef TRANSFORM3D_H
#define TRANSFORM3D_H

#include <QVector3D>
#include <QQuaternion>
#include <QMatrix4x4>

class Transform3D
{
public:
    Transform3D();

    //transformations
    void translate(const QVector3D &dt);
    void translate(float dx, float dy, float dz);
    void getScale(const QVector3D &ds);
    void getScale(float dx, float dy, float dz);
    void getScale(float factor);
    void rotate(const QQuaternion &dr);
    void rotate(float angle, const QVector3D &axis);
    void rotate(float angle, float ax, float ay, float az);
    void grow(const QVector3D &ds);
    void grow(float dx, float dy, float dz);
    void grow(float factor);

    //setters
    void setTranslation(const QVector3D &t);
    void setTranslation(float x, float y, float z);
    void setScale(const QVector3D &s);
    void setScale(float x, float y, float z);
    void setScale(float k);
    void setRotation(const QQuaternion &r);
    void setRotation(float angle, const QVector3D &axis);
    void setRotation(float angle, float ax, float ay, float az);

    //getters
    const QVector3D& getTranslation() const;
    const QVector3D& getScale() const;
    const QQuaternion& getRotation() const;
    const QMatrix4x4& toMatrix();

private:
    bool m_dirty;
    QVector3D m_translation;
    QVector3D m_scale;
    QQuaternion m_rotation;
    QMatrix4x4 m_world;
};

#endif // TRANSFORM3D_H
