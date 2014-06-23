#include "ParticleCoreShellView.h"


ParticleCoreShellView::ParticleCoreShellView(QGraphicsItem *parent)
    : ConnectableView(parent)
{
    setName("ParticleCoreShell");
    setLabel("Core shell\nparticle");
    setColor(DesignerHelper::getDefaultParticleColor());
    setRectangle( QRect(0, 0, DesignerHelper::getDefaultParticleWidth(), DesignerHelper::getDefaultParticleHeight()) );
    addPort("out", NodeEditorPort::Output, NodeEditorPort::FormFactor);
    addPort("core", NodeEditorPort::Input, NodeEditorPort::FormFactor);
    addPort("shell", NodeEditorPort::Input, NodeEditorPort::FormFactor);
    m_roundpar = 5;
    m_label_vspace = 45;
}


