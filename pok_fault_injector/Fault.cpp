#include "Fault.hh"

/*!
*  \brief Constructeur
*
* 
*
*  \param id_fault : identificateur du type de faute
*  \param id_target : identificateur de la cible de la faute
*/
Fault::Fault(QString id_fault, QString id_target, QString pok_appli_path){

    this.id_fault = id_fault;
    this.id_target = id_target;
    this.pok_appli_path = pok_appli_path;

}

/*!
*  \brief getteur pour obs_vars
*
*  
*
*  \return obs_vars
*/
QStringList Fault::get_obs_vars(){
	return Fault::obs_vars;
}

/*!
*  \brief getteur id_fault
*

*
*  \return QStringList id_fault
*/
QString Fault::get_id_fault(){
	return this.id_fault;
}

/*!
*  \brief getteur pour id_target
*
*  
*
*  \return id_target
*/
QString Fault::get_id_target(){
	return this.id_target;
}

/*!
*  \brief getteur pour pok_appli_path
*
*  
*
*  \return pok_appli_path
*/
QString Fault::get_pok_appli_path(){
	return this.pok_appli_path;
}
