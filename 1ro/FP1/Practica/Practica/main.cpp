#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#include <cstdlib> // srand() y rand()
#include <ctime>   // time()

using namespace std;

// En esta asignatura no se podia usar breaks y returns en los bucles.

#define JIEINT 1
#define CEINT 2
#define MCE 3
#define FIEINT 4


const unordered_map<int, string> errorMessages = {
	{JIEINT, "Error: Indice de jugador fuera de intervalo"},
	{CEINT, "Error: Casilla fuera de intervalo"},
	{MCE, "Error: No hay ficha para mandar a casa"},
	{FIEINT, "Error: Indice de ficha fuera de intervalo"}
};

#define CASILLASP 68
#define JUGADORES 4
#define FICHAS 4


/*
Precondicion: errorCode puede ser cualquier error

Devuelve un booleano:
	true: si la casilla seleccionada es un seguro
	false: en caso contrario
*/
string getMensajeError(int errorCode) {
	string ret;
	auto it = errorMessages.find(errorCode);

	if (it != errorMessages.end()) ret = it->second;
	else ret = "Error desconocido";

	return ret;
}

int num_error;

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
	alguna de ellas de otro jugador, se manda la ultima que haya llegado a casa.
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
typedef tColor tCasillas[CASILLASP];
typedef int tFichas[JUGADORES];
typedef tFichas tJugadores[JUGADORES];




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

// extra
void imprimeTablero(tJugadores jugadores, tCasillas fila1, tCasillas fila2);
tColor intAColor(int val);
int colorAInt(tColor val);


void setColor(int color) {
	switch (color) {
	case 0:
		cout << "\x1b[33;107m";
		break;
	case 1:
		cout << "\x1b[34;107m";
		break;
	case 2:
		cout << "\x1b[31;107m";
		break;
	case 3:
		cout << "\x1b[32;107m";
		break;
	case 4:
	case 5:
		cout << "\x1b[90;107m";
		break;
	}
}


void imprimeTablero(tJugadores jugadores, tCasillas fila1, tCasillas fila2) {


	string print;
	int i, j, k; // punteros


	cout << "00000000001111111111222222222233333333334444444444555555555566666666\n";
	cout << "01234567890123456789012345678901234567890123456789012345678901234567\n";
	cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";


	// ----------------------------------------------------------------------------------
	// --- Fila 2 -----------------------------------------------------------------------
	// ----------------------------------------------------------------------------------

	for (i = 0; i < CASILLASP; i++) {
		if (fila2[i] != Ninguno) {
			setColor(fila2[i]);

			for (j = 0; j < JUGADORES; j++) {
				if (jugadores[colorAInt(fila2[i])][j] == i) {
					cout << j + 1;
					break;
				}
			}
			setColor(4);
		}
		else cout << " ";
	}
	cout << "\n";


	cout << "o----o------o----o----o------o----o----o------o----o----o------o----\n";

	// ----------------------------------------------------------------------------------
	// --- Fila 1 -----------------------------------------------------------------------
	// ----------------------------------------------------------------------------------

	for (i = 0; i < CASILLASP; i++) {
		if (fila1[i] != Ninguno) {
			setColor(fila1[i]);

			for (j = 3; j >= 0; j--) {
				if (jugadores[colorAInt(fila1[i])][j] == i) {
					cout << j + 1;
					break;
				}
			}
			setColor(4);
		}
		else cout << " ";
	}
	cout << "\n";

	// ----------------------------------------------------------------------------------
	// --- Entrada a meta ---------------------------------------------------------------
	// ----------------------------------------------------------------------------------

	for (i = 0; i < JUGADORES; i++) {
		setColor(i);
		cout << "V";
		setColor(4);
		cout << ">>>>";
		setColor(i);
		cout << "^";
		setColor(4);
		cout << ">>>>>>>>>>>";
	}
	cout << "\n";

	// ----------------------------------------------------------------------------------
	// --- Subidas a meta ---------------------------------------------------------------
	// ----------------------------------------------------------------------------------
	// 
	// --- + Casas ----------------------------------------------------------------------
	int cont = 101, tmp = 0;
	for (i = 0; i < 4; i++) {
		tmp = 0;
		for (j = 0; j < JUGADORES; j++) {
			setColor(j);
			print = "VV   ^           ";
			if (jugadores[j][i] == -1) print[5] = 49 + i;

			for (k = 0; k < FICHAS; k++) {
				if (jugadores[j][k] == cont) {
					print[tmp++] = 49 + k;
				}
			}

			cout << print;
		}
		cout << "\n";
		cont++;
	}

	// --- sin Casas --------------------------------------------------------------------
	for (i = 0; i < 3; i++) {
		tmp = 0;
		for (j = 0; j < JUGADORES; j++) {
			setColor(j);
			print = "VV               ";
			for (k = 0; k < JUGADORES; k++) {
				if (jugadores[j][k] == cont) {
					print[tmp++] = 49 + k;
				}
			}

			cout << print;
		}
		cout << "\n";
		cont++;
	}

	// ----------------------------------------------------------------------------------
	// --- Metas ------------------------------------------------------------------------
	// ----------------------------------------------------------------------------------

	for (i = 0; i < 2; i++) {
		for (j = 0; j < JUGADORES; j++) {
			setColor(j);
			print = "..               ";
			if (jugadores[j][(2 * i)] == 108) print[0] = 49 + (2 * i);
			if (jugadores[j][(2 * i + 1)] == 108) print[1] = 49 + (2 * i + 1);

			cout << print;
		}
		cout << "\n";
		cont++;
	}

	// reinicia el color
	setColor(4);
	cout << "\n";
}



int main() {
	tCasillas calle1, calle2;
	tJugadores jugadores;
	tColor jugadorTurno;
	int jugador = 1;

	bool fin = false;
	int tirada = -1;
	int premio = 0;
	int seises = 0;
	int ultimaFichaMovida = -1;


	bool pasaTurno = true;
	bool juega = false;


	iniciar(jugadores, calle1, calle2, jugadorTurno);
	jugadorTurno = intAColor(1);

	while (!fin) {
		imprimeTablero(jugadores, calle1, calle2);

		cin >> tirada;
		//tirada = (rand() % 6) + 1;


		if (tirada == 6) {
			juega = procesa6(jugadores, jugadorTurno, premio, pasaTurno,
				seises, ultimaFichaMovida, tirada, calle1, calle2);
		}
		else {
			pasaTurno = true;
			seises = 0;

			if (tirada == 5) {
				juega = procesa5(jugadores, jugadorTurno, premio, pasaTurno,
					calle1, calle2);
				if (juega) {
					setColor(jugadorTurno);
					cout << "Sale una ficha de casa\n";
					setColor(4);
				}
			}
		}


		if (!juega) {
			jugar(jugadores, jugadorTurno, premio, fin, seises, ultimaFichaMovida, tirada, calle1, calle2);
		}

		while (premio != 0) {
			imprimeTablero(jugadores, calle1, calle2);
			jugar(jugadores, jugadorTurno, premio, fin, seises, ultimaFichaMovida, premio, calle1, calle2);
		}

		if (pasaTurno) {
			jugador = (jugador + 1) % JUGADORES;
			jugadorTurno = intAColor(jugador);
		}

		juega = false;
	}

	int ganador = -1;
	for (int i = 0; i < JUGADORES; i++) {
		if (cuantasEn(jugadores[i], 108) == 4) ganador = i;
	}
	setColor(ganador);
	cout << "Fin de la partida. Gana " << colorACadena(intAColor(ganador)) << ".\n";
	setColor(4);

	/*imprimeTablero(jugadores, calle1, calle2);

	jugadores[0][0] = 101;
	jugadores[0][1] = 103;
	jugadores[0][2] = 103;
	jugadores[0][3] = 104;

	imprimeTablero(jugadores, calle1, calle2);
	int casilla = 101;
	if (puedeMover(jugadores, jugadorTurno, 0, casilla, tirada, calle1, calle2))
		mover(jugadores, jugadorTurno, 0, 103, premio, ultimaFichaMovida, calle1, calle2);
	imprimeTablero(jugadores, calle1, calle2);*/

	/*

	/*fila1[67] = Rojo;
	jugadores[1][2] = 67;

	fila2[67] = Rojo;
	jugadores[0][2] = 67;//*

	jugadores[2][3] = 108;
	//jugadores[3][2] = 108;

	calle1[0] = Azul;
	jugadores[1][0] = 0;

	calle1[29] = Verde;
	jugadores[3][0] = 29;
	/*calle2[29] = Rojo;
	jugadores[2][1] = 29;//*


	calle1[22] = Amarillo;
	jugadores[0][2] = 22;







	procesa5(jugadores, jugadorTurno, premio, pasaTurno, calle1, calle2);
	imprimeTablero(jugadores, calle1, calle2);
	procesa5(jugadores, jugadorTurno, premio, pasaTurno, calle1, calle2);
	//procesa5(jugadores, jugadorTurno, premio, pasaTurno, calle1, calle2);

	imprimeTablero(jugadores, calle1, calle2);

	int ficha = 2;
	int casilla = 0;
	int tirada = 7;
	if (puedeMover(jugadores, jugadorTurno, ficha, casilla, tirada, calle1, calle2)) {
		mover(jugadores, jugadorTurno, ficha, casilla, premio, ultimaFichaMovida, calle1, calle2);
	}

	imprimeTablero(jugadores, calle1, calle2);
	*/

	return 0;
}


/**
* Precondicion: casilla puede ser cualquier entero.
*
* Devuelve un booleano:
*	true: si la casilla seleccionada es un seguro
*	false: en caso contrario
*/
bool esSeguro(int casilla) {
	return casilla == 0 || casilla == 12 || casilla == 17 || casilla == 29 ||
		casilla == 34 || casilla == 46 || casilla == 51 || casilla == 63 ||
		casilla == 5 || casilla == 22 || casilla == 39 || casilla == 56;
}

/**
* Precondicion: jugador tiene que estar en el intervalo [0-3].
*
* Devuelve un entero:
*	la casilla de salida asignada al jugador.
*	-1 si la variable "jugador" no pertenece al intervalo designado.
*/
int salidaJugador(int jugador) {
	if (jugador < 0 || jugador>3) { num_error = JIEINT; return -1; }
	int ret = 5;

	if (jugador == 1) ret = 22;
	else if (jugador == 2) ret = 39;
	else if (jugador == 3) ret = 56;

	return ret;
}

/**
* Precondicion: jugador tiene que estar en el intervalo [0-3].
*
* Devuelve un entero:
*	la casilla zanata asignada al jugador.
*	-1 si la variable "jugador" no pertenece al intervalo designado.
*/
int zanataJugador(int jugador) {
	if (jugador < 0 || jugador>3) { num_error = JIEINT; return -1; }
	int ret = 0;

	if (jugador == 1) ret = 17;
	else if (jugador == 2) ret = 34;
	else if (jugador == 3) ret = 51;

	return ret;
}

/**
* Precondicion: color puede ser cualquier tColor.
*
* Traduce tColor a string
*/
string colorACadena(tColor color) {
	string ret = "Amarillo";

	if (color == 1) ret = "Azul";
	else if (color == 2) ret = "Rojo";
	else if (color == 3) ret = "Verde";
	else if (color == 4) ret = "Ninguno";
	else if (color == 5) ret = "Gris";

	return ret;
}

/**
* Precondicion: color puede ser cualquier tColor.
*
* Traduce tColor a char
*/
char colorALetra(tColor color) {
	char ret = 'A';

	if (color == 1) ret = 'Z'; // azul
	else if (color == 2) ret = 'R';
	else if (color == 3) ret = 'E'; // verde
	else if (color == 4) ret = 'N';
	else if (color == 5) ret = 'G';

	return ret;
}

/**
* Inicializa el generador de numeros aleatorios, con srand() y los elementos del juego (ficha y tablero)
* Tambien pone el color de la fuente en gris sobre fondo blanco.
*
* Devuelve el jugador que empieza a jugar (aleatorio de [0,3])
*/
void iniciar(tJugadores jugadores, tCasillas calle1, tCasillas calle2,
	tColor& jugadorTurno) {

	int i = 0;

	srand(static_cast<unsigned>(time(0)));
	setColor(4);
	jugadorTurno = intAColor(rand() % JUGADORES + 1);

	// init filas
	for (; i < CASILLASP; i++) {
		calle1[i] = Ninguno;
		calle2[i] = Ninguno;
	}



	// init jugadores
	for (i = 0; i < JUGADORES; i++) {
		for (int j = 0; j < JUGADORES; j++) {
			jugadores[i][j] = -1;
		}
	}


}


/**
* Precondicion: casilla tiene que ser un entero [0,67] U [101,107]
*
* Devuelve un booleano:
*	true: si en la casilla hay dos fichas de mismo color.
*	false: en caso contrario.
*/
bool puente(const tCasillas calle1, const tCasillas calle2, int casilla) {
	if (casilla < 0 || casilla > 107 || (casilla > 67 && casilla < 101)) { num_error = CEINT; return false; }

	bool ret = false;

	if (calle2[casilla] != Ninguno && calle1[casilla] == calle2[casilla]) ret = true;

	return ret;
}

/**
* Precondicion: la casilla tiene que ser un entero con valor [-1,67] U [101, 108]
*
* Devuelve un entero. El numero de fichas de un jugador en una casilla
*/
int cuantasEn(const tFichas jugador, int casilla) {
	if (casilla < -1 || casilla > 108 || (casilla > 67 && casilla < 101)) { num_error = CEINT; return -1; }

	int ret = 0;
	int i = 0;

	for (; i < JUGADORES; i++) {
		if (jugador[i] == casilla) ret++;
	}


	return ret;
}

/**
* Precondicion: la casilla tiene que ser un entero con valor [-1,67] U [101, 108]
*
* Menor indice de ficha del jugador que esta en esa casilla.
* Se usa para sacar de casa una ficha.
*
* Devuelve un entero:
*	-1: si no hay ninguna en la casilla
*	[0,3]: el indicde de la ficha
*/
int primeraEn(const tFichas jugador, int casilla) {
	if (casilla < -1 || casilla > 108 || (casilla > 67 && casilla < 101)) { num_error = CEINT; return -1; }

	int i = 0;
	bool fin = false;

	while (i < JUGADORES && !fin) {
		if (jugador[i] == casilla) fin = true;
		i++;
	}


	return i - 1;
}

/**
*
* Mayor indice de ficha del jugador que esta en esa casilla
* Se usa para determinar que ficha se va a casa (aCasita)
* y en el manejo de los puentes abrirPuente() y procesa6()
*
* Devuelve un entero:
*	-1: si no hay ninguna en la casilla
*	[0,3]: el indicde de la ficha
* Mayor	índice	de	ficha	del
*/
int segundaEn(const tFichas jugador, int casilla) {
	if (casilla < -1 || casilla > 108 || (casilla > 67 && casilla < 101)) { num_error = CEINT; return -1; }

	int i = 3;
	bool fin = false;

	while (i >= 0 && !fin) {
		if (jugador[i] == casilla) fin = true;
		i--;
	}


	return i + 1;
}

/**
*
* Sale de casa una ficha del jugador, concretamente la de menor indice que este en casa.
* La que sale va a la calle 1 y si hubiera otra se coloca en la calle 2.
*/
void saleFicha(tJugadores jugadores, tColor jugadorTurno, tCasillas calle1, tCasillas calle2) {
	int indice, salida;

	indice = primeraEn(jugadores[jugadorTurno], -1);
	salida = salidaJugador(jugadorTurno);

	jugadores[jugadorTurno][indice] = salida;

	if (calle1[salida] != Ninguno) calle2[salida] = calle1[salida];// calle1[salida];
	calle1[salida] = jugadorTurno;
}

/**
*
* Manda a casa la ultima ficha que llego a la casilla, la que esta en la calle2
*/
void aCasita(tJugadores jugadores, int casilla, tCasillas calle1, tCasillas calle2) {
	if (calle2[casilla] == Ninguno) { num_error = MCE; return; }
	if (casilla < -1 || casilla > 108 || (casilla > 67 && casilla < 101)) { num_error = CEINT; return; }

	int indice;
	int i = 0;

	for (; i < JUGADORES; i++) {
		if (jugadores[calle2[casilla]][i] == casilla) indice = i;
	}

	jugadores[calle2[casilla]][indice] = -1;
	calle2[casilla] = Ninguno;
}

/**
*
* Devuele un booleano:
*	true: si todas las fichas del jugador estan en la meta (casilla 108)
*	false: en caso contrario
*/
bool todasEnMeta(const tFichas jugador) {
	int cont = 0;
	int i = 0;

	for (; i < JUGADORES; i++) {
		if (jugador[i] == 108) cont++;
	}

	return cont == JUGADORES;
}


// -----------------------------------------------------------------------------------------------------
// --- Subprogramas de dinamica del juego  -------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------


/* NO IMPLEMENTADA, PORQUE EN LA PRACTICA SOLO ABRIA PUENTE CON 2 FICHAS DEL MISMO COLOR
* PERO LO HE IMPLEMENTADO PARA QUE ABRA CUALQUIER PUENTE SI SALE UN 6
*
* Abre el puente del jugador en casilla, llevando la ficha con mayor indice en el puente a la casilla 2
* y ganando el premio si se come otra ficha. El movimiento en si se realiza invocando desde aqui la
* funcion mover() para realizar el movimiento correspondiente.
*/
void abrirPuente(tJugadores jugadores, int casilla, int casilla2, int& premio,
	tColor jugadorTurno, int& ultimaFichaMovida, tCasillas calle1,
	tCasillas calle2) {}

/**
*
* Intenta sacar una ficha de casa del jugador, si queda alguna.
* Si ya hay dos fichas en la casilla de salida, entonces si ambas son suyas no sale de casa.
* Si de las dos una es de otro jugador, se come esa, y si las dos son de otro jugador, se come la ultima
* que haya llegado. Al comer gana un premio de 20 movimientos extra y el jugador conserva el turno.
* No se encarga de mover al jugador
*
* Devuelve un booleano:
*	true: si se ha podido sacar ficha.
*	false: en caso contrario
*/
bool procesa5(tJugadores jugadores, tColor jugadorTurno, int& premio,
	bool& pasaTurno, tCasillas calle1, tCasillas calle2) {

	bool ret = true;
	int salida, indice, indiceS;
	int i;
	premio = 0;
	pasaTurno = true;

	salida = salidaJugador(jugadorTurno);
	indiceS = primeraEn(jugadores[jugadorTurno], -1);

	// cero/una ficha
	if (calle2[salida] == Ninguno) saleFicha(jugadores, jugadorTurno, calle1, calle2);
	else { // dos fichas


		if (calle1[salida] == jugadorTurno &&
			calle1[salida] == calle2[salida]) { // suyas = no sale
			ret = false;
		}
		else { // 1 distinta = se la come
			if (calle2[salida] == jugadorTurno) { // calle1 de distinto color del jugador que sale
				for (i = 0; i < JUGADORES; i++) {
					if (jugadores[calle1[salida]][i] == salida) indice = i;
				}
				jugadores[calle1[salida]][indice] = -1;		// a casa. valor del jugador que se va
				calle1[salida] = jugadorTurno;				// cambio de color
				jugadores[jugadorTurno][indiceS] = salida;	// sale de casa. valor del jugador que sale
			}
			else { // calle 1 del color del jugador que sale o dos colores distintos
				for (i = 0; i < JUGADORES; i++) {
					if (jugadores[calle2[salida]][i] == salida) indice = i;
				}
				jugadores[calle2[salida]][indice] = -1;		// a casa. valor del jugador que se va
				calle2[salida] = jugadorTurno;				// cambio de color
				jugadores[jugadorTurno][indiceS] = salida;	// sale de casa. valor del jugador que sale
			}
			premio = 20;

		}

	}


	return ret;
}

/*TODO
*
* Actualiza la tirada a 7 si no quedan fichas en casa y gestiona los dos casos especiales (dado=6).
* manda ultimaFichaMovida a casa si es el tercer seis consecutivo, o abre obligatoriamente un puente
* que tenga el jugador (si tiene dos, el usuario ha de decidir cual).
*
* El jugador mantiene turno si no es su tercer seis consecutivo.
* Si no hay movimiento obligatorio, el movimiento no se lleva a cabo en esta funcion, al igual que en
* procesa5() pues es responsabilidad de jugar(), no sera invocada desde aqui.
*
* Devuelve un booleano:
*	true: si el movimiento se ha llevado a cabo de alguna de esas dos maneras (incluso si deberia de abrir
*		puente pero no puede por bloqueo)
*	false: en caso contrario.
*/
bool procesa6(tJugadores jugadores, tColor jugadorTurno, int& premio,
	bool& pasaTurno, int& seises, int& ultimaFichaMovida, int& tirada,
	tCasillas calle1, tCasillas calle2) {
	setColor(jugadorTurno);


	bool ret = false;
	int i = 0; // iterador
	// variables de abrir puente
	int puentes[FICHAS] = { -1,-1,-1,-1 };
	int pos, cont = 0, ficha;

	pasaTurno = false;

	// actualiza
	if (cuantasEn(jugadores[jugadorTurno], -1) == 0) {
		cout << "Todas las fichas fuera de casa. tirada=7\n";
		tirada++;
	}

	for (; i < FICHAS; i++) {
		pos = jugadores[jugadorTurno][i];
		if ((pos > -1 && pos < 68) && pos != -1 && calle2[pos] != Ninguno) {
			cont++;
			puentes[i] = pos;
		}
	}

	// casos especiales
	if (seises == 2) {
		int num = cuantasEn(jugadores[jugadorTurno], -1);
		if (num != 4) {
			cout << "Tercer seis consecutivo. Ultima ficha movida (" << ultimaFichaMovida + 1 << ") a casa.\n";
			pos = jugadores[jugadorTurno][ultimaFichaMovida];

			if (calle2[pos] == jugadorTurno) calle2[pos] = Ninguno;
			else calle1[pos] = Ninguno;
			// manda a casa
			jugadores[jugadorTurno][ultimaFichaMovida] = -1;
		}
		else cout << "Tercer seis consecuitivo. Ninguna ficha fuera de casa, solo pierde el turno.\n";

		pasaTurno = true;
		ret = true;
	}
	else if (cont > 0) {
		cout << "Abrir puente:\n";
		for (i = 0; i < FICHAS; i++) {
			if (puentes[i] != -1) {
				cout << i + 1 << ": De la casilla " << puentes[i] << " a la casilla " << puentes[i] + tirada << "\n";
			}
		}
		cout << "Ficha (0 para salir):";
		do {
			cin >> ficha;
		} while (ficha < 0 && ficha > 4 && puentes[ficha - 1] != -1);


		mover(jugadores, jugadorTurno, ficha - 1, jugadores[jugadorTurno][ficha - 1] + tirada, premio, ultimaFichaMovida, calle1, calle2);
		cout << "\n";
		ret = true;
	}

	seises++;


	setColor(4);
	return ret;
}

/*TODO
*
* Esta funcion se invocara cuando no haya salida una ficha de casa con 5, no se
* haya ido una ficha a casa con 6, ni haya habido que abrir un puente.
*
* La funcion preguntara al usuario que ficha quiere mover "tirada" movimientos,
* de entre las fichas que se puedan mover. Entonces se llevara a cabo el movimiento
* de dicha ficha invocando la funcion mover(). Ademas, se actualizara la ultimaFichaMovida.
* Si el usuario introduce 0 en lugar de un numero de ficha, fin valdra true, lo que provocara
* el resto del programa finalice el jugo.
*
* Devuelve un booleano:
*	true: si el turno debe pasar al siguiente.
*	false: en caso contrario.
*/
bool jugar(tJugadores jugadores, tColor jugadorTurno, int& premio, bool&
	fin, int& seises, int& ultimaFichaMovida, int tirada, tCasillas calle1,
	tCasillas calle2) {

	int disponibles[FICHAS] = { -1, -1, -1, -1 };
	int casilla, ficha, cont = 0;
	int pos, zanata;
	int i = 0;



	setColor(jugadorTurno);
	if (premio == 0) cout << "Turno para el jugador " << colorACadena(jugadorTurno) << "... Sale un " << tirada << "\n";
	else if (premio == 20) cout << "Se ha comido una ficha. Premio = 20\n";
	else cout << "Una ficha ha llegado a la meta. Premio = 10\n";
	cout << "Por favor, elige la ficha que quieres mover...\n";

	premio = 0;

	for (; i < FICHAS; i++) {
		if (puedeMover(jugadores, jugadorTurno, i, casilla, tirada, calle1, calle2)) {
			cout << i + 1 << ": De la casilla " << jugadores[jugadorTurno][i] << " a la casilla " << casilla << "\n";
			disponibles[i] = casilla;
			cont++;
		}
	}
	if (cont == 0) cout << "Ninguna ficha se puede mover. Introduce 0 para terminar el juego: ";
	else cout << "Ficha (0 para salir): ";

	bool a, b, c;
	do {
		cin >> ficha;
	} while (ficha < 0 || ficha > 4 || (disponibles[ficha - 1] == -1));

	if (ficha == 0) fin = true;
	else if (disponibles[ficha - 1] != -1) {
		/*pos = jugadores[jugadorTurno][ficha - 1];
		zanata = zanataJugador(jugadorTurno);
		if (pos < zanata && (pos + tirada) > zanata) {
			casilla = 101 - (zanata - pos - tirada + 1);
		}
		else casilla = (pos + tirada) % CASILLASP;*/
		mover(jugadores, jugadorTurno, ficha - 1, disponibles[ficha - 1],
			premio, ultimaFichaMovida, calle1, calle2);
		ultimaFichaMovida = ficha - 1;
	}

	if (cuantasEn(jugadores[jugadorTurno], 108) == 4) fin = true;

	cout << "\n";
	setColor(4);

	return false;
}

/**
*
* Precondicion: ficha es un entero en el intervalo [0,3]
*
* Indica la casilla a la que puede ir la ficha del jugador con esa tirada.
*
* Devuelve un booleano:
*	true: si puede mover la ficha
*	false: en caso contrario
*/
bool puedeMover(const tJugadores jugadores, tColor jugadorTurno, int
	ficha, int& casilla, int tirada, const tCasillas calle1, const tCasillas
	calle2) {
	if (ficha < 0 || ficha > 3) { num_error = FIEINT; return false; }

	bool ret = false, fin;

	if (jugadores[jugadorTurno][ficha] != 108) {
		int i = 0;
		ret = true;
		int zanata;

		casilla = jugadores[jugadorTurno][ficha];
		zanata = zanataJugador(jugadorTurno);
		if (casilla == zanata) {
			i++;
			casilla = 101;
		}
		fin = (casilla >= 101);

		if (casilla == -1) ret = false;

		for (; i < tirada && ret && !fin; i++) {
			if (casilla != zanata) {
				casilla++;
				casilla %= CASILLASP;

				if (calle1[casilla] != Ninguno && calle1[casilla] == calle2[casilla]) ret = false;
			}
			else {
				fin = true; // ha llegado a la zanata		
				if (i < tirada) {
					casilla = 101;
				}
			}
		}

		if (fin) {
			for (; i < tirada && ret && fin; i++) {
				casilla++;

				if (casilla == 109) fin = false;
				if (casilla != 108 && cuantasEn(jugadores[jugadorTurno], casilla) == 2) ret = false;
			}
			ret = (i == tirada) && fin;
		}
	}
	return ret;
}

/**
*
* Precondicion: ficha es un entero en el intervalo [0,3]
*
* Ejecuta el movimiento de la ficha, se usa depues de haber usado puedoMover().
*/
void mover(tJugadores jugadores, tColor jugadorTurno, int ficha, int
	casilla, int& premio, int& ultimaFichaMovida, tCasillas calle1,
	tCasillas calle2) {
	if (ficha < 0 || ficha >3) { num_error = FIEINT; return; }

	int i;
	int pos;
	int colorComido, fichaComida = -1;

	premio = 0;
	ultimaFichaMovida = ficha;

	pos = jugadores[jugadorTurno][ficha];
	// elimina el color de la posicion anterior
	if (calle2[pos] == jugadorTurno) calle2[pos] = Ninguno;
	else {
		calle1[pos] = calle2[pos];
		calle2[pos] = Ninguno;
	}

	// mueve la ficha a la nueva casilla
	pos = casilla;
	jugadores[jugadorTurno][ficha] = casilla;
	if (casilla < 101) {
		if (calle1[casilla] != Ninguno) { // en la casilla hay una ficha
		// es un seguro, se situa en la calle2
			if (esSeguro(casilla)) calle2[casilla] = jugadorTurno;
			else { // no es un seguro, se come la ficha
				if (calle1[casilla] != jugadorTurno) {
					premio = 20;

					colorComido = calle1[casilla];
					for (i = 0; i < FICHAS; i++) {
						if (jugadores[colorComido][i] == casilla) fichaComida = i;
					}
					jugadores[colorComido][fichaComida] = -1;

					calle1[casilla] = jugadorTurno;
				}
				else {
					calle2[casilla] = jugadorTurno;
				}
			}
		}
		else calle1[casilla] = jugadorTurno; // esta vacia
	}
	else {
		if (casilla == 108) premio = 10;
	}

}

// -----------------------------------------------------------------------------------------------------
// --- Extra -------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------


/**
* Devuelve un tColor, asociado a la posicion en el enumerado
*/
tColor intAColor(int val) {
	tColor ret = Amarillo;

	if (val == 1) ret = Azul;
	else if (val == 2) ret = Rojo;
	else if (val == 3) ret = Verde;
	else if (val == 4) ret = Ninguno;
	else if (val == 5) ret = Gris;

	return ret;
}

/**
* Devuelve un entero, asociado a la posicion en el enumerado
*/
int colorAInt(tColor val) {
	int ret = 0;

	if (val == Azul) ret = 1;
	else if (val == Rojo) ret = 2;
	else if (val == Verde) ret = 3;
	else if (val == Ninguno) ret = 4;
	else if (val == Gris) ret = 5;

	return ret;
}