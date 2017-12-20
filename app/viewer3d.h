#ifndef VIEWER3D_H
#define VIEWER3D_H

#include <QtQuick/QQuickFramebufferObject>
#include "stlrenderer.h"

class Viewer3D : public QQuickFramebufferObject
{
    Q_OBJECT
public:
    Renderer *createRenderer() const;
//    StlRenderer obj;
};

#endif // VIEWER3D_H
