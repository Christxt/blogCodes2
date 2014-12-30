#include "process_manager.hpp"
#include "qprocess_guard.hpp"
#include "start_qprocess_repeat.hpp"

#include <QDir>
#include <QFile>
#include <QRegularExpression>

process_manager::process_manager(QString const &file)
{
    auto const AbsFilePath = QDir(file).absoluteFilePath(file);
    QFile file_read(AbsFilePath);
    file_read.open(QIODevice::ReadOnly);

    QString const Contents(file_read.readAll());
    auto const Splitted = Contents.split(QRegularExpression("\r|\n|\r\n|\n\r"));

    for(auto const Data : Splitted){
        create_process(Data);
    }
}

process_manager::~process_manager()
{

}

void process_manager::create_process(const QString &data)
{
    QStringList const Arguments = get_argument(data);
    QString const Program = Splitted[0];
    if(!Splitted.empty()){
       std::unique_ptr<QProcess> process(new QProcess);
       start_qprocess_repeat start(*process, Program, Arguments);
       std::unique_ptr<qprocess_guard> guard(new qprocess_guard(process.get()));

       process_.insert(std::make_pair(Program, std::move(process)));
       guard_process_.insert(std::make_pair(Program, std::move(guard)));
    }
}

QStringList process_manager::get_argument(const QString &data) const
{
    static QRegularExpression reg("\\s+");
    auto const Splitted = data.split(reg);
    QStringList arguments;
    if(Splitted.size() > 1){
        for(int i = 1; i != Splitted.size(); ++i){
            arguments.push_back(Splitted[i]);
        }
    }

    return arguments;
}

