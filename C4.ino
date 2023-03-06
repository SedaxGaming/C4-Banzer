#include <LiquidCrystal_I2C.h> //inclusão da biblioteca módulo I2c
#include <Keypad.h> //inclusão da biblioteca teclado matricial
#include <string.h>
#define LedVermelho 12 
//definição pino dos leds
#define LedVerde 13
#define tempo 10 
//tempo do som


char* senha; //definir uma senha
int posicao = 0; //posição do numero na senha
int time=3600; // contador time
const byte rows = 4; //numero de linhas e colunas do teclado
const byte cols = 4;
int autofalante=7; //pino do autofalante
int freq=2000;     //frequencia para o bip
int dur=120;       //duração do bip
int codepos=0;
int estadoled = LOW;  //variável para o estado do led
int intervalo=1000;
int previousMillis = 0;
int frequencia = 0;

char keyMap [rows] [cols] = { //teclado matricial, deixe igual o fisico

  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins [rows] = {11, 10,9,8}; //pinos do teclado
byte colPins [cols] = {6, 5, 4};

Keypad myKeypad = Keypad( makeKeymap(keyMap), rowPins, colPins, rows, cols);

Adafruit_LiquidCrystal lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);//endereço I2c módulo display

void setup(){

  lcd.begin(16, 2);
  pinMode(LedVermelho, OUTPUT);  //setando o led como saída
  pinMode(LedVerde, OUTPUT);
  lcd.setCursor(0, 0);
  lcd.print("*******");
  lcd.setCursor(0, 0);
}

  void contador(int tempoinicial){ //rotina de acionamento da bomba
    lcd.clear();
     lcd.print("*******");
    lcd.setCursor(0, 1);
    lcd.print("BOMBA ARMADA");
    int count=time;
    while(count>0){
      
     char numteclado;
    numteclado=keyget();
     if(numteclado == '*' || numteclado == '#'){ //reseta senha
    posicao=0;
  }
  if(numteclado == senha [posicao]){

    posicao ++;
  }
  if(posicao == 7){//rotina para desarmar se a senha for correta
    
     lcd.print("BOMBA DESARMADA");
     lcd.setCursor(0, 1);
      lcd.print("COUNTER-TERRORIST WIN");
      digitalWrite(LedVerde,HIGH);
      digitalWrite(LedVermelho,LOW);
    while(1);
  }
 
  lcd.setCursor(0, 1); //rotina para contagem regressiva
  int temporestante=time-(millis()/1000-tempoinicial);
  lcd.print("BOMBA ARMADA  ");
  lcd.print(temporestante);
 


  
    if (temporestante<10){//Colocar 0 na frente quando for menor que 10
      lcd.setCursor(13, 1);
      lcd.print("0");
     lcd.setCursor(15, 1);
      lcd.print("   ");
  }
  
  if (temporestante==25){//rotinas para mudança da velocidade do bip
    intervalo=800;
  }
  
    if (temporestante==15){
    intervalo=700;
  }
  
    if (temporestante==10){
    intervalo=600;
  }
  
    if (temporestante==6){
    intervalo=400;
  }
  
    if (temporestante==3){
    intervalo=250;
  }
    
    int currentMillis=millis();
    if (currentMillis - previousMillis >= intervalo) {

    previousMillis = currentMillis;
    
    if (estadoled == LOW) {//Led piscando durante a contagem
      estadoled = HIGH;
    } else {
      estadoled = LOW;
    }
    
    digitalWrite(12, estadoled);
    tone(autofalante,freq,dur);
    }
    
    if (temporestante<=0){//Mensagem se o tempo acabar
    lcd.setCursor(0, 0);
    lcd.print("DETONADA");
    lcd.setCursor(0, 1);
    lcd.print("TERRORISTS WIN");
     digitalWrite(LedVermelho,HIGH);
    tocarsom();
    while(1);
  }
   
 
    }
    return;
  }

void tocarsom(){//som quando perfe
    // for (frequencia =150; frequencia < 1800; frequencia += 1) 
  {
    //tone(autofalante, frequencia, tempo); 
    //delay(1);
  }
  for (frequencia = 2800; frequencia > 150; frequencia -= 1) 
  {
    tone(autofalante, frequencia, tempo); 
    delay(1);
  }
}


char keyget(){
    char numteclado = myKeypad.getKey(); //define qual tecla é pressionada com getKey

  if (numteclado >='0' && numteclado<='9'){ //posição da senha
    codepos++;
  }
  
    if(numteclado == '*' || numteclado == '#'){//reseta senha

    posicao=0;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" ENTRY RESET!");
    delay(100);
    lcd.clear();
    lcd.print("*******");
    codepos=0;
  lcd.setCursor(0, 0);
  }
  
  if (codepos>=7){
    lcd.clear();
    lcd.print("*******");
    codepos=0;
  lcd.setCursor(0, 0);
  }
  
  lcd.setCursor(codepos-1, 0);
  if (numteclado != NO_KEY){

//rotina para um som diferente para cada tecla pressionada

  if (numteclado == '1'){
     tone(autofalante,freq,dur);
      lcd.print(1);
  }
  
    if (numteclado == '2'){
     tone(autofalante,freq*1.25,dur);
      lcd.print(2);
  }
  
      if (numteclado == '3'){
     tone(autofalante,freq*1.5,dur);
      lcd.print(3);
  }
  
      if (numteclado == '4'){
     tone(autofalante,freq*1.75,dur);
      lcd.print(4);
  }
  
      if (numteclado == '5'){
     tone(autofalante,freq*2,dur);
      lcd.print(5);
  }
  
      if (numteclado == '6'){
     tone(autofalante,freq*2.25,dur);
      lcd.print(6);
  }
  
      if (numteclado == '7'){
     tone(autofalante,freq*2.5,dur);
      lcd.print(7);
  }
  
      if (numteclado == '8'){
     tone(autofalante,freq*2.75,dur);
      lcd.print(8);
  }
  
      if (numteclado == '9'){
     tone(autofalante,freq*3,dur);
      lcd.print(9);
      
  }
  
      if (numteclado == '0'){
     tone(autofalante,freq*3.25,dur);
      lcd.print(0);
  }
  }
  return numteclado;
}  


void loop(){

  char numteclado;
  numteclado=keyget();
  if(numteclado == '*'){

    posicao=0;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" ENTRY RESET!");
    delay(100);
    lcd.clear();
    lcd.print("*******");
    codepos=0;
  lcd.setCursor(0, 0);
  }
  while(numteclado != '#'){
  senha += numteclado
    posicao ++;
  }
  if(posicao == strlen(senha)){
    posicao=0;
    int tempoinicial=(millis())/1000;
    contador(tempoinicial);
  }
  delay(100);
}
