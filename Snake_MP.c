/* Ruler 1         2         3         4         5         6         7        */

/******************************* DISPRO PROJECT *******************************/

/* ------------------------------- FINAL STAGE ------------------------------ */
/* ----------------------------------- ING.  -------------------------------- */
/* -------------- DANIEL ALVAREZ, JAVIER FRANCO, JULIAN LOPEZ --------------- */


/* ------------------------- Definition of Varibles ------------------------- */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args) write(args);
#else
#define printByte(args) print(args, BYTE);
#endif

#define MAX_COL 14
#define MAX_ROW 15


#define MAX_SNAKES 5
#define MAX_SNAKE 182
#define NUM_SNAKE 1

/* -------------------------------------------------------------------------- */
/* ----------------------- Music Finite State MAchine ----------------------- */

// musica
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Tone Frequencies SMB
#define QT 0
#define E6 1319 / 2
#define G6 1568 / 2
#define A6 1760 / 2
#define AS6 1865 / 2
#define B6 1976 / 2
#define C7 2093 / 2
#define D7 2349 / 2
#define E7 2637 / 2
#define F7 2794 / 2
#define G7 3136 / 2
#define A7 3520 / 2
/*
  // Define tone frequencies Snake
  #define QT 0
  #define C4 261.63
  #define D4 293.66
  #define E4 329.63
  #define F4 349.23
  #define G4 392.00
  #define A4 440.00
  #define B4 493.88
  #define C5 523.25
  #define D5 587.33


// Define tone frequencies for London Bridge
#define QT 0
#define E6 1319*4
#define G6 1568*4
#define A6 1760*4
#define AS6 1865*4
#define B6 1976*4
#define C7 2093*4
#define D7 2349*4
#define E7 2637*4
#define F7 2794*4
#define G7 3136*4
#define A7 3520*4
#define F6 1397*4
*/
typedef enum {
  Validar,
  Silencio,
  High,
  Down,
  Actual,
  Delay_Note
} STATE_BUZZ;

typedef struct
{
  unsigned int tone_freq;
  unsigned long duration;
} NOTE;

#define Song_pin 8
#define Song_pause 0.7

// Definir La Melodia
NOTE Song[] = {
  { E7, 80 }, { E7, 80 }, { QT, 80 }, { E7, 80 }, { QT, 80 }, { C7, 80 }, { E7, 80 }, { QT, 80 }, { G7, 80 }, { QT, 80 }, { QT, 80 }, { QT, 80 }, { G6, 80 }, { QT, 80 }, { QT, 80 }, { QT, 80 },

  { C7, 80 },
  { QT, 80 },
  { QT, 80 },
  { G6, 80 },
  { QT, 80 },
  { QT, 80 },
  { E6, 80 },
  { QT, 80 },
  { QT, 80 },
  { A6, 80 },
  { QT, 80 },
  { B6, 80 },
  { QT, 80 },
  { AS6, 80 },
  { A6, 80 },
  { QT, 80 },

  { G6, 110 },
  { E7, 110 },
  { G7, 110 },
  { A7, 80 },
  { QT, 80 },
  { F7, 80 },
  { G7, 80 },
  { QT, 80 },
  { E7, 80 },
  { QT, 80 },
  { C7, 80 },
  { D7, 80 },
  { B6, 80 },
  { QT, 80 },
  { QT, 80 },

  { C7, 80 },
  { QT, 80 },
  { QT, 80 },
  { G6, 80 },
  { QT, 80 },
  { QT, 80 },
  { E6, 80 },
  { QT, 80 },
  { QT, 80 },
  { A6, 80 },
  { QT, 80 },
  { B6, 80 },
  { QT, 80 },
  { AS6, 80 },
  { A6, 80 },
  { QT, 80 },

  { G6, 110 },
  { E7, 110 },
  { G7, 110 },
  { A7, 80 },
  { QT, 80 },
  { F7, 80 },
  { G7, 80 },
  { QT, 80 },
  { E7, 80 },
  { QT, 80 },
  { C7, 80 },
  { D7, 80 },
  { B6, 80 },
  { QT, 80 },
  { QT, 80 }
};
/*
  // Melody matrix for the snake background song
  NOTE Song[] = {
  {E4, 250}, {G4, 250}, {C5, 250}, {D4, 250},
  {E4, 250}, {G4, 250}, {C5, 250}, {D4, 250},
  {E4, 250}, {G4, 250}, {C5, 250}, {D4, 250},
  {G4, 500}, {B4, 250}, {D5, 250},
  {C5, 500}, {A4, 250}, {F4, 250},
  {E4, 500}, {C4, 250}, {E4, 250}, {G4, 250},
  {D4, 500}, {G4, 250}, {B4, 250},
  {C5, 500}, {A4, 250}, {F4, 250},
  {E4, 1000}
  };


// Melody matrix for "London Bridge Is Falling Down"
NOTE Song[] = {
  { G6, 500 }, { F6, 250 }, { E6, 250 }, { F6, 250 }, { G6, 500 }, { A6, 250 }, { G6, 250 }, { F6, 500 }, { E6, 250 }, { F6, 250 }, { G6, 500 }, { G6, 500 }, { F6, 250 }, { E6, 250 }, { F6, 250 }, { G6, 500 }, { A6, 250 }, { G6, 250 }, { F6, 500 }, { E6, 250 }, { F6, 250 }, { G6, 500 }, { G6, 500 }, { F6, 250 }, { E6, 250 }, { F6, 250 }, { G6, 500 }, { A6, 250 }, { G6, 250 }, { F6, 500 }, { E6, 250 }, { F6, 250 }, { G6, 1000 }
};
*/
unsigned int Song_size = (sizeof(Song) / sizeof(NOTE));

void songfsm(NOTE *notes);
STATE_BUZZ Buzzer_State;

void songfsm(NOTE(*notes)) {
  static long Previous_Time;
  static long Current_Time;

  static long Time_High;
  static long Time_Initial_Buzzer;
  static long Time_Initial_High;
  static long Time_Initial_Low;
  static long Time_Now;

  static int note_counter = 0;

  switch (Buzzer_State) {
    case Validar:

      if (note_counter < Song_size) {

        Previous_Time = micros();
        Buzzer_State = Silencio;
      } else {

        note_counter = 0;
      }
      break;
    case Silencio:

      if ((*(notes + note_counter)).tone_freq != QT) {

        Time_Initial_Buzzer = micros();
        Buzzer_State = High;
      } else {

        Current_Time = micros();

        if (Current_Time - Previous_Time < (*(notes + note_counter)).duration * 1000) {
          Buzzer_State = Silencio;
        } else {

          Previous_Time = micros();
          Buzzer_State = Delay_Note;
        }
      }
      break;
    case High:

      Time_High = 1000000 / ((*(notes + note_counter)).tone_freq * 2);

      Time_Now = micros();

      digitalWrite(Song_pin, HIGH);

      if (Time_Now - Time_Initial_Buzzer > (*(notes + note_counter)).duration * 1000) {
        Buzzer_State = Delay_Note;
        Previous_Time = micros();
      } else {

        Time_Initial_High = micros();
        Buzzer_State = Actual;
      }
      break;
    case Actual:

      Time_Now = micros();

      if (Time_Now - Time_Initial_High > Time_High) {

        Time_Initial_Low = micros();
        Buzzer_State = Down;
      } else {
        Buzzer_State = Actual;
      }
      break;

    case Down:
      Time_Now = micros();
      digitalWrite(Song_pin, LOW);

      if (Time_Now - Time_Initial_Low > 1000000 / (*(notes + note_counter)).tone_freq - Time_High) {
        Buzzer_State = High;
      } else {
        Buzzer_State = Down;
      }
      break;

    case Delay_Note:
      digitalWrite(Song_pin, LOW);
      Current_Time = micros();
      if (Current_Time - Previous_Time > (*(notes + note_counter)).duration * 1000 * Song_pause) {
        note_counter++;
        Buzzer_State = Validar;
      } else {
        Buzzer_State = Delay_Note;
      }
      break;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* -------------------------------------------------------------------------- */
/* ------------------------ LCD Finite State Machine ------------------------ */

uint8_t MZ_F0C0[8];
uint8_t MZ_F0C1[8];
uint8_t MZ_F0C2[8];
uint8_t MZ_F0C3[8];
uint8_t MZ_F0C4[8];
uint8_t MZ_F0C5[8];
uint8_t MZ_F0C6[8];

uint8_t MZ_F1C0[8];
uint8_t MZ_F1C1[8];
uint8_t MZ_F1C2[8];
uint8_t MZ_F1C3[8];
uint8_t MZ_F1C4[8];
uint8_t MZ_F1C5[8];
uint8_t MZ_F1C6[8];

uint8_t *MZ_LCD_TOTAL[14] = { MZ_F0C0,
                              MZ_F0C1,
                              MZ_F0C2,
                              MZ_F0C3,
                              MZ_F0C4,
                              MZ_F0C5,
                              MZ_F0C6,
                              MZ_F1C0,
                              MZ_F1C1,
                              MZ_F1C2,
                              MZ_F1C3,
                              MZ_F1C4,
                              MZ_F1C5,
                              MZ_F1C6 };

int Game_Board[MAX_ROW + 1][MAX_COL + 1] = { { 0 } };

// State para cad auna de las snakes

typedef enum {
  WAIT,
  VALIDATION,
  MOVES,
  APPLE,
  RAN_APPLE,
  SOUND,
  DEAD,
  UPDATE
} STATES_SNAKE;

typedef enum {
  CERO,
  ONE,
  TWO,
  THREE,
  FOUR
} STATE_CONTROL;

//Class for the snakes given
typedef struct
{
  int size;
  int life;  // 1 Nothing 0 Dead 2 Apple
  int mov;   // 1(up),2(down),3(left),4(right)
  int i;
  int deltaX;
  int deltaY;
  int y_desired;
  int x_desired;
  int pulsador1;  //// Arriba
  int pulsador2;  //// Derecha
  int pulsador3;  //// Izquierda
  int pulsador4;  //// Abajo
  bool ValPul1;
  bool ValPul2;
  bool ValPul3;
  bool ValPul4;
  int pulsador;
  long previous;
  long current;

  int score;

  int posx[MAX_SNAKE];
  int posy[MAX_SNAKE];
  STATES_SNAKE state;
  STATE_CONTROL state_control;

  // dead and food sound
  long periodo;
  long frecuencia;
  long tiempoEncendido;
  long tiempoInicio;
  long duracion;

} Snake;

void Matriz_to_LCD(int Game_Board[MAX_ROW + 1][MAX_COL + 1], Snake *jugador);

LiquidCrystal_I2C lcd(0x27, 20, 4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void Matriz_to_LCD(int Game_Board[MAX_ROW + 1][MAX_COL + 1], Snake *jugador) {

  static int intaux, exponente, contadorfilas = 0, contadorfilas_PX = 0;
  static uint8_t HexAux;

  static int state, LCD_F = 0, LCD_C, LCD_PX_F, LCD_PX_C, contador_digito = 0;

  switch (state) {
    case 0:
      if (LCD_F < 2) {
        LCD_C = 0;
        state = 1;
      } else {
        LCD_F = 0;
        state = 0;
      }
      break;
      {
        case 1:
          if (LCD_C < 3) {
            LCD_PX_F = 0 + 8 * LCD_F;
            state = 2;
          } else {
            LCD_F++;
            state = 0;
          }
          break;
        case 2:
          if (LCD_PX_F < 8 + 8 * LCD_F) {
            LCD_PX_C = 0 + 5 * LCD_C;
            state = 3;
          } else {
            LCD_C++;
            contadorfilas_PX = 0;

            if (contador_digito == 0) {
              lcd.createChar(0, MZ_F0C0);
              lcd.setCursor(1, 0);
              lcd.printByte(0);
              contador_digito++;

              if ((jugador + 0)->life == 0) {
                lcd.setCursor(5, 0);
                lcd.print("P1 ");
                lcd.print((jugador + 0)->score);
                lcd.print(" DEAD");
              } else {
                lcd.setCursor(5, 0);
                lcd.print("Score 1:");
                lcd.print((jugador + 0)->score);
              }

            } else if (contador_digito == 1) {
              lcd.createChar(1, MZ_F0C1);
              lcd.setCursor(2, 0);
              lcd.printByte(1);
              contador_digito++;
            } else if (contador_digito == 2) {
              lcd.createChar(2, MZ_F0C2);
              lcd.setCursor(3, 0);
              lcd.printByte(2);
              contador_digito++;

              if ((jugador + 1)->life == 0) {
                lcd.setCursor(5, 1);
                lcd.print("P2 ");
                lcd.print((jugador + 1)->score);
                lcd.print(" DEAD");
              } else {
                lcd.setCursor(5, 1);
                lcd.print("Score 2:");
                lcd.print((jugador + 1)->score);
              }

            } else if (contador_digito == 3) {
              lcd.createChar(3, MZ_F1C0);
              lcd.setCursor(1, 1);
              lcd.printByte(3);
              contador_digito++;
            } else if (contador_digito == 4) {
              lcd.createChar(4, MZ_F1C1);
              lcd.setCursor(2, 1);
              lcd.printByte(4);
              contador_digito++;
            } else if (contador_digito == 5) {
              lcd.createChar(5, MZ_F1C2);
              lcd.setCursor(3, 1);
              lcd.printByte(5);
              contador_digito = 0;
            }

            if ((jugador + 0)->life == 0 && (jugador + 1)->life == 0) {
              lcd.clear();
              state = 4;
            } else {
              state = 1;
            }
            /*
            
            lcd.createChar(0, MZ_F0C0);
            lcd.createChar(1, MZ_F0C1);
            lcd.createChar(2, MZ_F0C2);
            lcd.createChar(3, MZ_F1C0);
            lcd.createChar(4, MZ_F1C1);
            lcd.createChar(5, MZ_F1C2);

            lcd.setCursor(1, 0);
            lcd.printByte(0);
            lcd.printByte(1);
            lcd.printByte(2);
            lcd.setCursor(1, 1);
            lcd.printByte(3);
            lcd.printByte(4);
            lcd.printByte(5);
            */
          }
          break;
        case 3:
          if (LCD_PX_C < 5 + 5 * LCD_C) {
            //CHCHC1

            if (Game_Board[LCD_PX_F][LCD_PX_C] != 0) {

              exponente = ((LCD_PX_C - ((LCD_C * 5) - 1)) - 1);

              if (exponente == 0) {
                intaux += 16;
              } else if (exponente == 1) {
                intaux += 8;
              } else if (exponente == 2) {
                intaux += 4;
              } else if (exponente == 3) {
                intaux += 2;
              } else if (exponente == 4) {
                intaux += 1;
              }
            }

            LCD_PX_C++;
            state = 3;
          } else {
            //CHCHCHC22

            HexAux = static_cast<uint8_t>(intaux);
            //Serial.println(HexAux);
            //Serial.print("Valor en hexadecimal: 0x%02X\n", intaux);
            //Serial.print("Valor en hexadecimal: 0x");
            //Serial.print(intaux, HEX);
            //Serial.println();
            if (LCD_F == 0) {
              MZ_LCD_TOTAL[LCD_C][contadorfilas_PX] = HexAux;
            } else if (LCD_F == 1) {
              MZ_LCD_TOTAL[LCD_C + 7][contadorfilas_PX] = HexAux;
            }

            intaux = 0;
            HexAux = 0;
            contadorfilas_PX++;

            LCD_PX_F++;
            state = 2;
          }
          break;

        case 4:
          lcd.setCursor(2, 0);
          lcd.print("P1");
          lcd.setCursor(2, 1);
          lcd.print((jugador + 0)->score);

          lcd.setCursor(6, 0);
          lcd.print("GAME");
          lcd.setCursor(6, 1);
          lcd.print("OVER");

          lcd.setCursor(12, 0);
          lcd.print("P2");
          lcd.setCursor(12, 1);
          lcd.print((jugador + 1)->score);

          break;
      }
  }
}



void cambiar_mz() {
  static unsigned long tiempoActual = millis(), tiempoAnterior = 0;  // Obtener el tiempo actual
  static int count;
  // Verificar si ha pasado 1 segundo desde la última actualización
  tiempoActual = millis();
  long x = tiempoActual - tiempoAnterior;
  //Serial.println(tiempoAnterior);
  if (tiempoActual - tiempoAnterior >= 500) {
    // Actualizar la matriz
    if (count < 15) {
      Game_Board[4][count] = 1;
      count++;
    } else {
      count = 0;
    }

    tiempoAnterior = tiempoActual;
  }
}

void cambiar_mz2() {
  static unsigned long tiempoActual = millis(), tiempoAnterior = 0;  // Obtener el tiempo actual
  static int count;
  // Verificar si ha pasado 1 segundo desde la última actualización
  tiempoActual = millis();
  long x = tiempoActual - tiempoAnterior;
  //Serial.println(tiempoAnterior);
  if (tiempoActual - tiempoAnterior >= 500) {
    // Actualizar la matriz
    if (count < 15) {
      Game_Board[11][count] = 1;
      count++;
    } else {
      count = 0;
    }

    tiempoAnterior = tiempoActual;
  }
}

/* -------------------------------------------------------------------------- */
/* ---------------------- Snake Movement State Machine ---------------------- */

// x filas, y columnas
// int Game_Board[MAX_ROW + 1][MAX_COL + 1];

typedef struct
{
  long interval;
  int comidaX;
  int comidaY;
  int numSnakes;
  int isnake;
  int numControl;
  int iControl;
} Variable;

Snake snakes[MAX_SNAKES];
Variable variables;

void Juego(Snake *jugador, Variable *variab);
void mov_snake(Snake *jugador, Variable *variab);
void clear_scr(int Game_Board[MAX_ROW + 1][MAX_COL + 1]);
void random_apple(Variable *variab);
void generarTono(Snake *jugador, Variable *variab);

// Game funtions
void My_delay(Variable *pointer, Snake *jugador);
void Validation(Snake *jugador, Variable *pointer);
void Movement(Variable *variab, Snake *jugador);
void apple(Variable *variab, Snake *jugador);
void kill_snake(Snake *jugador, Variable *variab);
void update_scr(Snake *jugador, int Game_Board[MAX_ROW + 1][MAX_COL + 1], Variable *variab);
void Control(Snake *jugador, Variable *variab);

int buzzerPin = 8;

// Funcion usada unicamente para inicializar la matriz
void clear_scr(int Game_Board[MAX_ROW + 1][MAX_COL + 1]) {
  for (int i = 0; i <= MAX_ROW; i++) {
    for (int j = 0; j <= MAX_COL; j++) {
      if (i == 0 || i == MAX_ROW || j == 0 || j == MAX_COL) {
        Game_Board[i][j] = 1;
      } else {
        Game_Board[i][j] = 0;
      }
    }
  }

  Game_Board[5][5] = 1;
  Game_Board[6][5] = 1;
  Game_Board[7][5] = 1;


  Game_Board[5][9] = 1;
  Game_Board[6][9] = 1;
  Game_Board[7][9] = 1;

  Game_Board[7][6] = 1;
  Game_Board[7][7] = 1;
  Game_Board[7][8] = 1;
}

void generarTono(Snake *jugador, Variable *variab) {
  if (millis() - jugador->tiempoInicio < jugador->tiempoEncendido) {
    digitalWrite(buzzerPin, HIGH);  // Enciende el buzzer durante la primera mitad del período
  } else {
    digitalWrite(buzzerPin, LOW);  // Apaga el buzzer durante la segunda mitad del período
  }
}

void Juego(Snake *jugador, Variable *variab) {
  if (variab->isnake < variab->numSnakes) {
    switch ((jugador + variab->isnake)->state) {

      case WAIT:
        My_delay(variab, (jugador + variab->isnake));
        break;

      case RAN_APPLE:

        random_apple(variab);
        if (Game_Board[variab->comidaX][variab->comidaY] == 0) {
          Game_Board[variab->comidaX][variab->comidaY] = 2;
              variab->interval = variab->interval * 0.9;
          (jugador + variab->isnake)->i = 0;
          (jugador + variab->isnake)->periodo = 1000000 / (jugador + variab->isnake)->frecuencia;  // Calcula el período del tono en microsegundos
          (jugador + variab->isnake)->tiempoEncendido = (jugador + variab->isnake)->periodo / 2;   // Calcula el tiempo de encendido (50% del ciclo)

          (jugador + variab->isnake)->tiempoInicio = millis();  // Registra el tiempo de inicio

          (jugador + variab->isnake)->state = SOUND;
        } else {
          (jugador + variab->isnake)->state = RAN_APPLE;
        }

        break;

      case SOUND:

        if (millis() - (jugador + variab->isnake)->tiempoInicio < (jugador + variab->isnake)->duracion) {
          generarTono((jugador + variab->isnake), variab);
          (jugador + variab->isnake)->state = SOUND;
        } else {
          digitalWrite(buzzerPin, LOW);  // Asegúrate de apagar el buzzer al final
          (jugador + variab->isnake)->i = 0;
          (jugador + variab->isnake)->state = UPDATE;
        }

        break;

      case VALIDATION:
        // Asigno el valor del pulsador de la variable global al Snake
        (jugador + variab->isnake)->mov = (jugador + variab->isnake)->pulsador;

        Validation((jugador + variab->isnake), variab);

        if ((jugador + variab->isnake)->life == 0) {

          (jugador + variab->isnake)->i = 1;
          (jugador + variab->isnake)->state = DEAD;
        } else if ((jugador + variab->isnake)->life == 1) {

          (jugador + variab->isnake)->i = 1;
          (jugador + variab->isnake)->state = MOVES;
        } else {
          (jugador + variab->isnake)->i = 0;
          (jugador + variab->isnake)->score = (jugador + variab->isnake)->score + 1;
          (jugador + variab->isnake)->state = APPLE;
        }
        break;

      case MOVES:

        if ((jugador + variab->isnake)->i <= (jugador + variab->isnake)->size) {

          Movement(variab, (jugador + variab->isnake));
          (jugador + variab->isnake)->state = MOVES;
        } else {
          (jugador + variab->isnake)->i = 0;
          //clear_scr(Game_Board);
          (jugador + variab->isnake)->state = UPDATE;
        }
        break;

      case APPLE:

        if ((jugador + variab->isnake)->i <= (jugador + variab->isnake)->size) {
          Movement(variab, (jugador + variab->isnake));
          (jugador + variab->isnake)->state = APPLE;
        } else {
          (jugador + variab->isnake)->size++;
          (jugador + variab->isnake)->state = RAN_APPLE;
        }
        break;

      case DEAD:

        if ((jugador + variab->isnake)->i <= (jugador + variab->isnake)->size) {
          kill_snake((jugador + variab->isnake), variab);
          (jugador + variab->isnake)->state = DEAD;
        } else {
          (jugador + variab->isnake)->i = 0;
          //clear_scr(Game_Board);
          (jugador + variab->isnake)->state = UPDATE;
        }
        break;

      case UPDATE:
        Serial.println("///////////////77");
        if ((jugador + variab->isnake)->i < (jugador + variab->isnake)->size) {
          update_scr((jugador + variab->isnake), Game_Board, variab);
          (jugador + variab->isnake)->state = UPDATE;
        } else {
          (jugador + variab->isnake)->i = 0;
          (jugador + variab->isnake)->state = WAIT;
        }

        break;
    }
    (variab->isnake)++;
  } else {
    variab->isnake = 0;
  }
}
// Matriz 0= nada, 1 = serpiente, 2 = manzana
void Validation(Snake *jugador, Variable *pointer) {

  if (jugador->mov == 1) {
    if (Game_Board[jugador->posx[0] - 1][jugador->posy[0]] == 1) {
      jugador->life = 0;
    } else if (Game_Board[jugador->posx[0] - 1][jugador->posy[0]] == 2) {
      jugador->life = 2;
    } else
      jugador->life = 1;
  }
  if (jugador->mov == 2) {
    if (Game_Board[jugador->posx[0] + 1][jugador->posy[0]] == 1) {
      jugador->life = 0;
    } else if (Game_Board[jugador->posx[0] + 1][jugador->posy[0]] == 2) {
      jugador->life = 2;
    } else
      jugador->life = 1;
  }

  if (jugador->mov == 3) {

    jugador->y_desired = jugador->posy[0] - 1;
    jugador->x_desired = jugador->posx[0];

    if (Game_Board[jugador->x_desired][jugador->y_desired] == 0)
      jugador->life = 1;

    else if (Game_Board[jugador->x_desired][jugador->y_desired] == 2)
      jugador->life = 2;

    else
      jugador->life = 0;
  }
  if (jugador->mov == 4) {

    jugador->y_desired = jugador->posy[0] + 1;
    jugador->x_desired = jugador->posx[0];

    if (Game_Board[jugador->x_desired][jugador->y_desired] == 0) {
      jugador->life = 1;
    }

    else if (Game_Board[jugador->x_desired][jugador->y_desired] == 2)
      jugador->life = 2;

    else
      jugador->life = 0;
  }
}

void My_delay(Variable *pointer, Snake *jugador) {

  if (jugador->current - jugador->previous < pointer->interval) {
    jugador->current = millis();
  } else {
    jugador->current = jugador->previous = millis();
    jugador->state = jugador->state + 1;
  }
}

void Movement(Variable *variab, Snake *jugador) {
  // Movimiento
  //    1
  //  3    4
  //    2

  switch (jugador->mov) {
    case 1:
      jugador->deltaX = -1;
      jugador->deltaY = 0;
      mov_snake(jugador, variab);
      break;
    case 2:
      jugador->deltaX = 1;
      jugador->deltaY = 0;
      mov_snake(jugador, variab);
      break;
    case 3:
      jugador->deltaX = 0;
      jugador->deltaY = -1;
      mov_snake(jugador, variab);
      break;
    case 4:

      jugador->deltaX = 0;
      jugador->deltaY = 1;
      mov_snake(jugador, variab);
      break;
  }
}

void mov_snake(Snake *jugador, Variable *variab) {
  if (jugador->state == 2 && jugador->i == 1) {
    Game_Board[jugador->posx[jugador->size - jugador->i]][jugador->posy[jugador->size - jugador->i]] = 0;
  }
  if (jugador->i < jugador->size) {
    jugador->posx[jugador->size - jugador->i] = jugador->posx[jugador->size - (jugador->i + 1)];
    jugador->posy[jugador->size - jugador->i] = jugador->posy[jugador->size - (jugador->i + 1)];
    // jugador->posx[jugador->size - (jugador->i - 1)] =  jugador->posx[jugador->size - jugador->i] ;
    // jugador->posy[jugador->size - (jugador->i - 1)] =  jugador->posy[jugador->size - jugador->i] ;
  } else {
    jugador->posx[jugador->size - jugador->i] = jugador->posx[jugador->size - jugador->i] + jugador->deltaX;
    jugador->posy[jugador->size - jugador->i] = jugador->posy[jugador->size - jugador->i] + jugador->deltaY;
  }
  (jugador->i)++;

  Game_Board[variables.comidaX][variables.comidaY] = 2;
}

void random_apple(Variable *variab) {
  variab->comidaX = random(1, MAX_ROW);
  variab->comidaY = random(1, MAX_COL);
}

void kill_snake(Snake *jugador, Variable *variab) {

  Game_Board[jugador->posx[jugador->size - jugador->i]][jugador->posy[jugador->size - jugador->i]] = 0;
  jugador->posx[jugador->size - jugador->i] = 0;
  jugador->posy[jugador->size - jugador->i] = 0;

  (jugador->i)++;
}

void update_scr(Snake *jugador, int Game_Board[MAX_ROW + 1][MAX_COL + 1],
                Variable *variab) {
  Game_Board[jugador->posx[jugador->i]][jugador->posy[jugador->i]] = 1;
  Game_Board[variables.comidaX][variables.comidaY] = 2;
  jugador->i++;
}

/* -------------------------------------------------------------------------- */
/* ---------------------- Control Finite State Machine ---------------------- */

void Control(Snake *jugador, Variable *variab) {
  // estado de los pulsadores
  if (variab->iControl < variab->numControl) {
    (jugador + variab->iControl)->ValPul1 = digitalRead((jugador + variab->iControl)->pulsador1);  //// Arriba
    (jugador + variab->iControl)->ValPul2 = digitalRead((jugador + variab->iControl)->pulsador2);  //// Derecha
    (jugador + variab->iControl)->ValPul3 = digitalRead((jugador + variab->iControl)->pulsador3);  //// Izquierda
    (jugador + variab->iControl)->ValPul4 = digitalRead((jugador + variab->iControl)->pulsador4);  //// Abajo
    // Serial.println(pulsador);
    // Serial.println(variab->ValPul2);
    // Serial.println(variab->ValPul3);
    // Serial.println(variab->ValPul4);

    switch ((jugador + variab->iControl)->state_control) {
      case CERO:
        if ((jugador + variab->iControl)->ValPul1) {
          (jugador + variab->iControl)->state_control = ONE;
        } else if ((jugador + variab->iControl)->ValPul4) {
          (jugador + variab->iControl)->state_control = TWO;
        } else if ((jugador + variab->iControl)->ValPul3) {
          (jugador + variab->iControl)->state_control = THREE;
        } else if ((jugador + variab->iControl)->ValPul2) {
          (jugador + variab->iControl)->state_control = FOUR;
        } else {
          (jugador + variab->iControl)->state_control = CERO;
        }
        break;

      case ONE:
        if ((jugador + variab->iControl)->ValPul1) {
          (jugador + variab->iControl)->state_control = ONE;
        } else {
          (jugador + variab->iControl)->pulsador = 1;
          (jugador + variab->iControl)->state_control = CERO;
        }
        break;
      case TWO:
        if ((jugador + variab->iControl)->ValPul2) {
          (jugador + variab->iControl)->state_control = TWO;
        } else {
          (jugador + variab->iControl)->state_control = CERO;
          (jugador + variab->iControl)->pulsador = 2;
        }
        break;
      case THREE:
        if ((jugador + variab->iControl)->ValPul3) {
          (jugador + variab->iControl)->state_control = THREE;
        } else {
          (jugador + variab->iControl)->state_control = CERO;
          (jugador + variab->iControl)->pulsador = 3;
        }
        break;
      case FOUR:
        if ((jugador + variab->iControl)->ValPul4) {
          (jugador + variab->iControl)->state_control = FOUR;
        } else {
          (jugador + variab->iControl)->state_control = CERO;
          (jugador + variab->iControl)->pulsador = 4;
        }
        break;
    }
    (variab->iControl)++;
  } else {
    variab->iControl = 0;
  }
}

//-----------------------------------------------------------------------------------------------------------------
void setup() {
  // MUSICA
  pinMode(Song_pin, OUTPUT);
  Buzzer_State = Validar;
  // SERIAL
  Serial.begin(9600);

  // LCD
  lcd.init();  // initialize the lcd
  lcd.backlight();

  // JUEGO
  variables.numSnakes = 2;
  variables.isnake = 0;

  variables.numControl = 2;
  variables.iControl = 0;

  for (int k = 0, j = 1; k < variables.numSnakes; k++, j++) {
    snakes[k].posx[0] = random(1, MAX_ROW);
    snakes[k].posy[0] = random(1, MAX_COL);
    snakes[k].mov = 4;
    snakes[k].size = 1;
    snakes[k].life = 1;
    snakes[k].state = UPDATE;
    snakes[k].pulsador = 2;
  }

  variables.interval = 800;
  clear_scr(Game_Board);

  random_apple(&variables);
  while (Game_Board[variables.comidaX][variables.comidaY] == 1) {
    random_apple(&variables);
  }
  Game_Board[variables.comidaX][variables.comidaY] = 2;

  // Pines de los pulsadores ARDUINO
  snakes[0].pulsador1 = 3;  // up 3
  snakes[0].pulsador2 = 4;  // rigth 4
  snakes[0].pulsador3 = 5;  // left 5
  snakes[0].pulsador4 = 6;  // down 6

  snakes[1].pulsador1 = 10;  // up
  snakes[1].pulsador2 = 9;   // rigth
  snakes[1].pulsador3 = 12;  // left
  snakes[1].pulsador4 = 11;  // down

  snakes[0].frecuencia = B6;
  snakes[1].frecuencia = B6;
  snakes[0].duracion = 1000;
  snakes[1].duracion = 1000;

  snakes[0].score = 0;
  snakes[1].score = 0;

  pinMode(snakes[0].pulsador1, INPUT);
  pinMode(snakes[0].pulsador2, INPUT);
  pinMode(snakes[0].pulsador3, INPUT);
  pinMode(snakes[0].pulsador4, INPUT);

  pinMode(snakes[1].pulsador1, INPUT);
  pinMode(snakes[1].pulsador2, INPUT);
  pinMode(snakes[1].pulsador3, INPUT);
  pinMode(snakes[1].pulsador4, INPUT);
}

void loop() {
  Matriz_to_LCD(Game_Board, snakes);

  songfsm(Song);

  // cambiar_mz();
  // cambiar_mz2();

  Control(snakes, &variables);
  Juego(snakes, &variables);
}
