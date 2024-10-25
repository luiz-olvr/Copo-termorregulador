#include <Wire.h> 
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h> 
Adafruit_SSD1306 display = Adafruit_SSD1306(); 

const int LM35 = A2; 
float temperatura;
int setTemp = 0, Aument = 13, Dimin = 10, estadorele = 8, buttonState = 0, ganho = 4, pot = 0;

void setup() {
pinMode(Aument, INPUT_PULLUP);
pinMode(estadorele, OUTPUT);
pinMode(Dimin, INPUT_PULLUP);  
Serial.begin(9600); 
Wire.begin(); 
display.clearDisplay(); 
display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
display.setTextColor(WHITE); 
display.setTextSize(3); 
}
// Função para mostrar a tela
void mostraTela(){
  Serial.println(setTemp);
  display.setCursor(10,10);
  display.print(setTemp); // mostra na tela a temperatura que o usuario escolheu
  display.setTextSize(1); 
  display.print("  O ");
  display.setTextSize(3); 
  display.print("C");
  display.display(); // faz a escrita no display
  display.clearDisplay();
}
// Função para setar a temperatura
void SetarTemp(){
  // Para aumentar a temperatura
  buttonState = digitalRead(Aument);
  if(buttonState == LOW){
  setTemp++;
  Serial.println("a");
  }
  // Para diminuir a temperatura
  buttonState = digitalRead(Dimin);
  if(buttonState == LOW){
  setTemp--;
  Serial.println("b");
  }

}
// Função para impor limite na temperatura e verificar se pode ou não ligar a P.P.


void ligaResis(){

  pot = (setTemp - temperatura) * ganho;
  digitalWrite(estadorele, pot);

}





void condRele(){
  // Verificar se o rele pode ou não ligar
  if (temperatura >setTemp + 2){
    digitalWrite(estadorele,LOW);
  }
  if(temperatura < setTemp - 2){
    digitalWrite(estadorele,HIGH);
  }
  // Limites de temperatura
  if(setTemp > 50){
  setTemp = 20;}
  
  if(setTemp < -10){
  setTemp = -10;
  }
}


void loop() {
temperatura = (((analogRead(LM35)*5.0)/1023)/0.01);
Serial.print("Temperatura: "); 
Serial.println(temperatura);

  //condRele();
  ligaResis();
  SetarTemp();
  
  mostraTela();
  
}
