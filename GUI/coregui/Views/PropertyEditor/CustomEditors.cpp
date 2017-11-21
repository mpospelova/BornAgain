// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/CustomEditors.h
//! @brief     Implements CustomEditors classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "CustomEditors.h"
#include "CustomEventFilters.h"
#include "MaterialProperty.h"
#include "MaterialSvc.h"
#include "GroupProperty.h"
#include "ComboProperty.h"
#include "ColorProperty.h"
#include <QBoxLayout>
#include <QLabel>
#include <QToolButton>
#include <QComboBox>
#include <QColorDialog>

//! Sets the data from the model to editor.

void CustomEditor::setData(const QVariant& data)
{
    m_data = data;
}

//! Saves the data from editor and inform external delegates.

void CustomEditor::setDataIntern(const QVariant& data)
{
    setData(data);
    dataChanged(m_data);
}

// --- MaterialPropertyEditor ---

MaterialPropertyEditor::MaterialPropertyEditor(QWidget* parent)
    : CustomEditor(parent)
    , m_textLabel(new QLabel)
    , m_pixmapLabel(new QLabel)
    , m_focusFilter(new LostFocusFilter(this))
{
    setMouseTracking(true);
    setAutoFillBackground(true);

    auto layout = new QHBoxLayout;
    layout->setMargin(2);
    layout->setSpacing(0);

    MaterialProperty defProperty; // to get label and pixmap of undefined material
    m_textLabel->setText(defProperty.getName());
    m_pixmapLabel->setPixmap(defProperty.getPixmap());

    auto button = new QToolButton;
    button->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred));
    button->setText(QLatin1String("..."));
    layout->addWidget(m_pixmapLabel, Qt::AlignLeft);
    layout->addWidget(m_textLabel, Qt::AlignLeft);
    layout->addStretch(1);
    layout->addWidget(button);
    setFocusPolicy(Qt::StrongFocus);
    setAttribute(Qt::WA_InputMethodEnabled);
    connect(button, &QToolButton::clicked, this, &MaterialPropertyEditor::buttonClicked);

    setLayout(layout);
}

void MaterialPropertyEditor::setData(const QVariant& data)
{
    Q_ASSERT(data.canConvert<MaterialProperty>());
    CustomEditor::setData(data);

    MaterialProperty materialProperty = m_data.value<MaterialProperty>();
    m_textLabel->setText(materialProperty.getName());
    m_pixmapLabel->setPixmap(materialProperty.getPixmap());
}

void MaterialPropertyEditor::buttonClicked()
{
    // temporarily installing filter to prevent loss of focus caused by too insistent dialog
    installEventFilter(m_focusFilter);
    MaterialProperty materialProperty = m_data.value<MaterialProperty>();
    MaterialProperty mat = MaterialSvc::selectMaterialProperty(materialProperty);
    removeEventFilter(m_focusFilter);

    if(mat.isDefined() )
        setDataIntern(mat.getVariant());
}

// --- ColorPropertyEditor ---

ColorPropertyEditor::ColorPropertyEditor(QWidget* parent)
    : CustomEditor(parent)
    , m_textLabel(new QLabel)
    , m_pixmapLabel(new QLabel)
    , m_focusFilter(new LostFocusFilter(this))
{
    setMouseTracking(true);
    setAutoFillBackground(true);

    auto layout = new QHBoxLayout;
    layout->setMargin(2);
    layout->setSpacing(0);

    ColorProperty defProperty; // to get label and pixmap of undefined material
    m_textLabel->setText(defProperty.getText());
    m_pixmapLabel->setPixmap(defProperty.getPixmap());

    auto button = new QToolButton;
    button->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred));
    button->setText(QLatin1String("..."));
    layout->addWidget(m_pixmapLabel, Qt::AlignLeft);
    layout->addWidget(m_textLabel, Qt::AlignLeft);
    layout->addStretch(1);
    layout->addWidget(button);
    setFocusPolicy(Qt::StrongFocus);
    setAttribute(Qt::WA_InputMethodEnabled);
    connect(button, &QToolButton::clicked, this, &ColorPropertyEditor::buttonClicked);

    setLayout(layout);
}

void ColorPropertyEditor::setData(const QVariant& data)
{
    Q_ASSERT(data.canConvert<ColorProperty>());
    CustomEditor::setData(data);

    ColorProperty colorProperty = m_data.value<ColorProperty>();
    m_textLabel->setText(colorProperty.getText());
    m_pixmapLabel->setPixmap(colorProperty.getPixmap());
}

void ColorPropertyEditor::buttonClicked()
{
    ColorProperty colorProperty = m_data.value<ColorProperty>();

    bool ok = false;
    QRgb oldRgba = colorProperty.getColor().rgba();
    QRgb newRgba = QColorDialog::getRgba(oldRgba, &ok, this);
    if (ok && newRgba != oldRgba) {
        colorProperty.setColor(QColor::fromRgba(newRgba));
        m_pixmapLabel->setPixmap(colorProperty.getPixmap());
        setDataIntern(colorProperty.getVariant());
    }
}

// --- CustomComboEditor ---

CustomComboEditor::CustomComboEditor(QWidget* parent)
    : CustomEditor(parent)
    , m_box(new QComboBox)
{
    setAutoFillBackground(true);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_box);

    setLayout(layout);
    setConnected(true);
}

QSize CustomComboEditor::sizeHint() const
{
    return m_box->sizeHint();
}

QSize CustomComboEditor::minimumSizeHint() const
{
    return m_box->minimumSizeHint();
}

void CustomComboEditor::setData(const QVariant& data)
{
    CustomEditor::setData(data);

    setConnected(false);

    m_box->clear();
    m_box->insertItems(0, internLabels());
    m_box->setCurrentIndex(internIndex());

    setConnected(true);
}

void CustomComboEditor::onIndexChanged(int)
{
}

//! Returns list of labels for QComboBox

QStringList CustomComboEditor::internLabels()
{
    return QStringList();
}

//! Returns index for QComboBox.

int CustomComboEditor::internIndex()
{
    return -1;
}

void CustomComboEditor::setConnected(bool isConnected)
{
    if (isConnected)
        connect(m_box, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
                this, &CustomComboEditor::onIndexChanged, Qt::UniqueConnection);
    else
        disconnect(m_box, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
                this, &CustomComboEditor::onIndexChanged);
}

// --- GroupPropertyEditor ---

GroupPropertyEditor::GroupPropertyEditor(QWidget* parent)
    : CustomComboEditor(parent)
{
}

void GroupPropertyEditor::onIndexChanged(int index)
{
    GroupProperty_t groupProperty = m_data.value<GroupProperty_t>();

    if (groupProperty->currentIndex() != index) {
        groupProperty->setCurrentIndex(index);
        setDataIntern(QVariant::fromValue<GroupProperty_t>(groupProperty));
    }
}

QStringList GroupPropertyEditor::internLabels()
{
    Q_ASSERT(m_data.canConvert<GroupProperty_t>());
    GroupProperty_t groupProperty = m_data.value<GroupProperty_t>();
    return groupProperty->itemLabels();
}

int GroupPropertyEditor::internIndex()
{
    Q_ASSERT(m_data.canConvert<GroupProperty_t>());
    GroupProperty_t groupProperty = m_data.value<GroupProperty_t>();
    return groupProperty->currentIndex();
}

// --- ComboPropertyEditor ---

ComboPropertyEditor::ComboPropertyEditor(QWidget* parent)
    : CustomComboEditor(parent)
{
}

void ComboPropertyEditor::onIndexChanged(int index)
{
    ComboProperty comboProperty = m_data.value<ComboProperty>();

    if (comboProperty.currentIndex() != index) {
        comboProperty.setCurrentIndex(index);
        setDataIntern(QVariant::fromValue<ComboProperty>(comboProperty));
    }
}

QStringList ComboPropertyEditor::internLabels()
{
    Q_ASSERT(m_data.canConvert<ComboProperty>());
    ComboProperty comboProperty = m_data.value<ComboProperty>();
    return comboProperty.getValues();
}

int ComboPropertyEditor::internIndex()
{
    Q_ASSERT(m_data.canConvert<ComboProperty>());
    ComboProperty comboProperty = m_data.value<ComboProperty>();
    return comboProperty.currentIndex();
}