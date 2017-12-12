/**************************************************************************
 * PolyShaper 3D Cam                                                      *
 * Copyright (C) 2017                                                     *
 * Tomassino Ferrauto <tomassino.ferrauto@gmail.com>                      *
 * Flavio Prattico <flavioprattico@gmail.com>                             *
 * Carmine Gianfagna <carmine.gianfagna@gmail.com>                        *
 *                                                                        *
 * This program is free software; you can redistribute it and/or modify   *
 * it under the terms of the GNU General Public License as published by   *
 * the Free Software Foundation; either version 3 of the License, or      *
 * (at your option) any later version.                                    *
 *                                                                        *
 * This program is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 * GNU General Public License for more details.                           *
 *                                                                        *
 * You should have received a copy of the GNU General Public License      *
 * along with this program; if not, write to the                          *
 * Free Software Foundation, Inc.,                                        *
 * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.              *
 **************************************************************************/

#ifndef GCODEGENERATOR_H
#define GCODEGENERATOR_H

#include <QObject>

class GCodeGenerator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString path READ getPath NOTIFY pathChanged)

    Q_PROPERTY(float altezzaUt READ getAltezzaUtensile NOTIFY altezzaChanged)
    Q_PROPERTY(float diametroUt READ getDiametroUtensile NOTIFY diametroChanged)
    Q_PROPERTY(float velocitaUt READ getVelocitaUtensile NOTIFY velocitaChanged)
    Q_PROPERTY(QString formaUt READ getFormaUtensile  NOTIFY formaChanged)
    Q_PROPERTY(float overlap READ getOverlapPassate NOTIFY overlapChanged)
    Q_PROPERTY(float volumeX READ getVolumeX NOTIFY volumeXChanged)
    Q_PROPERTY(float volumeY READ getVolumeY NOTIFY volumeYChanged)
    Q_PROPERTY(float volumeZ READ getVolumeZ NOTIFY volumeZChanged)

public:
    enum Forma
    {
        Sferica,
        Candela
    };

    float getAltezzaUtensile() const ;
    float getDiametroUtensile() const;
    float getVelocitaUtensile() const;
    QString getFormaUtensile() const;
    float getOverlapPassate() const;
    float getVolumeX() const;
    float getVolumeY() const;
    float getVolumeZ() const;
    QString getPath() const;
    GCodeGenerator();

signals:
    void altezzaChanged(float newAltezza);
    void diametroChanged(float newDiametro);
    void velocitaChanged(float newVelocita);
    void formaChanged(QString newForma);
    void overlapChanged(float newOverlap);
    void volumeXChanged(float newVolumeX);
    void volumeYChanged(float newVolumeY);
    void volumeZChanged(float newVolumeZ);

    void textRead(QString text);
    void pathChanged(QString path);

public slots:
    void setAltezza(float a);
    void setDiametro(float d);
    void setVelocita(float v);
    void setForma(QString f);
    void setOverlap(float o);
    void setVolumeX(float x);
    void setVolumeY(float y);
    void setVolumeZ(float z);

    //    void readAndGenerate();
    void openFile(QString path);

private:
    QString filePath;

    float altezzaUtensile;
    float diametroUtensile;
    float velocitaUtensile;
    Forma formaUtensile;
    float overlapPassate;
    float volumeXAxis;
    float volumeYAxis;
    float volumeZAxis;

    void readAndGenerate();

};

#endif // GCODEGENERATOR_H
