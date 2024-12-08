#include "pso.h"

// Funções matemáticas customizadas
double raizQuadradaPersonalizada(double numero) {
    double chute = numero / 2.0;
    double epsilon = 0.00001;
    if (numero < 0) return -1;
    while ((chute * chute - numero) > epsilon || (numero - chute * chute) > epsilon) {
        chute = (chute + numero / chute) / 2.0;
    }
    return chute;
}

double valorAbsolutoPersonalizado(double numero) {
    return numero < 0 ? -numero : numero;
}

double senoPersonalizado(double x) {
    double termo = x, resultado = termo;
    int n = 1, sinal = -1;
    while (valorAbsolutoPersonalizado(termo) > 0.00001) {
        termo *= x * x / ((2 * n) * (2 * n + 1));
        resultado += sinal * termo;
        sinal *= -1;
        n++;
    }
    return resultado;
}

// Função objetivo (Eggholder)
double eggholder(double x, double y) {
    return -(y + 47) * senoPersonalizado(raizQuadradaPersonalizada(valorAbsolutoPersonalizado((x / 2) + y + 47))) - 
           x * senoPersonalizado(raizQuadradaPersonalizada(valorAbsolutoPersonalizado(x - (y + 47))));
}

// Inicializa o enxame
void inicializarEnxame(Swarm *enxame, int numParticulas, int dimensoes, double posMin, double posMax, double velMax) {
    enxame->particles = (Particle *)malloc(numParticulas * sizeof(Particle));
    enxame->globalBestPosition = (double *)malloc(dimensoes * sizeof(double));
    enxame->globalBestFitness = DBL_MAX;
    enxame->numParticles = numParticulas;
    enxame->dimensions = dimensoes;

    for (int i = 0; i < numParticulas; i++) {
        Particle *p = &enxame->particles[i];
        p->position = (double *)malloc(dimensoes * sizeof(double));
        p->velocity = (double *)malloc(dimensoes * sizeof(double));
        p->bestPosition = (double *)malloc(dimensoes * sizeof(double));
        p->fitness = DBL_MAX;
        p->bestFitness = DBL_MAX;

        for (int d = 0; d < dimensoes; d++) {
            p->position[d] = posMin + (posMax - posMin) * ((double)rand() / RAND_MAX);
            p->velocity[d] = -velMax + 2 * velMax * ((double)rand() / RAND_MAX);
            p->bestPosition[d] = p->position[d];
        }
    }
}

// Avalia a aptidão
double avaliarAptidao(double *posicao) {
    return eggholder(posicao[0], posicao[1]);
}

// Atualiza velocidade
void atualizarVelocidade(Particle *particula, double *globalBestPosition, int dimensoes, double w, double c1, double c2) {
    // a) Atualize a velocidade da partícula pela fórmula:
    
    for (int d = 0; d < dimensoes; d++) {
        double r1 = (double)rand() / RAND_MAX;
        double r2 = (double)rand() / RAND_MAX;
        particula->velocity[d] = w * particula->velocity[d] +
                                 c1 * r1 * (particula->bestPosition[d] - particula->position[d]) +
                                 c2 * r2 * (globalBestPosition[d] - particula->position[d]);
    }
}

// Atualiza posição
void atualizarPosicao(Particle *particula, double posMin, double posMax, int dimensoes) {
//     (b) Atualize a posição da particular pela fórmula:
    //  x (t +1)  x (t)+ v (t +1)
    for (int d = 0; d < dimensoes; d++) {
        particula->position[d] += particula->velocity[d];
        if (particula->position[d] < posMin) {
            particula->position[d] = posMin;
            particula->velocity[d] = 0;
        } else if (particula->position[d] > posMax) {
            particula->position[d] = posMax;
            particula->velocity[d] = 0;
        }
    }
}

// Atualiza melhores posições
void atualizarMelhoresPosicoes(Swarm *enxame) {
    for (int i = 0; i < enxame->numParticles; i++) {
        Particle *p = &enxame->particles[i];
        p->fitness = avaliarAptidao(p->position);
        if (p->fitness < p->bestFitness) {
            p->bestFitness = p->fitness;
            for (int d = 0; d < enxame->dimensions; d++) {
                p->bestPosition[d] = p->position[d];
            }
        }
        if (p->fitness < enxame->globalBestFitness) {
            enxame->globalBestFitness = p->fitness;
            for (int d = 0; d < enxame->dimensions; d++) {
                enxame->globalBestPosition[d] = p->position[d];
            }
        }
    }
}

// Executa PSO
double executarPSO(Swarm *enxame, int iteracoes, double w, double c1, double c2, double posMin, double posMax) {
    for (int iter = 0; iter < iteracoes; iter++) {
        for (int i = 0; i < enxame->numParticles; i++) {
            Particle *p = &enxame->particles[i];
            atualizarVelocidade(p, enxame->globalBestPosition, enxame->dimensions, w, c1, c2);
            atualizarPosicao(p, posMin, posMax, enxame->dimensions);
        }
        atualizarMelhoresPosicoes(enxame);
    }
    return enxame->globalBestFitness;
}

// Calcula média
double calcularMedia(double *resultados, int tamanho) {
    double soma = 0.0;
    for (int i = 0; i < tamanho; i++) {
        soma += resultados[i];
    }
    return soma / tamanho;
}

// Calcula desvio padrão
double calcularDesvioPadrao(double *resultados, int tamanho, double media) {
    double soma = 0.0;
    for (int i = 0; i < tamanho; i++) {
        soma += (resultados[i] - media) * (resultados[i] - media);
    }
    return raizQuadradaPersonalizada(soma / tamanho);
}

void executarEnxame(int populacoes[2], int rodadasPorPopulacao, double resultados[10], int iteracoes[3], int iter){
    for (int execucao = 0; execucao < 10; execucao++){
        Swarm enxame;
        inicializarEnxame(&enxame, populacoes[rodadasPorPopulacao], 2, -512, 512, 77);
        resultados[execucao] = executarPSO(&enxame, iteracoes[iter], 0.5, 1.5, 1.5, -512, 512);
        free(enxame.globalBestPosition);

        for (int i = 0; i < populacoes[rodadasPorPopulacao]; i++){
            free(enxame.particles[i].position);
            free(enxame.particles[i].velocity);
            free(enxame.particles[i].bestPosition);
        }
        free(enxame.particles);
    }
}

void execucoes(int populacoes[2], int p, double resultados[10], int iteracoes[3], int iter, FILE *arquivo){
        for (int execucao = 0; execucao < 10; execucao++)
        {
            Swarm enxame;
            inicializarEnxame(&enxame, populacoes[p], 2, -512, 512, 77);
            resultados[execucao] = executarPSO(&enxame, iteracoes[iter], 0.5, 1.5, 1.5, -512, 512);
            free(enxame.globalBestPosition);
            for (int i = 0; i < populacoes[p]; i++)
            {
                free(enxame.particles[i].position);
                free(enxame.particles[i].velocity);
                free(enxame.particles[i].bestPosition);
            }
            free(enxame.particles);
        }
        double media = calcularMedia(resultados, 10);
        double desvioPadrao = calcularDesvioPadrao(resultados, 10, media);
        fprintf(arquivo, "Populacao: %d, Iteracoes: %d, Melhor: %.6f, Media: %.6f, DesvioPadrao: %.6f\n",
                populacoes[p], iteracoes[iter], resultados[0], media, desvioPadrao);
    }

void executarInteracao(int populacoes[2], int p, int iteracoes[3], FILE *arquivo){
    for (int iter = 0; iter < 3; iter++){
        double resultados[10];
        execucoes(populacoes, p, resultados, iteracoes, iter, arquivo);
    }
}


void gerarRelatorio(FILE *arquivo, int populacoes[2], int rodadasPorPopulacao, int iteracoes[3], int iter, double resultados[10], double media, double desvioPadrao){
    int populacao = populacoes[rodadasPorPopulacao];
    int inters = iteracoes[iter];
    double melhor = resultados[0];

    fWiriteSTRING(arquivo, "População: ");
    fWiriteINT(arquivo, populacao);
    printf("População: %d",populacao);

    fWiriteSTRING(arquivo, ", Iterações: ");
    fWiriteINT(arquivo, inters);
    printf(", Iterações: %d",inters);

    fWiriteSTRING(arquivo, ", Melhor: ");
    fWiriteFLOAT(arquivo, melhor);
    printf(", Melhor: %0.6f",melhor);

    fWiriteSTRING(arquivo, ", Media: ");
    fWiriteFLOAT(arquivo, media);
    printf(", Media: %0.6f",media);

    fWiriteSTRING(arquivo, ", DesvioPadrão: ");
    fWiriteFLOAT(arquivo, desvioPadrao);
    printf(", DesvioPadrão: %0.6f",desvioPadrao);
    fWiriteLN(arquivo);
}

void inicializar(int populacoes[2], int iteracoes[3], FILE *arquivo){
    for (int rodadasPorPopulacao = 0; rodadasPorPopulacao < 3; rodadasPorPopulacao++)
    {
        for (int iter = 0; iter < 3; iter++)
        {
            double resultados[10];
            double media;

                executarEnxame(populacoes, rodadasPorPopulacao, resultados, iteracoes, iter);
                media = calcularDesvioPadrao(resultados, 10, media);
                printf("Melhor: %0.6f\n", resultados[0]);

            printf("\n\n\t MELHOR MINIMO ENCONTRADO: %0.6f\n\n", resultados[0]);
            media = calcularMedia(resultados, 10);
            double desvioPadrao = calcularDesvioPadrao(resultados, 10, media);
            gerarRelatorio(arquivo, populacoes, rodadasPorPopulacao, iteracoes, iter, resultados, media, desvioPadrao);

            // fprintf(arquivo, "Populacao: %d, Iteracoes: %d, Melhor: %.6f, Media: %.6f, DesvioPadrao: %.6f\n",
            //         populacoes[rodadasPorPopulacao], iteracoes[iter], resultados[0], media, desvioPadrao);
        }
    }
}

// Função principal
int main() {
    srand(time(NULL));
    // numero de rodadas internas
    int iteracoes[] = {20, 50, 100}; 
    int populacoes[] = {50, 100};
    int numRodaddas = 10;
    int count = 0;
    FILE *arquivo = escreverArquivo("resultados.txt");

    while (numRodaddas >= count){
        inicializar(populacoes, iteracoes, arquivo);
        count++;
    }

    printf("Fim do Enxame de Particulas");
    fclose(arquivo);
    return 0;
}
