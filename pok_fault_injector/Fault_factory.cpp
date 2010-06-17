#include "Fault_factory.hh"

Fault_factory::Fault_factory(){

}

/*!
*  \brief Constructeur
*
*  Constructeur de la classe Fault_factory, qui instancie une faute et l'ajoute à la liste de faute
*
*  \param id_fault : identificateur du type de faute
*  \param id_target : identificateur de la cible de la faute
*/
void Fault_factory::add_fault(QString id_fault, QString id_target){

  faults.append(new Fault(id_fault, id_target));

}

/*!
*  \brief return next fault
*
*  Methode qui retourne le premier element de la liste et le supprime
*
*  \return Fault* faults si la liste des fautes n'est pas vide, sinon return NULL.
*/
Fault* Fault_factory::next_fault(){

    //retourne le premier element de la liste et le supprime
    if(!faults.isEmpty()){
        return faults.takeFirst();
    }
    else {return NULL;}    
}
