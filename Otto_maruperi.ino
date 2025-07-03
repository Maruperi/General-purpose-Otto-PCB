#include <Otto.h>

/* PIN DEFINITIONS */
// SERVOS
const short int LEFT_LEG = 6;
const short int RIGHT_LEG = 7;
const short int LEFT_FOOT = 8;
const short int RIGHT_FOOT = 9;

const short int BUZZER = 10;

// ULTRASONIC
const short int TRIGGER = 11;
const short int ECHO = 12;

/* OTHER DEFINITIONS */
Otto Otto;
bool messageShown = false;
const bool AUTO_MESSAGE = true;

const short int MOVEMENT_SPEED = 750; //range (500 - 3000)ms, the higher the value the slower the movements

enum Otto_States {
  IDLE,
  WALKING_FORWARD,
  WALKING_BACKWARD,
  TURNING_LEFT,
  TURNING_RIGHT
};

Otto_States currentState = IDLE;

/* AUXILIARY FUNCTIONS DEFINITIONS */
void Serial_UI();

/* MAIN PROGRAM */
void setup() {
  Serial.begin(9600);
  Otto.init(LEFT_LEG, RIGHT_LEG, LEFT_FOOT, RIGHT_FOOT, true, BUZZER);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT); // Cambié a INPUT porque echo es entrada en ultrasonidos

  Otto.home();
}

void loop() {
  Serial_UI();

  switch (currentState) {
    case IDLE:
      Otto.home();
      break;
    case WALKING_FORWARD:
      Otto.walk(1, MOVEMENT_SPEED, 1);
      break;
    case WALKING_BACKWARD:
      Otto.walk(1, MOVEMENT_SPEED, -1);
      break;
    case TURNING_LEFT:
      Otto.turn(2, MOVEMENT_SPEED, 1);
      break;
    case TURNING_RIGHT:
      Otto.turn(2, MOVEMENT_SPEED, -1);
      break;

    default:
      break;
  }
}

/* AUXILIARY FUNCTIONS*/
void Serial_UI() {
  
  if (AUTO_MESSAGE && !messageShown) {
    Serial.println(F("--------------------------------------------------------------------------------------------------------------"));
    Serial.println(F("THIS PROGRAM WAS CREATED BY MARUPERI.\nGithub repository: https://github.com/Maruperi/General-purpose-Otto-PCB"));
    Serial.println(F("All pin definitions and more are in the \"Definitions.h\" file."));
    Serial.println(F("You can disable the previous messages on \"Definitions.h\" file (auto_message)..."));
    Serial.println(F("--------------------------------------------------------------------------------------------------------------"));
    messageShown = true;
  }

  while (Serial.available()) {
    char c = Serial.read();

    if (c == '\n' || c == '\r' || c == 0 || c == ' ') continue;

    switch (c) {
      case 'h':
        Serial.println(F("PRINT HELP COMMAND"));
        break;
      
      case 'i':
        Serial.println(F("Command i -> Idle..."));
        currentState = IDLE;
        break;
      case 'a':
        Serial.println(F("Command a -> Turning left..."));
        currentState = TURNING_LEFT;
        break;
      case 'w':
        Serial.println(F("Command w -> Walking forward..."));
        currentState = WALKING_FORWARD;
        break;
      case 's':
        Serial.println(F("Command s -> Walking backward..."));
        currentState = WALKING_BACKWARD;
        break;
      case 'd':
        Serial.println(F("Command d -> Turning right..."));
        currentState = TURNING_RIGHT;
        break;
      default:
        Serial.print(F("Unknown command: "));
        Serial.println(c);
    }
  }
}
