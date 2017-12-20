#ifndef CAMERA3D_H
#define CAMERA3D_H
#include "transform3d.h"

class Camera3D
{
public:

  // Constructors
  Camera3D();

  //transformations
  void translate(const QVector3D &dt);
  void translate(float dx, float dy, float dz);
  void rotate(const QQuaternion &dr);
  void rotate(float angle, const QVector3D &axis);
  void rotate(float angle, float ax, float ay, float az);

  //setters
  void setTranslation(const QVector3D &t);
  void setTranslation(float x, float y, float z);
  void setRotation(const QQuaternion &r);
  void setRotation(float angle, const QVector3D &axis);
  void setRotation(float angle, float ax, float ay, float az);

  //getters
  const QVector3D& getTranslation() const;
  const QQuaternion& getRotation() const;
  const QMatrix4x4& toMatrix();

private:
  bool m_dirty;
  QVector3D m_translation;
  QQuaternion m_rotation;
  QMatrix4x4 m_world;

};

#endif // CAMERA3D_H
