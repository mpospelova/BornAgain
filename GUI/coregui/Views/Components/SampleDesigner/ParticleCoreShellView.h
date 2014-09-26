#ifndef PARTICLECORESHELLVIEW_H
#define PARTICLECORESHELLVIEW_H

#include "ConnectableView.h"

//! Class representing view of Particle item
class BA_CORE_API_ ParticleCoreShellView : public ConnectableView
{
    Q_OBJECT

public:
    enum { Type = DesignerHelper::ParticleType };

    ParticleCoreShellView(QGraphicsItem *parent = 0);

    int type() const { return Type; }

    void addView(IView *childView, int row = 0);

};


#endif
