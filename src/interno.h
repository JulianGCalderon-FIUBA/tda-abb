#ifndef __INTERNO__H__
#define __INTERNO__H__

#include "abb.h"
#include <stdio.h>

/**
 * PRE: 
 *      'comparador' debe ser una funcion valida.
 * POST: 
 *      Inserta el elemento en la posicion correcta del arbol.
 *      Si pudo insertar correctamente, almacena TRUE en 'pudo_insertar'
 *      Si no pudo, almacena FALSE.
 */
nodo_abb_t *abb_insertar_aux(nodo_abb_t *nodo, void *elemento, abb_comparador comparador, bool *pudo_insertar);

/**
 * PRE: 
 *      'comparador' debe ser una funcion valida.
 * POST: 
 *      Elimina el nodo del subarbol que contiene el elemento indicado.
 *      Devuelve el nodo ingresado (actualizado).
 *      Almacena el elemento eliminado en 'elemento_quitado'.
 */
nodo_abb_t *abb_quitar_aux(nodo_abb_t *nodo, void *elemento, abb_comparador comparador, void **elemento_quitado);

/**
 * PRE:
 *      'comparador' debe ser una funcion valida.
 * POST: 
 *      Busca el elemento en el arbol.
 *      Si lo encuentra, devuelve el elemento.
 *      Si no lo encuentra, devuelve NULL.
 */
void *abb_buscar_aux(nodo_abb_t *nodo, void *elemento, abb_comparador comparador);

/**
 * POST: 
 *      Libera la memoria almacenada para el nodo ingresado y todos sus sucesores.
 */
void abb_destruir_aux(nodo_abb_t *nodo);

/**
 * PRE: 
 *      'destructor' debe ser una funcion valida.
 * POST: 
 *      Liberar la memoria almacenada para el nodo ingresado y todos sus sucesores.
 *      Aplica la funcion destructor a todos los elementos.
 */
void abb_destruir_todo_aux(nodo_abb_t *nodo, void (*destructor)(void *));

/**
 * PRE: 
 *      'funcion' debe ser valida
 *      'terminar_ejecucion' debe ser inicialmente false
 * POST: 
 *      Aplica la funcion a cada elemento del arbol en el recorrido indicado (inorden).
 *      Corta la ejecucion si alguna de las funciones devuelve false.
 *      Devuelve la cantidad de veces que se aplico la funcion
 */
size_t abb_con_cada_elemento_inorden(nodo_abb_t *nodo, bool (*funcion)(void *, void *), void *aux, bool *terminar_ejecucion);

/**
 * PRE: 
 *      'funcion' debe ser valida
 *      'terminar_ejecucion' debe ser inicialmente false
 * POST: 
 *      Aplica la funcion a cada elemento del arbol en el recorrido indicado (preorden).
 *      Corta la ejecucion si alguna de las funciones devuelve false.
 *      Devuelve la cantidad de veces que se aplico la funcion
 */
size_t abb_con_cada_elemento_preorden(nodo_abb_t *nodo, bool (*funcion)(void *, void *), void *aux, bool *terminar_ejecucion);

/**
 * PRE: 
 *      'funcion' debe ser valida
 *      'terminar_ejecucion' debe ser inicialmente false
 * POST: 
 *      Aplica la funcion a cada elemento del arbol en el recorrido indicado (postorden).
 *      Corta la ejecucion si alguna de las funciones devuelve false.
 *      Devuelve la cantidad de veces que se aplico la funcion
 */
size_t abb_con_cada_elemento_postorden(nodo_abb_t *nodo, bool (*funcion)(void *, void *), void *aux, bool *terminar_ejecucion);

/**
 * PRE: 
 *      '_parametros' debe tener la estructura valida.
 *      Es un vector de punteros void con los siguientes elementos:
 *          [0] Un vector de punteros void
 *          [1] El maximo del vector (puntero)
 *          [2] El tope del vector (puntero)
 * POST: 
 *      Devuelve TRUE si aun no se alcanzo el maximo del vector.
 *      Devuelve FALSE de lo contrario.
 */
bool agregar_elemento(void *elemento, void *_parametros);

#endif /* __INTERNO__H__ */
