#ifndef LOG_CREATOR_HH
#define LOG_CREATOR_HH

#include <QString>
#include <QByteArray>
#include <QFile>
#include "Fault.hh"

class Log_creator
{
private:

  Fault* fault;//!<la faute courante injectée
  QByteArray begin_tag;
  QByteArray end_tag;
  QFile log_file;//!<le fichier qui contiendra le rapport
 

public:
  Log_creator(const QString& path_to_journal);
  ~Log_creator();
  bool parse_ram(const QString& file_path);
  void write_error(const QString& error_message);
  void write_message(const QString& message);
  void set_fault(Fault* f);
};

#endif
