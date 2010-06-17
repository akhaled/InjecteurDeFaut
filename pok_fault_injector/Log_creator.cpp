#include <iostream>
#include <cmath>
#include <QTextStream>


#include "Log_creator.hh"

#define TAG "begin"

Log_creator::Log_creator(const QString& path_to_journal) {
  log_file.setFileName(path_to_journal);

  // Erase the file
  log_file.open(QIODevice::WriteOnly | QIODevice::Text);
  log_file.close();

  tag = TAG;
  fault = NULL;
}

Log_creator::~Log_creator() {
}

bool Log_creator::parse_ram(const QString& file_path){
  QFile ram_file(file_path);
  QByteArray ram;
  int index_in_file;
  int vars_nb = fault->get_obs_vars().length();
  int* lengths = fault->get_lengths();
  int i,j;
  qint64 value;

  if (!ram_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      write_error("Can't open RAM file");
      return false;
    }

  // Get the ram
  ram = ram_file.readAll();

  // Search the tag
  index_in_file = ram.indexOf(tag);

  // If we didn't find it
  if(index_in_file == -1)
    {
      return false;
    }

  // Set the index just after the tag
  index_in_file += tag.length();

  // Clear old values
  values.clear();

  // Get the variables
  for(i = 0; i < vars_nb; i++)
    {
      value = 0;

      for(j = 0; j < lengths[i]; j++)
        {
          value += ram.at(index_in_file) * std::pow(256, j);
          index_in_file++;
        }

      values.append(value);
    }

  return true;
}



void Log_creator::write_obs_vars(){
  QStringList obs_vars = fault->get_obs_vars();
  log_file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);

  QTextStream out(&log_file);
  out << "***********" << "\n";
  out << "Observation: " << fault->get_id_fault() << "," << fault->get_id_target() + "\n";

  for(int i = 0; i < obs_vars.length(); i++)
    {
      out << obs_vars.at(i) << ": " << values.at(i) << "\n";
    }

  out.flush();
  log_file.close();
}

void Log_creator::write_error(const QString& error_message){
  std::cout << "ERROR: " << error_message.toStdString() << std::endl;

  log_file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
  QTextStream out(&log_file);
  
  out <<  "ERR0R: " + error_message << '\n';
  
  out.flush();
  log_file.close();
}


void Log_creator::write_message(const QString& message) {
  log_file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
  QTextStream out(&log_file);

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
