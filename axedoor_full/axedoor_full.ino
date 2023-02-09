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
#define NOTE_C4  262
#define NOTE_G3  196
#define NOTE_A3  220
#define NOTE_B3  247
#define NOTE_C4  262


// notas en melodia
int melodia[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// duración de notas: 4 = cuarto de nota, 8 = octava nota, etc.:
int duracionNota[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void setup() {
//si quieres que se reproduzca una vez poner aquí el codigo del loop
}

void loop() {
    // iteración de notas:
  for (int estaNota = 0; estaNota < 8; estaNota++) {
    // para calcular la duración de la nota, toma un segundo
    // dividido por el tipo de nota.
    //ejemplo. nota negra = 1000 / 4, corchea = 1000/8, etc.
    int duracionNotas = 1000 / duracionNota[estaNota];
    // funcion tone(pin de salida, notas a reproducir, tiempo de duracion por nota);
    tone(8, melodia[estaNota], duracionNotas);
    // para distinguir las notas, establecer un tiempo minimo entre ellas.
    // la duracion de la nota + 30% parece funcionar bien:
    int pausaEntreNotas = duracionNotas * 1.30;
    delay(pausaEntreNotas);
    // detener de sonar el tono:
    noTone(8);  
  }
  //tiempo de espera entre cada iteracion de todas las notas
  delay(500);
}
