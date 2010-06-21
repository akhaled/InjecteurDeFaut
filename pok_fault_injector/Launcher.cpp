#include <iostream>
#include <QDir>
#include <unistd.h>
#include "Launcher.hh"
#define QEMU_COMMAND "make -C generated-code run"
#define TIME 5000000
#define RAM_FILE_NAME "qemu_ram"
//#define QEMU_COMMAND "qemu -cdrom xubuntu-10.04-desktop-i386.iso"

/*!
*  \brief Constructeur
*
*  Constructeur de la classe Launcher
*
*  \param *Log : 
*  \param loop_nb : 
*  \param pok_appli_path :
*  \param obs_loops_nb : 
*/
Launcher::Launcher(Log_creator* log, int loop_nb): obs_loops_nb(loop_nb)
{
  log_creator = log;
  // Create the observer
  observer= new Observer();
}

/*!
*  \brief Destructeur 
*/
Launcher::~Launcher()
{ 
  delete observer;
}

/*!
*  \brief lancer QEMU
*
* Methode qui lance QEMU 
*
*  \return TRUE si QEMU est lancé, sinon retoune FALSE
*/
bool Launcher::run_qemu(const QString& pok_appli_path) {
  QString command(QEMU_COMMAND);

  //Go in the pok appli path to launch the command
  QDir::setCurrent(pok_appli_path);
  return qemu_process.startDetached(command);
}

/*!
*  \brief arrêter QEMU
*/
void Launcher::exit_qemu() {
  observer->exit_qemu();
}

/*!
*  \brief commencer l'observation
*
* Methode qui lance QEMU et la phase d’observation 
*
*  \param *fault : la fault courrent
*/
void Launcher::start_observation(Fault* fault) {


  QString ram_file = fault->get_pok_appli_path() + "/generated-code/cpu/" + RAM_FILE_NAME;
  log_creator->set_fault(fault);


  std::cout << "run QEMU" << std::endl;
  // Launch QEMU with POK
  if(!run_qemu(fault->get_pok_appli_path()))
    {
      log_creator->write_error(QString("Can't launch QEMU."));
      return;
    }
  else log_creator->write_message(QString("QEMU launched"));

  // Connect to QEMU monitor
  if(!observer->connect_to_qemu())
    {
      log_creator->write_error(QString("Can't connect to QEMU."));
      exit_qemu();
      return;
    }
  else log_creator->write_message(QString("Connected to QEMU"));
  
  
  for(int i = 0; i < obs_loops_nb; i++)
    {
      usleep(TIME);
      // Copy QEMU ram into file RAM_FILE_NAME and parse it to find the variables
      observer->ram_to_file(RAM_FILE_NAME);

      if(!log_creator->parse_ram(ram_file))
        {
          log_creator->write_error("Can't parse the ram.");
        }

    }

  
  exit_qemu();
  log_creator->write_message("exit QEMU");


}
