# ESP32CAM_MQTT-Basic
Este repositorio contiene el programa básico para conectar el ESP32CAM a un broker MQTT, enviar y recibir mensajes.

* [Requerimientos](#requerimientos)
  * [Hardware](#hardware)
  * [Software](#software)
* [Configuración](#Configuración)
* [Funcionamiento](#funcionamiento)

## Requerimientos
### Hardware
---
Para que el código de este repositorio funcione, es necesario contar con lo siguiente hardware:
* ESP32CAM AI-Thinker
* Camara OV2640
* Programador FTDI con su cable

### Software
---
Para que el código de este repositorio funcione, es necesario contar con lo siguiente software:
* Ubuntu 20.04 o superior
* Alguna IDE:
  * [Arduino 1.8 o superior](#arduino-ide)
    * Biblioteca [PubSubClient](#pubsubclient)
  * Atom / Visual Studio Code
* [Broker Mosquitto](#broker-mosquitto) funcionando de forma local en el puerto 1883
* [NodeRed](#nodered) corriendo de forma local en el puerto 1880

## Configuración
### Broker Mosquitto
---
Para configurar correctamente tu broker mosquitto puedes consultar el siguiente enlace.

https://edu.codigoiot.com/course/view.php?id=818

### NodeRed
---
Para configurar correctamente NodeRed puedes consultar el siguiente enlace.

https://edu.codigoiot.com/course/view.php?id=817

Es necesario instalar los nodos Dashboard para NodeRed

El flow de NodeRed lee en el tema `esp32/data` y publica en el tema `esp32/output`, por lo que deberás configurar los nodos MQTT para conectarse a estos temas y al broker de tu elección.

Los nodos switch y text de la sección dashboard deberán tener correctamente configurados el tab y group en el que se visualizarán.

### Arduino IDE
---
Para configurar correctamente la IDE de Arduino para trabajar con el ESP32CAM, puedes consultar el siguiente enlace.
https://edu.codigoiot.com/course/view.php?id=850

#### PubSubClient
Puedes obtener la biblioteca PubSubClient desde el siguiente enlace.
https://github.com/knolleary/pubsubclient

#### Abrir el programa
Para abrir el programa en Arduino es necesario copiar el codigo del del archivo `main.cpp` ubicado en la carpeta `src`

### Atom / Visual Studio Code
---
En Atom y en Visual Studio Code se puede instalar la extension de ***PlatfromIO IDE***. En Atom la extencion se ecncuentra como `platformio-ide` mientras que para Visual Studio Code se encuentra con el nombre de `PlatfromIO IDE`

**No es necesario instalar la libreria PubSubClient**

#### Abrir el programa
Para abrir el programa solo es necesario abrir el folder en el IDE con la extensión de PlatfromIO y este estara listo para ser cargado al ESP32CAM

### Funcionamiento
---
Para observar el funcionamiento de este proyecto deberás realizar lo siguiente.

1. Carga el flow MQTT+ESP32CAM-Basic.json en NodeRed.
2. Comprueba que el broker MQTT esté funcionando.
3. Carga el programa ES2CAM_MQTT-Basic en el ESP32CAM.
4. Visita el dashboard de NodeRed

Podrás observar una cuenta progresiva, la cual envía el prográma base del ESP32CAM. Puedes controlar el led flash del ESP32CAM con el switch del dashboard.
