// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/PropertyEditorFactory.cpp
//! @brief     Implements PropertyEditorFactory namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "PropertyEditorFactory.h"
#include "SessionItem.h"
#include "RealLimits.h"
#include "ExternalProperty.h"
#include "GroupItemController.h"
#include "CustomEditors.h"
#include "ComboProperty.h"
#include "CustomEventFilters.h"
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <limits>
#include <cmath>

namespace {
QWidget* createCustomDoubleEditor(const SessionItem& item);
QWidget* createCustomIntEditor(const SessionItem& item);
QWidget* createCustomStringEditor(const SessionItem& item);

//! Single step for QDoubleSpinBox.

double singleStep(const SessionItem& item) {
    // For item with decimals=3 (i.e. 0.001) single step will be 0.1
    return 1. / std::pow(10., item.decimals() - 1);
}

bool isDoubleProperty(const QVariant& variant)
{
    return variant.type() == QVariant::Double;
}

bool isIntProperty(const QVariant& variant)
{
    return variant.type() == QVariant::Int;
}

bool isExternalProperty(const QVariant& variant)
{
    return variant.canConvert<ExternalProperty>();
}

bool isComboProperty(const QVariant& variant)
{
    return variant.canConvert<ComboProperty>();
}

bool isStringProperty(const QVariant& variant)
{
    return variant.type() == QVariant::String;
}

bool isBoolProperty(const QVariant& variant)
{
    return variant.type() == QVariant::Bool;
}

}

bool PropertyEditorFactory::IsCustomVariant(const QVariant& variant)
{
    if (isExternalProperty(variant))
        return true;
    if (isComboProperty(variant))
        return true;
    if (isBoolProperty(variant))
        return true;

    return false;
}

QString PropertyEditorFactory::ToString(const QVariant& variant)
{
    if (isExternalProperty(variant))
        return variant.value<ExternalProperty>().text();
    if (isComboProperty(variant))
        return variant.value<ComboProperty>().getValue();
    if (isBoolProperty(variant))
        return variant.toBool() ? "True" : "False";

    return QString();
}


QWidget* PropertyEditorFactory::CreateEditor(const SessionItem& item, QWidget* parent)
{
    QWidget* result(nullptr);

    if (isDoubleProperty(item.value())) {
        if (item.editorType() == Constants::ScientificEditorType) {
            auto editor = new ScientificDoublePropertyEditor;
            auto limits = item.limits();
            editor->setLimits(limits);
            editor->setData(item.value());
            result = editor;
        } else {
            result = createCustomDoubleEditor(item);
        }
    }
    else if(isIntProperty(item.value())) {
        result = createCustomIntEditor(item);
    }
    else if(isBoolProperty(item.value())) {
        auto editor = new BoolEditor;
        editor->setData(item.value());
        result = editor;
    }
    else if(isStringProperty(item.value())) {
        result = createCustomStringEditor(item);
    }
    else if(isExternalProperty(item.value())) {
        auto editor = new ExternalPropertyEditor;
        editor->setData(item.value());
        if (item.editorType() != Constants::DefaultEditorType)
            editor->setExternalDialogType(item.editorType());
        result = editor;
    }
    else if(isComboProperty(item.value())) {
        auto editor = new ComboPropertyEditor;
        editor->setData(item.value());
        result = editor;
    }
    if (parent && result)
        result->setParent(parent);

    return result;
}



namespace {

QWidget* createCustomDoubleEditor(const SessionItem& item)
{
    auto result = new QDoubleSpinBox;
    result->setKeyboardTracking(true);

    result->setFocusPolicy(Qt::StrongFocus);
//    result->installEventFilter(new WheelEventEater(result));

    result->setMaximum(std::numeric_limits<double>::max());
    result->setMinimum(std::numeric_limits<double>::lowest());

    result->setDecimals(item.decimals());
    result->setSingleStep(singleStep(item));

    RealLimits limits = item.limits();
    if (limits.hasLowerLimit())
        result->setMinimum(limits.getLowerLimit());
    if (limits.hasUpperLimit())
        result->setMaximum(limits.getUpperLimit());

    result->setValue(item.value().toDouble());
    return result;
}

QWidget* createCustomIntEditor(const SessionItem& item)
{
    auto result = new QSpinBox;
    result->setFocusPolicy(Qt::StrongFocus);
//    result->installEventFilter(new WheelEventEater(result));

    result->setMaximum(std::numeric_limits<int>::max());
    result->setKeyboardTracking(true);

    RealLimits limits = item.limits();
    if (limits.hasLowerLimit())
        result->setMinimum(static_cast<int>(limits.getLowerLimit()));
    if (limits.hasUpperLimit())
        result->setMaximum(static_cast<int>(limits.getUpperLimit()));

    result->setValue(item.value().toInt());

    return result;
}

QWidget* createCustomStringEditor(const SessionItem& item)
{
    QWidget* result(nullptr);

    if (item.isEditable()) {
        auto editor = new QLineEdit;
        editor->setText(item.value().toString());
        result = editor;
    } else {
        auto editor = new QLabel;
        editor->setText(item.value().toString());
        result = editor;
    }

    return result;
}

}

