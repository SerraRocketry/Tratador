# Tratador Automático

Aqui você pode descrever o que o projeto faz, suas funcionalidades e objetivos.

## Funcionalidades
- Descrição de funcionalidades do projeto.

## Hardware
- Descrição do hardware utilizado (ex: Arduino Uno, Mega, etc.)
- Descrição de sensores, atuadores e outros componentes.

## Configuração de Pinos
- Descrição dos pinos utilizados no Arduino e suas funções.
- Exemplo:
  - **Pino 2**: Sensor de temperatura
  - **Pino 3**: LED indicador

## Bibliotecas Utilizadas
- Descrição das bibliotecas utilizadas no projeto.
- Exemplo:
  - `Wire.h`: Comunicação I2C
  - `SPI.h`: Comunicação SPI

## Estrutura do Projeto
A estrutura do projeto é organizada da seguinte forma:
```
/home/viniciusmonnerat/Documentos/Serra Rocketry/Tratador2/
├── docs/                     # Documentação (diagramas, imagens, datasheets)
├── firmware/                 # Código principal do Arduino
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
    git clone url_do_repositorio.git
    ```
2. Navegue até o diretório do projeto
    ```bash
    cd /home/viniciusmonnerat/Documentos/Serra Rocketry/Tratador2
    ```
3. Abra o arquivo `firmware/firmware.ino` no Arduino IDE
    ```bash
    arduino firmware/firmware.ino
    ```
    ou abra o Arduino IDE e selecione `File > Open` e escolha o arquivo `firmware.ino`.
4. Carregue o código no seu Controlador

## Contribuições
- Sinta-se à vontade para contribuir com melhorias, correções de bugs ou novas funcionalidades.
- Para contribuir, siga as instruções no arquivo `contributing.md`.
