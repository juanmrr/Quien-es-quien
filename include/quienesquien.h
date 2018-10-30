//Alberto S�crates Ortega Calvo
//Juan Manuel Rubio Rodr�guez

/**
 * @file quienesquien.h
 * @brief Fichero cabecera del QuienEsQuien.
 *
 * Almacena el �rbol de preguntas para jugar al �Qui�n es qui�n?.
 */

#ifndef _QUIENESQUIEN_H_
#define _QUIENESQUIEN_H_

#define DEBUG_QUIENESQUIEN 0

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <cassert>
#include <set>
#include <sstream>

#include "pregunta.h"
#include "bintree.h"

using namespace std;

/**
 * @brief T.D.A. QuienEsQuien
 *
 * Conjunto de personajes con sus atributos.
 */
class QuienEsQuien{
private:
	/**
	  * @brief Almacena el nombre de los personajes. Su �ndice en 
	  *        este vector corresponde con el �ndice de su 
	  *        descripci�n en el tablero.
	  */
	vector<string> personajes;

	/**
	  * @brief Almacena los atributos.  Su �ndice en este vector 
	  *        corresponde con el �ndice correspondiente de cada 
	  *        vector del tablero.
	  */
	vector<string> atributos;

	/**
	  * @brief Matriz que almacena para cada personaje su valor para 
	  *        cada atributo.
	  */
	vector<vector<bool>> tablero;

	/**
	  * @brief Arbol de preguntas para adivinar personajes.
	  */
	bintree<Pregunta> arbol;

	/**
	  * @brief Nodo del arbol de preguntas correspondiente a la jugada 
	  *        actual.
	  */
	bintree<Pregunta>::node jugada_actual;
public:
	/**
	  * @brief Constructor b�sico de la clase
	  */
	QuienEsQuien();
	/**
	  * @brief Constructor de copia.
	  * @param quienEsQuien QuienEsQuien a copiar.
	  */
	QuienEsQuien(const QuienEsQuien &quienEsQuien);
	/**
	* @brief Destructor del pregunta.
	*/
	~QuienEsQuien();
	/**
	  * @brief Vacia todos los datos del QuienEsQuien receptor.
	  */
	void limpiar();
	/**
	* @brief Sobrecarga del operador de asignaci�n.
	* @param quienEsQuien objeto a copiar.
	* @return Referencia al objeto copiado.
	*/
	QuienEsQuien& operator = (const QuienEsQuien &quienEsQuien);
	
	/**
	* @brief Operador de extracci�n de flujo.
	* @param is Stream de entrada
	* @param quienEsQuien Quien es quien a leer.
	* @return Referencia al stream de entrada.
	* 
	* Lee de @e is un quien es quien y lo almacena en @e 
	* quienEsQuien. El formato aceptado para la lectura es un TSV 
	* (tab-separated values) en el que las columnas tienen cabecera y 
	* son las preguntas. La �ltima columna corresponde al nombre del 
	* personaje. Tras la cabecera se especifica en cada l�nea un 
	* personaje, teniendo el valor 1 o 0 si tiene/no tiene el 
	* atributo de la columna. En la �ltima columna se da el 
	* nombre del personaje.
	*/
	friend istream& operator >> (istream& is, QuienEsQuien &quienEsQuien);
	
	/**
	* @brief Operador de inserci�n de flujo.
	* @param os Stream de salida
	* @param quienEsQuien Quien es quien a escribir.
	* @return Referencia al stream de salida.
	* 
	* Escribe en @e is un quien es quien.
	* El formato usado para la escritura es un TSV 
	* (tab-separated values) en el que las columnas tienen cabecera y 
	* son las preguntas. La �ltima columna corresponde al nombre del 
	* personaje. Tras la cabecera se especifica en cada l�nea un 
	* personaje, teniendo el valor 1 o 0 si tiene/no tiene el 
	* atributo de la columna. En la �ltima columna se da el 
	* nombre del personaje.
	*/
	friend ostream& operator << (ostream& os, const QuienEsQuien &quienEsQuien);

	/**
	  * @brief Escribe en la salida estandard las estructuras atributos, personajes y tablero.
	  */
	void mostrar_estructuras_leidas();

	/**
	  * @brief Este m�todo construye el �rbol de preguntas para todos los personajes del tablero.
	  */
	bintree<Pregunta> crear_arbol();
	
	/**
	  * @brief Sustituye el �rbol actual por el �rbol pasado por par�metro.
	  * 
	  * @param arbol_nuevo Arbol de preguntas que sustituye al actual.
	  * 
	  */
	void usar_arbol(bintree<Pregunta> arbol_nuevo);

	/**
	  * @brief Escribe el arbol generado en la salida estandard.
	  */
	void escribir_arbol_completo() const;

	/**
	   @brief M�todo que modifica el �rbol de preguntas para que haya
	          preguntas redundantes.
	   @post El �rbol de preguntas se modifica.
	*/
	void eliminar_nodos_redundantes();

	/**
	 * @brief Inicializa el juego.
	 * @post  Si la partida anterior no hab�a terminado se 
	 *        pierde el progreso.
	 */
	void iniciar_juego();

	/**
	  * @brief Dado un estado del tablero devuelve los nombres de 
	  *        los personajes que a�n no han sido tumbados en el 
	  *        tablero.
	  *
	  * @param jugada_actual Nodo del estado del tablero.
	  * 
	  * @return Conjunto de personajes que no han sido tumbados en el tablero.
	  * 
	  * @pre El arbol del QuienEsQuien receptor debe haber sido construido previamente.
	  * @pre El nodo indicado debe ser un nodo del arbol del QuienEsQuien receptor.
	  */
	set<string> informacion_jugada(bintree<Pregunta>::node jugada_actual);
	
	/**
	  * @brief Este m�todo permite calcular la media de la profundidad de las hojas del �rbol. Este valor representa el n�mero (promedio) de preguntas necesarias para adivinar cada personaje. A menor profundidad promedio, mejor soluci�n. Esta m�trica es un indicador para evaluar la calidad de vuestra soluci�n.
	  *
	  * @return Profundidad media del arbol de preguntas.
	  *
	  * @pre El arbol de preguntas debe haber sido construido previamente.
	  */
	float profundidad_promedio_hojas(); 

	/**
	  * @brief Rellena los datos del QuienEsQuien con un tablero calculado aleatoriamente.
	  * 
	  * @param numero_de_personajes N�mero de personajes que tiene el tablero a crear.
	  */
	void tablero_aleatorio(int numero_de_personajes);

	/**
	  * @brief construye completamente el �rbol, se usa como apoyo recursivo en crear arbol.
	  * 
	  * @param columna_actual columna sobre la que operamos (atributo sobre el que preguntamos).
	  * @param numero_personajes que quedan.
	  * @param vector_posiciones vector con las posiciones de los personajes que quedan.
	  */

	bintree<Pregunta> construir_pregunta(int columna_actual, int numero_personajes, vector<int> vector_posiciones);

	/**
	  * @brief proporciona la informaci�n de la jugada recursivamente, se usa como apoyo recursivo de informacion_jugada.
	  * 
	  * @param jugada_actual, nodo por el que vamos buscando.
	  * @param personajes_levantados, set en el que se van a almacenar los nombres de los jugadores restantes.
	  */

	bintree<Pregunta>::node info_jugada_recursivo(bintree<Pregunta>::node jugada_actual, set<string> & personajes_levantados);

	/**
	  * @brief Este m�todo construye el �rbol de preguntas con las preguntas m�s discriminatorias.
	  */

	bintree<Pregunta> crear_arbol_entropia();

	/**
	  * @brief construye completamente el �rbol �ptimo, se usa como apoyo recursivo en crear arbol entropia
	  * 
	  * @param pregunta_mas_discriminatoria, que es el atributo que se va a tratar.
	  * @param numero_personajes que quedan.
	  * @param vector_posiciones vector con las posiciones de los personajes que quedan.
	  * @param preguntas_restantees vector con las preguntas que ya hemos hecho.
	  */

	
	bintree<Pregunta> construir_pregunta_entropia(int pregunta_mas_discriminatoria, int numero_personajes, vector<int> vector_posiciones, set<int> preguntas_restantes);

	/**
	  * @brief devuelve la pregunta m�s �ptima, el atributo m�s discriminatorio
	  * 
	  * @param numero_personajes que quedan.
	  * @param vector_posiciones vector con las posiciones de los personajes que quedan.
	  * @param preguntas_restantees vector con las preguntas que ya hemos hecho.
	  */

	int entropia (set<int> preguntas_restantes, vector<int> vector_posiciones, int numero_personajes);

	/**
	  * @brief devuelve el historial de preguntas anterior a una jugada.
	  * 
	  * @param jugada, jugada desde la que queremos obtener el historial.
	  */

	void preguntas_formuladas (bintree<Pregunta>::node jugada);

	/*void aniade_personaje (string nombre, vector<bool> caracteristicas);*/

	/**
	  * @brief elimina un personaje del tablero.
	  * 
	  * @param nombre, nombre del personaje que queremos eliminar del tablero.
	  */

	void elimina_personaje (string nombre);

};

#endif

