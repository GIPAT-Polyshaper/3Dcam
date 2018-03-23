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

  const float getAzimuth();
  const float getDistance();
  const float getElevation();

  const QMatrix4x4& toMatrix();

  void setCenter(QVector3D c);
private:
  bool dirty;
  QMatrix4x4 camera;

  float azimuth;
  float distance;
  float elevation;
  QVector3D center;
};

#endif // CAMERA3D_H
