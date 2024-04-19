# Parcial-Sistemas-Operativos-Corte-2

# INTEGRANTES

*   David Arias Rueda
*   Juan David Carvajal Lozano
*   Paula Andrea Gómez Aldana

## PARCIAL 2

### SISTEMAS OPERATIVOS

#### Planificación por Prioridades Dinámicas:

Implementar un algoritmo de planificación que permita a los procesos cambiar dinámicamente sus prioridades en función de su comportamiento y estado. La implementación puede debe ser en Python y en C.

Ejemplo, se podría usar el algoritmo de planificación de retroalimentación multinivel (MLFQ) donde los procesos se mueven entre colas con diferentes prioridades en función de su tiempo de CPU utilizado.

#### Recomendación:

Para implementar un algoritmo de planificación con prioridades dinámicas, se necesita una forma de calcular y ajustar las prioridades de los procesos en función de su comportamiento. Por ejemplo, se podría aumentar la prioridad de un proceso si ha esperado mucho tiempo en la cola de listos, o reducir su prioridad si ha utilizado una gran cantidad de tiempo de CPU recientemente. (Se adjunta modelo).

## SOLUCIÓN

#### Programa en C

Este programa se ejecutó 15 veces con el fin de tomar su tiempo de ejecución y hacer un análisis más específico, los siguientes son los tiempos de ejecución:

#### Programa en Python

Este programa se ejecutó 15 veces con el fin de tomar su tiempo de ejecución y hacer un análisis más específico, los siguientes son los tiempos de ejecución:

#### Análisis entre tiempos de ejecución en la gestión de procesos, según el lenguaje de programación (C y Python)

Teniendo en cuenta la gráfica anterior se evidencia que los tiempos de ejecución presentados en Python son más altos que los presentados en C, esto puede deberse a que Python es un lenguaje de programación interpretado, a diferencia de C que es un lenguaje de programación compilado, lo que afecta directamente a su tiempo de ejecución.
