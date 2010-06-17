#include <iostream>
#include <cmath>
#include <QTextStream>
#include <QDir>

#include "Log_creator.hh"

#define BEGINTAG "tagbegin"
#define ENDTAG "tagend"
#define SEPARATOR ','

Log_creator::Log_creator(const QString& path_to_journal) {

  log_file.setFileName(QDir::currentPath() + "/" + path_to_journal);

  // Erase the file
  log_file.open(QIODevice::WriteOnly | QIODevice::Text);
  log_file.close();

  begin_tag = BEGINTAG;
  end_tag = ENDTAG;

  fault = NULL;
}

Log_creator::~Log_creator() {
}

bool Log_creator::parse_ram(const QString& file_path){
  QFile ram_file(file_path);
  QByteArray ram;
  QByteArray vars;
  int begin_tag_index, end_tag_index;
  int time = 0;
  QList<QByteArray> values; 
  QString num;

  while(!ram_file.open(QIODevice::ReadOnly | QIODevice::Text) && time < 10)
    {
      usleep(1000000);
      time++;
    }

  if (time >=10)
    {
      write_error("Can't open RAM file");
      return false;
    }
  else
    {
      write_message("RAM file opened");
    }

  // Get the ram
  ram = ram_file.readAll();

  write_message("**** SIZE:");
  write_message(num.setNum(ram.length()));

  // Search the tag
  begin_tag_index = ram.indexOf(begin_tag);
  end_tag_index = ram.indexOf(end_tag);

  // If we didn't find it
  if(begin_tag_index == -1)
    {
      write_error("Can't find the tag "  + begin_tag + " in ram");
      return false;
    }
  if(end_tag_index == -1)
    {
      write_error("Can't find the tag "  + end_tag + " in ram");
    }

  write_message("Tags " + begin_tag + " and " + end_tag + " found");
  
  vars = ram.mid(begin_tag_index + begin_tag.length(), end_tag_index - begin_tag_index - begin_tag.length());

  /*
  values = vars.split(SEPARATOR);
  write_message("**** VALUES ****");
  for(int i = 0; i < values.length(); i++)
    { 
      write_message(QString(values.at(i)));
    }
  */

  write_message("**** VALUES ****");
  write_message(QString(vars));
  
  return true;
}



void Log_creator::write_obs_vars(){

  //  QStringList obs_vars = fault->get_obs_vars();
  log_file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);

  QTextStream out(&log_file);
  out << "***********" << "\n";
  out << "Observation: " << fault->get_id_fault() << "," << fault->get_id_target() + "\n";


  //xout << values;
  /*
  for(int i = 0; i < obs_vars.length(); i++)
    {
      out << obs_vars.at(i) << ": " << values.at(i) << "\n";
    }
  */



  out.flush();
  log_file.close();
}

void Log_creator::write_error(const QString& error_message){
  std::cout << "\033[31m" << "ERROR: " << error_message.toStdString() << "\033[0m" << std::endl;

  log_file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
  QTextStream out(&log_file);
  
  out <<  "ERR0R: " + error_message << '\n';
  
  out.flush();
  log_file.close();
}


void Log_creator::write_message(const QString& message) {
  log_file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
  QTextStream out(&log_file);

  std::cout << message.toStdString() << std::endl;

  out << message << "\n";

  out.flush();
  log_file.close();

}

void Log_creator::set_fault(Fault* f) {
  // If f is the first fault of the campaign, current_fault == NULL
  if(fault != NULL)
    {
      delete fault;
    }
  fault = f;
}
