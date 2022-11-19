#include <Wire.h>               // Biblioteca utilizada para fazer a comunicação com o I2C
#include <LiquidCrystal_I2C.h>  // Biblioteca utilizada para fazer a comunicação com o display 16x2

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);
const int pinoSensor = A0;  //PINO UTILIZADO PELO SENSOR
const int ldr = A1;         //Atribui A0 a variável ldr
int valorLidoUmid;          //VARIÁVEL QUE ARMAZENA O PERCENTUAL DE UMIDADE DO SOLO
//Porta ligada ao pino IN1 do modulo
int porta_rele1 = 9;
int valorldr = 0;
int ledAlertIrrig = 47;

int analogSoloSeco = 900;     //VALOR MEDIDO COM O SOLO SECO (VOCÊ PODE FAZER TESTES E AJUSTAR ESTE VALOR)
int analogSoloMolhado = 300;  //VALOR MEDIDO COM O SOLO MOLHADO (VOCÊ PODE FAZER TESTES E AJUSTAR ESTE VALOR)
int percSoloSeco = 0;         //MENOR PERCENTUAL DO SOLO SECO (0% - NÃO ALTERAR)
int percSoloMolhado = 100;    //MAIOR PERCENTUAL DO SOLO MOLHADO (100% - NÃO ALTERAR)

int statusIrrig = false;

void setup() {
  lcd.begin (16,2); //SETA A QUANTIDADE DE COLUNAS(16) E O NÚMERO DE LINHAS(2) DO DISPLAY
  lcd.setBacklight(HIGH); //LIGA O BACKLIGHT (LUZ DE FUNDO)
  Serial.begin(9600);  //INICIALIZA A SERIAL
  pinMode(ldr, INPUT);
  pinMode(pinoSensor, INPUT);
  pinMode(ledAlertIrrig, OUTPUT);
  pinMode(porta_rele1, OUTPUT);
  Serial.println("Lendo a umidade do solo...");  //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print("Umidade do solo: ");                                                                     //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print(valorLidoUmid);                                                                           //IMPRIME NO MONITOR SERIAL O PERCENTUAL DE UMIDADE DO SOLO
  Serial.println("%"); 
  lcd.setCursor(0,0); //SETA A POSIÇÃO DO CURSOR
  lcd.print("----- CAUI -----"); //IMPRIME
  delay(2000);                                   //INTERVALO DE 2 SEGUNDOS
}

void CheckUmid() {
  valorldr = analogRead(ldr);              //Lê o valor do sensor ldr e armazena na variável valorldr
  Serial.print("Valor lido pelo LDR = ");  //Imprime na serial a mensagem Valor lido pelo LDR
  Serial.println(valorldr);                //Imprime na serial os dados de valorldr
  valorLidoUmid = analogRead(pinoSensor);
  valorLidoUmid = constrain(analogRead(pinoSensor), analogSoloMolhado, analogSoloSeco);                  //MANTÉM valorLidoUmid DENTRO DO INTERVALO (ENTRE analogSoloMolhado E analogSoloSeco)
  valorLidoUmid = map(valorLidoUmid, analogSoloMolhado, analogSoloSeco, percSoloMolhado, percSoloSeco);  //EXECUTA A FUNÇÃO "map" DE ACORDO COM OS PARÂMETROS PASSADOS
  Serial.print("Umidade do solo: ");                                                                     //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print(valorLidoUmid);                                                                           //IMPRIME NO MONITOR SERIAL O PERCENTUAL DE UMIDADE DO SOLO
  Serial.println("%"); 
  lcd.setCursor(0,0); //SETA A POSIÇÃO DO CURSOR
  lcd.print("Umidade: "); //IMPRIME
  lcd.print(valorLidoUmid); //IMPRIME O TEXTO NO DISPLAY LCD
  lcd.print(" %    "); //IMPRIME
  lcd.setCursor(0,1); //SETA A POSIÇÃO DO CURSOR
  lcd.print("Luz: "); //IMPRIME
  lcd.print(valorldr); //IMPRIME
  lcd.print("        "); //IMPRIME
}
void loop() {
  CheckUmid();
  Serial.println("-----Irrigação desligada-----");

  while (valorLidoUmid < 50 & valorldr < 150) {
    Serial.println("-----Irrigando-----");
    digitalWrite(ledAlertIrrig, HIGH);  //Liga rele 1
    digitalWrite(porta_rele1, LOW);     //Liga rele 1
    lcd.setCursor(0,1); //SETA A POSIÇÃO DO CURSOR
    lcd.print("Irrigacao: ON"); //IMPRIME
    delay(2000); //INTERVALO IRRIGANDO ANTES DE CHEGAR A UMIDADE NOVAMENTE
    CheckUmid();
  }

  //digitalWrite(porta_rele1, LOW);  //Liga rele 1
  //delay(2000);// tempo de irigação a depender do ambiente e temperatura
  delay(2000);
  digitalWrite(ledAlertIrrig, LOW);  //Liga rele 1
  digitalWrite(porta_rele1, HIGH);   // Desliga rele 1
}