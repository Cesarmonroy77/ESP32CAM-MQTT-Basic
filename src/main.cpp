/*
 * Conexión básica por MQTT del NodeMCU
 * Por: Cesar Monroy
 * Fecha: 28 de junio de 2021
 *
 * Este programa envía datos  por Internet a través del protocolo MQTT, para poder
 * encender el led Flash.
 * Es necesario conectarse a un broker para poder recibir le información.
 * Para que el programa funciones es necesario cambiar el ssid y el password
 * del internet para conectarse por wifi, ademas, se necesita poner la IP, puerto, tema
 * y un id de usuario para poder conectarse al broker deseado.
 * En este programa se usan los leds soldados sobre la placa
 * ESP32CAM, el led flash y el led de status.
 *
 * Componente     PinESP32CAM     Estados lógicos
 * ledStatus------GPIO 33---------On=>LOW, Off=>HIGH
 * ledFlash-------GPIO 4----------On=>HIGH, Off=>LOW
 */

//**************************************
//*********** LIBRERIAS ****************
//**************************************
#include <WiFi.h>  //Libreria para manejar el WiFi del ESP32CAM
#include <PubSubClient.h> //Libreria para manejar MQTT

//**************************************
//*********** OBJETOS ******************
//**************************************
WiFiClient espClient; //Maneja los datos de conexion WiFi
PubSubClient client(espClient); //Maneja los datos de conexion al broker

//************************
//****** FUNCIONES *******
//************************
void conectar_wifi(const char*,const char*,int);
void callback(char* topic, byte* mensaje, unsigned int length);
void reconnect(const char*,const char*);

// Inicialización del programa
void setup() {
  //**************************************
  //*********** PINES CONFIG *************
  //**************************************
  int statusLedPin = 33;  // Esta variable controla el led de status ubicado en el pin 33
  int flashLedPin = 4; // Esta variable controla el led Flash ubicado en el pin 4
  pinMode (statusLedPin, OUTPUT);// Se configura el pin 33 como salida
  pinMode (flashLedPin, OUTPUT);// Se configura el pin 4 como salida
  digitalWrite (statusLedPin, HIGH);// Se comienza con el led de Status apagado
  digitalWrite (flashLedPin, LOW);// Se comienza con el Flash apagado

  //**************************************
  //*********** WIFICONFIG ***************
  //**************************************
  const char* ssid = "*************";  // Poner el nombre de la red a la que se desea conectar
  const char* password = "**************";  // Escribir la contraseña de la red

  //**************************************
  //*********** MQTT SERVIDOR ************
  //**************************************
  const char* mqtt_servidor = "127.0.0.1";  //Poner la IP del broker al que se quiere conectar
  const int mqtt_puerto = 1883;

  conectar_wifi(ssid, password, statusLedPin);  //Función para realizar la conexion
  client.setServer(mqtt_servidor, mqtt_puerto); //Función que define el servidor MQTT
  client.setCallback(callback); //Llama a la función que se ejecuta en caso de recibir un mensaje
}

//bucle principal
void loop() {
  //**************************************
  //*********** MQTT CLIENTE ************
  //**************************************
  const char* clientId = "************";  //Poner el id de cliente que se quiere para conectarse al broker
  const char* topic = "esp32/output"; //Tema a suscribirse

  if (!client.connected()) {  //Comprueba la conexion al broker
    reconnect(clientId ,topic);  //Si no hay conexión, ejecuta la función de reconexión
  }
  client.loop(); //Ejecuta de manera no bloqueante las funciones necesarias para la comunicación con el broker
}

void conectar_wifi(const char* ssid,const char* password,int ledStatus){
  Serial.begin (115200);  //Inicialización de comunicación serial a 1152000 baudios
  //Imprimir en el monitor serial
  Serial.print("\n\nConectando a ");
  Serial.println(ssid);

  // Iniciar el WiFi
  WiFi.begin(ssid, password); //Esta es la función que realiza la conexión a WiFi

  while (WiFi.status() != WL_CONNECTED) { // Este bucle espera a que se realice la conexión
    digitalWrite (ledStatus, HIGH); //Se apaga el led de Status
    delay(100); //dado que es de suma importancia esperar a la conexión, debe usarse espera bloqueante
    digitalWrite (ledStatus, LOW); //Se enciende el led de Status
    Serial.print(".");  // Indicador de progreso
    delay (5);
  }

  // Cuando se haya logrado la conexión, el programa avanzará, Se imprime en el monitor serial
  Serial.println("\nWiFi conectado");
  Serial.println("Direccion IP: ");
  Serial.println(WiFi.localIP());
  digitalWrite (ledStatus, LOW);  // Se enciende el led de Status
}

void reconnect(const char* clientId, const char* topic) {
  while (!client.connected()) { // Pregunta si hay conexión
    Serial.print("Intentando conexión Mqtt...");
    //Intentamos conectar
    if (client.connect(clientId)) {
      Serial.println("¡Conectado!");
      // Nos suscribimos
      if(client.subscribe(topic)){
        Serial.println("Suscripcion ok");
      }else{
        Serial.println("fallo Suscripciión");
      }
    }else {
			Serial.print("falló :( con error -> ");
			Serial.print(client.state());
			Serial.println(" Intentamos de nuevo en 5 segundos");
			delay(5000);
		}
  }
}

//*****************************
//***       CALLBACK        ***
//*****************************
void callback(char* topic, byte* payload, unsigned int length){
  int ledFlash=4; // Nos suscribimos
	String mensaje = "";
	Serial.print("Mensaje recibido desde -> ");
	Serial.println(topic);
  //Concatenamos el mensaje en una variable
	for (int i = 0; i < length; i++) {
		mensaje += (char)payload[i];
	}
	Serial.println("Mensaje -> " + mensaje);
  if (mensaje=="true") {
    digitalWrite(ledFlash,HIGH);  //Enceder Flash
  }else{
    digitalWrite(ledFlash,LOW); //Apagar Flash
  }
}
