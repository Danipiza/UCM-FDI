#include <iostream>
#include <vector>
#include <string>

using namespace std;


/* Como es una asignatura del primer cuatrimestre de la carrera, no nos dejaban estructurar el proyecto en
varios ficheros, todo el proyecto tenia que estar en un unico fichero .cpp */


/*
Recordemos los elementos y las reglas de nuestro juego del parchis:

- Hay cuatro colores: amarillo, azul, rojo y verde.
- Cada jugador juega con cuatro fichas de su color asignado.
- Se utiliza un dado para determinar los movimientos para las fichas
- Casas: zonas cuadradas con circulos en color que hay en las esquinas del tablero;
	las fichas de cada jugador comienzan encerradas en su casa.
- Alrededor de las casas hay 68 casillas, numeradas del 0 al 67.
	No puede haber mas de dos fichas en una misma casilla.
- Salida: casillas rectangulaes en color que hay junto a cada casa (5, 22, 39 y 56).
- Los jugadores sacan una ficha a su salida cuando el dado marca un cinco.
- Seguros: casillas rectangulares con circulo gris (0, 12, 17, 29, 34, 46, 51 y 63)
	ademas de las salida
- Metas: casillas triangulares en color que hay en el centro del tablero.
- Zanatas: casullas junto a las subidas a meta (0, 17, 34, 51);
	cada ficha accede a la subida a meta desde la zanata de su jugador
- Puente: dos fichas de igual color en una misma casilla
	(si estan en un seguro es una barrera que no se puede franquear)
- Si un jugador debe sacar una ficha de casa y la salida hay dos fichas,
	alguna de ellas de otro jugador, se manda la uñtima que haya llegado a casa.
- Las fichas se mueven siempre en el sentido creciente del numero de casilla, siendo
	circuito continuo (se pasa de nuevo a la casilla 0 desde la casilla 67).
- Una ficha que ya haya salido de casa y no este bloqueada se
	podra mover tantas casillas como indique el dado
- Un jugador gana cuando todas sus fichas ha llegado a la meta;
	las fichas solo pueden llegar a la meta con el numero de movimientos exacto
- Comer: una ficha llega a una casilla, que no sea un seguro, en la que hay otra ficha de un comentario,
	enviando esta ultima a su casa y ganando una jugada extra de 20
- Cuando una ficha llega a la meta, el jugador gana una jugada extra de 10 movimientos.
- Cuando todas las fichas de un jugador estan fuera de casa los seises se cuentan como sietes.
- Cuando un jugador juega un seis, tiene derecho a una nueva jugada.
	Pero al tercer seis consecutivo se manda a casa la ultima ficha movida por el jugador,
	excepto si ese ultimo movimiento fue en la subida a meta.
*/

// amarillo, azul, rojo, verde 
// dado se genera aleatoriamente

typedef enum { Amarillo, Azul, Rojo, Verde, Ninguno, Gris } tColor;
typedef tColor tCasillas[68];
typedef int tFichas[4];
typedef tFichas tJugadores[4];



bool esSeguro(int casilla);
int salidaJugador(int jugador);
int zanataJugador(int jugador);
string colorACadena(tColor color);
char colorALetra(tColor color);

void iniciar(tJugadores jugadores, tCasillas calle1, tCasillas calle2, tColor& jugadorTurno);
bool puente(const tCasillas calle1, const tCasillas calle2, int casilla);
int cuantasEn(const tFichas jugador, int casilla);
int primeraEn(const tFichas jugador, int casilla);
int segundaEn(const tFichas jugador, int casilla);
void saleFicha(tJugadores jugadores, tColor jugadorTurno, tCasillas calle1, tCasillas calle2);
void aCasita(tJugadores jugadores, int casilla, tCasillas calle1, tCasillas calle2);
bool todasEnMeta(const tFichas jugador);

// Subprogramas de dinamica del juego 
void abrirPuente(tJugadores jugadores, int casilla, int casilla2, int& premio,
	tColor jugadorTurno, int& ultimaFichaMovida, tCasillas calle1,
	tCasillas calle2);
bool procesa5(tJugadores jugadores, tColor jugadorTurno, int& premio,
	bool& pasaTurno, tCasillas calle1, tCasillas calle2);
bool procesa6(tJugadores jugadores, tColor jugadorTurno, int& premio,
	bool& pasaTurno, int& seises, int& ultimaFichaMovida, int& tirada,
	tCasillas calle1, tCasillas calle2);
bool jugar(tJugadores jugadores, tColor jugadorTurno, int& premio, bool&
	fin, int& seises, int& ultimaFichaMovida, int tirada, tCasillas calle1,
	tCasillas calle2);
bool puedeMover(const tJugadores jugadores, tColor jugadorTurno, int
	ficha, int& casilla, int tirada, const tCasillas calle1, const tCasillas
	calle2);
void mover(tJugadores jugadores, tColor jugadorTurno, int ficha, int
	casilla, int& premio, int& ultimaFichaMovida, tCasillas calle1,
	tCasillas calle2);


int main() {

	tCasillas fila1, fila2;
	int cont6;
	int ultFicha;
	int jugador;
	int dado;

	return 0;
}


/*TODO
*/
bool esSeguro(int casilla) {
	
}

/*TODO
*/
int salidaJugador(int jugador) {
	
}

/*TODO
*/
int zanataJugador(int jugador) {
	
}

/*TODO
*/
string colorACadena(tColor color) {
	
}

/*TODO
*/
char colorALetra(tColor color) {
	
}

/*TODO
*/
void iniciar(tJugadores jugadores, tCasillas calle1, tCasillas calle2,
	tColor& jugadorTurno) {

}


/*TODO
*/
bool puente(const tCasillas calle1, const tCasillas calle2, int casilla) {

}

/*TODO
*/
int cuantasEn(const tFichas jugador, int casilla) {

}

/*TODO
*/
int primeraEn(const tFichas jugador, int casilla) {

}

/*TODO
*/
int segundaEn(const tFichas jugador, int casilla) {

}

/*TODO
*/
void saleFicha(tJugadores jugadores, tColor jugadorTurno, tCasillas calle1, tCasillas calle2) {

}

/*TODO
*/
void aCasita(tJugadores jugadores, int casilla, tCasillas calle1, tCasillas calle2) {

}

/*TODO
*/
bool todasEnMeta(const tFichas jugador) {

}


// -----------------------------------------------------------------------------------------------------
// --- Subprogramas de dinamica del juego  -------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------


/*TODO
*/
void abrirPuente(tJugadores jugadores, int casilla, int casilla2, int& premio,
	tColor jugadorTurno, int& ultimaFichaMovida, tCasillas calle1,
	tCasillas calle2) {


}

/*TODO
*/
bool procesa5(tJugadores jugadores, tColor jugadorTurno, int& premio,
	bool& pasaTurno, tCasillas calle1, tCasillas calle2) {


}

/*TODO
*/
bool procesa6(tJugadores jugadores, tColor jugadorTurno, int& premio,
	bool& pasaTurno, int& seises, int& ultimaFichaMovida, int& tirada,
	tCasillas calle1, tCasillas calle2) {


}

/*TODO
*/
bool jugar(tJugadores jugadores, tColor jugadorTurno, int& premio, bool&
	fin, int& seises, int& ultimaFichaMovida, int tirada, tCasillas calle1,
	tCasillas calle2) {

}

/*TODO
*/
bool puedeMover(const tJugadores jugadores, tColor jugadorTurno, int
	ficha, int& casilla, int tirada, const tCasillas calle1, const tCasillas
	calle2) {


}

/*TODO
*/
void mover(tJugadores jugadores, tColor jugadorTurno, int ficha, int
	casilla, int& premio, int& ultimaFichaMovida, tCasillas calle1,
	tCasillas calle2) {



}