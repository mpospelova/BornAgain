// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobViewDocks.cpp
//! @brief     Implements class JobViewDocks
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "JobViewDocks.h"
#include "FitActivityPanel.h"
#include "JobMessagePanel.h"
#include "JobModel.h"
#include "JobOutputDataWidget.h"
#include "JobRealTimeWidget.h"
#include "JobSelectorWidget.h"
#include "JobView.h"
#include "JobViewActivities.h"
#include <QAbstractItemView>
#include <QAction>
#include <QDockWidget>
#include <QTimer>

namespace
{
const JobViewFlags::Activity default_activity = JobViewFlags::JOB_VIEW_ACTIVITY;
}

JobViewDocks::JobViewDocks(JobView* parent)
    : QObject(parent)
    , m_jobSelector(nullptr)
    , m_jobOutputDataWidget(nullptr)
    , m_jobRealTimeWidget(nullptr)
    , m_fitActivityPanel(nullptr)
    , m_jobMessagePanel(nullptr)
    , m_jobView(parent)
{
}

void JobViewDocks::initViews(class JobModel* jobModel)
{
    initJobWidgets(jobModel);
    initDocks();
}

JobRealTimeWidget* JobViewDocks::jobRealTimeWidget()
{
    return m_jobRealTimeWidget;
}

FitActivityPanel* JobViewDocks::fitActivityPanel()
{
    return m_fitActivityPanel;
}

JobSelectorWidget* JobViewDocks::jobSelector()
{
    return m_jobSelector;
}

JobOutputDataWidget* JobViewDocks::jobOutputDataWidget()
{
    return m_jobOutputDataWidget;
}

JobMessagePanel* JobViewDocks::jobMessagePanel()
{
    return m_jobMessagePanel;
}

//! Sets docks visibility so they match the activity flag.

void JobViewDocks::setActivity(int activity)
{
    QVector<JobViewFlags::Dock> docksToShow
        = JobViewActivities::activeDocks(JobViewFlags::Activity(activity));

    for (int i = 0; i < JobViewFlags::NUMBER_OF_DOCKS; i++) {
        JobViewFlags::Dock id = static_cast<JobViewFlags::Dock>(i);
        if (docksToShow.contains(id))
            m_dockWidgets[i]->show();
        else
            m_dockWidgets[i]->hide();
    }
}

void JobViewDocks::setItem(JobItem* jobItem)
{
    jobOutputDataWidget()->setItem(jobItem);
    jobRealTimeWidget()->setItem(jobItem);
    fitActivityPanel()->setItem(jobItem);
}

//! Sets the state of JobView to the default.

void JobViewDocks::onResetLayout()
{
    m_jobView->setTrackingEnabled(false);
    QList<QDockWidget*> dockWidgetList = m_jobView->dockWidgets();
    for(QDockWidget* dockWidget : dockWidgetList) {
        dockWidget->setFloating(false);
        m_jobView->removeDockWidget(dockWidget);
    }

    m_jobView->addDockWidget(Qt::LeftDockWidgetArea, dock(JobViewFlags::JOB_LIST_DOCK));
    m_jobView->addDockWidget(Qt::RightDockWidgetArea, dock(JobViewFlags::REAL_TIME_DOCK));
    m_jobView->addDockWidget(Qt::RightDockWidgetArea, dock(JobViewFlags::FIT_PANEL_DOCK));
    m_jobView->addDockWidget(Qt::BottomDockWidgetArea, dock(JobViewFlags::JOB_MESSAGE_DOCK));

    for(QDockWidget* dockWidget : dockWidgetList)
        dockWidget->show();

    m_jobView->setTrackingEnabled(true);

    setActivity(static_cast<int>(default_activity));
}

//! Shows/hides JobSelectorWidget.

void JobViewDocks::onToggleJobSelector()
{
    QDockWidget* selectorDock = dock(JobViewFlags::JOB_LIST_DOCK);
    selectorDock->setHidden(!selectorDock->isHidden());
}

//! A hack to request update of QDockWidget size if its child (e.g. InfoWidget) wants it.
//! The problem bypassed here is that there is no direct method to QMainWindow to recalculate
//! position of splitters surrounding given QDockWidget. So our child QWidget requests here
//! the change of Min/Max size of QDockWidget, this will trigger recalculation of QDockWidget
//! layout and will force QDockWidget to respect sizeHints provided by ChildWidget. Later (in one
//! single timer shot) we return min/max sizes of QDockWidget back to re-enable splitters
//! functionality.

void JobViewDocks::setDockHeightForWidget(int height)
{
    QWidget* widget = qobject_cast<QWidget*>(sender());
    Q_ASSERT(widget);
    QDockWidget* dock = findDock(widget);
    Q_ASSERT(dock);

    m_dock_info.m_dock = dock;
    m_dock_info.m_min_size = dock->minimumSize();
    m_dock_info.m_max_size = dock->maximumSize();

    if (height > 0) {
        if (dock->height() < height)
            dock->setMinimumHeight(height);
        else
            dock->setMaximumHeight(height);
    }

    QTimer::singleShot(1, this, &JobViewDocks::dockToMinMaxSizes);
}

void JobViewDocks::onWidgetCloseRequest()
{
    QWidget* widget = qobject_cast<QWidget*>(sender());
    Q_ASSERT(widget);
    QDockWidget* dock = findDock(widget);
    Q_ASSERT(dock);

    dock->toggleViewAction()->trigger();
}

void JobViewDocks::dockToMinMaxSizes()
{
    Q_ASSERT(m_dock_info.m_dock);
    m_dock_info.m_dock->setMinimumSize(m_dock_info.m_min_size);
    m_dock_info.m_dock->setMaximumSize(m_dock_info.m_max_size);
    m_dock_info.m_dock = nullptr;
}

//! Returns job widget with given Id.

QWidget* JobViewDocks::jobWidget(JobViewFlags::Dock dockId)
{
    return m_jobWidgets.at(static_cast<int>(dockId));
}

//! Returns dock with given id.

QDockWidget* JobViewDocks::dock(JobViewFlags::Dock dockId)
{
    return m_dockWidgets.at(static_cast<int>(dockId));
}

QWidget* JobViewDocks::centralWidget() {
    return m_jobOutputDataWidget;
}

//! Inits all main JobWidgets.

void JobViewDocks::initJobWidgets(JobModel* jobModel)
{
    m_jobWidgets.resize(JobViewFlags::NUMBER_OF_DOCKS);
    m_dockWidgets.resize(JobViewFlags::NUMBER_OF_DOCKS);

    m_jobOutputDataWidget = new JobOutputDataWidget(jobModel, m_jobView);

    m_jobSelector = new JobSelectorWidget(jobModel, m_jobView);
    m_jobWidgets[JobViewFlags::JOB_LIST_DOCK] = m_jobSelector;

    m_jobRealTimeWidget = new JobRealTimeWidget(jobModel, m_jobView);
    m_jobWidgets[JobViewFlags::REAL_TIME_DOCK] = m_jobRealTimeWidget;

    m_fitActivityPanel = new FitActivityPanel(jobModel, m_jobView);
    m_jobWidgets[JobViewFlags::FIT_PANEL_DOCK] = m_fitActivityPanel;

    m_jobMessagePanel = new JobMessagePanel(m_jobView);
    connect(m_jobMessagePanel, &JobMessagePanel::widgetHeightRequest,
            this, &JobViewDocks::setDockHeightForWidget);
    connect(m_jobMessagePanel, &JobMessagePanel::widgetCloseRequest,
            this, &JobViewDocks::onWidgetCloseRequest);

    m_jobWidgets[JobViewFlags::JOB_MESSAGE_DOCK] = m_jobMessagePanel;

    m_fitActivityPanel->setRealTimeWidget(m_jobRealTimeWidget);
    m_fitActivityPanel->setJobMessagePanel(m_jobMessagePanel);

    m_jobView->setCentralWidget(centralWidget());
}

//! Init docks for JobView.

void JobViewDocks::initDocks()
{
    m_jobView->setDocumentMode(true);
    m_jobView->setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::South);
    m_jobView->setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    m_jobView->setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

    for (int i = 0; i < JobViewFlags::NUMBER_OF_DOCKS; i++) {
        QWidget* subWindow = jobWidget(JobViewFlags::Dock(i));
        m_dockWidgets[i] = m_jobView->addDockForWidget(subWindow);
        // m_dockWidgets[i]->setMinimumSize(QSize());

        // Since we have 1-pixel splitters, we generally want to remove
        // frames around item views. So we apply this hack for now.
        QList<QAbstractItemView*> frames = subWindow->findChildren<QAbstractItemView*>();
        for (int i = 0; i < frames.count(); ++i)
            frames[i]->setFrameStyle(QFrame::NoFrame);
    }

    onResetLayout();
}

QDockWidget* JobViewDocks::findDock(QWidget* widget)
{
    int index = m_jobWidgets.indexOf(widget);
    return index>=0 ? m_dockWidgets[index] : nullptr;
}
