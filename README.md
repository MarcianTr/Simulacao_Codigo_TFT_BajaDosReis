# 🏎️ Painel Digital ESP32 (Baja/Veicular)

Projeto desenvolvido por **Wellington Marciano**, para o sistema de instrumentação do primeiro protótipo, chamado carinhosamente de **BR-01** pela equipe **Baja dos Reis** (2021 - 2025), projeto de extensão Baja-SAE.

**Propósito:** O intuito deste repositório é servir de suporte para pequenas equipes que estão em desenvolvimento, promovendo a troca de ideias sobre como criar um painel funcional de baixo custo.

O sistema consiste em um painel de instrumentos digital completo utilizando **ESP32** e display **TFT**. Ele monitora velocidade, rotação (RPM), temperatura do motor e nível de combustível em tempo real.

![Status do Projeto](https://img.shields.io/badge/Status-Funcional-green)
![Hardware](https://img.shields.io/badge/Hardware-ESP32-blue)
![Bibliotecas](https://img.shields.io/badge/Bibliotecas-Inclusas-orange)

<div align="center">
  <img width="80%" src="https://github.com/user-attachments/assets/ca4ef5bf-b569-474c-8ad7-47992c2b9b98" />
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
* **Interface Gráfica (GUI):** Interface responsiva criada com **GUIslice**.

<div align="center">
  <img src="https://github.com/user-attachments/assets/8182d2cd-37f3-4b42-9b4b-951f2ce36a80" width="45%" alt="Tela de Boot" />
  <img src="https://github.com/user-attachments/assets/04afe296-bbce-48be-a2b9-5407437a4e7f" width="45%" alt="GUIslice Builder" />
  <br>
  <sub>Esq: Tela de Inicialização | Dir: Design no GUIslice Builder</sub>
</div>

## 🛠️ Hardware Necessário

| Componente | Quantidade | Descrição |
| :--- | :---: | :--- |
| **ESP32 DevKit V1** | 1 | Microcontrolador principal |
| **Display TFT 2.4"** | 1 | Driver ILI... ou outro (SPI) |
| **Sensor DS18B20** | 1 | Sensor de temperatura à prova d'água |
| **Sensor Hall/Indutivo** | 1 | Para leitura de RPM/Velocidade |
| **Sensores Capacitivos**| 2 | Para nível de combustível |
| **Placa de Filtro** | 1 | Condicionamento de sinal (12V -> 3.3V) |
| **Ímãs de Neodímio** | 10 | Fixados na roda para leitura de velocidade |

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

### ⚙️ Sensores
| Sensor | Pino ESP32 | Detalhes |
| :--- | :--- | :--- |
| **Temperatura (DS18B20)** | **GPIO 32** | Dados (Pull-up via hardware) |
| **Velocidade (RPM)** | **GPIO 33** | Sensor Hall (Interrupção Externa) |
| **Combustível (Nível 1)** | **GPIO 34** | Entrada Digital (Sensor Capacitivo) |
| **Combustível (Nível 2)** | **GPIO 35** | Entrada Digital (Sensor Capacitivo) |

> ⚠️ **Atenção:** Os pinos **34 e 35** são *Input Only* e não possuem pull-up interno. A nossa **Placa de Filtro** realiza o tratamento elétrico necessário (optoacoplador/divisor), garantindo a leitura correta.

## 🚀 Como Instalar e Compilar

Este repositório já contém todas as dependências necessárias na pasta `lib`. **Você não precisa baixar bibliotecas manualmente.**

### Opção 1: Usando VS Code + PlatformIO (Recomendado)
1. Clone ou baixe este repositório.
2. Abra a pasta do projeto no **VS Code**.
3. O PlatformIO reconhecerá automaticamente a estrutura e as bibliotecas locais (`GUIslice`, `DallasTemperature`, `OneWire`, `TFT_eSPI`).
4. Clique em **Upload** para gravar no ESP32.

### Opção 2: Usando Arduino IDE
1. Baixe o projeto.
2. Abra o arquivo principal.
3. Copie as pastas de `lib` para a pasta `libraries` do seu Arduino caso tenha problemas de compilação.

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
