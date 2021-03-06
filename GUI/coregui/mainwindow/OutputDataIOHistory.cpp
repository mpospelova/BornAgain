// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/OutputDataIOHistory.cpp
//! @brief     Defines OutputDataIOHistory classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "OutputDataIOHistory.h"
#include "GUIHelpers.h"

//! Static method to create info for just saved IntensityDataItem.

OutputDataSaveInfo OutputDataSaveInfo::createSaved(const DataItem *item)
{
    Q_ASSERT(item);

    OutputDataSaveInfo result;
    result.m_dataItem = item;
    result.m_file_name = item->fileName();
    result.m_last_saved = QDateTime::currentDateTime();
    return result;
}

bool OutputDataSaveInfo::wasModifiedSinceLastSave() const
{
    return wasSavedBefore(m_dataItem->lastModified());
}

//! Returns true if IntensityDataItem was saved before given time.

bool OutputDataSaveInfo::wasSavedBefore(const QDateTime& dtime) const
{
    // positive number means that m_last_saved is older than dtime
    return m_last_saved.msecsTo(dtime) > 0;
}

//-----------------------------------------------------------------------------

void OutputDataDirHistory::markAsSaved(const DataItem *item)
{
    if (contains(item))
        throw GUIHelpers::Error("OutputDataDirHistory::markAsSaved() -> Error. "
                                "Already existing item.");

    m_history.push_back(OutputDataSaveInfo::createSaved(item));
}

bool OutputDataDirHistory::wasModifiedSinceLastSave(const DataItem *item)
{
    // non existing item is treated as modified since last save
    return contains(item) ? itemInfo(item).wasModifiedSinceLastSave() : true;
}

bool OutputDataDirHistory::contains(const DataItem *item) {
    for(auto& info : m_history)
        if(info.dataItem() == item)
            return true;

    return false;
}

//! Returns list of file names used to save all IntensityDataItem in a history.

QStringList OutputDataDirHistory::savedFileNames() const
{
    QStringList result;

    for(auto& info : m_history)
        result.append(info.fileName());

    return result;
}

OutputDataSaveInfo OutputDataDirHistory::itemInfo(const DataItem* item) const
{
    for(auto& info : m_history) {
        if (info.dataItem() == item)
            return info;
    }

    throw GUIHelpers::Error("OutputDataDirHistory::itemInfo() -> Error. No info exists.");
}

//-----------------------------------------------------------------------------

bool OutputDataIOHistory::hasHistory(const QString& dirname) const
{
    return m_dir_history.find(dirname) == m_dir_history.end() ? false : true;
}

bool OutputDataIOHistory::wasModifiedSinceLastSave(const QString& dirname,
                                                   const DataItem *item)
{
    if (!hasHistory(dirname))
        throw GUIHelpers::Error("OutputDataIOHistory::wasModifiedSinceLastSave() -> Error. "
                                "No info for directory '"+dirname+"'.");
    return m_dir_history[dirname].wasModifiedSinceLastSave(item);
}

//! Sets history for given directory. Previous history will be rewritten.

void OutputDataIOHistory::setHistory(const QString& dirname, const OutputDataDirHistory& history)
{
    Q_ASSERT(dirname.isEmpty() == false);

    m_dir_history[dirname] = history;
}

QStringList OutputDataIOHistory::savedFileNames(const QString& dirname) const
{
    if (!hasHistory(dirname))
        throw GUIHelpers::Error("OutputDataIOHistory::savedFileNames() -> Error. "
                                "No info for directory '"+dirname+"'.");

    return m_dir_history[dirname].savedFileNames();
}

