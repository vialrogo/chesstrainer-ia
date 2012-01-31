#include "Ficha.h"

Ficha::Ficha() :
    QObject(0), QGraphicsPixmapItem(0)
{
    setCacheMode(DeviceCoordinateCache);
    X=0;
    Y=0;
}

Ficha::Ficha(const QPixmap& pixmap) :
    QObject(0), QGraphicsPixmapItem(pixmap)
{
    setCacheMode(DeviceCoordinateCache);
}

Ficha::Ficha(QSizeF size, const QPixmap& pixmap, QObject* parent) :
    QObject(parent), QGraphicsPixmapItem(pixmap)
{
    m_size = size;
    setCacheMode(DeviceCoordinateCache);
}

Ficha::~Ficha()
{
}

QRectF Ficha::boundingRect() const
{
return QRectF(0, 0, m_size.width(), m_size.height());
}

void Ficha::animatePosition(const QPointF& end, int mtime)
{
    // Start animate this class
    QPropertyAnimation* anim = new QPropertyAnimation(this, "pos");

    // 2 second duration animation
    anim->setDuration(mtime);
    // position to start animation
//    anim->setStartValue(start);
    // end position of animation
    anim->setEndValue(end);
    // easing curve
    //anim->setEasingCurve(QEasingCurve::InOutElastic);

    // Listen animation finished signal
    QObject::connect(anim, SIGNAL(finished()), this, SLOT(animationFinished()));

    // Start animation and delete QPropertyAnimation class on the end
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void Ficha::animationFinished()
{
    // This slot is called when animation ends
}

int Ficha::getX()
{
    return X;
}

int Ficha::getY()
{
    return Y;
}

void Ficha::setX(int X_in)
{
    X=X_in;
}

void Ficha::setY(int Y_in)
{
    Y=Y_in;
}
