#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <ctime>
#include <chrono>
#include <thread>
#include <fstream>
#include <time.h>

using namespace std;

class gpioPin {
  int Number;
  int Value;
  string Mode;
};

class gpio {
  const string sysP = "/sys/class/gpio";
  const string expP = sysP+"/export";
  const string uneP = sysP+"/unexport";
  const string pinP = sysP+"/gpio";
  const string valP = "/value";
  const string dirP = "/direction";

  void expVal(string path, string val);
 public:
  const string OUT = "out";
  const string IN = "in";

  const int UP = 1;
  const int DOWN = 0;
  
  //void openPin(gpioPin &pin);
  //void closePin(gpioPin &pin);
  //void setPin(gpioPin &pin);
  //void readPin(gpioPin &pin);

  void sleep(long int mil_delay);
  
  int openPin(int pinNumber, string mode);
  int closePin(int pinNumber);
  int setPin(int pinNumber, int state);
  int readPin(int pinNumber);
};

void gpio::sleep(long int mil_delay)
{
  double sec_delay = mil_delay/1000;
  string cmd = "sleep "+to_string(sec_delay);
  char c_cmd[(const int)cmd.size()];

  for(int i = 0; i < cmd.size()+1; i++)
    {
      c_cmd[i] = cmd[i];
    }

  system(c_cmd);
}

void gpio::expVal(string path, string value)
{
  ofstream fout;
  
  fout.open(path);
  fout<<value;
  fout.close();
}

int gpio::openPin(int pinNumber, string mode)
{
  string pNum = to_string(pinNumber);
  expVal(expP, pNum);
  expVal(pinP+pNum+dirP, mode);
  return 0;
}

int gpio::closePin(int pinNumber)
{
  string pNum = to_string(pinNumber);
  expVal(uneP, pNum);
  return 0;
}

int gpio::setPin(int pinNumber, int state)
{
  string pNum = to_string(pinNumber);
  expVal(pinP+pNum+valP, to_string(state));
  return 0;
}

int gpio::readPin(int pinNumber)
{
  string pNum = to_string(pinNumber);
  ifstream fin;
  int val = -1;
  
  fin.open(pinP+pNum+valP);
  if(!fin)
    {
      return -1;
    }
  fin>>val;
  return val;
}

//gpio::void openPin(gpioPin &pin);
//gpio::void closePin(gpioPin &pin);
//gpio::void setPin(gpioPin &pin);
//gpio::void readPin(gpioPin &pin);
