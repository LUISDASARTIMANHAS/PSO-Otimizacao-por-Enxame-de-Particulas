# Título do Projeto: Otimização por Enxame de Partículas (PSO) para Minimização da Função Eggholder

## 1. Resumo

Este projeto implementa um algoritmo de Otimização por Enxame de Partículas (PSO) para resolver o problema de minimização da função Eggholder. A função Eggholder é um benchmark clássico em otimização, conhecida por sua complexidade devido à presença de múltiplos mínimos locais e um mínimo global desafiador de ser encontrado. O objetivo principal é demonstrar a eficácia do PSO na busca por soluções ótimas em espaços de busca complexos, analisando seu desempenho sob diferentes configurações de parâmetros e critérios de parada.

## 2. Introdução

A otimização é um campo fundamental em diversas áreas da ciência e engenharia, buscando encontrar os melhores parâmetros para um determinado problema. Algoritmos meta-heurísticos, como o Otimização por Enxame de Partículas (PSO), têm se mostrado eficientes na resolução de problemas de otimização complexos onde métodos tradicionais podem falhar. Este trabalho foca na aplicação do PSO para minimizar a função Eggholder, uma função bidimensional com características que a tornam um excelente caso de teste para algoritmos de otimização. Serão exploradas as configurações do algoritmo, os critérios de parada e a análise estatística dos resultados para avaliar a robustez e a precisão do PSO.

## 3. Fundamentação Teórica: Otimização por Enxame de Partículas (PSO)

O Otimização por Enxame de Partículas (PSO) é uma meta-heurística inspirada no comportamento social de bandos de pássaros ou cardumes de peixes. Cada "partícula" no enxame representa uma solução potencial no espaço de busca e ajusta sua trajetória com base em sua própria melhor experiência (pBest) e na melhor experiência de todo o enxame (gBest). O algoritmo é iterativo e as posições e velocidades das partículas são atualizadas a cada passo, conforme as equações:

- **Atualização da Velocidade:**
  `v_i(t+1) = W * v_i(t) + φ1 * rand1() * (pBest_i - x_i(t)) + φ2 * rand2() * (gBest - x_i(t))`

- **Atualização da Posição:**
  `x_i(t+1) = x_i(t) + v_i(t+1)`

Onde:
- `v_i(t)` é a velocidade da partícula `i` no tempo `t`.
- `x_i(t)` é a posição da partícula `i` no tempo `t`.
- `W` é o fator de inércia, controlando a influência da velocidade anterior.
- `φ1` e `φ2` são os coeficientes de aceleração, representando a influência do `pBest` e `gBest`, respectivamente.
- `rand1()` e `rand2()` são números aleatórios uniformemente distribuídos entre 0 e 1.
- `pBest_i` é a melhor posição encontrada pela partícula `i` até o momento.
- `gBest` é a melhor posição encontrada por qualquer partícula no enxame até o momento.

## 4. Problema Abordado: Função Eggholder

A função Eggholder é uma função de teste de otimização bidimensional, definida pela equação:

`f(x, y) = -(y + 47) * sin(sqrt(abs(x/2 + (y + 47)))) - x * sin(sqrt(abs(x - (y + 47))))`

Esta função é caracterizada por múltiplos mínimos locais e um mínimo global em `f(512, 404.2319) = -959.6407`. O domínio de busca para `x` e `y` é tipicamente `[-512, 512]`. A complexidade da função Eggholder a torna um desafio significativo para algoritmos de otimização, exigindo estratégias robustas para evitar a convergência prematura em mínimos locais.

## 5. Metodologia

A metodologia empregada neste projeto para a otimização da função Eggholder utilizando PSO segue os seguintes passos:

### 5.1. Configuração do Algoritmo PSO

- **Número de Partículas (População):** Serão testadas populações de 50 e 100 indivíduos.
- **Inicialização:** As posições iniciais (`x`) de cada partícula serão inicializadas aleatoriamente dentro do espaço de busca `[-512, 512]` para ambas as dimensões. As velocidades iniciais (`v`) serão geradas aleatoriamente, limitadas a 15% do espaço de busca de cada parâmetro (aproximadamente `[-77, +77]`).
- **Parâmetros do Algoritmo:** Os parâmetros `W`, `φ1` e `φ2` serão definidos com base na literatura para garantir um bom equilíbrio entre exploração e explotação do espaço de busca.

### 5.2. Limites de Velocidade e Posição

- **Limite de Velocidade (`v_max`):** Serão impostos limites para a velocidade de cada partícula em cada dimensão para evitar que o sistema extrapole o espaço de busca.
- **Correção de Posição:** Caso uma partícula saia do intervalo `[-512, 512]`, sua posição será corrigida para o limite máximo ou mínimo do intervalo, e sua velocidade será zerada para aquela dimensão.

### 5.3. Critérios de Parada

O critério de parada será baseado no número máximo de iterações. Serão realizadas simulações com 20, 50 e 100 iterações para analisar o impacto do número de gerações na qualidade da solução.

### 5.4. Análise Estatística

Para cada configuração de parâmetros e critério de parada, serão realizadas 10 execuções independentes. Os resultados serão analisados estatisticamente, registrando-se:
- **Melhor resultado:** O valor mínimo da função encontrado.
- **Média dos resultados:** A média dos valores mínimos encontrados nas 10 execuções.
- **Desvio padrão:** Uma medida da dispersão dos resultados.

Serão gerados gráficos da curva de convergência, mostrando o melhor resultado e a média dos resultados ao longo das iterações para cada cenário.

## 6. Tecnologias Utilizadas

- **Linguagem de Programação:** C (conforme indicado pelos arquivos `pso.c` e `pso.h`).
- **Ferramentas de Compilação:** `compile.cmd` (provavelmente GCC ou similar via linha de comando).
- **Análise de Dados:** `resultados.csv` indica a exportação de dados para análise posterior, possivelmente com ferramentas como Python (Pandas, Matplotlib) ou planilhas eletrônicas.

## 7. Resultados e Análise

*Esta seção será preenchida após a execução das simulações e a análise dos dados coletados. Incluirá tabelas comparativas, gráficos de convergência e uma discussão aprofundada sobre o desempenho do algoritmo PSO em diferentes cenários.*

## 8. Conclusão

*Esta seção apresentará as conclusões obtidas a partir dos resultados e análises, destacando a eficácia do PSO na minimização da função Eggholder e possíveis direções para trabalhos futuros.*

## 9. Como Compilar e Executar

Para compilar o projeto, utilize o script `compile.cmd`.
Para executar o algoritmo, siga as instruções específicas do executável gerado.

## 10. Referências

*Esta seção listará todas as referências bibliográficas utilizadas no desenvolvimento e análise deste projeto.*