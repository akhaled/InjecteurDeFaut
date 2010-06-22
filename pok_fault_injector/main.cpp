#include <iostream>
#include "Injector.hh"
#include "Log_creator.hh"
//#include "Launcher.hh"
#include "Fault.hh"

#define CONFIG_FILE "config_file.txt"

int main(int argc, char *argv[])
{


  if(argc != 3)
    {
      std::cout << "Usage: " << argv[0] << " file_entry " << "log_file" << std::endl;
      return 1;
    }

  QString file_entry(argv[1]);
  QString Journal(argv[2]);
  QString config_file(CONFIG_FILE);

  Log_creator log(Journal);

  Injector injector(&log, config_file, file_entry);
  //Launcher launcher(&log);
  //Fault_factory factory;
  

    Fault* current_fault = injector.inject();



  //  while(current_fault != NULL)
  //   {

  //factory.add_fault("Hors_limite", "blackboard", "/home/vince/inf380/pok-20100317");
  //launcher.start_observation(factory.next_fault());
      //    current_fault = injector.inject();
      //}

  return 0;
}
