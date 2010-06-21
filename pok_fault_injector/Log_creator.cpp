#include <iostream>
#include <cmath>
#include <QTextStream>
#include <QDir>

#include "tags.h"
#include "Log_creator.hh"

#define RAM_SIZE 128*1024*1024

/*!
*  \brief Constructeur
*
*  Constructeur de la classe Log_creator qui prend en paramètre le chemin vers le fichier qui contiendra le rapport
*
*  \param &path_to_journal : le chemin vers le fichier du rapport
*/
Log_creator::Log_creator(const QString& path_to_journal) {

  log_file.setFileName(QDir::currentPath() + "/" + path_to_journal);

  // Erase the file
  log_file.open(QIODevice::WriteOnly | QIODevice::Text);
  log_file.close();

  QByteArray tagsArray(tags);

  begin_tag = tagsArray.left(TAG_SIZE);
  end_tag = tagsArray.right(TAG_SIZE);
  sep = separator;

  fault = NULL;
}

/*!
*  \brief Destructeur 
*/
Log_creator::~Log_creator() {
}



/*!
*  \brief cherche dans ram les variables
*
*  Methode qui qui cherche dans ram les variables de obs_vars et qui remplie values avec ces dernières
*
*  \return TRUE si les variables ont bien été trouvées, sinon retourne FALSE
*/
bool Log_creator::parse_ram(const QString& file_path){
  QFile ram_file(file_path);
  QByteArray ram;
  QByteArray vars;
  int begin_tag_index = 0;
  int end_tag_index = 0;
  int time = 0;
  QList<QByteArray> values; 
  QString num;
  QStringList obs_vars = fault->get_obs_vars();

  // wait for the ram file to be written
  while((ram_file.size() < RAM_SIZE || !ram_file.open(QIODevice::ReadOnly | QIODevice::Text))
        && time < 10)
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
  std::cout << "SIZE: " << ram_file.size() << std::endl;

  do {
    // Search the tags in the ram
    begin_tag_index = ram.indexOf(begin_tag, begin_tag_index);
    end_tag_index = ram.indexOf(end_tag, begin_tag_index);

    if(begin_tag_index == -1 || end_tag_index == -1)
      {
        write_message("Can't find the vars in RAM");
        break;
      }

    begin_tag_index += begin_tag.length();

    // get the variables between the tags
    vars = ram.mid(begin_tag_index,
                   end_tag_index - begin_tag_index);

    // separates the vars
    values = vars.split(sep);

  }
  // We didn't find the right numbers of variables
  while(values.length() != obs_vars.length());



  // writes vars in the log file
  write_message("**** Observation: " + fault->get_id_fault() + ","
                + fault->get_id_target() + " ****");

  for(int i = 0; i < values.length(); i++)
    {
      write_message(obs_vars.at(i) + ": " + QString(values.at(i)));
    }

  write_message("**************************************");
  

  ram_file.close();
  ram_file.remove();
  return true;
}


/*!
*  \brief écrit les messages des erreurs dans le rapport
*
*  Methode qui écrit les messages des erreur dans le rapport et l’affiche également à l’écran.
*
*/
void Log_creator::write_error(const QString& error_message){
  std::cout << "\033[31m" << "ERROR: " << error_message.toStdString() << "\033[0m" << std::endl;

  log_file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
  QTextStream out(&log_file);
  
  out <<  "ERR0R: " + error_message << '\n';
  
  out.flush();
  log_file.close();
}

/*!
*  \brief écrit les messages dans le rapport
*
*  Methode qui écrit les messages dans le rapport et l’affiche également à l’écran.
*
*/
void Log_creator::write_message(const QString& message) {
  log_file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
  QTextStream out(&log_file);

  std::cout << message.toStdString() << std::endl;

  out << message << "\n";

  out.flush();
  log_file.close();

}

/*!
*  \brief mise à jour de fault
*
*  Methode qui met à jour l’attribut fault
*
*/
void Log_creator::set_fault(Fault* f) {
  // If f is the first fault of the campaign, current_fault == NULL
  if(fault != NULL)
    {
      delete fault;
    }
  fault = f;
}
