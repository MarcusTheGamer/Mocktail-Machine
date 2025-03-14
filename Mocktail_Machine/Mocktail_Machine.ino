#include <Vector.h>

#include <Time.h>
#include <TimeLib.h>

#include <List.hpp>

//Opsætning af pins for nemmere tilgåelse.

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
  Kokosmaelk,
  Limejuice,
  Danskvand,
  Grenadine,
  Appelsinjuice,
  BlaaCuracao,
  LemonSoda,
  MangoSirup
};

class Mocktail {
  public:
    String Name;
    static const int MAX_SIZE = 10;
    Outputs Ingredients[MAX_SIZE];
    int Ratios[MAX_SIZE];
    int Size;

    Mocktail(String name, const Outputs ingredients[], const int ratios[], int size) 
      : Name(name), Size(size) {

      for (int i = 0; i < size; i++) {
        Ingredients[i] = ingredients[i];
        Ratios[i] = ratios[i];
      }
    }
};


Outputs Ingredients1[] = { Kokosmaelk, Limejuice, Danskvand, Grenadine };
int Ratios1[] = { 1, 2, 3, 4 };

Outputs Ingredients2[] = { Limejuice, Danskvand };
int Ratios2[] = { 2, 3 };

Outputs Ingredients3[] = { Kokosmaelk, Grenadine };
int Ratios3[] = { 1, 4 };

Mocktail mocktails[3] = {
    Mocktail("Tropical Breeze", Ingredients1, Ratios1, 4),
    Mocktail("Citrus Fizz", Ingredients2, Ratios2, 2),
    Mocktail("Sweet Sunset", Ingredients3, Ratios3, 2)
};

//Sætter pins til at være output

void setup() {
  pinMode(pin1, OUTPUT);
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

//Maybe chance conflicting name index

void pourButton(int index)
{
  Mocktail mocktail = mocktails[index];

  for (int i = 0; i < sizeof(mocktail.Ingredients) / sizeof(mocktail.Ingredients[0]); i++)
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