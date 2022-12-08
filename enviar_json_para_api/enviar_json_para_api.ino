#include "WiFi.h"
#include <WiFiMulti.h>
WiFiMulti wifiMulti;
#include <HTTPClient.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// codigo do leleo

const char *AP_SSID = "";             //Adicione aqui o nome da rede WiFi
const char *AP_PWD = "";              //Adicione aqui o nome da rede WiFi

void postDataToServer(){

 
  // conectar a uma rede WiFi local que possui acesso à internet "a mesma que foi definida no início do código" 
  wifiMulti.addAP(AP_SSID, AP_PWD);

  if(wifiMulti.run() == WL_CONNECTED) {
    HTTPClient http;
    // endereço da API
    http.begin("https://ur524n-3000.preview.csb.app/teobaldo");
    http.addHeader("Content-Type", "application/json");
    StaticJsonDocument<200> doc;

    // Campos que serão enviados para a API e adicionados ao banco de dados
    doc["Nome do Aluno"] = "leleo";
    doc["Turma"] = "Turma 3",
    doc["Grupo"] = "Grupo 2";
    doc["Mensagem em texto"] = "leleo";
    doc["Mensagem criptografada"] = criptografar();


    String requestBody;
    serializeJson(doc, requestBody);
    int httpResponseCode = http.POST(requestBody);

    // printar o json postado na API
    if(httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    
    // retornar uma mensagem de erro caso tenho ocorrido alguma falha no envio de dados para a API
    } else {
      Serial.printf("Error occurred while sending HTTP POST: %s\n");
    }
  }
}


const char palavra [] = {'l', 'e', 'l', 'e', 'o'};
char palavra_nova [5] = {}; 
int combinacao = 0;
const char letras [] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

int count = 0;

char* criptografar(){
  combinacao = 5;
  
  for(int i = 0; i<5; i++){
    for(int j = 0; j<26; j++){
      if(palavra[i] == letras[j]){
        count = j + combinacao;
        palavra_nova[i] = letras[count];
      }
    }
  }

  for(int k = 0; k<5; k++){
    Serial.println(palavra_nova[k]);
  }
  return palavra_nova;
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println('Hello, ESP32-S3!');
}

int rodar = 1;
void loop() {
  while(rodar == 1){
  criptografar();
  rodar = 0;
  while(rodar == 0){
    postDataToServer();
    rodar = 2;
  }
}
}
