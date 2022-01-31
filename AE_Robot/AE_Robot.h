#include "AE_GPIO.h"

using namespace std;
class AE_Motor
{
  int pin1, pin2;
  gpio pins;

 public: 
  void init(int Pin1, int Pin2);
  void go(char dir);
  void stop();
  void close();
};

void AE_Motor::stop()
{
  pins.setPin(pin1, pins.DOWN);
  pins.setPin(pin2, pins.DOWN);
}

void AE_Motor::close()
{
  pins.closePin(pin1);
  pins.closePin(pin2);
}

void AE_Motor::init(int Pin1, int Pin2)
{ 
  pin1 = Pin1;
  pin2 = Pin2;

  pins.openPin(pin1, pins.OUT);
  pins.openPin(pin2, pins.OUT);
}

void AE_Motor::go(char dir)
{
  switch (dir)
    {
    case 'f':
    case'F':
      pins.setPin(pin1, pins.UP);
      pins.setPin(pin2, pins.DOWN);
    break;
    case 'b':
    case 'B':
      pins.setPin(pin2, pins.UP);
      pins.setPin(pin1, pins.DOWN);	
      break;
    default:
      cout<<"Not a valed direction, [F/f]orward or [B/b]ackward"<<endl;
      break;
    }
}

class AE_Robot {
 public:
  AE_Motor motA, motB;
  gpio pins;
  
  void init(int pin1A, int pin1B, int pin2A, int pin2B);
  void head(char dir);
  void turn(char dir);
  void stop();
  void close();
};

void AE_Robot::init(int pin1A, int pin2A, int pin1B, int pin2B) {
  motA.init(pin1A, pin2A);
  motB.init(pin1B, pin2B);
}

void AE_Robot::head(char dir)
{
  motA.go(dir);
  motB.go(dir);
}

void AE_Robot::turn(char dir)
{
  switch (dir)
    {
    case 'l':
    case'L':
      motA.go('f');
      motB.go('b');
      break;
    case 'r':
    case 'R':
      motA.go('b');
      motB.go('f');
      break;
    default:
      cout<<"Not a valed direction, [R/r]ight or [L/l]eft"<<endl;
      break;
    }
}

void AE_Robot::stop()
{
  motA.stop();
  motB.stop();
}

void AE_Robot::close()
{
  motA.close();
  motB.close();
}
