## Escenario de arquitectura y desarrollo de software:

La empresa XYZ ha adquirido un nuevo cliente con el fin de desarrollar una aplicación de control de acceso que sea gestionado y accedido desde cualquier lugar (Aplicación Cloud) y que contenga comunicación con el hardware local que esta encargado de la adquisición de datos de DNI y Huellas dactilares, ademas del control físico para acceder.


1. Elabore según su criterio un diagrama de cuál sería la mejor arquitectura de software a emplear
2. Elabore según su criterio un diagrama de cuál sería la mejor infraestructura de la aplicación Cloud
3. Elabore según su criterio un diagrama de cuál sería el mejor Hardware para el sistema IoT encargado de la adquisición de datos y control.
4. Elabore un script en su lenguaje preferido para simular la comunicación entre un dispositivo IoT y el sistema Cloud explicando la lógica para enviar datos.
5. Elabore un script en su lenguaje preferido para simular la recepción y respuesta de datos en el sistema Cloud
6. Describa cómo protegería la comunicación entre dispositivos y la nube (cifrado, autenticación, etc.).
   - La comunicación entre los dispositivos y el servidor debería ir cifrada implementando el estandar tls 1.3 tanto en las comunicaciones https como en wss. A su vez, se espera que cada dispostivo tenga un token de autenticación que le permitan acceder únicamente a los recursos que necesite de la nube y se deniegen los que no requiera.