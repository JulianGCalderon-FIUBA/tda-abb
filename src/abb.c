#include "abb.h"
#include "interno.h"
#include <stddef.h>
#include <stdlib.h>

#define ERROR 0

abb_t *abb_crear(abb_comparador comparador)
{
    if (!comparador)
    {
        return NULL;
    }

    abb_t *arbol = calloc(1, sizeof(abb_t));
    if (!arbol)
    {
        return NULL;
    }

    arbol->comparador = comparador;

    return arbol;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
    if (!arbol)
    {
        return NULL;
    }

    bool pudo_insertar;
    arbol->nodo_raiz = abb_insertar_aux(arbol->nodo_raiz, elemento, arbol->comparador, &pudo_insertar);

    if (!pudo_insertar)
    {
        return NULL;
    }

    arbol->tamanio++;
    return arbol;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
    if (!arbol)
    {
        return NULL;
    }

    void *elemento_quitado = NULL;
    arbol->nodo_raiz = abb_quitar_aux(arbol->nodo_raiz, elemento, arbol->comparador, &elemento_quitado);

    if (elemento_quitado)
    {
        (arbol->tamanio)--;
    }

    return elemento_quitado;
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
    if (!arbol || !elemento)
    {
        return NULL;
    }

    return abb_buscar_aux(arbol->nodo_raiz, elemento, arbol->comparador);
}

bool abb_vacio(abb_t *arbol)
{
    if (!arbol)
    {
        return true;
    }

    return arbol->tamanio == 0;
}

size_t abb_tamanio(abb_t *arbol)
{
    if (!arbol)
    {
        return ERROR;
    }

    return arbol->tamanio;
}

void abb_destruir(abb_t *arbol)
{
    if (!arbol)
    {
        return;
    }

    abb_destruir_aux(arbol->nodo_raiz);

    free(arbol);
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
    if (!arbol || !destructor)
    {
        return;
    }

    abb_destruir_todo_aux(arbol->nodo_raiz, destructor);

    free(arbol);
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido, bool (*funcion)(void *, void *), void *aux)
{
    if (!arbol || !funcion)
    {
        return ERROR;
    }

    bool terminar_ejecucion = false;

    switch (recorrido)
    {
    case INORDEN:
        return abb_con_cada_elemento_inorden(arbol->nodo_raiz, funcion, aux, &terminar_ejecucion);
    case PREORDEN:
        return abb_con_cada_elemento_preorden(arbol->nodo_raiz, funcion, aux, &terminar_ejecucion);
    case POSTORDEN:
        return abb_con_cada_elemento_postorden(arbol->nodo_raiz, funcion, aux, &terminar_ejecucion);
    }

    return ERROR;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array, size_t tamanio_array)
{
    if (!arbol || !array || tamanio_array == 0)
    {
        return ERROR;
    }

    int tope = 0;
    void *parametros[3] = {array, &tamanio_array, &tope};
    return abb_con_cada_elemento(arbol, recorrido, agregar_elemento, parametros);
}
