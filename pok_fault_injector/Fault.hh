#ifndef DEF_FAULT
#define DEF_FAULT

#include <QString>
#include <QStringList>

class Fault{


private:
  QString id_target;//!<identificateur de la cible de la faute
  QString id_fault;//!<identificateur du type de faute
  QStringList obs_vars;//!<la liste des variables à récupérer dans la RAM de QEMU par la partie observation. Lors de son instanciation, elle ira chercher cette liste dans son fichier .fault
  QString pok_appli_path;
  QString fault_file_path;

public:
  Fault(QString id_fault, QString id_target, QString pok_appli_path);
  QStringList get_obs_vars();
  const QString& get_id_fault();
  const QString& get_id_target();
  const QString& get_pok_appli_path();
  const QString& get_fault_file_path();

};


#endif
