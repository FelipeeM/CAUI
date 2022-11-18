const int pinoSensor = A0; //PINO UTILIZADO PELO SENSOR
int valorLido; //VARIÁVEL QUE ARMAZENA O PERCENTUAL DE UMIDADE DO SOLO
//Porta ligada ao pino IN1 do modulo
int porta_rele1 = 13;

int analogSoloSeco = 400; //VALOR MEDIDO COM O SOLO SECO (VOCÊ PODE FAZER TESTES E AJUSTAR ESTE VALOR)
int analogSoloMolhado = 150; //VALOR MEDIDO COM O SOLO MOLHADO (VOCÊ PODE FAZER TESTES E AJUSTAR ESTE VALOR)
int percSoloSeco = 0; //MENOR PERCENTUAL DO SOLO SECO (0% - NÃO ALTERAR)
int percSoloMolhado = 100; //MAIOR PERCENTUAL DO SOLO MOLHADO (100% - NÃO ALTERAR)

int statusIrrig = false;
 
void setup(){
 Serial.begin(9600); //INICIALIZA A SERIAL
 pinMode(porta_rele1, OUTPUT);
 Serial.println("Lendo a umidade do solo..."); //IMPRIME O TEXTO NO MONITOR SERIAL
 delay(2000); //INTERVALO DE 2 SEGUNDOS
}
 
void CheckUmid()
{
  valorLido = constrain(analogRead(pinoSensor),analogSoloMolhado,analogSoloSeco); //MANTÉM valorLido DENTRO DO INTERVALO (ENTRE analogSoloMolhado E analogSoloSeco)
  valorLido = map(valorLido,analogSoloMolhado,analogSoloSeco,percSoloMolhado,percSoloSeco); //EXECUTA A FUNÇÃO "map" DE ACORDO COM OS PARÂMETROS PASSADOS
  Serial.print("Umidade do solo: "); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print(valorLido); //IMPRIME NO MONITOR SERIAL O PERCENTUAL DE UMIDADE DO SOLO
  Serial.println("%"); //IMPRIME O CARACTERE NO MONITOR SERIAL
}

void loop(){  
 CheckUmid();
 delay(1000);  //INTERVALO DE 1 SEGUNDO 

  while(valorLido < 50){
    Serial.println("-----Irrigando-----"); //IMPRIME O CARACTERE NO MONITOR SERIAL
    digitalWrite(porta_rele1, HIGH); //Desliga rele 1
    delay(2000); //INTERVALO IRRIGANDO ANTES DE CHEGAR A UMIDADE NOVAMENTE
    CheckUmid();
  }
  
  //digitalWrite(porta_rele1, LOW);  //Liga rele 1
  //delay(2000);// tempo de irigação a depender do ambiente e temperatura
 
 digitalWrite(porta_rele1, LOW);

}