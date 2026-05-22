# dns-forwarder

Para funcionar pelo navegador direto:

desativa o resolvedor do sistema operacional:
sudo nano /etc/systemd/resolved.conf
DNSStubListener=no

reinicia 
sudo systemctl restart systemd-resolved

alterar resolv.conf para:
sudo nano /etc/resolv.conf
nameserver 127.0.0.1
