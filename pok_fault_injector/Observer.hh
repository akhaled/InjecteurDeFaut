#ifndef OBSERVER_HH
#define OBSERVER_HH

#include <QLocalServer>
#include <QLocalSocket>
#include <stdlib.h>

class Observer {

private:
  QString socket_path;//!<le chemin de la socket Unix utilisée pour communiquer avec QEMU
  QLocalSocket* qemu_socket;//!<socket Unix pour la communication avec QEMU
  QLocalServer qemu_server;//!<serveur auquel se connecte QEMU
  
public:
  Observer();
  ~Observer();
  bool connect_to_qemu();
  void disconnect_from_qemu();
  void ram_to_file(const QString& file_path);
  QByteArray* get_ram();
  const QString& get_socket_path();
  void exit_qemu();
  QLocalSocket::LocalSocketState get_state();
};

#endif
