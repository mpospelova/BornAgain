// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SessionItemUtils.cpp
//! @brief     Implements namespace SessionItemUtils
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SessionItemUtils.h"
#include "SessionItem.h"
#include "VectorItem.h"
#include "MaterialItem.h"
#include "ExternalProperty.h"
#include "GroupInfoCatalogue.h"
#include "GUIHelpers.h"
#include <QColor>
#include <QIcon>
#include <QPixmap>

namespace {
const GroupInfoCatalogue& groupInfoCatalogue()
{
    static GroupInfoCatalogue s_catalogue = GroupInfoCatalogue();
    return s_catalogue;
}
}

int SessionItemUtils::ParentRow(const SessionItem& item)
{
    if (item.parent())
        return item.parent()->rowOfChild(const_cast<SessionItem*>(&item));
    return -1;
}

kvector_t SessionItemUtils::GetVectorItem(const SessionItem& item, const QString& name)
{
    SessionItem* vectorItem = item.getItem(name);
    Q_ASSERT(vectorItem);
    double x = vectorItem->getItemValue(VectorItem::P_X).toDouble();
    double y = vectorItem->getItemValue(VectorItem::P_Y).toDouble();
    double z = vectorItem->getItemValue(VectorItem::P_Z).toDouble();
    return { x, y, z };
}

void SessionItemUtils::SetVectorItem(const SessionItem& item, const QString& name, kvector_t value)
{
    auto p_vector_item = item.getItem(name);
    p_vector_item->setItemValue(VectorItem::P_X, value.x());
    p_vector_item->setItemValue(VectorItem::P_Y, value.y());
    p_vector_item->setItemValue(VectorItem::P_Z, value.z());
}

int SessionItemUtils::ParentVisibleRow(const SessionItem& item)
{
    int result(-1);

    if (!item.parent() || !item.isVisible())
        return result;

    for(auto child : item.parent()->children()) {
        if (child->isVisible())
            ++result;

        if (&item == child)
            return result;
    }

    return result;
}

QVariant SessionItemUtils::TextColorRole(const SessionItem& item)
{
    return item.isEnabled() ? QVariant() : QColor(Qt::gray);
}

QVariant SessionItemUtils::ToolTipRole(const SessionItem& item, int ncol)
{
    QString result = item.toolTip();
    if (result.isEmpty()) {
        result = item.displayName();
        if (ncol == 1 && item.value().canConvert<QString>())
            result = item.value().toString();
    }

    return QVariant(result);
}


QVariant SessionItemUtils::DecorationRole(const SessionItem& item)
{
    if (item.value().canConvert<ExternalProperty>())
        return QIcon(item.value().value<ExternalProperty>().pixmap());

    return QVariant();
}

QVariant SessionItemUtils::CheckStateRole(const SessionItem& item)
{
    if (item.value().type() == QVariant::Bool)
        return item.value().toBool() ? Qt::Checked : Qt::Unchecked;
    return QVariant();
}

bool SessionItemUtils::IsValidGroup(const QString& group_type)
{
    return groupInfoCatalogue().containsGroup(group_type);
}

GroupInfo SessionItemUtils::GetGroupInfo(const QString& group_type)
{
    return groupInfoCatalogue().groupInfo(group_type);
}

int SessionItemUtils::VariantType(const QVariant& variant)
{
    int result = static_cast<int>(variant.type());
    if (result == QVariant::UserType)
        result = variant.userType();
    return result;
}

bool SessionItemUtils::CompatibleVariantTypes(const QVariant& oldValue, const QVariant& newValue)
{
    // if olfValue is undefined than it is compatible with any value, otherwise newValue
    // should have same variant type as oldValue

    if (oldValue.isValid())
        return SessionItemUtils::VariantType(oldValue) == SessionItemUtils::VariantType(newValue);
    else
        return true;
}

// For custom variants (based on ExternalProperty, ComboProperty) will always return false, i.e.
// we will rely here on our custom editors.
// This is done to not to register custom comparators in main.cpp.
bool SessionItemUtils::IsTheSame(const QVariant& var1, const QVariant& var2)
{
    // variants of different type are always reported as not the same
    if (VariantType(var1) != VariantType(var2))
        return false;

    // custom type variants are always reported as not the same
    if (var1.type() == QVariant::UserType)
        return false;

    // standard variants (based on double, int, etc) are compared by value they are holding
    return var1 == var2;
}
