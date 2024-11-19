#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display = Adafruit_SSD1306();

const int LM35 = A2;
float temperatura;
int setTemp = 0, Aument = 13, Dimin = 10, saturacao = 8, buttonState = 0, ganho = 5, pot = 0, media = 0;
int StAtual, ProximoSt;

#define StAquecer 0
#define StAnalisar 1

void setup() {
  pinMode(Aument, INPUT_PULLUP);
  pinMode(saturacao, OUTPUT);
  pinMode(Dimin, INPUT_PULLUP);
  Serial.begin(9600);
  Wire.begin();
  display.clearDisplay();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);
  display.setTextSize(3);
}
// Função para mostrar a tela
void mostraTela() {
  if( StAtual == StAnalisar){
  display.setCursor(10, 10);
  display.print(temperatura);
  display.setTextSize(1);
  display.print(" O ");
  display.setTextSize(3);
  display.print("C");  

  }
  Serial.print("Valor na tela: ");
  Serial.println(setTemp);
  display.setCursor(10, 10);
  display.print(setTemp);  // mostra na tela a temperatura que o usuario escolheu
  display.setTextSize(1);
  display.print(" O ");
  display.setTextSize(3);
  display.print("C");
  display.display();  // faz a escrita no display
  display.clearDisplay();
}
// Função para setar a temperatura
void SetarTemp() {
  // Para aumentar a temperatura
  buttonState = digitalRead(Aument);
  if (buttonState == LOW) {
    setTemp++;
    Serial.println("botao de aumentar apertado");
  }
  // Para diminuir a temperatura
  buttonState = digitalRead(Dimin);
  if (buttonState == LOW) {
    setTemp--;
    Serial.println("botao de diminuir apertado");
  }

  if( digitalRead(Aument) == LOW && digitalRead(Dimin) == LOW){
    while (digitalRead(Aument) == LOW && digitalRead(Dimin) == LOW);
    ProximoSt = !ProximoSt;

  }
}
// Função para impor limite na temperatura e verificar se pode ou não ligar os resistores


void ligaResis() {

  pot = (setTemp - temperatura) * ganho;
  Serial.print("Potencia calculo: ");
  Serial.println(pot);

  if (pot >= 255) {
    analogWrite(saturacao, 255);
    Serial.print("Potencia no led: ");
    Serial.println('255');
  }

  if (pot > 0 && pot < 255) {
    analogWrite(saturacao, pot);
    Serial.print("Potencia no resistor: ");
    Serial.println(pot);
  }

  if (pot <= 0) {
    analogWrite(saturacao, 0);
    Serial.print("Potencia no resistor: ");
    Serial.println('0');
  }
}

void loop() {
  if( StAtual == StAquecer){

  Serial.print("Temperatura: ");
  Serial.println(temperatura);

  ligaResis();
  SetarTemp();
  mostraTela();

  }
    media = 0;
  for (int c = 0; c <= 50; c++) {
    media += (((analogRead(LM35) * 5.0) / 1023) / 0.01);
  }
  temperatura = media / 50;

  if( StAtual == StAnalisar){
  mostraTela(); 
  SetarTemp();
  }

  Serial.print("Proximo estado: ");
  Serial.println(ProximoSt);
  delay(1200);
  StAtual = ProximoSt;
}
