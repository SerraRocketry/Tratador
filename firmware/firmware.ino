#include<ESP8266WiFi.h> 
#include<ESP8266WebServer.h> 
#include <Servo.h> 
#include“FS.h” 
#include<ArduinoJson.h> 
#include<time.h> // Biblioteca para lidar com o tempo

// — Configurações de Wi-Fi — 
const char ssid = “SSID”; 
const char password = “PASSWORD”;

// — Configurações de Tempo (NTP) — 
const char ntpServer = “a.st1.ntp.br”; // Servidor NTP brasileiro 
const long gmtOffset_sec = -3 3600; // Offset para o fuso horário de Brasília (UTC-3) 
const int daylightOffset_sec = 0; // O Brasil não utiliza mais horário de verão

// — Componentes — S
ervo meuServo; 
ESP8266WebServer server(80);

int pinoServo = 2;

// — Variáveis de Controle — 
String horarios[3] = {“07:00”, “13:00”, “19:00”}; 
float tempoMotorLigado = 1.0; // Em segundos

bool refeicaoServida[3] = {false, false, false};

void setup()
{
    Serial.begin(115200);
    meuServo.attach(pinoServo);
    meuServo.write(160);

    if (!SPIFFS.begin())
    {
        Serial.println("Erro ao montar o SPIFFS");
        return;
    }

    carregarConfiguracoes();

    // --- Conexão Wi-Fi ---
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi conectado!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    // --- SINCRONIZAÇÃO DA HORA PELA INTERNET ---
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    Serial.print("Sincronizando hora");
    while (time(nullptr) < 8 * 3600 * 2)
    { // Espera até que a hora seja válida
        Serial.print(".");
        delay(500);
    }
    Serial.println("\nHora sincronizada!");

    // --- Endpoints do Servidor Web (permanecem os mesmos) ---
    server.on("/", HTTP_GET, []()
              {
File file = SPIFFS.open("/index.html", "r");
server.streamFile(file, "text/html");
file.close(); });
    server.on("/settings", HTTP_GET, handleGetSettings);
    server.on("/save", HTTP_POST, handleSaveSettings);
    server.on("/test", HTTP_POST, handleTestMotor);

    server.begin();
}

void loop()
{
    server.handleClient();

    meuServo.detach();

    // --- LÓGICA DE ALIMENTAÇÃO COM HORA DA INTERNET ---
    time_t now = time(nullptr);
    struct tm *timeinfo;
    timeinfo = localtime(&now);

    // Reinicia o controle de refeição servida à meia-noite
    if (timeinfo->tm_hour == 0 && timeinfo->tm_min == 0)
    {
        for (int i = 0; i < 3; i++)
        {
            refeicaoServida[i] = false;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        int hora = horarios[i].substring(0, 2).toInt();
        int minuto = horarios[i].substring(3, 5).toInt();

        // Compara a hora e minuto atuais com os horários programados
        if (timeinfo->tm_hour == hora && timeinfo->tm_min == minuto && !refeicaoServida[i])
        {
            alimentar();
            refeicaoServida[i] = true;
        }
    }
    delay(10);
}

void alimentar()
{
    meuServo.attach(pinoServo);

    Serial.println("Liberando ração...");
    meuServo.write(0);
    delay(tempoMotorLigado * 1000); // Converte segundos para milissegundos
    meuServo.write(160);
    Serial.println("Ração liberada.");
    delay(1000);

    meuServo.detach();
}

void handleGetSettings()
{
    StaticJsonDocument<200> doc;
    doc[“morning”] = horarios[0];
    doc[“afternoon”] = horarios[1];
    doc[“evening”] = horarios[2];
    doc[“activeTime”] = tempoMotorLigado;

    String output;
    serializeJson(doc, output);

    server.send(200, "application/json", output);
}

void handleSaveSettings()
{
    if (server.hasArg(“morning”) && server.hasArg(“afternoon”) && server.hasArg(“evening”) && server.hasArg(“activeTime”))
    {
        horarios[0] = server.arg(“morning”);
        horarios[1] = server.arg(“afternoon”);
        horarios[2] = server.arg(“evening”);
        tempoMotorLigado = server.arg(“activeTime”).toFloat();

        salvarConfiguracoes();
        server.send(200, "text/plain", "Configurações salvas com sucesso!");
    }
    else
    {
        server.send(400, "text/plain", "Faltando parâmetros");
    }
}

void handleTestMotor()
{
    if (server.hasArg(“activeTime”))
    {
        float testTime = server.arg(“activeTime”).toFloat();
        Serial.print(“Testando motor por”);
        Serial.print(testTime);
        Serial.println(” segundos.”);

        meuServo.attach(pinoServo);

        meuServo.write(0);
        delay(testTime * 1000);
        meuServo.write(160);
        delay(testTime * 1000);

        meuServo.detach();

        server.send(200, "text/plain", "Teste concluído");
    }
    else
    {
        server.send(400, "text/plain", "Faltando parâmetro 'activeTime'");
    }
}

void salvarConfiguracoes()
{
    File arquivo = SPIFFS.open(“/ config.txt”, “w”);
    if (!arquivo)
        return;

    arquivo.println(horarios[0]);
    arquivo.println(horarios[1]);
    arquivo.println(horarios[2]);
    arquivo.println(tempoMotorLigado);

    arquivo.close();
    Serial.println("Configurações salvas no SPIFFS.");
}

void carregarConfiguracoes()
{
    File arquivo = SPIFFS.open(“/ config.txt”, “r”);
    if (!arquivo)
    {
        Serial.println(“Arquivo de config não encontrado, usando padrões.”);
        return;
    }

    if (arquivo.available())
    {
        horarios[0] = arquivo.readStringUntil('\n');
    }
    if (arquivo.available())
    {
        horarios[1] = arquivo.readStringUntil('\n');
    }
    if (arquivo.available())
    {
        horarios[2] = arquivo.readStringUntil('\n');
    }
    if (arquivo.available())
    {
        tempoMotorLigado = arquivo.readStringUntil('\n').toFloat();
    }

    horarios[0].trim();
    horarios[1].trim();
    horarios[2].trim();

    arquivo.close();
    Serial.println("Configurações carregadas do SPIFFS.");
}