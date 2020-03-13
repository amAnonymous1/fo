/* 
 * Autor/a: amAnonymous1
 * Descripción:
 *  Parcial de TEORIA de Fundamentos de Ordenadores (FO).
 *  Versión más simple del UNO.
 *  AVISO!!! : Este código es una posible solución que he pensado.
 *              No descarto que pueden haber otras soluciones mejores que esta.
 *              Aún así espero que les ayude a entender el examen.
 * INCLUYE FUNCIONES Y PUNTEROS
 * Fecha: 21/11/18, Cuatrimestre otoño 2018
*/

#include <stdio.h>

#define MAX_CADENA  40
#define MAX_CARTAS  112
#define RED         'R'
#define GREEN       'G'
#define YELLOW      'Y'
#define BLUE        'B'

typedef struct {
    int num;    /* Número de la carta */
    char color; /* Color de la carta: R-RED, G-GREEN, B-BLUE */
} tcarta;

typedef struct {
    char nombre[MAX_CADENA];    /* Nombre del jugador, finalizado siempre con '.' */
    int ncartas;                /* Número de cartas en la mano */
    tcarta vcartas[MAX_CARTAS]; /* Cartas que el jugasor tiene en la mano */
} tjugador;

/* Funciones */
int puntuacion_total(tcarta cartas[], int length);
void informacion_user(tjugador jug, tcarta mazo);
void eliminar_carta(int pos, tjugador *jug);
void tirar_carta(int pos, tcarta *mazo, tjugador *jug);
int carta_mas_alta(tcarta cartas[], int ncartas, tcarta mazo);

void main() {
    tjugador jug1 = {"Pedro.", 8, {{1,RED}, {0,GREEN}, {3,BLUE}, {7,RED}, 
                        {5,BLUE}, {3,RED}, {9,GREEN}, {2,BLUE}}};
    tcarta carta_mazo;
    int pos, j, k;

    /* Código Ejercicio A */
    do {
        printf("Introduce la carta superior del mazo de descarte (Ej: 7R): ");
        scanf("%d%c",&carta_mazo.num, &carta_mazo.color);
    } while((carta_mazo.num < 0 || carta_mazo.num > 9)
            && (carta_mazo.color != RED || carta_mazo.color!=GREEN 
            || carta_mazo.color!=YELLOW || carta_mazo.color!=BLUE));
    // En el condicional da un error si ponemos (por ejemplo) '7E'
    informacion_user(jug1, carta_mazo);
    
    /* Código Ejercicio C */
    //Recorre todo el array y para hasta que encuentra que el número de la carta
    // es igual a la del mazo. Guarda la posicion en pos
    for(k=0; (k<jug1.ncartas) && (carta_mazo.num != jug1.vcartas[k].num);k++) {
        //Tambien: pos=k+1; Y quitamos el 'pos' que esta fuera el for
    }
    pos=k;
    // Si recorre todo el array y no encuentra nada,
    // busquemos las cartas con la misma letra que la del mazo
    if(pos==jug1.ncartas) {
        for(j=0; j < jug1.ncartas; j++) {
            //Puede haber más de una carta con la misma letra y distinto número
            if(carta_mazo.color==jug1.vcartas[j].color) {
                pos = carta_mas_alta(jug1.vcartas, jug1.ncartas, carta_mazo);
            }
        }
    }
    // Si en ninguno de los casos pudimos encontrar algo, 
    // Entonce el jugador no tira
    if(pos==jug1.ncartas) {
        printf("\n\nEl jugador no puede tirar.\n");
    } else {
        tirar_carta(pos, &carta_mazo, &jug1);
    }      
    informacion_user(jug1, carta_mazo);
}

/* Código Ejercicio B */
void informacion_user(tjugador jug, tcarta mazo) {
    printf("\nNombre: %s", jug.nombre);
    printf("\nCartas: %d%c", jug.vcartas[0].num, jug.vcartas[0].color);
        for(int i=1; i<jug.ncartas; i++) {
            printf(", %d%c", jug.vcartas[i].num, jug.vcartas[i].color);
        }
    printf("\nPuntuacion: %d", puntuacion_total(jug.vcartas, jug.ncartas));
    printf("\nMAZO: %d%c", mazo.num, mazo.color);
}

int puntuacion_total(tcarta cartas[], int length) {
    int total=0;
    for(int i=0; i<length ;i++) {
        total += cartas[i].num;
    }
    return total;
}

/* Código Ejercicio C - eliminando carta */
void eliminar_carta(int pos, tjugador *jug) {
    for(int i=pos; i<jug->ncartas;i++) {
        jug->vcartas[i].color = jug->vcartas[i+1].color;
        jug->vcartas[i].num = jug->vcartas[i+1].num;
    }
    jug->ncartas--;
}

/* Código Ejercicio C - tirando carta */
void tirar_carta(int pos, tcarta *mazo, tjugador *jug) {
    mazo->num = jug->vcartas[pos].num;
    mazo->color = jug->vcartas[pos].color;
    printf("\n\nEl jugador tira la carta: %d%c", mazo->num, mazo->color);
    printf("\n...Eliminamos carta de la mano del jugador y actualizamos el mazo de descarte.\n");
    eliminar_carta(pos, jug);
}

/* Código Ejercicio C - La carta más alta */
// Esta función indicará la posicion de la carta más alta
// Teniendo en cuenta que la letra es la misma que la del mazo
int carta_mas_alta(tcarta cartas[], int ncartas, tcarta mazo) {
    tcarta lcartas[MAX_CARTAS];
    int mayor, nlcartas=0, j=0, pos[MAX_CARTAS], pmayor;
    
    // creamos un vector de cartas con las letras iguales al mazo
    for(int i= 0; i<ncartas;i++) {
        if(mazo.color == cartas[i].color) {
            lcartas[j].num = cartas[i].num;
            lcartas[j].color = cartas[i].color;
            pos[j]=i;   // array de posiciones
            nlcartas++;
            j++;
        }
    }
    mayor = lcartas[0].num;
    for(int i=1; i<nlcartas && mayor<lcartas[i].num;i++) {
        pmayor = pos[i-1]; // Posicion donde se encuentra la carta más alta
    }
    return pmayor;
}