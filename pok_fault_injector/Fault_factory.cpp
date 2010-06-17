#include "Fault_factory.hh"

Fault_factory::Fault_factory(){

}

//**************************instancie une faute et l'ajoute à la liste de faute*****************************
void Fault_factory::add_fault(QString id_fault, QString id_target){

    fault = new Fault(id_fault, id_target);
    faults.append(fault);

}

Fault* Fault_factory::next_fault(){

    //retourne le premier element de la liste et le supprime
    if(!faults.isEmpty()){
        return faults.takeFirst();
    }
    else {return NULL;}    
}
