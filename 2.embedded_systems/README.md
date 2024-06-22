## Escenario de Sistemas Embebidos:

Suponiendo que tienes una lectora de códigos Qr conectada a un dispositivo IoT mediante el protocolo de comunicación RS 232 adquiriendo la siguiente trama de datos: 

```
01ICCOLO01121047415001<<<<<<<<<< 9210181M3110278COL1030432234<2PEPITO<PEREZ<<DIOMEDES<DANIEL<<<< 
```

extraiga el número DNI de la trama mediante cualquier lenguaje de programación. (Tenga en cuenta que el numero DNI es el que está después de segundo “C0L”)

- Ver carpeta [qr](qr)

La empresa XYZ necesita integrar una cámara facial con su plataforma de registro de accesos. La cámara facial cuenta con una API REST que permite registrar, actualizar y eliminar personas con sus rostros, dicha cámara envía los eventos de acceso por un puerto http. la plataforma que registra los accesos provee un recurso por el cual registrar los accesos.

Proponer una arquitectura para la integración de la cámara facial con la plataforma de registro de accesos usando diagramas.

- La arquitectura Propuesta contempla la implementación de un motor de registro de eventos en la plataforma de registro de accesos. La cual se encargará de clasificar y registrar los eventos que cualquier cámara pueda llegar a reportar.
