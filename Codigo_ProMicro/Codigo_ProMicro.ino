int Motor_1D = 2;
int Motor_1I = 3;
int Motor_2D = 5;
int Motor_2I = 4;

int ESP_Motor_1D = A0;
int ESP_Motor_1I = A1;
int ESP_Motor_2D = A2;
int ESP_Motor_2I = A3;

int Estado_Motor_1D = 0;
int Estado_Motor_1I = 0;
int Estado_Motor_2D = 0;
int Estado_Motor_2I = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(Motor_1D,OUTPUT);
  pinMode(Motor_1I,OUTPUT);
  pinMode(Motor_2D,OUTPUT);
  pinMode(Motor_2I,OUTPUT);

  pinMode(ESP_Motor_1D,INPUT);
  pinMode(ESP_Motor_1I,INPUT);
  pinMode(ESP_Motor_2D,INPUT);
  pinMode(ESP_Motor_2I,INPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Estado_Motor_1D = digitalRead(ESP_Motor_1D);
  Estado_Motor_1I = digitalRead(ESP_Motor_1I);
  Estado_Motor_2D = digitalRead(ESP_Motor_2D);
  Estado_Motor_2I = digitalRead(ESP_Motor_2I);
  Serial.println("");
  if (Estado_Motor_1D){
    Serial.print("||  Motor_1D: ");
    Serial.print(Estado_Motor_1D);
    digitalWrite(Motor_1D,HIGH);  
  }
  if (Estado_Motor_1I){
    Serial.print("|| Motor_1I: ");
    Serial.print(Estado_Motor_1I);
    digitalWrite(Motor_1I,HIGH);  
  }
  if (Estado_Motor_2D){
    Serial.print("|| Motor_2D: ");
    Serial.print(Estado_Motor_2D);
    digitalWrite(Motor_2D,HIGH);  
  }
  if (Estado_Motor_2I){
    Serial.print("|| Motor_2I: ");
    Serial.print(Estado_Motor_2I);
    digitalWrite(Motor_2I,HIGH);  
  }
  if(!Estado_Motor_1D and !Estado_Motor_1I and !Estado_Motor_2D and !Estado_Motor_1I){
    digitalWrite(Motor_1D,LOW);
    digitalWrite(Motor_1I,LOW);
    digitalWrite(Motor_2D,LOW);
    digitalWrite(Motor_2I,LOW);
  }
}
