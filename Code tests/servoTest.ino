#include <Servo.h>

#define num_of_servos 8
#define num_of_steps 1
#define delay_between_steps 15

Servo servo[num_of_servos];  // create Servo object as an array
int pins[num_of_servos] = {2, 3, 4, 5, 6, 7, 8, 9};
int pos = 0;

void setup() {
  for (int i = 0; i < 8; i++){
    servo[i].attach(pins[i]);
  }
  
}

void loop() {

  for (pos = 0; pos <= 180; pos += num_of_steps) {
    for (int i = 0; i < num_of_servos; i++) {
      servo[i].write(pos);
    }
    delay(delay_between_steps);
  }

  for (pos = 180; pos >= 0; pos -= num_of_steps) {
    for (int i = 0; i < num_of_servos; i++) {
      servo[i].write(pos);
    }
    delay(delay_between_steps);
  }

}
