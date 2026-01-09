# 🏎️ Painel Digital ESP32 (Baja/Veicular)

Projeto desenvolvido por **Wellington Marciano**, para o sistema de instrumentação do primeiro protótipo, chamado carinhosamente de **BR-01** pela equipe **Baja dos Reis** (2021 - 2025), projeto de extensão Baja-SAE.

**Propósito:** O intuito deste repositório é servir de suporte para pequenas equipes que estão em desenvolvimento, promovendo a troca de ideias sobre como criar um painel funcional de baixo custo e facilitando a utilização do ESP32 com o simulador Wokwi no VS Code.

O sistema consiste em um painel de instrumentos digital completo utilizando **ESP32** e display **TFT**. Ele monitora velocidade, rotação (RPM), temperatura do motor e nível de combustível em tempo real.

![Status do Projeto](https://img.shields.io/badge/Status-Funcional-green)
![Hardware](https://img.shields.io/badge/Hardware-ESP32-blue)
![Simulador](https://img.shields.io/badge/Simulador-Wokwi-orange)
![Instalação](https://img.shields.io/badge/Instalação-Plug_&_Play-brightgreen)


<div align="center">
  <img width="80%" src="https://github.com/user-attachments/assets/978eb178-02ba-4564-bdb1-f44cea07a9ed" />
  <br>
  <sub>Interface Principal do Sistema</sub>
</div>

## ⚡ Funcionalidades

* **Velocímetro e Tacômetro:** Leitura via sensor magnético (Hall) com cálculo de **km/h**, **RPM** e **RPS**.
* **Filtro de Ruído:** Implementação de média móvel (15 amostras) para estabilizar a leitura da velocidade.
* **Monitoramento Térmico:** Leitura precisa de temperatura do motor via sensor **DS18B20**.
* **Nível de Combustível Inteligente:** Sistema de dois sensores capacitivos com lógica visual:
    * 🟢 **Cheio:** Ambos sensores ativos.
    * 🟡 **Médio:** Apenas um sensor ativo.
    * 🔴 **Crítico:** Ambos inativos (Alerta piscante na tela).
* **Interface Gráfica (GUI):** Interface responsiva criada com **GUIslice** e barra de carregamento (loading screen) na inicialização.

<div align="center">
  <img src="https://github.com/user-attachments/assets/8182d2cd-37f3-4b42-9b4b-951f2ce36a80" width="45%" alt="Tela de Boot" />
  <img src="https://github.com/user-attachments/assets/04afe296-bbce-48be-a2b9-5407437a4e7f" width="45%" alt="GUIslice Builder" />
  <br>
  <sub>Esq: Tela de Inicialização | Dir: Design no GUIslice Builder</sub>
</div>

## 🎮 Simulação no Wokwi

Este projeto está configurado para rodar nativamente no simulador **Wokwi** via VS Code, permitindo testar o código e a interface sem precisar do hardware físico.

### ⚠️ Atenção ao Editar a Interface
O design das telas é gerado pela ferramenta **GUIslice Builder**. Os arquivos `.ino` e `.h` (cabeçalho) contêm áreas geradas automaticamente pelo software e áreas onde reside a sua lógica customizada.

* O arquivo **`src/Baja_GSLC.h`** (e partes do `.ino`) é atualizado automaticamente pelo Builder quando você salva mudanças no layout.
* **Cuidado:** Ao regenerar o código pelo GUIslice Builder, certifique-se de **não sobrescrever** as funções lógicas manuais (como cálculos de sensores e `void loop`). O código está estruturado com tags como `//<App !Start!>` para guiar onde é seguro editar.

> **Dica:** O arquivo de projeto do GUIslice (`.prj`) está incluído na pasta `src`. Você pode abri-lo no GUIslice Builder para modificar cores e posições dos botões, e depois salvar para atualizar o código automaticamente.

## 🛠️ Hardware Necessário

<div align="center">

| Componente | Quantidade | Descrição |
| :--- | :---: | :--- |
| **ESP32 DevKit V1** | 1 | Microcontrolador principal |
| **Display TFT 2.4"** | 1 | Driver ILI... ou outro (SPI) |
| **Sensor DS18B20** | 1 | Sensor de temperatura à prova d'água |
| **Sensor Hall/Indutivo** | 1 | Para leitura de RPM/Velocidade |
| **Sensores Capacitivos**| 2 | Para nível de combustível |
| **Placa de Filtro** | 1 | Condicionamento de sinal (12V -> 3.3V) |
| **Ímãs de Neodímio** | 10 | Fixados na roda para leitura de velocidade |

</div>

> ⚠️ **Nota Técnica:** Neste projeto, utilizamos uma placa de filtro customizada (veja o esquemático abaixo). O Pull-up para o sensor DS18B20 já está acoplado internamente no chicote.
>
> **Importante:** No protótipo atual (BR-01) utilizamos apenas **1 ímã no disco** de freio. Lembre-se de alterar a variável `NumeroDeImas` no código antes de gravar.

### 🔌 Esquemático
<div align="center">
  <img width="80%" src="https://github.com/user-attachments/assets/9dd35826-6fe1-48f0-954c-dd8cb595c772" alt="Esquemático do Projeto" />
  <br>
  <sub>Diagrama de conexões elétricas</sub>
</div>

## 📍 Pinout Detalhado

### 🖥️ Display TFT (SPI)

<div align="center">

| Pino Display | Pino ESP32 | Notas |
| :--- | :--- | :--- |
| **VCC** | 3.3V | Alimentação |
| **GND** | GND | Terra |
| **CS** | GPIO 22 | Chip Select |
| **RESET** | GPIO 4 | Reset |
| **DC** | GPIO 21 | Data/Command |
| **MOSI** | GPIO 23 | Dados SPI |
| **SCK** | GPIO 18 | Clock SPI |
| **LED** | 3.3V | Backlight |

</div>

### ⚙️ Sensores

<div align="center">

| Sensor | Pino ESP32 | Detalhes |
| :--- | :--- | :--- |
| **Temperatura (DS18B20)** | **GPIO 32** | Dados (Pull-up via hardware) |
| **Velocidade (RPM)** | **GPIO 33** | Sensor Hall (Interrupção Externa) |
| **Combustível (Nível 1)** | **GPIO 34** | Entrada Digital (Sensor Capacitivo) |
| **Combustível (Nível 2)** | **GPIO 35** | Entrada Digital (Sensor Capacitivo) |

</div>

> ⚠️ **Atenção:** Os pinos **34 e 35** são *Input Only* e não possuem pull-up interno. A nossa **Placa de Filtro** realiza o tratamento elétrico necessário (optoacoplador/divisor), garantindo a leitura correta.

## 🚀 Instalação (Plug & Play)

Este projeto foi configurado para ser **"Baixar e Usar"**.
Todas as bibliotecas necessárias já estão inclusas dentro da pasta `lib`. **Você não precisa instalar nada manualmente.**

### ⚡ Passo a Passo Rápido

1. **Baixe o Código:**
   - Clique em `<> Code` no topo desta página e selecione **"Download ZIP"**.
   - Extraia a pasta no seu computador.

2. **Abra e Grave:**

   #### 🟢 Via VS Code (Recomendado)
   - Certifique-se de ter as extensões **Wokwi Simulator** e **PlatformIO** instaladas.
   - Abra a pasta extraída no VS Code.
   - O **PlatformIO** vai configurar tudo sozinho.
   - Clique no **Check (✔)** para compilar e abra o arquivo `.json` para iniciar o simulador.

   #### 🔵 Via Arduino IDE
   - Abra o arquivo `src/Baja.ino`.
   - Copie as pastas de dentro de `lib` para a sua pasta de bibliotecas do Arduino (geralmente em `Documentos/Arduino/libraries`).
   - Instale o suporte à placa **ESP32** no gerenciador de placas.
   - Selecione a porta e clique em **Carregar**.

## ⚙️ Configuração da Roda

Antes de gravar, ajuste as variáveis no início do código para calibrar o velocímetro:

```cpp
unsigned int NumeroDeImas = 10;  // Quantidade de ímãs na roda (Ajuste para 1 no BR-01)
float RaioDaRoda = 0.265;        // Raio da roda em metros
```

## 🎥 Próximos Passos (Em Breve)

Para facilitar ainda mais a reprodução deste projeto, estou produzindo um **tutorial completo em vídeo** que cobrirá todo o processo de desenvolvimento.

O conteúdo incluirá:
* 📐 Explicação detalhada do **Esquemático e Eletrônica**.
* 🎨 Criação e edição da interface passo-a-passo no **GUIslice Builder**.
* 💻 Lógica do código e como editar para o seu veículo.
* ☁️ Como subir e testar o projeto no simulador **VS Code e Wokwi**.

**Previsão de lançamento:** Em cerca de 2 meses.
> *Dica: Clique em "Watch" ou "Star" ⭐ no topo desta página para ser notificado quando o vídeo sair!*

## ⚖️ Licença e Atribuição

Este projeto está sob a licença MIT. Isso significa que você pode replicá-lo livremente para fins de estudo ou em sua própria equipe de Baja/Fórmula.

**🤝 Como contribuir:**
Se este projeto foi útil para você ou sua equipe, pedimos gentilmente que nos dê o crédito:
1. Mantenha o cabeçalho de autoria nos arquivos de código.
2. Se postar nas redes sociais, marque a **@BajaDosReis** e o **@marciano_well**.
3. Se usar em competições, cite no **Design Report** ou apresentações de projeto.

> "A engenharia cresce quando compartilhamos conhecimento."

### Autor

<a href="https://www.linkedin.com/in/wellington-marciano-aa02a5235/">
  <img src="https://img.shields.io/badge/LinkedIn-Wellington%20Marciano-blue?style=flat&logo=linkedin">
</a>
