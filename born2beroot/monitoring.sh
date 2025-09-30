#!/bin/bash

# Script de monitoring pour le projet Born2BeRoot
# Affiche les informations système : CPU, RAM, disque, réseau, etc.

# Architecture du système
arch=$(uname -a)

# Nombre de CPU physiques
cpuf=$(grep "physical id" /proc/cpuinfo | wc -l)

# Nombre de vCPU
cpuv=$(grep "processor" /proc/cpuinfo | wc -l)

# Utilisation de la RAM
ram_total=$(free --mega | awk '$1 == "Mem:" {print $2}')
ram_use=$(free --mega | awk '$1 == "Mem:" {print $3}')
ram_percent=$(free --mega | awk '$1 == "Mem:" {printf("%.2f"), $3/$2*100}')

# Utilisation du disque
# Calcule l'espace disque total (en Go), utilisé (en Mo) et le pourcentage d'utilisation, en excluant /boot
disk_total=$(df -m | grep "/dev/" | grep -v "/boot" | awk '{disk_t += $2} END {printf ("%.1fGb\n"), disk_t/1024}')
disk_use=$(df -m | grep "/dev/" | grep -v "/boot" | awk '{disk_u += $3} END {print disk_u}')
disk_percent=$(df -m | grep "/dev/" | grep -v "/boot" | awk '{disk_u += $3} {disk_t+= $2} END {printf("%d"), disk_u/disk_t*100}')

# Charge CPU
cpul=$(vmstat 1 2 | tail -1 | awk '{printf $15}')
cpu_op=$(expr 100 - $cpul)
cpu_fin=$(printf "%.1f" $cpu_op)

# Connexions TCP
tcpc=$(ss -ta | grep ESTAB | wc -l)

# Utilisateurs connectés
ulog=$(users | wc -w)

# Informations réseau
ip=$(hostname -I)
mac=$(ip link | grep "link/ether" | awk '{print $2}')

# Nombre de commandes sudo
cmnd=$(journalctl _COMM=sudo | grep COMMAND | wc -l)

# Affichage des informations
# Envoie le rapport à tous les terminaux connectés ; nécessite des privilèges sudo, sinon aucun affichage n'est produit
wall "
=== Rapport de Monitoring Système ===
Architecture      : $arch
CPU Physique      : $cpuf
vCPU              : $cpuv
Mémoire           : $ram_use/${ram_total}MB ($ram_percent%)
Disque            : $disk_use/${disk_total} ($disk_percent%)
Charge CPU        : ${cpu_fin}%
Connexions TCP    : $tcpc ESTABLISHED
Utilisateurs      : $ulog
Réseau            : IP $ip ($mac)
Commandes Sudo    : $cmnd
=============================
"
