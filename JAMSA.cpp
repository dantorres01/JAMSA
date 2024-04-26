#define BLYNK_TEMPLATE_ID "TMPL20Zq-Xb8p"
#define BLYNK_TEMPLATE_NAME "JAMSA"
#define BLYNK_AUTH_TOKEN "RXWD4tQLxRz2Y8mYIl2kf_WqUABWKXNY"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial
#include <ESP32Servo.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

Servo servo1;  // BASE
Servo servo2;  // HOMBRO1
Servo servo3;  // CODO1
Servo servo4;  // CODO2
Servo servo5;  // MUÑECA
Servo servo6;  // GRIPPER

int s1Vel = 30; 
int s2Vel = 25; 
int s3Vel = 20; 
int s4Vel = 20; 
int s5Vel = 15; 
int s6Vel = 15;

int almacen = 0; // Cambio de nombre de la variable index a almacen
int velG = 2500;

int s1Act, s2Act, s3Act, s4Act, s5Act, s6Act; // Posicion actual de los servos
int s1Ant, s2Ant, s3Ant, s4Ant, s5Ant, s6Ant; // Posicion anterior de los servos
int s1[50], s2[50], s3[50], s4[50], s5[50], s6[50]; // Matrices para almacenar las posiciones de cada servo

bool saving = false;
bool running = false;

//////////°°°°°°°°°°°°°°WPKWI°°°°°°°°°°°°°°
char ssid[] = "Wokwi-GUEST";
char pass[] = "";
char auth[] = BLYNK_AUTH_TOKEN;
void setup() {
  Serial.begin(115200);

  // Ancho mínimo y máximo para un servo MG996R
  servo1.attach(33, 500, 2400);  
  servo2.attach(25, 500, 2400);  
  servo3.attach(26, 500, 2400);  
  servo4.attach(27, 500, 2400);  
  servo5.attach(14, 500, 2400);  
  servo6.attach(12, 500, 2400);  

  s1Ant = 90;  // BASE
  servo1.write(s1Ant);
  //Importante empezar s2 y s3 complementados a 180°;es decir; s2+s3=180;
  s2Ant = 90; // HOMBRO1 
  servo2.write(s2Ant); 
  
  s3Ant = 0; // CODO1
  servo3.write(s3Ant);
  
  s4Ant = 0;  // CODO2
  servo4.write(s4Ant);
  
  s5Ant = 0;  // MUÑECA
  servo5.write(s5Ant);
  
  s6Ant = 0; // GRIPPER
  servo6.write(s6Ant);
  
  delay(50);
    // WOKWI SIMULACION DE ESP32
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");

  // Inicia conexión Blynk
  Blynk.begin(auth, ssid, pass);
}

//////////////////////°°°°°°°°°°°°°°°°°°°°°°VOID LOOP°°°°°°°°°°°°°°°°°°°°°°°°
void loop() {
  Blynk.run(); // Ejecuta Blynk
    
  if (running) { // Verifica si la ejecución está activa
    runPositions(); // Ejecuta las posiciones guardadas mientras la ejecución está activa
  }
}



///°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°
BLYNK_WRITE(V0) {
  // Captura el valor del slider virtual V0 en la app Blynk
  int s1Act = param.asInt();
  // Mueve el servo1 a la posición especificada por el slider
  servo1.write(s1Act);
  delay(s1Vel);
}

BLYNK_WRITE(V1) {
  // Captura el valor del slider virtual V1 en la app Blynk
  int s2Act = param.asInt();
  // Mueve el servo2 a la posición especificada por el slider
  servo2.write(s2Act);
  delay(s2Vel);
}
BLYNK_WRITE(V2) {
  // Captura el valor del slider virtual V1 en la app Blynk
  int s3Act = param.asInt();
  // Mueve el servo2 a la posición especificada por el slider
  servo3.write(s3Act);
  delay(s3Vel);
}
BLYNK_WRITE(V3) {
  // Captura el valor del slider virtual V1 en la app Blynk
  int s4Act = param.asInt();
  // Mueve el servo2 a la posición especificada por el slider
  servo4.write(s4Act);
  delay(s4Vel);
}
BLYNK_WRITE(V4) {
  // Captura el valor del slider virtual V1 en la app Blynk
  int s5Act = param.asInt();
  // Mueve el servo2 a la posición especificada por el slider
  servo5.write(s5Act);
  delay(s5Vel);
}
BLYNK_WRITE(V5) {
  // Captura el valor del slider virtual V1 en la app Blynk
  int s6Act = param.asInt();
  // Mueve el servo2 a la posición especificada por el slider
  servo6.write(s6Act);
  delay(s6Vel);
}

BLYNK_WRITE(V6) {
  int resetButtonState = param.asInt(); // Obtener el estado del botón
  if (resetButtonState == 1) { // Si el botón está presionado (valor 1)
    resetPositions(); // Llama a la función resetPositions()
  }
}

BLYNK_WRITE(V7) {
  int saveButtonState = param.asInt(); // Obtener el estado del botón
  if (saveButtonState == 1) { // Si el botón está presionado (valor 1)
    savePositions(); // Llama a la función savePositions()
  }
}

BLYNK_WRITE(V8) {
  int runButtonState = param.asInt(); // Obtener el estado del botón
  if (runButtonState == 1) { // Si el botón está presionado (valor 1)
    runPositions(); // Llama a la función runPositions()
  }
}




void savePositions() {

  
  // Guardar las posiciones actuales de los servos en las matrices
  s1[almacen] = servo1.read();
  s2[almacen] = servo2.read();
  s3[almacen] = servo3.read();
  s4[almacen] = servo4.read();
  s5[almacen] = servo5.read();
  s6[almacen] = servo6.read();
 
  // Incrementa el índice para la siguiente posición
  almacen++;
}

void resetPositions() {
  // Reinicia las matrices de posiciones y el índice
  memset(s1, 0, sizeof(s1));
  memset(s2, 0, sizeof(s2));
  memset(s3, 0, sizeof(s3));
  memset(s4, 0, sizeof(s4));
  memset(s5, 0, sizeof(s5));
  memset(s6, 0, sizeof(s6));

  
  almacen = 0;
}

void runPositions() {
  // Ejecutar las posiciones guardadas
  running = true;
  for (int i = 0; i < almacen; i++) {
    if (!running) break; // Si se detiene la ejecución
    // Mueve los servos a las posiciones guardadas
    servo1.write(s1[i]);
    servo2.write(s2[i]);
    servo3.write(s3[i]);
    servo4.write(s4[i]);
    servo5.write(s5[i]);
    servo6.write(s6[i]);
    delay(velG); // Pausa entre movimientos
  }
  //running = false; // No necesitas establecer running en false aquí, ya que se hace en la función loop cuando termina de ejecutarse runPositions()
}
