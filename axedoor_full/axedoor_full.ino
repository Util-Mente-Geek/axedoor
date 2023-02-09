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
char CLAVE_MAESTRA[5] = "1234";   // almacena en un array la contraseña maestra
byte INDICE = 0;      // indice del array
int led = 9;

  
void setup(){
 Serial.begin(9600);      // inicializa comunicacion serie
 pinMode(led, OUTPUT);
}

void loop(){
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
      digitalWrite(led, HIGH);
      }
    else{
      Serial.println(" Incorrecta");  // imprime en monitor serial que es incorrecta la clave
      digitalWrite(led, LOW);
    
    }
    INDICE = 0;
  }
}
