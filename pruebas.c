#include "src/abb.h"
#include <stdio.h>
#include "pa2mm.h"
#include "string.h"

// AUXILIARES

int comparador_entero(void *_e1, void *_e2)
{
  int *e1 = _e1;
  int *e2 = _e2;

  return *e1 - *e2;
}

int comparador_caracter(void *_e1, void *_e2)
{
  char *e1 = _e1;
  char *e2 = _e2;

  return *e1 - *e2;
}

bool insertar_caracter(void *_e1, void *_e2)
{
  char *caracter = _e1;
  char *cadena = _e2;

  strncat(cadena, caracter, 1);

  return *caracter != 'd';
}

// CREAR

void puedoCrearUnABBCorrectamente()
{
  abb_t *abb = abb_crear(comparador_entero);
  if (!abb)
  {
    return;
  }

  pa2m_afirmar(abb, "El arbol se crea correctamente");
  pa2m_afirmar(!abb->nodo_raiz, "El arbol se crea con raiz NULL");
  pa2m_afirmar(!abb->tamanio, "El arbol se crea con tamaño CERO");
  pa2m_afirmar(abb->comparador == comparador_entero, "El arbol se crea con el comparador especificado");

  abb_destruir(abb);
}

// TAMAÑO

void dadoUnABBNull_tamanioDevuelveCero()
{
  abb_t *abb = NULL;

  pa2m_afirmar(!abb_tamanio(abb), "Tamaño de un arbol NULL devuelve NULL");
}

void dadoUnABBVacio_tamanioDevuelveCero()
{
  abb_t *abb = abb_crear(comparador_entero);
  if (!abb)
  {
    return;
  }

  pa2m_afirmar(!abb_tamanio(abb), "Tamaño de un arbol vacio devuelve NULL");

  abb_destruir(abb);
}

void dadoUnABBNoVacio_tamanioDevuelveCorrectamente()
{
  abb_t *abb = abb_crear(comparador_entero);
  if (!abb)
  {
    return;
  }

  abb->tamanio = 3;

  pa2m_afirmar(abb_tamanio(abb) == 3, "Tamaño de un arbol no vacio devuelve correctamente");

  abb_destruir(abb);
}

// VACIO

void dadoUnABBNull_vacioDevuelveTrue()
{
  abb_t *abb = NULL;

  pa2m_afirmar(abb_vacio(abb), "Al verificar si un arbol NULL esta vacio, devuelve true");

  abb_destruir(abb);
}

void dadoUnABBVacio_vacioDevuelveTrue()
{
  abb_t *abb = abb_crear(comparador_entero);
  if (!abb)
  {
    return;
  }

  pa2m_afirmar(abb_vacio(abb), "Al verificar si un arbol vacio esta vacio, devuelve true");

  abb_destruir(abb);
}

void dadoUnABBNoVacio_vacioDevuelveFalse()
{
  abb_t *abb = abb_crear(comparador_entero);
  if (!abb)
  {
    return;
  }

  abb->tamanio = 3;

  pa2m_afirmar(!abb_vacio(abb), "Al verificar si un arbol no vacio esta vacio, devuelve false");

  abb_destruir(abb);
}

// INSERTAR

void dadoUnABBNull_noPuedoInsertarUnElemento()
{
  abb_t *abb = NULL;

  int elemento1 = 1;

  pa2m_afirmar(!abb_insertar(abb, &elemento1), "Dado un ABB Null, no puedo insertar un elemento");
}

void dadoUnABBVacio_puedoInsertarVariosElementos()
{
  abb_t *abb = abb_crear(comparador_entero);
  if (!abb)
  {
    return;
  }

  int elemento1 = 1;
  int elemento2 = 2;
  int elemento3 = 0;

  abb = abb_insertar(abb, &elemento1);

  pa2m_afirmar(abb, "Dado un ABB vacio, puedo insertar un elemento");
  pa2m_afirmar(abb->nodo_raiz->elemento == &elemento1, " El elemento se inserta correctamente");

  abb = abb_insertar(abb, &elemento2);

  pa2m_afirmar(abb, "Dado el ABB anterior, puedo insertar un segundo elemento");
  pa2m_afirmar(abb->nodo_raiz->derecha->elemento == &elemento2, " El elemento se inserta correctamente");

  abb = abb_insertar(abb, &elemento3);

  pa2m_afirmar(abb, "Dado el ABB anterior, puedo insertar un tercer elemento");
  pa2m_afirmar(abb->nodo_raiz->izquierda->elemento == &elemento3, " El elemento se inserta correctamente");

  abb_destruir(abb);
}

void dadoUnABBVacio_puedoInsertarVariosElementos_conDestruccionTotal()
{
  abb_t *abb = abb_crear(comparador_entero);
  if (!abb)
  {
    return;
  }

  int *elemento1 = malloc(sizeof(int));
  int *elemento2 = malloc(sizeof(int));
  int *elemento3 = malloc(sizeof(int));

  *elemento1 = 1;
  *elemento2 = 2;
  *elemento3 = 0;

  abb = abb_insertar(abb, elemento1);

  pa2m_afirmar(abb, "Dado un ABB vacio, puedo insertar un elemento");
  pa2m_afirmar(abb->nodo_raiz->elemento == elemento1, " El elemento se inserta correctamente");

  abb = abb_insertar(abb, elemento2);

  pa2m_afirmar(abb, "Dado el ABB anterior, puedo insertar un segundo elemento");
  pa2m_afirmar(abb->nodo_raiz->derecha->elemento == elemento2, " El elemento se inserta correctamente");

  abb = abb_insertar(abb, elemento3);

  pa2m_afirmar(abb, "Dado el ABB anterior, puedo insertar un tercer elemento");
  pa2m_afirmar(abb->nodo_raiz->izquierda->elemento == elemento3, " El elemento se inserta correctamente");

  abb_destruir_todo(abb, free);
}

// BUSCAR

void dadoUnABBNull_alBuscarUnElemento_devuelveNULL()
{
  abb_t *abb = NULL;
  int elemento = 1;

  pa2m_afirmar(!abb_buscar(abb, &elemento), "dado un ABB NULL, al buscar un elemento, devuelve NULL");
}

void dadoUnABBNoNull_alBuscarUnElementoNull_devuelveNULL()
{
  abb_t *abb = abb_crear(comparador_entero);
  if (!abb)
  {
    return;
  }

  int *elemento = NULL;

  pa2m_afirmar(!abb_buscar(abb, elemento), "dado un ABB no NULL, al buscar un elemento NULL, devuelve NULL");

  abb_destruir(abb);
}

void dadoUnABBVacio_alBuscarUnElemento_devuelveNULL()
{
  abb_t *abb = abb_crear(comparador_entero);
  if (!abb)
  {
    return;
  }

  int elemento = 1;

  pa2m_afirmar(!abb_buscar(abb, &elemento), "dado un ABB vacio, al buscar un elemento, devuelve NULL");

  abb_destruir(abb);
}

void dadoUnABBNoVacio_alBuscarUnElementoInexistente_devuelveNULL()
{
  abb_t *abb = abb_crear(comparador_entero);
  if (!abb)
  {
    return;
  }

  int elemento1 = 1;
  int elemento2 = 2;
  int elemento3 = 3;

  abb = abb_insertar(abb, &elemento1);
  abb = abb_insertar(abb, &elemento2);

  pa2m_afirmar(!abb_buscar(abb, &elemento3), "dado un ABB no vacio, al buscar un elemento inexistente, devuelve NULL");

  abb_destruir(abb);
}

void dadoUnABBNoVacio_alBuscarUnElementoExistente_devuelveEseElemento()
{
  abb_t *abb = abb_crear(comparador_entero);
  if (!abb)
  {
    return;
  }

  int elemento1 = 1;
  int elemento2 = 2;
  int elemento3 = 3;

  abb = abb_insertar(abb, &elemento1);
  abb = abb_insertar(abb, &elemento2);
  abb = abb_insertar(abb, &elemento3);

  int elemento_a_buscar = 2;

  pa2m_afirmar(abb_buscar(abb, &elemento_a_buscar) == &elemento2, "dado un ABB no vacio, al buscar un elemento existente, devuelve ese elemento");

  abb_destruir(abb);
}

// QUITAR

void dadoUnABBNull_noPuedoQuitarUnElemento()
{
  abb_t *abb = NULL;
  int elemento = 1;

  pa2m_afirmar(!abb_quitar(abb, &elemento), "Dado un ABB NULL, no puedo quitar un elemento");
}

void dadoUnABBVacio_alQuitarUnElemento_devuelveNULL()
{
  abb_t *abb = abb_crear(comparador_entero);
  if (!abb)
  {
    return;
  }
  int elemento = 1;

  pa2m_afirmar(!abb_quitar(abb, &elemento), "Dado un ABB vacio, al quitar un elemento, devuelve NULL");

  abb_destruir(abb);
}

void dadoUnABBNoVacio_alQuitarUnElementoInexistente_devuelveNULL()
{
  abb_t *abb = abb_crear(comparador_entero);
  if (!abb)
  {
    return;
  }

  int elemento1 = 1;
  int elemento2 = 2;

  abb = abb_insertar(abb, &elemento1);

  pa2m_afirmar(!abb_quitar(abb, &elemento2), "Dado un ABB no vacio, al quitar un elemento inexistente, devuelve NULL");

  abb_destruir(abb);
}

void dadoUnABBNoVacio_puedoQuitarUnaHoja()
{
  abb_t *abb = abb_crear(comparador_entero);
  if (!abb)
  {
    return;
  }

  int elemento0 = 0;
  int elemento1 = 1;
  int elemento2 = 2;
  int elemento3 = 3;

  abb = abb_insertar(abb, &elemento1);
  abb = abb_insertar(abb, &elemento0);
  abb = abb_insertar(abb, &elemento2);
  abb = abb_insertar(abb, &elemento3);

  int elemento_a_quitar = 3;

  pa2m_afirmar(abb_quitar(abb, &elemento_a_quitar) == &elemento3, "Dado un ABB no vacio, al quitar un elemento sin hijos, devuelve ese elemento");

  pa2m_afirmar(abb->tamanio == 3, " Luego de quitarlo, el tamaño se reduce en uno");

  bool puedo_acceder_eliminado = abb_buscar(abb, &elemento3);
  pa2m_afirmar(!puedo_acceder_eliminado, " Luego de quitarlo, no puedo encontrar ese elemento");

  bool puedo_acceder_restantes = abb_buscar(abb, &elemento0) == &elemento0 &&
                                 abb_buscar(abb, &elemento1) == &elemento1 &&
                                 abb_buscar(abb, &elemento2) == &elemento2;
  pa2m_afirmar(puedo_acceder_restantes, " Luego de quitarlo, puedo encontrar el resto de elementos");

  abb_destruir(abb);
}

void dadoUnABBNoVacio_puedoQuitarUnaNodoConUnHijo()
{
  abb_t *abb = abb_crear(comparador_entero);
  if (!abb)
  {
    return;
  }

  int elemento0 = 0;
  int elemento1 = 1;
  int elemento2 = 2;
  int elemento3 = 3;

  abb = abb_insertar(abb, &elemento1);
  abb = abb_insertar(abb, &elemento0);
  abb = abb_insertar(abb, &elemento2);
  abb = abb_insertar(abb, &elemento3);

  int elemento_a_quitar = 2;

  pa2m_afirmar(abb_quitar(abb, &elemento_a_quitar) == &elemento2, "Dado un ABB no vacio, al quitar un elemento con un hijo, devuelve ese elemento");

  pa2m_afirmar(abb->tamanio == 3, " Luego de quitarlo, el tamaño se reduce en uno");

  bool puedo_acceder_eliminado = abb_buscar(abb, &elemento2);
  pa2m_afirmar(!puedo_acceder_eliminado, " Luego de quitarlo, no puedo encontrar ese elemento");

  bool puedo_acceder_restantes = abb_buscar(abb, &elemento0) == &elemento0 &&
                                 abb_buscar(abb, &elemento1) == &elemento1 &&
                                 abb_buscar(abb, &elemento3) == &elemento3;
  pa2m_afirmar(puedo_acceder_restantes, " Luego de quitarlo, puedo encontrar el resto de elementos");

  abb_destruir(abb);
}

void dadoUnABBNoVacio_puedoQuitarUnaNodoConDosHijos()
{
  abb_t *abb = abb_crear(comparador_entero);
  if (!abb)
  {
    return;
  }

  int elemento0 = 0;
  int elemento1 = 1;
  int elemento2 = 2;
  int elemento3 = 3;
  int elemento4 = 4;
  int elemento5 = 5;

  abb = abb_insertar(abb, &elemento1);
  abb = abb_insertar(abb, &elemento0);
  abb = abb_insertar(abb, &elemento4);
  abb = abb_insertar(abb, &elemento3);
  abb = abb_insertar(abb, &elemento2);
  abb = abb_insertar(abb, &elemento5);

  int elemento_a_quitar = 4;

  pa2m_afirmar(abb_quitar(abb, &elemento_a_quitar) == &elemento4, "Dado un ABB no vacio, al quitar un elemento con dos hijos, devuelve ese elemento");

  pa2m_afirmar(abb->tamanio == 5, " Luego de quitarlo, el tamaño se reduce en uno");

  bool puedo_acceder_eliminado = abb_buscar(abb, &elemento4);
  pa2m_afirmar(!puedo_acceder_eliminado, " Luego de quitarlo, no puedo encontrar ese elemento");

  bool puedo_acceder_restantes = abb_buscar(abb, &elemento0) == &elemento0 &&
                                 abb_buscar(abb, &elemento1) == &elemento1 &&
                                 abb_buscar(abb, &elemento2) == &elemento2 &&
                                 abb_buscar(abb, &elemento3) == &elemento3 &&
                                 abb_buscar(abb, &elemento5) == &elemento5;
  pa2m_afirmar(puedo_acceder_restantes, " Luego de quitarlo, puedo encontrar el resto de elementos");

  abb_destruir(abb);
}

// RECORRER

void dadoUnABBNull_noPuedoRecorrer()
{
  abb_t *abb = NULL;

  void *recorrido[10];
  pa2m_afirmar(abb_recorrer(abb, INORDEN, recorrido, 10) == 0, "No puedo recorrer un ABB NULL");
}

void dadoUnABBVacio_noPuedoRecorrer()
{
  abb_t *abb = abb_crear(comparador_entero);
  if (!abb)
  {
    return;
  }

  void *recorrido[10];
  pa2m_afirmar(abb_recorrer(abb, INORDEN, recorrido, 10) == 0, "No puedo recorrer un ABB vacio");

  abb_destruir(abb);
}

void dadoUnABBNoVacio_noPuedoRecorrerloConParametrosInvalidos()
{
  abb_t *abb = abb_crear(comparador_entero);
  if (!abb)
  {
    return;
  }

  int elemento = 1;
  abb = abb_insertar(abb, &elemento);

  void *recorrido[10];

  pa2m_afirmar(abb_recorrer(abb, 5, recorrido, 10) == 0, "No puedo recorrer un ABB con recorrido invalido");
  pa2m_afirmar(abb_recorrer(abb, INORDEN, NULL, 10) == 0, "No puedo recorrer un ABB con vector NULL");
  pa2m_afirmar(abb_recorrer(abb, INORDEN, recorrido, 0) == 0, "No puedo recorrer un ABB con tamaño CERO");

  abb_destruir(abb);
}

void dadoUnABBNoVacio_alRecorrerInordenTodo_recorreCorrectamente()
{
  abb_t *abb = abb_crear(comparador_entero);
  if (!abb)
  {
    return;
  }

  int elemento1 = 1;
  int elemento2 = 2;
  int elemento3 = 3;
  int elemento4 = 4;
  int elemento5 = 5;

  abb = abb_insertar(abb, &elemento3);
  abb = abb_insertar(abb, &elemento1);
  abb = abb_insertar(abb, &elemento5);
  abb = abb_insertar(abb, &elemento4);
  abb = abb_insertar(abb, &elemento2);

  void *recorrido[5];
  pa2m_afirmar(abb_recorrer(abb, INORDEN, recorrido, 5) == 5, "Dado un ABB no vacio, recorrer INORDEN recorre todos los elementos");

  void *recorrido_esperado[5] = {&elemento1, &elemento2, &elemento3, &elemento4, &elemento5};

  bool recorrido_es_correcto = recorrido[0] == recorrido_esperado[0] &&
                               recorrido[1] == recorrido_esperado[1] &&
                               recorrido[2] == recorrido_esperado[2] &&
                               recorrido[3] == recorrido_esperado[3] &&
                               recorrido[4] == recorrido_esperado[4];

  pa2m_afirmar(recorrido_es_correcto, " El ABB se recorre en el orden correcto");

  abb_destruir(abb);
}

void dadoUnABBNoVacio_alRecorrerPreordenTodo_recorreCorrectamente()
{
  abb_t *abb = abb_crear(comparador_entero);
  if (!abb)
  {
    return;
  }

  int elemento1 = 1;
  int elemento2 = 2;
  int elemento3 = 3;
  int elemento4 = 4;
  int elemento5 = 5;

  abb = abb_insertar(abb, &elemento3);
  abb = abb_insertar(abb, &elemento1);
  abb = abb_insertar(abb, &elemento5);
  abb = abb_insertar(abb, &elemento4);
  abb = abb_insertar(abb, &elemento2);

  void *recorrido[5];
  pa2m_afirmar(abb_recorrer(abb, PREORDEN, recorrido, 5) == 5, "Dado un ABB no vacio, recorrer INORDEN recorre todos los elementos");

  void *recorrido_esperado[5] = {&elemento3, &elemento1, &elemento2, &elemento5, &elemento4};

  bool recorrido_es_correcto = recorrido[0] == recorrido_esperado[0] &&
                               recorrido[1] == recorrido_esperado[1] &&
                               recorrido[2] == recorrido_esperado[2] &&
                               recorrido[3] == recorrido_esperado[3] &&
                               recorrido[4] == recorrido_esperado[4];

  pa2m_afirmar(recorrido_es_correcto, " El ABB se recorre en el orden correcto");

  abb_destruir(abb);
}

void dadoUnABBNoVacio_alRecorrerPostordenTodo_recorreCorrectamente()
{
  abb_t *abb = abb_crear(comparador_entero);
  if (!abb)
  {
    return;
  }

  int elemento1 = 1;
  int elemento2 = 2;
  int elemento3 = 3;
  int elemento4 = 4;
  int elemento5 = 5;

  abb = abb_insertar(abb, &elemento3);
  abb = abb_insertar(abb, &elemento1);
  abb = abb_insertar(abb, &elemento5);
  abb = abb_insertar(abb, &elemento4);
  abb = abb_insertar(abb, &elemento2);

  void *recorrido[5];
  pa2m_afirmar(abb_recorrer(abb, POSTORDEN, recorrido, 5) == 5, "Dado un ABB no vacio, recorrer POSTORDEN recorre todos los elementos");

  void *recorrido_esperado[5] = {&elemento2, &elemento1, &elemento4, &elemento5, &elemento3};

  bool recorrido_es_correcto = recorrido[0] == recorrido_esperado[0] &&
                               recorrido[1] == recorrido_esperado[1] &&
                               recorrido[2] == recorrido_esperado[2] &&
                               recorrido[3] == recorrido_esperado[3] &&
                               recorrido[4] == recorrido_esperado[4];

  pa2m_afirmar(recorrido_es_correcto, " El ABB se recorre en el orden correcto");

  abb_destruir(abb);
}

void dadoUnABBNoVacio_alRecorrerHastaUnMaximo_recorreCorrectamente()
{
  abb_t *abb = abb_crear(comparador_entero);
  if (!abb)
  {
    return;
  }

  int elemento1 = 1;
  int elemento2 = 2;
  int elemento3 = 3;
  int elemento4 = 4;
  int elemento5 = 5;

  abb = abb_insertar(abb, &elemento3);
  abb = abb_insertar(abb, &elemento1);
  abb = abb_insertar(abb, &elemento5);
  abb = abb_insertar(abb, &elemento4);
  abb = abb_insertar(abb, &elemento2);

  void *recorrido[4];
  pa2m_afirmar(abb_recorrer(abb, POSTORDEN, recorrido, 4) == 4, "Dado un ABB no vacio, recorrer POSTORDEN recorre todos los elementos hasta MAXIMO");

  void *recorrido_esperado[4] = {&elemento2, &elemento1, &elemento4, &elemento5};

  bool recorrido_es_correcto = recorrido[0] == recorrido_esperado[0] &&
                               recorrido[1] == recorrido_esperado[1] &&
                               recorrido[2] == recorrido_esperado[2] &&
                               recorrido[3] == recorrido_esperado[3];

  pa2m_afirmar(recorrido_es_correcto, " El ABB se recorre en el orden correcto");

  abb_destruir(abb);
}

// FUNCION A CADA ELEMENTO

void dadoUnABBNull_noPuedoAplicarFuncionACadaElemento()
{
  abb_t *abb = NULL;

  char cadena[10] = "";
  pa2m_afirmar(!abb_con_cada_elemento(abb, INORDEN, insertar_caracter, cadena), "Dado un ABB NULL, no se puede aplicar una funcion a cada elemento");
}

void dadoUnABBVacio_noPuedoAplicarFuncionACadaElemento()
{
  abb_t *abb = abb_crear(comparador_caracter);
  if (!abb)
  {
    return;
  }

  char cadena[10] = "";
  pa2m_afirmar(!abb_con_cada_elemento(abb, INORDEN, insertar_caracter, cadena), "Dado un ABB vacio, no se puede aplicar una funcion a cada elemento");

  abb_destruir(abb);
}

void dadoUnABBNoVacio_alAplicarFuncionACadaElementoInorden_SeAplicaCorrectamente()
{
  abb_t *abb = abb_crear(comparador_caracter);
  if (!abb)
  {
    return;
  }

  int elemento1 = 'a';
  int elemento2 = 'b';
  int elemento3 = 'c';

  abb = abb_insertar(abb, &elemento2);
  abb = abb_insertar(abb, &elemento1);
  abb = abb_insertar(abb, &elemento3);

  char cadena[10] = "";
  pa2m_afirmar(abb_con_cada_elemento(abb, INORDEN, insertar_caracter, cadena) == 3,
               "Dado un ABB no vacio, se puede aplicar una funcion a cada elemento (INORDER)");

  pa2m_afirmar(strcmp(cadena, "abc") == 0, " La funcion se aplica en el orden correcto");

  abb_destruir(abb);
}

void dadoUnABBNoVacio_alAplicarFuncionACadaElementoPreorden_SeAplicaCorrectamente()
{
  abb_t *abb = abb_crear(comparador_caracter);
  if (!abb)
  {
    return;
  }

  int elemento1 = 'a';
  int elemento2 = 'b';
  int elemento3 = 'c';

  abb = abb_insertar(abb, &elemento2);
  abb = abb_insertar(abb, &elemento1);
  abb = abb_insertar(abb, &elemento3);

  char cadena[10] = "";
  pa2m_afirmar(abb_con_cada_elemento(abb, PREORDEN, insertar_caracter, cadena) == 3,
               "Dado un ABB no vacio, se puede aplicar una funcion a cada elemento (PREORDEN)");

  pa2m_afirmar(strcmp(cadena, "bac") == 0, " La funcion se aplica en el orden correcto");

  abb_destruir(abb);
}

void dadoUnABBNoVacio_alAplicarFuncionACadaElementoPostorden_SeAplicaCorrectamente()
{
  abb_t *abb = abb_crear(comparador_caracter);
  if (!abb)
  {
    return;
  }

  int elemento1 = 'a';
  int elemento2 = 'b';
  int elemento3 = 'c';

  abb = abb_insertar(abb, &elemento2);
  abb = abb_insertar(abb, &elemento1);
  abb = abb_insertar(abb, &elemento3);

  char cadena[10] = "";
  pa2m_afirmar(abb_con_cada_elemento(abb, POSTORDEN, insertar_caracter, cadena) == 3,
               "Dado un ABB no vacio, se puede aplicar una funcion a cada elemento (POSTORDEN)");

  pa2m_afirmar(strcmp(cadena, "acb") == 0, " La funcion se aplica en el orden correcto");

  abb_destruir(abb);
}

void dadoUnABBNoVacio_alAplicarFuncionACadaElementoInordenHastaCORTE_SeAplicaCorrectamente()
{
  abb_t *abb = abb_crear(comparador_caracter);
  if (!abb)
  {
    return;
  }

  int elemento1 = 'a';
  int elemento2 = 'b';
  int elemento3 = 'c';
  int elemento4 = 'd';
  int elemento5 = 'e';

  abb = abb_insertar(abb, &elemento3);
  abb = abb_insertar(abb, &elemento1);
  abb = abb_insertar(abb, &elemento2);
  abb = abb_insertar(abb, &elemento5);
  abb = abb_insertar(abb, &elemento4);

  char cadena[10] = "";
  pa2m_afirmar(abb_con_cada_elemento(abb, INORDEN, insertar_caracter, cadena) == 4,
               "Dado un ABB no vacio, se puede aplicar una funcion a cada elemento con recorrido hasta CORTE (INORDEN)");

  pa2m_afirmar(strcmp(cadena, "abcd") == 0, " La funcion se aplica en el orden correcto");

  abb_destruir(abb);
}

void dadoUnABBNoVacio_alAplicarFuncionACadaElementoPreordenHastaCORTE_SeAplicaCorrectamente()
{
  abb_t *abb = abb_crear(comparador_caracter);
  if (!abb)
  {
    return;
  }

  int elemento1 = 'a';
  int elemento2 = 'b';
  int elemento3 = 'c';
  int elemento4 = 'd';
  int elemento5 = 'e';

  abb = abb_insertar(abb, &elemento3);
  abb = abb_insertar(abb, &elemento1);
  abb = abb_insertar(abb, &elemento2);
  abb = abb_insertar(abb, &elemento5);
  abb = abb_insertar(abb, &elemento4);

  char cadena[10] = "";
  pa2m_afirmar(abb_con_cada_elemento(abb, PREORDEN, insertar_caracter, cadena) == 5,
               "Dado un ABB no vacio, se puede aplicar una funcion a cada elemento con recorrido hasta CORTE (PREORDEN)");

  pa2m_afirmar(strcmp(cadena, "cabed") == 0, " La funcion se aplica en el orden correcto");

  abb_destruir(abb);
}

void dadoUnABBNoVacio_alAplicarFuncionACadaElementoPostordenHastaCORTE_SeAplicaCorrectamente()
{
  abb_t *abb = abb_crear(comparador_caracter);
  if (!abb)
  {
    return;
  }

  int elemento1 = 'a';
  int elemento2 = 'b';
  int elemento3 = 'c';
  int elemento4 = 'd';
  int elemento5 = 'e';

  abb = abb_insertar(abb, &elemento3);
  abb = abb_insertar(abb, &elemento1);
  abb = abb_insertar(abb, &elemento2);
  abb = abb_insertar(abb, &elemento5);
  abb = abb_insertar(abb, &elemento4);

  char cadena[10] = "";
  pa2m_afirmar(abb_con_cada_elemento(abb, POSTORDEN, insertar_caracter, cadena) == 3,
               "Dado un ABB no vacio, se puede aplicar una funcion a cada elemento con recorrido hasta CORTE (POSTORDEN)");

  pa2m_afirmar(strcmp(cadena, "bad") == 0, " La funcion se aplica en el orden correcto");

  abb_destruir(abb);
}

// MAIN

int main()
{
  pa2m_nuevo_grupo("ABB: Crear");
  puedoCrearUnABBCorrectamente();

  pa2m_nuevo_grupo("ABB: Tamaño");
  dadoUnABBNull_tamanioDevuelveCero();
  dadoUnABBVacio_tamanioDevuelveCero();
  dadoUnABBNoVacio_tamanioDevuelveCorrectamente();

  pa2m_nuevo_grupo("ABB: Vacio");
  dadoUnABBNull_vacioDevuelveTrue();
  dadoUnABBVacio_vacioDevuelveTrue();
  dadoUnABBNoVacio_vacioDevuelveFalse();

  pa2m_nuevo_grupo("ABB: Insertar");
  dadoUnABBNull_noPuedoInsertarUnElemento();
  dadoUnABBVacio_puedoInsertarVariosElementos();

  pa2m_nuevo_grupo("ABB: Insertar (destruccion total)");
  dadoUnABBVacio_puedoInsertarVariosElementos_conDestruccionTotal();

  pa2m_nuevo_grupo("ABB: Buscar");
  dadoUnABBNull_alBuscarUnElemento_devuelveNULL();
  dadoUnABBNoNull_alBuscarUnElementoNull_devuelveNULL();
  dadoUnABBVacio_alBuscarUnElemento_devuelveNULL();
  dadoUnABBNoVacio_alBuscarUnElementoInexistente_devuelveNULL();
  dadoUnABBNoVacio_alBuscarUnElementoExistente_devuelveEseElemento();

  pa2m_nuevo_grupo("ABB: Quitar");
  dadoUnABBNull_noPuedoQuitarUnElemento();
  dadoUnABBVacio_alQuitarUnElemento_devuelveNULL();
  dadoUnABBNoVacio_alQuitarUnElementoInexistente_devuelveNULL();
  dadoUnABBNoVacio_puedoQuitarUnaHoja();
  dadoUnABBNoVacio_puedoQuitarUnaNodoConUnHijo();
  dadoUnABBNoVacio_puedoQuitarUnaNodoConDosHijos();

  pa2m_nuevo_grupo("ABB: Recorrer");
  dadoUnABBNull_noPuedoRecorrer();
  dadoUnABBVacio_noPuedoRecorrer();
  dadoUnABBNoVacio_noPuedoRecorrerloConParametrosInvalidos();
  dadoUnABBNoVacio_alRecorrerInordenTodo_recorreCorrectamente();
  dadoUnABBNoVacio_alRecorrerPreordenTodo_recorreCorrectamente();
  dadoUnABBNoVacio_alRecorrerPostordenTodo_recorreCorrectamente();
  dadoUnABBNoVacio_alRecorrerHastaUnMaximo_recorreCorrectamente();

  pa2m_nuevo_grupo("ABB: Funcion a cada elemento");
  dadoUnABBNull_noPuedoAplicarFuncionACadaElemento();
  dadoUnABBVacio_noPuedoAplicarFuncionACadaElemento();
  dadoUnABBNoVacio_alAplicarFuncionACadaElementoInorden_SeAplicaCorrectamente();
  dadoUnABBNoVacio_alAplicarFuncionACadaElementoPreorden_SeAplicaCorrectamente();
  dadoUnABBNoVacio_alAplicarFuncionACadaElementoPostorden_SeAplicaCorrectamente();
  dadoUnABBNoVacio_alAplicarFuncionACadaElementoInordenHastaCORTE_SeAplicaCorrectamente();
  dadoUnABBNoVacio_alAplicarFuncionACadaElementoPreordenHastaCORTE_SeAplicaCorrectamente();
  dadoUnABBNoVacio_alAplicarFuncionACadaElementoPostordenHastaCORTE_SeAplicaCorrectamente();

  return pa2m_mostrar_reporte();
}
