//Sensor de temperatura usando o LM35
#include <Wire.h> //INCLUSÃO DE BIBLIOTECA
#include <Adafruit_GFX.h> //INCLUSÃO DE BIBLIOTECA
#include <Adafruit_SSD1306.h> //INCLUSÃO DE BIBLIOTECA
Adafruit_SSD1306 display = Adafruit_SSD1306(); //OBJETO DO TIPO Adafruit_SSD1306
int buttonState = 0;
int buttonState2 = 0;
const int LM35 = A2; // Define o pino que lera a saída do LM35
float temperatura; // Variável que armazenará a temperatura medida
int setTemp = 0;
int Aument = 13;
int Dimin = 10;
int estadorele = 8;
//Função que será executada uma vez quando ligar ou resetar o Arduino
void setup() {
pinMode(Aument, INPUT_PULLUP);
pinMode(estadorele, OUTPUT);
pinMode(Dimin, INPUT_PULLUP);  
Serial.begin(9600); // inicializa a comunicação serial
Wire.begin(); //INICIALIZA A BIBLIOTECA WIRE
display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //INICIALIZA O DISPLAY COM ENDEREÇO I2C 0x3C
display.setTextColor(WHITE); //DEFINE A COR DO TEXTO
display.setTextSize(3); //DEFINE O TAMANHO DA FONTE DO TEXTO
display.clearDisplay(); //LIMPA AS INFORMAÇÕES DO DISPLAY
}
 
//Função que será executada continuamente
void loop() {
temperatura = (((analogRead(LM35)*5.0)/1023)/0.01);
Serial.print("Temperatura: ");
Serial.println(temperatura);
  if (temperatura >setTemp + 2){
    digitalWrite(estadorele,LOW);
  }
  if(temperatura < setTemp - 2){
    digitalWrite(estadorele,HIGH);
  }
  if(setTemp > 50){
  setTemp = 20;}
  
  if(setTemp < -10){
  setTemp = -10;}

  buttonState = digitalRead(Aument);

  if(buttonState == LOW){
  setTemp++;
  Serial.println("a");
  }

  buttonState2 = digitalRead(Dimin);
  if(buttonState2 == LOW){
  setTemp--;
  Serial.println("b");
}

  Serial.println(setTemp);
  display.setCursor(10,10); //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
  display.print(setTemp); //ESCREVE O TEXTO NO DISPLAY
  display.setTextSize(1); //DEFINE O TAMANHO DA FONTE DO TEXTO
  display.print("  O ");
  display.setTextSize(3); //DEFINE O TAMANHO DA FONTE DO TEXTO
  display.print("C");
  display.display(); //EFETIVA A ESCRITA NO DISPLAY
  display.clearDisplay();
  
  
}