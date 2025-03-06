#include <Time.h>
#include <TimeLib.h>

#include <List.hpp>

int pin1 = 39;
int pin2 = 41;
int pin3 = 43;
int pin4 = 45;
int pin5 = 47;
int pin6 = 49;
int pin7 = 51;
int pin8 = 53;

int button1 = 12;
int button2 = 13;

enum Outputs
{
  Test1,
  Test2,
  Test3,
  Test4,
  Test5,
  Test6,
  Test7,
  Test8,
};

class Mocktail {
  public:
    String Name;
    List<Outputs> Ingredients;
    List<int> Ratios;

    Mocktail(String name, List<Outputs> ingredients, List<int> ratios)
      : Name(name), Ingredients(ingredients), Ratios(ratios) {}
};

  Mocktail mocktails[3] = {
    {"", {}, {}},
    {"", {}, {}},
    {"", {}, {}}
  };

void setup() {
  pinMode(pin1, OUTPUT); //sætter pin 39 til at være output
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(pin5, OUTPUT);
  pinMode(pin6, OUTPUT);
  pinMode(pin7, OUTPUT);
  pinMode(pin8, OUTPUT);
}

int flowspeed = 50;
int cupAmount = 0;
const int cupSize = 250;

void pour(int index, int time)
{
  
}

void pourButton(int index)
{
  Mocktail mocktail = mocktails[i];

  for (int i = 0; i < sizeof(mocktail.Ingredients) / sizeof(mocktails.Ingredients[0]); i++)
  {
    int index = 0;
    for (int j = 0; j < 8; j++)
    {
      if (mocktail.Ingredients[i] == Outputs(j))
      {
        index = j;
      }
    }

    int amount = cupSize / 100 * mocktail.Ratios[i];

    pour(index, round(amount / flowspeed * 100));
  };
}

void loop() {
  if (digitalRead(button1) == HIGH)
  {
    pourButton(0);
  }
  if (digitalRead(button2) == HIGH)
  {
    pourButton(1);
  }

  /*
  digitalWrite(pin1, HIGH);
  delay(50);
  digitalWrite(pin2, HIGH);
  delay(50);
  digitalWrite(pin3, HIGH);
  delay(50);
  digitalWrite(pin4, HIGH);
  delay(50);
  digitalWrite(pin1, LOW);
  delay(50);
  digitalWrite(pin2, LOW);
  delay(50);
  digitalWrite(pin3, LOW);
  delay(50);
  digitalWrite(pin4, LOW);
  delay(50);
  */
}