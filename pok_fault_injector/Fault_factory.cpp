#include <QFile>
#include <QTextStream>

#include "Fault_factory.hh"

/*!
*  \brief Constructeur
*/
Fault_factory::Fault_factory(){

}

/*!
*  \brief Instancie une faute et l'ajoute a la liste de faute
*
*  \param id_fault : identificateur du type de faute
*  \param id_target : identificateur de la cible de la faute
*/
void Fault_factory::add_fault(QString id_fault, QString id_target, QString pok_path){
  
  QString name = id_fault + "-" + id_target + ".fault";
  QFile fichier(name);
  QString line;
  QString fault_file_data;
  QStringList vars;
  QString var_tag("#VARIABLES");

  fichier.open(QIODevice::ReadOnly);
  QTextStream in(&fichier);
  line = in.readLine();
  
  Fault* fault = new Fault(id_fault, id_target, pok_path + "/" + line);
  fault_file_data = in.readAll();
  vars = fault_file_data.section("#VARIABLES", -1).split('\n');

  for(int i = 0; i < vars.length(); i++)
    {
      if(!vars.at(i).isEmpty())
        {
          fault->add_obs_var(vars.at(i));
        }
    }

  faults.append(fault);

}

/*!
*  \brief Return next fault
*
*  Methode qui retourne le premier element de la liste et le supprime de la liste
*
*  \return Fault* faults si la liste des fautes n'est pas vide, sinon return NULL.
*/
Fault* Fault_factory::next_fault(){

    if(!faults.isEmpty()){
        return faults.takeFirst();
    }
    else {return NULL;}    
}
