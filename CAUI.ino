const int pinoSensor = A0; //PINO UTILIZADO PELO SENSOR
const int ldr = A1;//Atribui A0 a variável ldr
int valorLidoUmid; //VARIÁVEL QUE ARMAZENA O PERCENTUAL DE UMIDADE DO SOLO
//Porta ligada ao pino IN1 do modulo
int porta_rele1 = 13;
int valorldr = 0;
int ledAlertIrrig = 12;

int analogSoloSeco = 900; //VALOR MEDIDO COM O SOLO SECO (VOCÊ PODE FAZER TESTES E AJUSTAR ESTE VALOR)
int analogSoloMolhado = 300; //VALOR MEDIDO COM O SOLO MOLHADO (VOCÊ PODE FAZER TESTES E AJUSTAR ESTE VALOR)
int percSoloSeco = 0; //MENOR PERCENTUAL DO SOLO SECO (0% - NÃO ALTERAR)
int percSoloMolhado = 100; //MAIOR PERCENTUAL DO SOLO MOLHADO (100% - NÃO ALTERAR)

int statusIrrig = false;
 
void setup(){
 Serial.begin(9600); //INICIALIZA A SERIAL
 pinMode(ldr, INPUT);
 pinMode(pinoSensor, INPUT);
 pinMode(ledAlertIrrig, INPUT);
 pinMode(porta_rele1, OUTPUT);
 Serial.println("Lendo a umidade do solo..."); //IMPRIME O TEXTO NO MONITOR SERIAL
 delay(2000); //INTERVALO DE 2 SEGUNDOS
}
 
void CheckUmid()
{ 
  valorldr=analogRead(ldr);//Lê o valor do sensor ldr e armazena na variável valorldr
  Serial.print("Valor lido pelo LDR = ");//Imprime na serial a mensagem Valor lido pelo LDR
  Serial.println(valorldr);//Imprime na serial os dados de valorldr
  valorLidoUmid = analogRead(pinoSensor);
  valorLidoUmid = constrain(analogRead(pinoSensor),analogSoloMolhado,analogSoloSeco); //MANTÉM valorLidoUmid DENTRO DO INTERVALO (ENTRE analogSoloMolhado E analogSoloSeco)
  valorLidoUmid = map(valorLidoUmid,analogSoloMolhado,analogSoloSeco,percSoloMolhado,percSoloSeco); //EXECUTA A FUNÇÃO "map" DE ACORDO COM OS PARÂMETROS PASSADOS
  Serial.print("Umidade do solo: "); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print(valorLidoUmid); //IMPRIME NO MONITOR SERIAL O PERCENTUAL DE UMIDADE DO SOLO
  Serial.println("%"); //IMPRIME O CARACTERE NO MONITOR SERIAL
}

void loop(){  
 CheckUmid();
 delay(1000);  //INTERVALO DE 1 SEGUNDO PARA CHECAR A UMIDADADE DO SOLO
   Serial.println("-----Irrigação desligada-----"); 

  while(valorLidoUmid < 50 & valorldr < 450 ){
    Serial.println("-----Irrigando-----"); 
    digitalWrite(ledAlertIrrig, HIGH); //Liga rele 1
    digitalWrite(porta_rele1, LOW); //Liga rele 1
    delay(2000); //INTERVALO IRRIGANDO ANTES DE CHEGAR A UMIDADE NOVAMENTE
    CheckUmid();
  }
  
  //digitalWrite(porta_rele1, LOW);  //Liga rele 1
  //delay(2000);// tempo de irigação a depender do ambiente e temperatura
 digitalWrite(ledAlertIrrig, LOW); //Liga rele 1
 digitalWrite(porta_rele1, HIGH); // Desliga rele 1

}