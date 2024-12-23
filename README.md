# Rede-em-Chip XINA - eXtensible Interconnect Network Architecture para Aplicações Espaciais

Autor: Laboratory of Embedded and Distributed Systems (LEDS - UNIVALI) CONTACT: Prof. Douglas Rossi de Melo (drm@univali.br)

Reviews 
  | Date - Version - Author | Description
  
  | 20/01/2023 - 1.0 - Welliton da Silva de Lima | Initial Modeling in SystemC

Este projeto implementa uma **Rede-em-Chip** utilizando a biblioteca **SystemC**, projetada especificamente para aplicações espaciais. A arquitetura inclui mecanismos de proteção para 
garantir comunicação confiável e execução correta em ambientes adversos, como o espaço, onde os sistemas estão sujeitos a radiação e falhas transientes.

---

## 🚀 Sobre o Projeto

As Redes-em-Chip são essenciais para sistemas embarcados complexos, fornecendo comunicação eficiente entre múltiplos núcleos. Este projeto é voltado para ambientes 
espaciais e incorpora proteções como:

- **Tolerância a falhas transientes**.
- **Correção de erros** em pacotes de comunicação.
- **Roteamento seguro** para mitigar falhas em nós ou canais.
- **Desempenho otimizado** para operações em ambientes de baixa energia.

O projeto foi desenvolvido com **SystemC**, uma biblioteca de simulação em nível de sistema amplamente usada na indústria de hardware.

---

## 🛠️ Funcionalidades

- **Topologia Configurável**:
  - Suporte a malhas 2D.
- **Tolerância a Falhas**:
  - Redundância modular tripla.
- **Roteamento XY**:
  - O pacote segue o caminho em X depois em Y.
- **Simulação**:
  - Simulação utilizando testebench em SystemC.

---

## 🌌 Aplicações

Este modelo é voltado para:

- Sistemas embarcados para satélites.
- Comunicação entre processadores em sistemas com proteção as adversidades do espaço.
- Simulação de redes de interconexão para aplicações espaciais.

---

## 🚀 Como executar

### Pré-requisitos

1. **SystemC**:
   - Baixe a biblioteca SystemC em: [https://www.accellera.org/downloads/standards/systemc](https://www.accellera.org/downloads/standards/systemc).
   - Compile e instale no seu sistema.

2. **Compilador C++**:
   - GCC (Linux) com suporte para C++11 ou superior.

3. **Código-fonte**:
   - Clone ou baixe o repositório:
     ```bash
     git clone https://github.com/Welliton-Lima/rede-em-chip-espacial.git
     ```

---

### Passos para compilar e executar

1. Navegue até o diretório do projeto:
   ```bash
   cd "rede-em-chip"
   
Compile o projeto
Exemplo:
  g++ -I/path/to/systemc/include -L/path/to/systemc/lib -lsystemc -o XINA.cpp

📜 Exemplos de Uso

  Configuração Padrão:
        Uma malha 2x2 com 4 roteadores conectados.
        Fluxo de pacotes simples para testar a comunicação.
