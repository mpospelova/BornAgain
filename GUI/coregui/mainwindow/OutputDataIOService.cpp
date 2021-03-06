// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/OutputDataIOService.h
//! @brief     Implements class OutputDataIOService
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "OutputDataIOService.h"
#include "ApplicationModels.h"
#include "DataItem.h"
#include "JobItemUtils.h"
#include "ProjectUtils.h"
#include "MessageService.h"

OutputDataIOService::OutputDataIOService(QObject* parent)
    : QObject(parent), m_applicationModels(nullptr)
{
    setObjectName("OutputDataIOService");
}

OutputDataIOService::OutputDataIOService(ApplicationModels* models, QObject* parent)
    : QObject(parent), m_applicationModels(nullptr)
{
    setObjectName("OutputDataIOService");
    setApplicationModels(models);
}

void OutputDataIOService::setApplicationModels(ApplicationModels* models)
{
    m_applicationModels = models;
}

void OutputDataIOService::save(const QString& projectDir)
{
    if (!m_history.hasHistory(projectDir))
        m_history.setHistory(projectDir, OutputDataDirHistory());

    OutputDataDirHistory newHistory;

    for (auto item : dataItems()) {

        if (m_history.wasModifiedSinceLastSave(projectDir, item))
            JobItemUtils::saveIntensityData(item, projectDir);

        newHistory.markAsSaved(item);
    }

    // dealing with files
    QStringList oldFiles = m_history.savedFileNames(projectDir);
    QStringList newFiles = newHistory.savedFileNames();
    cleanOldFiles(projectDir, oldFiles, newFiles);

    // if oldHistory contained some deleted IntensityDataItems, that info will be dropped here
    m_history.setHistory(projectDir, newHistory);
}

void OutputDataIOService::load(const QString& projectDir, MessageService* messageService)
{
    OutputDataDirHistory newHistory;

    for (auto item : dataItems()) {

        try {
            JobItemUtils::loadIntensityData(item, projectDir);
            newHistory.markAsSaved(item);
        } catch (const std::exception& ex) {
            if (messageService)
                messageService->send_warning(this, QString(ex.what()));
            else
                throw ex;
        }
    }

    m_history.setHistory(projectDir, newHistory);
}

//! Returns all IntensityDataItems available for save/load.

QVector<DataItem*> OutputDataIOService::dataItems() const
{
    QVector<DataItem*> result;

    if (!m_applicationModels)
        return result;

    for (auto item : m_applicationModels->nonXMLData())
        if (auto data_item = dynamic_cast<DataItem*>(item))
            result.push_back(data_item);

    return result;
}

//! Clean old saved files.
//! All files in oldSaves list, which are not in newSaves list, will be removed.

void OutputDataIOService::cleanOldFiles(const QString& projectDir, const QStringList& oldSaves,
                                        const QStringList& newSaves)
{
    QStringList to_remove = ProjectUtils::substract(oldSaves, newSaves);
    ProjectUtils::removeFiles(projectDir, to_remove);
}
