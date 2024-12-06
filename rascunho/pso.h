#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <float.h>

// Estrutura para representar uma partícula
typedef struct {
   double *position;    // Posição da partícula (vetor bidimensional)
   double *velocity;    // Velocidade da partícula
   double *bestPosition; // Melhor posição individual
   double fitness;       // Aptidão da partícula
   double bestFitness;   // Melhor aptidão individual
} Particle;


// Estrutura para representar o enxame
typedef struct {
   Particle *particles; // Array de partículas
   double *globalBestPosition; // Melhor posição global
   double globalBestFitness;   // Melhor aptidão global
   int numParticles;           // Número de partículas
   int dimensions;             // Dimensão do espaço (2D no caso)
} Swarm;


// Função objetivo (Eggholder function)
double eggholder(double x, double y);


// Inicialização do enxame
void initializeSwarm(Swarm *swarm, int numParticles, int dimensions, double minPos, double maxPos, double maxVel);


// Atualiza a aptidão de uma partícula
double evaluateFitness(double *position);


// Atualiza a velocidade de uma partícula
void updateVelocity(Particle *particle, double *globalBestPosition, int dimensions, double w, double c1, double c2);


// Atualiza a posição de uma partícula
void updatePosition(Particle *particle, double minPos, double maxPos, int dimensions);


// Atualiza as melhores posições e aptidões (individual e global)
void updateBestPositions(Swarm *swarm);


// Executa o PSO
double runPSO(Swarm *swarm, int iterations, double w, double c1, double c2, double minPos, double maxPos);
