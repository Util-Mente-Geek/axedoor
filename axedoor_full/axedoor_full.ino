/** AxeDoor
 * Codigo para Buzzer
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
#include <Keypad.h>     // importa libreria Keypad

const byte FILAS = 2;     // define numero de filas
const byte COLUMNAS = 2;    // define numero de columnas

char keys[FILAS][COLUMNAS] = {    // define la distribucion de teclas
  {'1','2'},
  {'3','4'},
};

byte pinesFilas[FILAS] = {13,12};   // pines correspondientes a las filas
byte pinesColumnas[COLUMNAS] = {11,10}; // pines correspondientes a las columnas

Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS);  // crea objeto

char TECLA;       // almacena la tecla presionada
char CLAVE[5];        // almacena en un array 6 digitos ingresados
char CLAVE_MAESTRA[5];   // almacena en un array la contraseña maestra
byte INDICE = 0;      // indice del array
byte INDICE2 = 0;
int ledC = 9;
int ledI = 8;
int btnConf = 7;
  
void setup(){
 Serial.begin(9600);      // inicializa comunicacion serie
 pinMode(ledC, OUTPUT);
 pinMode(ledI, OUTPUT);
 pinMode(btnConf, INPUT);
}

void loop(){
  configuracion();
  
  TECLA = teclado.getKey();   // obtiene tecla presionada y asigna a variable
  if (TECLA)        // comprueba que se haya presionado una tecla
  {
    CLAVE[INDICE] = TECLA;    // almacena en array la tecla presionada
    INDICE++;       // incrementa indice en uno
    Serial.print(TECLA);    // envia a monitor serial la tecla presionada
  }


  if(INDICE == 4)       // si ya se almacenaron los 6 digitos
  {
    if(!strcmp(CLAVE, CLAVE_MAESTRA)){   // compara clave ingresada con clave maestra
      Serial.println(" Correcta");  // imprime en monitor serial que es correcta la clave
      digitalWrite(ledC, HIGH);
      digitalWrite(ledI, LOW);
      delay(1000);
      }
    else{
      Serial.println(" Incorrecta");  // imprime en monitor serial que es incorrecta la clave
      digitalWrite(ledC, LOW);
      digitalWrite(ledI, HIGH);
      delay(1000);
    }
    INDICE = 0;
  }
}

void configuracion (){
  while (digitalRead(btnConf)){
    CLAVE_MAESTRA[5] = {"0,0,0,0,0"} ;
    TECLA = teclado.getKey();
    if (TECLA){
    CLAVE_MAESTRA[INDICE2] = TECLA;
    INDICE2++;
    Serial.print(TECLA);
      }
      if(INDICE2 == 4){
      INDICE2 = 0;
      Serial.println(" CAMBIADA");
      }
      digitalWrite(ledC, HIGH);
      digitalWrite(ledI, HIGH);
    }
    digitalWrite(ledC, LOW);
    digitalWrite(ledI, LOW);
  }
