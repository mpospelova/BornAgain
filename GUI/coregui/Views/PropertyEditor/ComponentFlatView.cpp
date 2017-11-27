// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/ComponentFlatView.cpp
//! @brief     Implements class ComponentFlatView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ComponentFlatView.h"
#include "ComponentUtils.h"
#include "PropertyEditorFactory.h"
#include "SessionItem.h"
#include "SessionModel.h"
#include "LayoutUtils.h"
#include "PropertyWidgetItem.h"
#include "CustomEventFilters.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDataWidgetMapper>
#include <QSpinBox>
#include <QComboBox>

ComponentFlatView::ComponentFlatView(QWidget* parent)
    : ComponentView(parent)
    , m_mainLayout(new QVBoxLayout)
    , m_gridLayout(nullptr)
    , m_model(nullptr)
    , m_show_children(true)
    , m_wheel_event_filter(new WheelEventEater)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_mainLayout->setMargin(10);
    m_mainLayout->setSpacing(0);

    initGridLayout();

    setLayout(m_mainLayout);
}

ComponentFlatView::~ComponentFlatView() = default;

void ComponentFlatView::setItem(SessionItem* item)
{
    clearEditor();

    m_topItems.push_back(item);
    setModel(item->model());
    updateItemProperties();
}

void ComponentFlatView::addItem(SessionItem* item)
{
    if (m_topItems.isEmpty()) {
        setItem(item);
        return;
    }

    m_topItems.push_back(item);
    updateItemProperties();
}

void ComponentFlatView::setModel(SessionModel* model)
{
    if (m_model) {
        disconnect(m_model, &SessionModel::dataChanged, this, &ComponentFlatView::onDataChanged);

    }

    m_model = model;

    if (m_model) {
        connect(m_model, &SessionModel::dataChanged, this, &ComponentFlatView::onDataChanged);
    }

}

void ComponentFlatView::clearLayout()
{
    Q_ASSERT(m_gridLayout);

    LayoutUtils::clearLayout(m_gridLayout, false);

    for(auto widget: m_widgetItems)
        delete widget;

    m_widgetItems.clear();

}

void ComponentFlatView::setShowChildren(bool show)
{
    m_show_children = show;

}

void ComponentFlatView::onDataChanged(const QModelIndex& topLeft, const QModelIndex&bottomRight,
                                      const QVector<int>& roles)
{
    Q_UNUSED(bottomRight);
    SessionItem *item = m_model->itemForIndex(topLeft);
    Q_ASSERT(item);
    if (item->modelType() == Constants::GroupItemType)
        updateItemProperties();

    if (roles.contains(SessionFlags::FlagRole))
        updateItemRoles(item);
}

void ComponentFlatView::clearEditor()
{
    m_topItems.clear();
    clearLayout();
}

void ComponentFlatView::updateItemProperties()
{    

    clearLayout();

    QList<const SessionItem*> allitems;

    for (auto item : m_topItems)
        allitems += ComponentUtils::componentItems(*item);

    int nrow(0);
    for (auto child : allitems) {

        auto widget = createWidget(child);
        if (!widget)
            continue;

        widget->addToGrid(m_gridLayout, ++nrow);
        m_widgetItems.push_back(widget);

        if (!m_show_children)
            break;
    }

}

void ComponentFlatView::updateItemRoles(SessionItem* item)
{
    for(auto widget: m_widgetItems)
        if (widget->item() == item)
            widget->updateItemRoles();
}

void ComponentFlatView::initGridLayout()
{
    delete m_gridLayout;
    m_gridLayout = new QGridLayout;
    m_gridLayout->setSpacing(6);
    m_mainLayout->addLayout(m_gridLayout);
    m_mainLayout->addStretch(1);
}

PropertyWidgetItem* ComponentFlatView::createWidget(const SessionItem* item)
{
    auto editor = PropertyEditorFactory::CreateEditor(*item);
    if (!editor)
        return nullptr;

    install_custom_filters(editor);

    auto result = new PropertyWidgetItem(this);
    result->setItemEditor(item, editor);

    return result;
}

void ComponentFlatView::install_custom_filters(QWidget* editor)
{
    editor->installEventFilter(m_wheel_event_filter.get());
    editor->setFocusPolicy(Qt::StrongFocus);

    for(auto w : editor->findChildren<QAbstractSpinBox *>()) {
        w->installEventFilter(m_wheel_event_filter.get());
        w->setFocusPolicy(Qt::StrongFocus);
    }

    for(auto w : editor->findChildren<QComboBox *>())
        w->installEventFilter(m_wheel_event_filter.get());

}
