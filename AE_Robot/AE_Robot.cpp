#include "AE_Robot.h"

using namespace std;

int main()
{
  gpio pins;
  AE_Robot Kharis; //phisical pins: {3, 5, 7, 8}
                       //GPIO pins: {2, 3, 4, 14}
  Kharis.init(2, 3, 4, 14);
  Kharis.head('f');
  pins.sleep(5000);
  Kharis.stop();
  
}
