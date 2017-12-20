#ifndef CAMERA3D_H
#define CAMERA3D_H
#include "transform3d.h"

class Camera3D
{
public:

  // Constructors
  Camera3D();

  void setAzimuth(float a);
  void setDistance(float d);
  void setElevation(float e);

  const float azimuth();
  const float distance();
  const float elevation();

  const QMatrix4x4& toMatrix();

private:
  bool m_dirty;
  QMatrix4x4 m_world;

  float m_azimuth;
  float m_distance;
  float m_elevation;
};

#endif // CAMERA3D_H
