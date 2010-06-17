#include "Fault.hh"

/*!
*  \brief Constructeur
*
*  Constructeur de la classe Fault, qui va initialiser obs_vars et lenghts en fonction des informations contenues dans le fichier .fault
*
*  \param id_fault : identificateur du type de faute
*  \param id_target : identificateur de la cible de la faute
*/
Fault::Fault(QString id_fault, QString id_target){

    Fault::id_fault = id_fault;
    Fault::id_target = id_target;

}

/*!
*  \brief return obs_vars
*
*  Methode qui renvoie obs_vars
*
*  \return QStringList obs_vars
*/
QStringList Fault::get_obs_vars(){
	return Fault::obs_vars;
}

/*!
*  \brief return id_fault
*
*  Methode qui renvoie id_fault
*
*  \return QStringList id_fault
*/
QString Fault::get_id_fault(){
	return Fault::id_fault;
}

/*!
*  \brief return id_target
*
*  Methode qui renvoie id_target
*
*  \return QStringList id_target
*/
QString Fault::get_id_target(){
	return Fault::id_target;
}

/*!
*  \brief return lengths
*
*  Methode qui renvoie lengths
*
*  \return lengths
*/
int* Fault::get_lengths(){
	return Fault::lengths;
}
