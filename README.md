# TASforWifi
Simulações de Time-Aware Shaping (TAS) em Wi-Fi

Este repositório contém todos os arquivos necessários para reproduzir as simulações realizadas no projeto de implementação de Time-Aware Shaping (TAS) em redes Wi-Fi baseadas no padrão IEEE 802.11.

Estrutura do Repositório

1. app

Contém a implementação do FTM App, responsável pela troca de mensagens UDP e sincronização de clocks entre nós usando o protocolo UDP.

2. linklayer

Inclui o modelo padrão de Wi-Fi IEEE 802.11 e suas modificações para suportar o Time-Aware Shaping (TAS) como mecanismo de Qualidade de Serviço (QoS).

Arquivos principais:

- Entrega_Final_2/linklayer/ieee80211/mac/queue/TimeAwareShaperWifi.ned

- Entrega_Final_2/linklayer/ieee80211/mac/queue/PendingQueue.cc

3. Simulation

Contém os arquivos de configuração das simulações:

- Arquivos .ned para a definição da topologia da rede.

- Arquivos .ini para configuração dos parâmetros de simulação.

4. TAS_Components

Abriga modelos de componentes relacionados ao TAS, como gates, filas e classificadores. Esses componentes foram adaptados e modificados para atender às necessidades específicas do projeto.

5. TASGate

Contém a implementação do TASGate desenvolvido especificamente para o projeto. Ele substitui o PeriodicGate, que não atendia aos requisitos de previsibilidade e controle necessários para as simulações.


