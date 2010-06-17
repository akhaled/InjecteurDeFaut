#ifndef LOG_CREATOR_HH
#define LOG_CREATOR_HH

#include <QString>
#include <QByteArray>
#include <QFile>
#include "Fault.hh"

class Log_creator
{
private:
  Fault* fault;
  QByteArray tag;
  QFile log_file;
  QList<qint64> values;
  

public:
  Log_creator(const QString& path_to_journal);
  ~Log_creator();
  bool parse_ram(const QString& file_path);
  void write_obs_vars();
  void write_error(const QString& error_message);
  void write_message(const QString& message);
  void set_fault(Fault* f);
};

#endif
