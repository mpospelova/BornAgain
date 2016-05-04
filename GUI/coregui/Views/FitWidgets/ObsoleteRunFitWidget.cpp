// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/ObsoleteRunFitWidget.cpp
//! @brief     Implements class ObsoleteRunFitWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "RunFitManager.h"
#include "SampleBuilderFactory.h"
#include "SimulationRegistry.h"
#include "FitSuite.h"
#include "GUIFitObserver.h"
#include "ObsoleteFitProgressWidget.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "ObsoleteFitModel.h"
#include "DomainSimulationBuilder.h"
#include "ObsoleteFitParameterItems.h"
#include "SessionItem.h"
#include "MultiLayerItem.h"
#include "InstrumentItem.h"
#include "SessionModel.h"
#include "IntensityDataIOFactory.h"

#include "ObsoleteRunFitWidget.h"

#include <QWidget>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileInfo>
#include <QDebug>

ObsoleteRunFitWidget::ObsoleteRunFitWidget(ObsoleteFitModel *fitModel, QWidget *parent)
    : QWidget(parent)
    , m_start_button(new QPushButton())
    , m_stop_button(new QPushButton())
    , m_interval_label(new QLabel())
    , m_interval_slider(new QSlider())
    , m_runfitmanager(new RunFitManager(this))
    , m_fitprogress(new ObsoleteFitProgressWidget(this))
    , m_fitModel(fitModel)
{
    // setup ui
    m_start_button->setText(tr("Start"));
    m_stop_button->setText(tr("Stop"));
    m_stop_button->setEnabled(false);
    m_interval_slider->setOrientation(Qt::Horizontal);
    m_interval_slider->setRange(1,20);
    m_interval_slider->setMaximumWidth(150);
    m_interval_slider->setMinimumWidth(150);
    m_interval_slider->setFocusPolicy(Qt::NoFocus);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addWidget(m_start_button);
    topLayout->addWidget(m_stop_button);
    topLayout->addStretch();
    topLayout->addWidget(m_interval_label);
    topLayout->addWidget(m_interval_slider);
    QWidget *topWidget = new QWidget();
    topWidget->setLayout(topLayout);
    mainLayout->addWidget(topWidget);
    mainLayout->addWidget(m_fitprogress);

    // connect everything
    connect(m_start_button, SIGNAL(clicked()), this, SLOT(onStartClicked()));
    connect(m_stop_button, SIGNAL(clicked()), this, SLOT(onStopClicked()));
    connect(m_runfitmanager, SIGNAL(startedFitting()), this, SLOT(onFittingStarted()));
    connect(m_runfitmanager, SIGNAL(finishedFitting()), this, SLOT(onFittingFinished()));
    connect(m_runfitmanager, SIGNAL(error(QString)), m_fitprogress, SLOT(updateLog(QString)));

    connect(m_interval_slider, SIGNAL(valueChanged(int)), this, SLOT(onIntervalChanged(int)));
    m_fitprogress->connectSlider(m_interval_slider);

    setLayout(mainLayout);
    m_interval_slider->setValue(10);
}

void ObsoleteRunFitWidget::onIntervalChanged(int value)
{
    m_interval_label->setText(QString("Update every %1th iteration").arg(value));
}

void ObsoleteRunFitWidget::onStartClicked()
{
    // used for test purposes
    std::shared_ptr<FitSuite> suite = init_test_fitsuite();
    m_fitprogress->setObserverToSuite(suite.get());

    m_runfitmanager->setFitSuite(suite);
    m_runfitmanager->runFitting();
}

void ObsoleteRunFitWidget::onStopClicked()
{
    m_runfitmanager->interruptFitting();
}

void ObsoleteRunFitWidget::onFittingStarted()
{
    m_start_button->setEnabled(false);
    m_stop_button->setEnabled(true);
}

void ObsoleteRunFitWidget::onFittingFinished()
{
    m_stop_button->setEnabled(false);
    m_start_button->setEnabled(true);
}



// test only
std::shared_ptr<FitSuite> ObsoleteRunFitWidget::init_test_fitsuite()
{
    SessionItem *multilayer = m_fitModel->getSelectedMultiLayerItem();
    SessionItem *instrument = m_fitModel->getSelectedInstrumentItem();

    DomainSimulationBuilder builder;
     std::shared_ptr<FitSuite> m_fitsuite = std::shared_ptr<FitSuite>(new FitSuite());

    try {

    const std::unique_ptr<GISASSimulation> simulation(builder.getSimulation(dynamic_cast<MultiLayerItem*>
                                                                          (multilayer),
                                                                          dynamic_cast<InstrumentItem*>
                                                                          (instrument)));



        QString path = m_fitModel->getInputDataPath();
    QFileInfo checkFile(path);

    OutputData<double> *data = 0;

    if (checkFile.exists() && checkFile.isFile()) {
        data = IntensityDataIOFactory::readOutputData(path.toStdString());
        qDebug() << data->totalSum();
        //Q_ASSERT(0);
    } else {

        simulation->runSimulation();
        data = simulation->getOutputData()->clone();
    }





    m_fitsuite->addSimulationAndRealData(*simulation.get(), *data);


    SessionItem *container = m_fitModel->getFitParameterContainer();



    QModelIndex c_index = m_fitModel->indexOfItem(container);
    for (int i = 0; i < m_fitModel->rowCount(c_index); i++) {
        QModelIndex child = m_fitModel->index(i,0,c_index);
        SessionItem *parameter = m_fitModel->itemForIndex(child);
        for (int j = 0; j < m_fitModel->rowCount(child); j++) {
            SessionItem *link = m_fitModel->itemForIndex(m_fitModel->index(j,0,child));
            QString value = link->getItemValue(ObsoleteFitParameterLinkItem::P_LINK).toString();
            value = value.replace("Position Offset/X", "PositionX");
            value = value.replace("Position Offset/Y", "PositionY");
            value = value.replace("Position Offset/Z", "PositionZ");
            value = value.replace("Rotation/ZRotation", "ZRotation");
            value = value.replace("Wavelength/DistributionNone/Value", "Wavelength");
            value = value.replace("Hurst parameter", "Hurst");
            value = value.replace("Lateral corr length", "CorrelationLength");
            value = value.replace(" ", "");
            std::string translated = "*" + value.toStdString();
            std::cout << translated;
            std::cout.flush();
            double min = parameter->getItemValue(ObsoleteFitParameterItem::P_MIN).toDouble();
            double max = parameter->getItemValue(ObsoleteFitParameterItem::P_MAX).toDouble();
            double init = parameter->getItemValue(ObsoleteFitParameterItem::P_INIT).toDouble();
            AttLimits limits;
            if (min==max && min < init) {
                limits = AttLimits::lowerLimited(min);
            } else if (min==max && max > init) {
                limits = AttLimits::upperLimited(max);
            } else if (min < init && max > init) {
                limits = AttLimits::limited(min, max);
            } else {
                limits = AttLimits::limitless();
            }
            m_fitsuite->addFitParameter(translated, init, limits);
        }
    }

    m_fitsuite->setMinimizer("Minuit2", m_fitModel->getMinimizerAlgorithm().toStdString());

} catch(const std::exception& ex) {
        QString message = QString::fromLatin1(ex.what());
            m_fitprogress->updateLog(message);
    }
    return m_fitsuite;
}