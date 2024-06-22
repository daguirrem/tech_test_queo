## Escenario Practico Administración de SO:

Suponiendo que tiene un sistema embebido trabajando bajo el S.O Linux que ejecuta una aplicación y, de repente, empiezas a recibir errores de “disco lleno”. El espacio en disco se ha agotado y necesitas resolverlo.

  - Para la resolución del problema, se toma como premisa la importancia de notificarle al administrador por algún medio el fallo que se está presentando en el sistema operativo. Por otra parte, se propone mitigar el fallo mientras el administrador revisa, eliminando el contendio de algunas carpetas predefinidas como lo pueden ser backups obsoletos, logs obsoletos etc. 


Con base a la respuesta anterior crea un autómata (Bash o Scripting con Python) para resolver el escenario anterior de forma automática.

  - El script se realiza en bash, y tiene como objetivo enviar un mensaje por telegram al administrador para que esté al tanto de la situación cuando supere un umbral.
  - En caso de que se supere un umbral crítico (diferente al mencionado en el anterior punto) se intentará liberar espacio de las carpetas y/o archivos predefinidos dentro del archivo *folder_list.txt* que está junto al script.
  - El Script está pensado para que se ejecute periodicamente cada determinado tiempo, y así se pueda preveer con anterioridad el posible fallo.

