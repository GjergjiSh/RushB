#include <Servo.h>
#define LEFTWHEEL 12
#define RIGHTWHEEL 13
#define CAMERA 11

Servo LeftServo;
Servo RightServo;
Servo TopServo;

//Tagged string sent through serial
String driver_wish;

//Values for the servos extracted from driver wish
String top_servo;
String left_servo;
String right_servo;

void setup()
{
  Serial.begin(50000);
  LeftServo.attach(LEFTWHEEL);
  RightServo.attach(RIGHTWHEEL);
  TopServo.attach(CAMERA);
  stop_servos();
}

void loop()
{
   if (Serial.available() > 0) {
    read_driver_wish();
    control_servos();
   } else {
    stop_servos();
   }
}

void stop_servos()
{
    LeftServo.write(90);
    RightServo.write(90);
    TopServo.write(90);
}

void control_servos()
{
  LeftServo.write(left_servo.toInt());
  RightServo.write(right_servo.toInt());
  TopServo.write(top_servo.toInt());
}

void read_driver_wish()
{
  driver_wish = Serial.readStringUntil('\n');
  left_servo = extract(driver_wish, "!", "@");
  right_servo = extract(driver_wish, "@", "#");
  top_servo = extract(driver_wish, "#", "$");
}

void print_driver_wish()
{
  Serial.println("Left Servo: " + left_servo);
  Serial.println("Right Servo: " + right_servo);
  Serial.println("Top Servo: " + top_servo);
}

String extract(String str, String start, String finish)
{
  int locStart = str.indexOf(start);
  if (locStart == -1)
    return "";
  locStart += start.length();
  int locFinish = str.indexOf(finish, locStart);
  if (locFinish == -1)
    return "";
  return str.substring(locStart, locFinish);
}
