#include "Fault.hh"

/*!
*  \brief Constructeur
*
*  \param id_fault : identificateur du type de faute
*  \param id_target : identificateur de la cible de la faute
*/
Fault::Fault(QString id_fault, QString id_target, QString pok_appli_path){

    this->id_fault = id_fault;
    this->id_target = id_target;
    this->pok_appli_path = pok_appli_path;
    this->fault_file_path = id_fault + "-" + id_target + ".fault";
}


/*!
*  \brief Permet d'ajouter une variable à observer à la faute
*
*  \return obs_vars
*/
void Fault::add_obs_var(const QString& obs_var)
{
  obs_vars.append(QString(obs_var));
}

/*!
*  \brief Getteur pour obs_vars
*
*  \return obs_vars
*/
const QStringList& Fault::get_obs_vars(){
	return obs_vars;
}

/*!
*  \brief Getteur id_fault
*
*  \return QStringList id_fault
*/
const QString& Fault::get_id_fault(){
	return id_fault;
}

/*!
*  \brief Getteur pour id_target
*
*  \return id_target
*/
const QString& Fault::get_id_target(){
	return id_target;
}

/*!
*  \brief Getteur pour pok_appli_path
*
*  \return pok_appli_path
*/
const QString& Fault::get_pok_appli_path(){
	return pok_appli_path;
}

/*!
*  \brief Getteur pour fault_file_path
*
*  \return fault_file_path
*/
const QString& Fault::get_fault_file_path(){
	return fault_file_path;
}

