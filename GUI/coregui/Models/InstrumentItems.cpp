// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/InstrumentItems.cpp
//! @brief     Implements InstrumentItems classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "InstrumentItems.h"
#include "AxesItems.h"
#include "BackgroundItems.h"
#include "BeamItems.h"
#include "DetectorItems.h"
#include "GroupItem.h"
#include "GUIHelpers.h"
#include "IDetector2D.h"
#include "Instrument.h"
#include "MaskItems.h"
#include "SessionModel.h"

namespace {
const QString background_group_label = "Type";
void addAxisGroupProperty(SessionItem* parent, const QString& tag);
}

const QString InstrumentItem::P_IDENTIFIER = "Identifier";
const QString InstrumentItem::P_BEAM = "Beam";
const QString InstrumentItem::P_BACKGROUND = "Background";

QStringList InstrumentItem::translateList(const QStringList& list) const
{
    QStringList result;
    // Add constant background directly to simulation
    // TODO: this way of directly adding background is too sensitive
    //       to the background name
    if (list.back().endsWith(P_BACKGROUND) && list.size()==2) {
        result << list[0] << list[1];
    } else {
        // TODO Consider usage of ModelTypeTranslator in IntrusmentItem's constructor
        // after the refactoring of SessionItem::translateList
        result = SessionItem::translateList(list);
        if (result.back() == Constants::GISASInstrumentType) {
            result.removeLast();
            result << QStringLiteral("Instrument");
        }
    }
    return result;
}

BeamItem* InstrumentItem::beamItem() const
{
    return &item<BeamItem>(P_BEAM);
}

BackgroundItem* InstrumentItem::backgroundItem() const
{
    return &groupItem<BackgroundItem>(P_BACKGROUND);
}

GroupItem* InstrumentItem::backgroundGroup()
{
    return &item<GroupItem>(P_BACKGROUND);
}

std::unique_ptr<Instrument> InstrumentItem::createInstrument() const
{
    std::unique_ptr<Instrument> result(new Instrument);

    auto beam = beamItem()->createBeam();
    result->setBeam(*beam);

    return result;
}

InstrumentItem::InstrumentItem(const QString& modelType)
    : SessionItem(modelType)
{
    setItemName(modelType);
    addProperty(P_IDENTIFIER, GUIHelpers::createUuid())->setVisible(false);

    auto item = addGroupProperty(P_BACKGROUND, Constants::BackgroundGroup);
    item->setDisplayName(background_group_label);
    item->setToolTip("Background type");
}

void InstrumentItem::initBeamGroup(const QString& beam_model)
{
    addGroupProperty(P_BEAM, beam_model);
}

SpecularInstrumentItem::SpecularInstrumentItem()
    : InstrumentItem(Constants::SpecularInstrumentType)
{
    initBeamGroup(Constants::SpecularBeamType);
}

SpecularBeamItem* SpecularInstrumentItem::beamItem() const
{
    return &item<SpecularBeamItem>(P_BEAM);
}

SpecularInstrumentItem::~SpecularInstrumentItem() = default;

std::unique_ptr<Instrument> SpecularInstrumentItem::createInstrument() const
{
    return InstrumentItem::createInstrument();
}

std::vector<int> SpecularInstrumentItem::shape() const
{
    const auto& axis_item = beamItem()->getInclinationAngleAxis();
    return {axis_item.getItemValue(BasicAxisItem::P_NBINS).toInt()};
}

void SpecularInstrumentItem::setShape(const std::vector<int>& data_shape)
{
    if (shape().size() != data_shape.size())
        throw GUIHelpers::Error("Error in SpecularInstrumentItem::setShape: The type of "
                                "instrument is incompatible with passed data shape.");
    auto& axis_item = beamItem()->getInclinationAngleAxis();
    axis_item.setItemValue(BasicAxisItem::P_NBINS, data_shape[0]);
}

const QString Instrument2DItem::P_DETECTOR = "Detector";

Instrument2DItem::Instrument2DItem(const QString& modelType)
    : InstrumentItem(modelType)
{
    initBeamGroup(Constants::GISASBeamType);
    addGroupProperty(P_DETECTOR, Constants::DetectorGroup);

    setDefaultTag(P_DETECTOR);
}

Instrument2DItem::~Instrument2DItem() = default;

DetectorItem* Instrument2DItem::detectorItem() const
{
    return &groupItem<DetectorItem>(P_DETECTOR);
}

GroupItem* Instrument2DItem::detectorGroup()
{
    return &item<GroupItem>(P_DETECTOR);
}

void Instrument2DItem::setDetectorGroup(const QString& modelType)
{
    setGroupProperty(P_DETECTOR, modelType);
}

void Instrument2DItem::clearMasks()
{
    detectorItem()->clearMasks();
}

void Instrument2DItem::importMasks(MaskContainerItem* maskContainer)
{
    detectorItem()->importMasks(maskContainer);
}

std::unique_ptr<Instrument> Instrument2DItem::createInstrument() const
{
    auto result = InstrumentItem::createInstrument();

    auto detector = detectorItem()->createDetector();
    result->setDetector(*detector);

    return result;
}

GISASInstrumentItem::GISASInstrumentItem()
    : Instrument2DItem(Constants::GISASInstrumentType)
{
}

std::vector<int> GISASInstrumentItem::shape() const
{
    auto detector_item = detectorItem();
    return {detector_item->xSize(), detector_item->ySize()};
}

void GISASInstrumentItem::setShape(const std::vector<int>& data_shape)
{
    if (shape().size() != data_shape.size())
        throw GUIHelpers::Error("Error in GISASInstrumentItem::setShape: The type of "
                                "instrument is incompatible with passed data shape.");
    detectorItem()->setXSize(data_shape[0]);
    detectorItem()->setYSize(data_shape[1]);
}

const QString OffSpecInstrumentItem::P_ALPHA_AXIS = "Alpha axis";

OffSpecInstrumentItem::OffSpecInstrumentItem()
    : Instrument2DItem(Constants::OffSpecInstrumentType)
{
    addAxisGroupProperty(this, P_ALPHA_AXIS);
}

std::vector<int> OffSpecInstrumentItem::shape() const
{
    const int x_size = getItem(P_ALPHA_AXIS)->getItemValue(BasicAxisItem::P_NBINS).toInt();
    auto detector_item = detectorItem();
    return {x_size, detector_item->ySize()};
}

void OffSpecInstrumentItem::setShape(const std::vector<int>& data_shape)
{
    if (shape().size() != data_shape.size())
        throw GUIHelpers::Error("Error in OffSpecInstrumentItem::setShape: The type of "
                                "instrument is incompatible with passed data shape.");
    getItem(OffSpecInstrumentItem::P_ALPHA_AXIS)
        ->setItemValue(BasicAxisItem::P_NBINS, data_shape[0]);
    detectorItem()->setYSize(data_shape[1]);
}

namespace
{
void addAxisGroupProperty(SessionItem* parent, const QString& tag)
{
    auto item = parent->addGroupProperty(tag, Constants::BasicAxisType);
    item->setToolTip("Incoming alpha range [deg]");
    item->getItem(BasicAxisItem::P_TITLE)->setVisible(false);
    item->getItem(BasicAxisItem::P_NBINS)->setToolTip("Number of points in scan");
    item->getItem(BasicAxisItem::P_MIN)->setToolTip("Starting value [deg]");
    item->getItem(BasicAxisItem::P_MAX)->setToolTip("Ending value [deg]");

    item->setItemValue(BasicAxisItem::P_TITLE, "alpha_i");
    item->setItemValue(BasicAxisItem::P_MIN, 0.0);
    item->setItemValue(BasicAxisItem::P_MAX, 10.0);
}
} // namespace

