# Tratador Automático para Pets

Um alimentador automático para pets, baseado na plataforma ESP8266, que permite o controle e agendamento da alimentação através de uma interface web acessível pela rede Wi-Fi.

O projeto visa oferecer uma solução de baixo custo e alta flexibilidade para cuidar da alimentação de animais de estimação, garantindo que recebam a quantidade correta de ração nos horários programados, mesmo na ausência do dono. As configurações são salvas na memória interna do dispositivo, persistindo mesmo após uma queda de energia.

## Funcionalidades

- Interface Web Integrada: Permite configurar os horários e a quantidade de ração de qualquer dispositivo com navegador na mesma rede local.
- Agendamento Triplo: Suporta a programação de três horários de alimentação diários (manhã, tarde e noite).
- Controle de Quantidade: A quantidade de ração é ajustável, baseada no tempo em que o motor dispensador permanece ativo.
- Persistência de Dados: As configurações de horário e quantidade são salvas na memória flash (SPIFFS) do ESP8266 e não se perdem ao reiniciar o dispositivo.
- Sincronização de Horário via Internet (NTP): O horário é obtido de servidores na internet, garantindo precisão sem a necessidade de um módulo de relógio (RTC) externo.
- Função de Teste: A interface web possui um botão para acionar o motor manualmente, facilitando a calibração da quantidade de ração.

## Hardware

- Controlador: ESP8266 (Wemos D1 Mini), escolhido por seu Wi-Fi integrado e baixo custo.
- Atuador: Servo Motor (ex: SG90 ou MG996R) para controlar o mecanismo que libera a ração.
- Fonte de Alimentação: Fonte externa de 5V / 2A para alimentar de forma estável o ESP8266 e o Servo Motor, garantindo que o consumo do motor não afete o controlador.

## Configuração de Pinos

- Pino D4 (GPIO2): Saída de sinal PWM para controle do Servo Motor.

## Bibliotecas Utilizadas

- `ESP8266WiFi.h`
- `ESP8266WebServer.h`
- `Servo.h`
- `FS.h`
- `ArduinoJson.h`
- `time.h`

## Estrutura do Projeto

A estrutura do projeto é organizada da seguinte forma:

```
Tratador/
├── docs/                     # Documentação (diagramas, imagens, datasheets)
├── firmware/                 # Código principal do ESP8266
│   ├── data/                 # Arquivos para o SPIFFS (ex: index.html)
│   └── firmware.ino
├── hardware/                 # Arquivos e informações do hardware
├── lib/                      # Bibliotecas personalizadas ou adaptadas
├── test/                     # Scripts de teste (verificação, debug, etc.)
├── extras/                   # Scripts auxiliares (ex: leitura serial em Python)
├── .gitignore                # Arquivos e pastas ignorados pelo Git
├── README.md                 # Descrição do projeto
└── contributing.md           # (Opcional) Como contribuir com o projeto
```

## Como usar

1. Clone o repositório
   ```bash
   git clone https://github.com/SerraRocketry/Tratador.git
   ```
2. Navegue até o diretório do projeto
   ```bash
   cd /Tratador
   ```
3. Abra o arquivo `firmware/firmware.ino` no Arduino IDE

   ```bash
   arduino firmware/firmware.ino
   ```

   ou abra o Arduino IDE e selecione `File > Open` e escolha o arquivo `firmware.ino`.

4. Instale o Uploader de Arquivos: Siga as instruções para instalar a ferramenta "ESP8266 Sketch Data Upload" na sua Arduino IDE.

5. Envie a Interface Web: Coloque o arquivo index.html na pasta firmware/data/ e, na Arduino IDE, vá em Ferramentas > ESP8266 Sketch Data Upload para enviar os arquivos para a memória do ESP8266.

6. Configure e Carregue: Altere as credenciais do seu Wi-Fi (ssid e password) no código e carregue o sketch para a sua placa ESP8266.

7. Acesse: Abra o Monitor Serial para visualizar o endereço de IP que o ESP8266 recebeu. Digite esse IP no seu navegador para acessar a interface de controle.

## Contribuições

- Sinta-se à vontade para contribuir com melhorias, correções de bugs ou novas funcionalidades.