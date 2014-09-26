#include "JobRealTimeWidget.h"
#include "JobQueueModel.h"
#include "ModelTuningWidget.h"
#include "styledtoolbar.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QAction>
#include <QLabel>
#include <QDebug>
#include "GUIHelpers.h"


JobRealTimeWidget::JobRealTimeWidget(JobQueueModel *jobQueueModel, QWidget *parent)
    : QWidget(parent)
    , m_jobQueueModel(0)
    , m_stack(new QStackedWidget(this))
    , m_toolBar(new StyledToolBar)
{
    setJobQueueModel(jobQueueModel);

    setMinimumSize(100, 400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    setWindowTitle(QLatin1String("Job Real Time"));
    setObjectName(QLatin1String("Job Real Time"));

    m_stack->setMinimumSize(100, 400);
    m_stack->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(m_toolBar);
    mainLayout->addWidget(m_stack);

    setLayout(mainLayout);
}


void JobRealTimeWidget::setJobQueueModel(JobQueueModel *jobQueueModel)
{
    Q_ASSERT(jobQueueModel);
    if(jobQueueModel != m_jobQueueModel) {
        m_jobQueueModel = jobQueueModel;

        connect(m_jobQueueModel,
            SIGNAL( selectionChanged(JobItem *) ),
            this,
            SLOT( itemClicked(JobItem *) )
            );

        connect(m_jobQueueModel->getJobQueueData(), SIGNAL(jobIsFinished(QString))
                , this, SLOT(onJobItemFinished(QString)));

        connect(m_jobQueueModel, SIGNAL(aboutToDeleteJobItem(JobItem*))
                , this, SLOT(onJobItemDelete(JobItem*)));
    }
}


void JobRealTimeWidget::itemClicked(JobItem * item)
{
    qDebug() << "JobOutputDataWidget::itemClicked()";



    m_currentJobItem = item;

    ModelTuningWidget *widget = m_jobItemToTuningWidget[item];
    if( !widget && (item->getStatus() == JobItem::Completed || item->getStatus() == JobItem::Canceled)) {

        qDebug() << "JobOutputDataWidget::itemClicked() -> creating";
        widget = new ModelTuningWidget(m_jobQueueModel->getJobQueueData());
        widget->setCurrentItem(item);
        m_stack->addWidget(widget);
        m_jobItemToTuningWidget[item] = widget;

    }
    else
    {
        if( m_stack->currentWidget())
        {
            m_stack->currentWidget()->hide();
        }
    }


    if(widget)
    {
        qDebug() << "JobOutputDataWidget::itemClicked() -> setCurrentWidget";

        if(widget->isHidden())
        {
            widget->show();
        }

        m_stack->setCurrentWidget(widget);
    }
}


void JobRealTimeWidget::onJobItemFinished(const QString &identifier)
{
    qDebug() << "JobOutputDataWidget::onJobItemFinished()";
    JobItem *jobItem = m_jobQueueModel->getJobQueueData()->getJobItem(identifier);

    if(jobItem == m_currentJobItem)
    {
        if((jobItem->getStatus() == JobItem::Completed || jobItem->getStatus() == JobItem::Canceled) && jobItem->getOutputDataItem())
        {
            qDebug() << "JobOutputDataWidget::dataChanged() JobItem::Completed";
            itemClicked(jobItem);
        }
    }
}


void JobRealTimeWidget::onJobItemDelete(JobItem *item)
{
    qDebug() << "JobOutputDataWidget::onJobItemDelete()";
    ModelTuningWidget *widget = m_jobItemToTuningWidget[item];
    if( !widget ) {
        // this is the case when user removes failed job which doesn't have propper widget
        return;
    }

    QMap<JobItem *, ModelTuningWidget *>::iterator it = m_jobItemToTuningWidget.begin();
    while(it!=m_jobItemToTuningWidget.end()) {
        if(it.value() == widget) {
            it = m_jobItemToTuningWidget.erase(it);
        } else {
            ++it;
        }
    }

    m_stack->removeWidget(widget);
    delete widget;
}
