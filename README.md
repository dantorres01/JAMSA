# JAMSA
JAMSA's Repository.

// ESPAÑOL //
Inclusión de bibliotecas y definiciones: Se incluyen las bibliotecas necesarias y se definen constantes como el ID y la autenticación de Blynk, así como los pines a los que están conectados los servos.
Configuración inicial en el setup(): Se establecen las conexiones WiFi y Blynk, se adjuntan los servos a los pines y se configuran las posiciones iniciales de los servos.
Funciones BLYNK_WRITE(): Estas funciones se activan cuando se recibe un valor desde la aplicación Blynk. Cada una mueve un servo de acuerdo al valor recibido.
Funciones para guardar, reiniciar y ejecutar posiciones: savePositions() guarda las posiciones de los servos en matrices. resetPositions() reinicia esas matrices y el índice de almacenamiento. runPositions() ejecuta las posiciones guardadas, moviendo los servos secuencialmente.
Loop principal: Se ejecuta continuamente, llamando a Blynk.run() para mantener la comunicación con la aplicación y, si está activada la ejecución (running es verdadero), llama a runPositions().
En resumen, el código permite controlar el brazo robótico a través de la aplicación Blynk, guardar y ejecutar secuencias de movimientos predefinidos.

// INGLES //
Inclusion of libraries and definitions: The required libraries are included and constants such as Blynk ID and authentication are defined, as well as the pins to which the servos are connected.
Initial setup in setup(): WiFi and Blynk connections are established, servos are attached to the pins, and the initial servo positions are configured.
BLYNK_WRITE() functions: These functions are triggered when a value is received from the Blynk application. Each one moves a servo according to the value received.
Functions to save, reset and execute positions: savePositions() saves the servo positions in arrays. resetPositions() resets those arrays and the storage index. runPositions() executes the saved positions, moving the servos sequentially.
Main Loop: Runs continuously, calling Blynk.run() to maintain communication with the application and, if execution is enabled (running is true), calls runPositions().
In summary, the code allows controlling the robotic arm through the Blynk application, saving and executing predefined sequences of movements.
