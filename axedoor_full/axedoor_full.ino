/** AxeDoor
 * Codigo para contraseña configurable guardada en eeprom
 * Microcontrolador: Arduino
 * Escrito por: Útil Mente Geek
 * PaginaWeb: www.utilmentegeek.com
 * YouTube: https://www.youtube.com/channel/UCBqfcl_tue6Zsk4Hc3BErWg
 * Instagram: https://www.instagram.com/utilmentegeek/
 * 
 * Recuerda que tambien pudes contribuir a la mejora de este codigo en GitHub
 * Y apoyar el desarrollo de estos proyectos así como resolver dudas sobre el codigo
 * en nuestras redes socilaes @Util Mente Geek.
 */
  #include <Keypad.h>        //Se incluye la libreria keypad (esta se modifica para nuestra necesidad que es matriz de 2x2)
  #include <EEPROM.h>        //Se incluye la librería eeprom para mantener siempre la contraseña almacenada

  const byte FILAS = 2;      //Se crea variable igual al número de filas 
  const byte COLUMNAS = 2;   //Se crea variable igual al número de columnas
  char keys[FILAS][COLUMNAS] = { //SE crea un array de dos dimensiones de tipo caracter que contiene las teclas que tenemos
    {'1','2'},
    {'3','4'}
                               };
  
  byte pinesFilas[FILAS] = {13,12}; //Se asigna en un array los pines donde conectaremos las filas
  byte pinesColumnas[COLUMNAS] = {11,10};//Se asigna en un array los pines donde conectaremos las columnas
  
  Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS); //Se crea un objeto llamado teclado que contiene el mapeo del teclado matricial
  
  char TECLA; //Variable de tipo caracter para almacenar la tecla presionada
  char CLAVE[5]; // array de tipo caracter para almacenar la clave ingresada
  char CLAVE_MAESTRA[5]; //array de tipo caracter para almacenar la clave que configuraremos
  byte INDICE = 0; // variable de 8 bits sin signo que nos ayuadara a movernos en los espacios de un array
  byte INDICE2 = 0;// variable de 8 bits sin signo que nos ayuadara a movernos en los espacios de un array
  int ledC = 9;    //variable tipo entero para indicar el pin donde conectaremos el led que indica que esta correcta la clave
  int ledI = 8;   //variable tipo entero para indicar el pin donde conectaremos el led que indica que esta incorrecta la clave
  int btnConf = 7; //variable tipo entero para indicar el pin donde conectaremos el boton que configurará la clave
  int ledN = 6;   ////variable tipo entero para indicar el pin donde conectaremos el led que indica que esta configurandose la clave
 
  
  void setup() {
    Serial.begin(9600); //Comenzamos la comunicación serial a 9600 baudios
    pinMode(ledC, OUTPUT); //Ponemos como salida el led
    pinMode(ledI, OUTPUT);  //Ponemos como salida el led
    pinMode(ledN, OUTPUT);  //Ponemos como salida el led
    pinMode(btnConf, INPUT); //Ponemos como entrada el boton de configuracion
  
    for (int i = 0; i < 5; i++) {  // Se crea for para recorrer los espacios de almacenamiento del array y de la memoria eeprom
      CLAVE_MAESTRA[i] = EEPROM.read(i); //SE lee la clave guardada en eeprom y se asigna a la clave maestra
                      }
                }
  
  void loop() {
    if (digitalRead(btnConf)){ //Pregunta si se mantiene presionado el boton de configuracion
      configuracion();        //Se manda llamar la funcion llamada configuracion 
         } 
         
      else {            //Si no está presionada la tecla configuracion hace esto
          TECLA = teclado.getKey(); //SE lee la tecla presionada y se asigna el valor a tecla
      if (TECLA) {    //Comprueba que este presionandose una tecla
        CLAVE[INDICE] = TECLA; //SE va guardando cada tecla en el array clave
        INDICE++;    // SE incrementa el valor de indice en 1 para recorrer los distintos espacios del array
        Serial.print(TECLA); //Imprime en el monitor serial la tecla que se presionó
             }
  
      if (INDICE == 4) {    //Si el indice llega al limite de teclas presionadas
      if (strcmp(CLAVE, CLAVE_MAESTRA) == 0) { //Compara ambas cadenas de caracteres de uno por uno y si son iguales a cero indica que son iguales
        Serial.println(" Correcta"); //imprime en monitor serial que la clave es correcta
        digitalWrite(ledC, HIGH);   //enciende led indicador de clave correcta
        digitalWrite(ledI, LOW);    //apaga led indicador de clave incorrecta
                              } 
      else {      //Si no es correcta la clave
      Serial.println(" Incorrecta"); //imprime que es incorrecta
      digitalWrite(ledC, LOW);    //apaga led indicador de clave correcta
      digitalWrite(ledI, HIGH);   //enciende led indicador de clave incorrecta
      
            }
       INDICE = 0;  //reinicia el indice una vez que se llego ya al limite
           }
         }
      }
  
  void configuracion() { //Se crea una funcion llamada configuracion
    
    memset(CLAVE_MAESTRA, 0, 5); // funcion que almacena ceros en los 5 espacios del array llamado clave maestra
    memset(CLAVE, 0, 5);    // funcion que almacena ceros en los 5 espacios del array llamado clave 
    
    INDICE = 0;  //reiniciamos el indice
    INDICE2 = 0;    //reiniciamos el indice2
    
    while (digitalRead(btnConf)) {  //mientras que el boton de configuracion se mantenga presionado...
          TECLA = teclado.getKey(); // asignamos la tecla presionada a la variable tecla
          
      if (TECLA){  // comprueba que la tecla haya sido presionada
        CLAVE_MAESTRA[INDICE2] = TECLA; // se asigna la tecla presionada al array
        INDICE2++; // incrementa el indice para recorrer los espacios del array
        Serial.print(TECLA); // imprime la tecla presionada en el monitor serial 
                }
                
      if (INDICE2 == 4) {  // si el indice llega al limite que es 4...
         INDICE2 = 0;  //Reiniciamos el indice
         Serial.println(" CAMBIADA"); // imprime en el monitor serial que cambió la clave
         for (int i = 0; i < 5; i++) { //Se crea for para recorrer cada espacio de almacenamiento en eeprom y en array
          EEPROM.write(i, CLAVE_MAESTRA[i]); //Se escribe en cada espacio de la memoria la clave
          delay (250);    //delay para que termine de guardar satisfactoriamente la clave en eeprom
                           }
                      }
                      
      digitalWrite(ledN, HIGH); //enciende led de configuracion siempre y cuando este presionado el boton correspondiente
                  }
      digitalWrite(ledN, LOW);// apaga led de configuracion
              }
