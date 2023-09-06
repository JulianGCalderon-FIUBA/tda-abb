#include "interno.h"

// FUNCIONES AUXILIARES

/**
 * POST: 
 *      Busca al nodo mayor del subarbol 'nodo'.
 *      Lo elimina del arbol y lo guarda en 'mayor';
 */
nodo_abb_t *extraer_maximo(nodo_abb_t *nodo, nodo_abb_t **mayor)
{
    if (!nodo->derecha)
    {
        *mayor = nodo;

        return nodo->izquierda;
    }

    nodo->derecha = extraer_maximo(nodo->derecha, mayor);
    return nodo;
}

// FUNCIONES PRINCIPALES

nodo_abb_t *abb_insertar_aux(nodo_abb_t *nodo, void *elemento, abb_comparador comparador, bool *pudo_insertar)
{
    if (!comparador)
    {
        return NULL;
    }

    if (!nodo)
    {
        nodo_abb_t *nuevo = calloc(1, sizeof(nodo_abb_t));
        if (!nuevo)
        {
            *pudo_insertar = false;
            return NULL;
        }
        nuevo->elemento = elemento;

        *pudo_insertar = true;
        return nuevo;
    }

    int comparacion = comparador(elemento, nodo->elemento);

    if (comparacion >= 0)
    {
        nodo->derecha = abb_insertar_aux(nodo->derecha, elemento, comparador, pudo_insertar);
    }
    else
    {
        nodo->izquierda = abb_insertar_aux(nodo->izquierda, elemento, comparador, pudo_insertar);
    }

    return nodo;
}

nodo_abb_t *abb_quitar_aux(nodo_abb_t *nodo, void *elemento, abb_comparador comparador, void **elemento_quitado)
{
    if (!nodo)
    {
        return NULL;
    }

    int comparacion = comparador(elemento, nodo->elemento);

    if (comparacion == 0)
    {
        *elemento_quitado = nodo->elemento;

        if (nodo->izquierda && nodo->derecha)
        {
            nodo_abb_t *remplazo;
            nodo->izquierda = extraer_maximo(nodo->izquierda, &remplazo);

            remplazo->derecha = nodo->derecha;
            remplazo->izquierda = nodo->izquierda;

            free(nodo);

            return remplazo;
        }
        else
        {
            nodo_abb_t *remplazo = nodo->derecha ? nodo->derecha : nodo->izquierda;

            free(nodo);

            return remplazo;
        }
    }
    else if (comparacion > 0)
    {
        nodo->derecha = abb_quitar_aux(nodo->derecha, elemento, comparador, elemento_quitado);
    }
    else
    {
        nodo->izquierda = abb_quitar_aux(nodo->izquierda, elemento, comparador, elemento_quitado);
    }

    return nodo;
}

void *abb_buscar_aux(nodo_abb_t *nodo, void *elemento, abb_comparador comparador)
{
    if (!nodo)
    {
        return NULL;
    }

    int comparacion = comparador(elemento, nodo->elemento);

    if (comparacion == 0)
    {
        return nodo->elemento;
    }
    else if (comparacion > 0)
    {
        return abb_buscar_aux(nodo->derecha, elemento, comparador);
    }
    return abb_buscar_aux(nodo->izquierda, elemento, comparador);
}

void abb_destruir_aux(nodo_abb_t *nodo)
{
    if (!nodo)
    {
        return;
    }

    abb_destruir_aux(nodo->izquierda);
    abb_destruir_aux(nodo->derecha);

    free(nodo);
}

void abb_destruir_todo_aux(nodo_abb_t *nodo, void (*destructor)(void *))
{
    if (!nodo || !destructor)
    {
        return;
    }

    abb_destruir_todo_aux(nodo->izquierda, destructor);
    abb_destruir_todo_aux(nodo->derecha, destructor);

    if (nodo->elemento)
    {
        destructor(nodo->elemento);
    }
    free(nodo);
}

size_t abb_con_cada_elemento_inorden(nodo_abb_t *nodo, bool (*funcion)(void *, void *), void *aux, bool *terminar_ejecucion)
{
    if (!nodo || *terminar_ejecucion)
    {
        return 0;
    }

    size_t contador = abb_con_cada_elemento_inorden(nodo->izquierda, funcion, aux, terminar_ejecucion);

    if (!*terminar_ejecucion)
    {
        contador++;
        *terminar_ejecucion = !funcion(nodo->elemento, aux);
    }

    contador += abb_con_cada_elemento_inorden(nodo->derecha, funcion, aux, terminar_ejecucion);

    return contador;
}

size_t abb_con_cada_elemento_preorden(nodo_abb_t *nodo, bool (*funcion)(void *, void *), void *aux, bool *terminar_ejecucion)
{
    if (!nodo || *terminar_ejecucion)
    {
        return 0;
    }

    size_t contador = 1;
    *terminar_ejecucion = !funcion(nodo->elemento, aux);

    contador += abb_con_cada_elemento_preorden(nodo->izquierda, funcion, aux, terminar_ejecucion);

    contador += abb_con_cada_elemento_preorden(nodo->derecha, funcion, aux, terminar_ejecucion);

    return contador;
}

size_t abb_con_cada_elemento_postorden(nodo_abb_t *nodo, bool (*funcion)(void *, void *), void *aux, bool *terminar_ejecucion)
{
    if (!nodo || *terminar_ejecucion)
    {
        return 0;
    }

    size_t contador = abb_con_cada_elemento_postorden(nodo->izquierda, funcion, aux, terminar_ejecucion);

    contador += abb_con_cada_elemento_postorden(nodo->derecha, funcion, aux, terminar_ejecucion);

    if (!*terminar_ejecucion)
    {
        contador++;
        *terminar_ejecucion = !funcion(nodo->elemento, aux);
    }

    return contador;
}

bool agregar_elemento(void *elemento, void *_parametros)
{
    if (!_parametros)
    {
        return false;
    }

    void **parametros = _parametros;

    void **arreglo = parametros[0];
    int *maximo = parametros[1];
    int *tope = parametros[2];

    if (*tope == *maximo)
    {
        return false;
    }

    arreglo[*tope] = elemento;
    (*tope)++;

    return *tope != *maximo;
}
