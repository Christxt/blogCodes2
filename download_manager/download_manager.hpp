#ifndef DOWNLOAD_MANAGER_H
#define DOWNLOAD_MANAGER_H

#include "download_info.hpp"

#include <QObject>
#include <QNetworkReply>
#include <QStringList>
#include <QUrl>

#include <map>
#include <queue>
#include <set>

class QNetworkAccessManager;

namespace dm{

namespace net{

/**
 * Manage multiple download files
 */
class download_manager : public QObject
{
    Q_OBJECT
public:
    explicit download_manager(QObject *obj = nullptr);

    bool append(QUrl const &value,
                QString const &save_at,
                QString const &save_as);

    size_t get_max_download_size() const;
    size_t get_total_download_file() const;

    void set_max_download_size(size_t value);
    bool start_download(const QUrl &value);

signals:
    void download_size_changed(size_t value);
    void download_finished(uint_least64_t uuid);
    void download_progress(uint_least64_t uuid,
                           qint64 bytes_received,
                           qint64 bytes_total);
    void download_ready_read(uint_least64_t uuid);

private slots:    
    void download_finished();
    void download_progress(qint64 bytes_received,
                           qint64 bytes_total);
    void download_ready_read();

private:    
    void save_data(download_info const &info,
                   QByteArray const &data);

    QNetworkReply* start_download_impl(QUrl const &value);

    download_info_index download_info_;
    QNetworkAccessManager *manager_;
    size_t max_download_size_;
    size_t total_download_files_;
    uint_fast64_t uuid_;
};

}

}

#endif // DOWNLOAD_MANAGER_H
