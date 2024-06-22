#/bin/bash
DIR_SCRIPT=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

SYSTEM_ID="LAB_123"

# Porcentajes de configuración
PERCENT_NOTIFY=95
PERCENT_CRITICAL=99

# Archivo donde se encuentran las carpetas a eliminar
FOLDER_LIST_FILE="$DIR_SCRIPT/folder_list.txt"

# Endpoint de notificación
ENDPOINT_BOT="XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
ENDPOINT_URL="$(printf 'https://api.telegram.org/bot%s/sendMessage' $ENDPOINT_BOT)"
ENDPOINT_ID_CHAT="YYYYYYYYYYYYYYYYYYYYYYYYYYYY"

#--------------------------------------------------------------------#

# Construye un mensaje de notificación según el porcentaje de uso y el espacio
# disponible de un disco duro, y lo intenta enviar mediante una petición POST
# según los parámetros ENDPOINT_XXX configurados.
# Argumentos:
# $1: Porcentaje de uso de disco. (int)
# $2: Espacio disponible en el disco (string)
notify() {
    echo "Notifying to system administrator disk event"
    
    local message="$(printf 'Disco del sistema con id %s está [casi] lleno (%d%%, disponible %sB), porfavor revise el sistema' $SYSTEM_ID $1 $2)"
    
    echo "Trying to send notify message"
    curl -H "Connection: close" -s $ENDPOINT_URL -d chat_id=$ENDPOINT_ID_CHAT -d text=$message
    echo ""
}

# Devuelve el porcetaje en uso del disco raíz
# y su espacio disponible en [(null)/K/M/G] bytes.
# Argumentos:
# $1: Variable donde se almacenará el porcentaje de uso del disco.
# $2: Variable donde se almacenará el espacio disponible del disco.
disk_used() {
    IFS='    '
    read -ra disk <<< "$(df -h --output=pcent,avail / | sed 1d)"
    eval "$1='$(echo ${disk[0]} | sed 's/.$//')'"
    eval "$2='${disk[1]}'"
}

# Elimina una lista de elementos de un archivo especificado.
# Argumentos:
# $1: Dirección de archivo de elementos a eliminar.
clean_up() {
	echo "Cleaning up disk"

    local FOLDER_LIST=
    readarray -t FOLDER_LIST < $1
    
    for value in "${FOLDER_LIST[@]}"
    do
      echo "Cleaning $value"
      rm -rf $value
    done
}

#--------------------------------------------------------------------#

disk_perc=
disk_avai=

disk_used disk_perc disk_avai

if [[ $disk_perc -lt $PERCENT_NOTIFY ]]
then
    echo "System Disk is ok, no action."
    exit 0
fi

printf "Disk is at %d%% usage\n" $disk_perc
notify $disk_perc $disk_avai

if [[ $disk_perc -ge $PERCENT_CRITICAL ]]
then
    echo "Disk use is upper than CRITICAL threshold"
    clean_up $FOLDER_LIST_FILE
fi

echo "Done"
exit 0

#notify $disk_perc $disk_avai
#clean_up $FOLDER_LIST_FILE
