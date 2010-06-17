#ifndef OBSERVER_HH
#define OBSERVER_HH

#include <QLocalServer>
#include <QLocalSocket>
#include <stdlib.h>

class Observer {

private:
  QString socket_path;
  QLocalSocket* qemu_socket;  
  QLocalServer qemu_server;
  
public:
  Observer();
  ~Observer();
  bool connect_to_qemu();
  void disconnect_from_qemu();
  void ram_to_file(const QString& file_path);
  QByteArray* get_ram();
  const QString& get_socket_path();
  void exit_qemu();
};

#endif
