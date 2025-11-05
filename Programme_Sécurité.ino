#include <Keypad.h>
#include <stdlib.h>

// Definition of the valid code
char code_coffre[] = {'6','4','7','1'};
// Definition of the keypad rows number
const byte ROWS = 4; 
// Definition of the keypad columns number
const byte COLS = 3; 
char keys[ROWS][COLS] = 
{
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'#','0','*'}
};

// Pins connected to the rows of the keypad
byte rowPins[ROWS] = {8,7,6,5}; 
// Pins connected to the columns of the keypad
byte colPins [COLS] = {4,3,2}; 
// Create the keypad structure
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); 
// Analog input pin that the chest is attached to
const int analogInPin = A0; 
// Value read from the potentiometer
int chestValue = 0; 

// LED configuration for alert and success
const int led_R1 = 13;
const int led_R2 = 12;
const int led_R3 = 11;
const int led_R4 = 10;

const int led_V1 = 9;
const int led_V2 = 15;
const int led_V3 = 16;
const int led_V4 = 17;
const int led_V5 = 18;
const int led_V6 = 19;

// Questions and correct answers
const char questions[4] = 
{
  "Quelle est la capitale de la France ? (1: Paris, 2: Lyon, 3: Marseille, 4: Toulouse) \n",
  "Quelle est votre nationalite ? (1: Russe, 2: Anglaise, 3: Francaise, 4: Allemande) \n",
  "Quel est le plus grand pays en superficie ? (1: Chine, 2: Etats-Unis, 3: Canada, 4: Russie) \n",
  "Quelle est votre situation ? (1: Marie(e), 2: Celibataire, 3: Enfant(s), 4: Separe(e)) \n"
};
// Indices of the correct answers
const int correctAnswer[4] = {1, 3, 4, 2}; 

// Counters
int compteur = 0;
int nb_erreur = 0;
char code_entre[] = {'0','0','0','0'};
bool code_correct = false;

// Authentication flags
bool MA1_valide = false;
bool MA2_valide = false;
bool MA3_valide = false;
bool MA4_valide = false;

void setup()
{
  Serial.begin(9600);
  pinMode(led_R1, OUTPUT);
  pinMode(led_R2, OUTPUT);
  pinMode(led_R3, OUTPUT);
  pinMode(led_R4, OUTPUT);
  pinMode(led_V1, OUTPUT);
  pinMode(led_V2, OUTPUT);
  pinMode(led_V3, OUTPUT);
  pinMode(led_V4, OUTPUT);
  pinMode(led_V5, OUTPUT);
  pinMode(led_V6, OUTPUT);
  resetLeds();
}

void loop()
{
  chestValue = analogRead(analogInPin); // Read the analog value
  if (chestValue >= 174 && chestValue <= 182) // Model 1
  { 
    resetLeds();
    Serial.println("Le code et la carte correspondent.");
    digitalWrite(led_V1, HIGH);
    secu_4(); // Start authentication procedure for this model
  } 
  else if (chestValue >= 306 && chestValue <= 314) // Model 2
  {
    resetLeds();
    Serial.println("Le code et la carte correspondent.\n");
    digitalWrite(led_V1, HIGH);
    secu_4();   
  }
  else if (chestValue >= 386 && chestValue <= 394) // Model 3
  {
    resetLeds();
    Serial.println("Le code et la carte correspondent.\n");
    digitalWrite(led_V1, HIGH);
    delay(500);
    secu_2();
  }
  else if (chestValue >= 474 && chestValue <= 483) // Model 4
  {
    resetLeds();
    Serial.println("Le code et la carte correspondent.\n");
    digitalWrite(led_V1, HIGH);
    delay(500);
    secu_2();
  }
  else if (chestValue >= 517 && chestValue <= 525) // Model 5
  {
    resetLeds();
    Serial.println("Le code et la carte correspondent.\n");
    digitalWrite(led_V1, HIGH);
    delay(500);
    secu_2();
  }
  else if (chestValue >= 553 && chestValue <= 561) // Model 6
  {
    resetLeds();
    Serial.println("Le code et la carte correspondent.\n");
    digitalWrite(led_V1, HIGH);
    delay(500);
    secu_3();
  }
  else if (chestValue >= 626 && chestValue <= 634) // Model 7
  {
    resetLeds();
    Serial.println("Le code et la carte correspondent.\n");
    digitalWrite(led_V1, HIGH);
    delay(500);
    secu_3();
  }
  else if (chestValue >= 688 && chestValue <= 697) // Model 8
  {
    resetLeds();
    Serial.println("Le code et la carte correspondent.\n");
    digitalWrite(led_V1, HIGH);
    delay(500);
    secu_1();
  }
  else
  {
    delay(5000);
    Serial.println("Le code et la carte ne correspondent pas \n");
    digitalWrite(led_R1, HIGH);
    digitalWrite(led_R2, HIGH);
    digitalWrite(led_R3, HIGH);
    digitalWrite(led_R4, HIGH);
  }
}

void secu_1()
{
  if (MA1_valide == false)
  {
    MA1();
    if (MA3_valide == false)
    {
      digitalWrite(led_V2, HIGH);
      digitalWrite(led_V3, HIGH);
      MA3();
      if (MA3_valide == true)
      {
        digitalWrite(led_V4, HIGH);
        digitalWrite(led_V5, HIGH);
        delay(500);
        Serial.print("Coffre deverrouille !");
        digitalWrite(led_V6, HIGH);
      }
    }
  }
}

void secu_2()
{
  if (MA1_valide == false)
  {
    MA1();
    if (MA4_valide == false)
    {
      digitalWrite(led_V2, HIGH);
      digitalWrite(led_V3, HIGH);
      MA4();
      if (MA4_valide == true)
      {
        digitalWrite(led_V4, HIGH);
        digitalWrite(led_V5, HIGH);
        delay(500);
        Serial.print("Coffre deverrouille !");
        digitalWrite(led_V6, HIGH);
      }
    }
  }
}

void secu_3()
{
  if (MA2_valide == false)
  {
    MA2();
    if (MA4_valide == false)
    {
      digitalWrite(led_V2, HIGH);
      digitalWrite(led_V3, HIGH);
      MA4();
      if (MA4_valide == true)
      {
        digitalWrite(led_V4, HIGH);
        digitalWrite(led_V5, HIGH);
        delay(500);
        Serial.print("Coffre deverrouille !");
        digitalWrite(led_V6, HIGH);
      }
    }
  }
}

void secu_4()
{
  if (MA1_valide == false)
  {
    MA1();
    if (MA2_valide == false)
    {
      digitalWrite(led_V2, HIGH);
      MA2();
      if (MA3_valide == false)
      {
        digitalWrite(led_V3, HIGH);
        MA3();
        if (MA4_valide == false)
        {
          digitalWrite(led_V4, HIGH);
          MA4();
          if (MA4_valide == true)
          {
            digitalWrite(led_V5, HIGH);
            delay(500);
            Serial.print("Coffre deverrouille !");
            digitalWrite(led_V6, HIGH);
            delay(500);
            exit(1);
          }
        }
      }
    }
  }
}

// Authentication by questions
void MA1()
{
  int questionIndex = 0;
  while (MA1_valide == false)
  {
    poserQuestion(questionIndex);
    char key = attendreReponse();

    if (verifierReponse(key - '0', questionIndex)) 
    {
      Serial.println("Bonne reponse !");
      questionIndex++;
      if (questionIndex == 1)
      {
        digitalWrite(led_R1, HIGH);
      }
      if (questionIndex == 2)
      {
        digitalWrite(led_R1, HIGH);
        digitalWrite(led_R2, HIGH);
      }
      if (questionIndex == 3)
      {
        digitalWrite(led_R1, HIGH);
        digitalWrite(led_R2, HIGH);
        digitalWrite(led_R3, HIGH);
      }
      if (questionIndex == 4) 
      {
        Serial.println("Toutes les reponses sont correctes. Prochaine etape d'authentification.");
        MA1_valide = true;
        // Restart from the first question
        questionIndex = 0;  
        digitalWrite(led_R1, HIGH);
        digitalWrite(led_R2, HIGH);
        digitalWrite(led_R3, HIGH);
        digitalWrite(led_R4, HIGH);
        delay(500);
        resetLeds();
      }
    }
    else
    {
      Serial.println("Mauvaise reponse ! Alerte activee.");
      alerter();
      nb_erreur++;
      if (nb_erreur == 4) 
      {
        Serial.println("4 erreurs, blocage de 30 secondes.");
        // Lock for 30 seconds
        delay(30000); 
        nb_erreur = 0;
      }
    }
  }
}

void poserQuestion(int index)
{
  Serial.println(questions[index]);
}

char attendreReponse()
{
  char key;
  while ((key = keypad.getKey()) == NO_KEY) 
  {
    // Wait for the response
  }
  return key;
}

bool verifierReponse(int reponse, int questionIndex)
{
  return reponse == correctAnswer[questionIndex];
}

void alerter()
{
  for (int i = 0; i < 6; i++) 
  {
    digitalWrite(led_R1, HIGH);
    digitalWrite(led_R2, HIGH);
    digitalWrite(led_R3, HIGH);
    digitalWrite(led_R4, HIGH);
    delay(500);
    resetLeds();
    delay(500);
  }
}

void resetLeds()
{
  digitalWrite(led_R1, LOW);
  digitalWrite(led_R2, LOW);
  digitalWrite(led_R3, LOW);
  digitalWrite(led_R4, LOW);
}

// Authentication by a code that changes over time
void MA2()
{
  char key = keypad.getKey();
  while (MA2_valide == false)
  {
    Serial.print("Veuillez entrer votre code d'acces \n");
    while (code_correct == false)
    {
      // Wait while no key is pressed
      key = keypad.getKey();
      if (key != NO_KEY) 
      {
        compteur++;
        code_entre[compteur - 1] = key; 
      }
      
      if (compteur == 1) 
      { 
        // First digit entered
        digitalWrite(led_R1, HIGH);
      }
      
      if (compteur == 2) 
      { 
        digitalWrite(led_R1, HIGH);
        // Second digit entered
        digitalWrite(led_R2, HIGH); 
      }
      
      if (compteur == 3) 
      { 
        digitalWrite(led_R1, HIGH);
        digitalWrite(led_R2, HIGH);
        // Third digit entered
        digitalWrite(led_R3, HIGH);
      }

      if (compteur == 4) 
      { 
        digitalWrite(led_R1, HIGH);
        digitalWrite(led_R2, HIGH);
        digitalWrite(led_R3, HIGH);
        // Fourth digit entered
        digitalWrite(led_R4, HIGH);
        code_correct = true;
        
        // Check the code
        for (int i = 0; i < 4; i++) 
        { 
          if (code_entre[i] != code_coffre[i]) 
          {
            code_correct = false;
          }
        }
          
        if (code_correct == true) 
        {
          MA2_valide = true;
          Serial.print("Code bon \n");
          delay(500);
          resetLeds();
        } 
        else 
        {
          // If the code is wrong, red LEDs blink
          for (int j = 0; j < 6; j++) 
          { 
            digitalWrite(led_R1, HIGH);
            digitalWrite(led_R2, HIGH);
            digitalWrite(led_R3, HIGH);
            digitalWrite(led_R4, HIGH);
            delay(500);
          
            digitalWrite(led_R1, LOW);
            digitalWrite(led_R2, LOW);
            digitalWrite(led_R3, LOW);
            digitalWrite(led_R4, LOW);
            delay(500);
          }
          
          compteur = 0;
          nb_erreur++;
          Serial.print("Code faux, plus que ");
          Serial.print(4 - nb_erreur);
          Serial.print(" essais avant blocage. \n");
        }
      }
      
      if (nb_erreur == 4) 
      {
        Serial.print("4 erreurs, blocage pendant 30 secondes.");
        delay(30000);
        nb_erreur = 0;
      }
    }
  }
}

// Function to simulate retina scan
void MA3()
{
  Serial.println("Simulation du scan retinien en cours...");
  delay(1000); // Delay to simulate scan time

  bool retineReconnu = verifierRetine();
  if (retineReconnu) 
  {
    MA3_valide = true;
    afficherAccesAutorise();
  } 
  else 
  {
    afficherAlerte();
  }
}

// Function to simulate retina verification
bool verifierRetine()
{
  // Simulate a retina scan (returns true to simulate recognized retina)
  return true;
}

// Function to show authorized access and turn on green LED
void afficherAccesAutorise()
{
  Serial.println("Retine reconnue. Acces autorise.");
  delay(500);
  MA3_valide = true;
}

// Function to show alert in case of unknown retina and blink red LEDs
void afficherAlerte()
{
  Serial.println("Retine inconnue. Alerte activee !");
  for (int j = 0; j < 6; j++) 
  {
    clignoterLEDsRouges();
  }
}

// Function to blink the red LEDs
void clignoterLEDsRouges()
{
  digitalWrite(led_R1, HIGH);
  digitalWrite(led_R2, HIGH);
  digitalWrite(led_R3, HIGH);
  digitalWrite(led_R4, HIGH);
  delay(500);
  digitalWrite(led_R1, LOW);
  digitalWrite(led_R2, LOW);
  digitalWrite(led_R3, LOW);
  digitalWrite(led_R4, LOW);
  delay(500);
}

// Function to simulate fingerprint scan
void MA4()
{
  Serial.println("Scan digital en cours... Veuillez appuyer pour simuler l'empreinte digitale.");
  while (MA4_valide == false)
  {  
    char key = keypad.getKey();
    if (key != NO_KEY) 
    {
      if (key == '1') // Define '1
	  {  
        Serial.println("Fingerprint recognized. Access granted.");
        delay(500);
        MA4_valide = true;
      } 
      else 
      {
        Serial.println("Fingerprint unknown! Access denied.");
        alerter();
      }
    }
  }
}
