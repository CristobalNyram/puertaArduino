
#include <Keypad.h>     // importa libreria Keypad
#include <Servo.h>
 
Servo myservo;  // crea el objeto servo


const byte FILAS = 4;     // define numero de filas
const byte COLUMNAS = 4;    // define numero de columnas
char keys[FILAS][COLUMNAS] = {    // define la distribucion de teclas
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pinesFilas[FILAS] = {12, 11, 10, 9}; // pines correspondientes a las filas
byte pinesColumnas[COLUMNAS] = {8, 7, 6, 5}; // pines correspondientes a las columnas
int ledRojo = 13;//declaramos el led que enceremos 

Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS);  // crea objeto

char TECLA;       // almacena la tecla presionada
char CLAVE[7];        // almacena en un array 6 digitos ingresados
char CLAVE_MAESTRA[7] = "123456";   // almacena en un array la contraseña maestra
byte INDICE = 0;      // indice del array


void setup()
{
  Serial.begin(9600);      // inicializa comunicacion serie
  pinMode(ledRojo, OUTPUT);
  myservo.attach(0);  // vincula el servo al pin digital 0
  mysero.write(0);//incializamos en 0 angulos
}

void loop() {

  TECLA = teclado.getKey();   // obtiene tecla presionada y asigna a variable
  if (TECLA)        // comprueba que se haya presionado una tecla
  {
    CLAVE[INDICE] = TECLA;    // almacena en array la tecla presionada
    INDICE++;       // incrementa indice en uno
    Serial.print(TECLA);    // envia a monitor serial la tecla presionada
  }

  if (INDICE == 6)      // si ya se almacenaron los 6 digitos
  {
    if (!strcmp(CLAVE, CLAVE_MAESTRA)) { // compara clave ingresada con clave maestra
      Serial.println(" Correcta");  // imprime en monitor serial que es correcta la clave
      digitalWrite(ledRojo, HIGH);
      myservo.write(50);    // ubica el servo a 50 grados(abrimos la puerta
      delay(10000);

    }


    else {
      Serial.println(" Incorrecta");  // imprime en monitor serial que es incorrecta la clave


    }
    INDICE = 0;
    digitalWrite(ledRojo, LOW);//apagamos nuestro foco/led
     myservo.write(0);    //cerramos la puerta/

  }
}
