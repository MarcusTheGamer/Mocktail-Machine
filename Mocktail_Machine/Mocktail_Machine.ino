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

int btn1 = 7;
int btn2 = 2;
int btn3 = 9;

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

int flowspeed = 50;
int cupAmount = 0;
const int cupSize = 250;

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

  Serial.begin(9600);
}



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

int SelectIndex = 0;

void TestFucntionAlsoDeleteLater(int intiger){
  switch(intiger){
    case 0:
      digitalWrite(pin1, HIGH);
      break;
    case 1:
      digitalWrite(pin2, HIGH);
      break;
    case 2:
      digitalWrite(pin3, HIGH);
      break;
    case 3:
      digitalWrite(pin4, HIGH);
      break;
    case 4:
      digitalWrite(pin5, HIGH);
      break;
    case 5:
      digitalWrite(pin6, HIGH);
      break;
    case 6:
      digitalWrite(pin7, HIGH);
      break;
    case 7:
      digitalWrite(pin8, HIGH);
      break;
  }
}

int LastBtn1State = LOW;
int LastBtn2State = LOW;
int LastBtn3State = LOW;

bool CompareBtnStates(int prev, int cur){
  if (prev == LOW && cur == HIGH){
    return true;
  }
  else {
    return false;
  }
}

void loop() {
  int Btn1StateNow = digitalRead(btn1);
  int Btn2StateNow = digitalRead(btn2);
  int Btn3StateNow = digitalRead(btn3);
  if (CompareBtnStates(LastBtn1State, Btn1StateNow) && SelectIndex < 7 )
  {
    SelectIndex++;
    Serial.println("i'm pooping it");
  }
  else if (CompareBtnStates(LastBtn3State, Btn3StateNow) && SelectIndex > 0)
  {
    SelectIndex--;
    Serial.println("pee pee poo poo 2: electric bogaloo");
  }
  //Serial.print(testThingDeleteLater);
  if (CompareBtnStates(LastBtn2State, Btn2StateNow)){
    //pourButton(testThingDeleteLater);
    TestFucntionAlsoDeleteLater(SelectIndex);
    Serial.println(SelectIndex);
  }
  LastBtn1State = digitalRead(btn1);
  LastBtn2State = digitalRead(btn2);
  LastBtn3State = digitalRead(btn3);
}