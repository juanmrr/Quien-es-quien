//Alberto Sócrates Ortega Calvo
//Juan Manuel Rubio Rodríguez

#include "../include/quienesquien.h"
#include <sstream>
#include <iostream>
#include <iterator>
#include <math.h>
#include <algorithm>
#include <vector>

QuienEsQuien::QuienEsQuien(){
	//TODO :)
	//personajes = "" //vector de personajes vacío.
	//atributos = "" //vector de atributos vacío.
	//tablero = 0;
	//arbol = 0;
	//jugada_actual = 0;
}
QuienEsQuien::QuienEsQuien(const QuienEsQuien &quienEsQuien){
	//TODO :)

	//if (quienEsQuien != 0){

		personajes = quienEsQuien.personajes;
		atributos = quienEsQuien.atributos;
		tablero = quienEsQuien.tablero;
		arbol = quienEsQuien.arbol;
		jugada_actual = quienEsQuien.jugada_actual;
	//}
}
QuienEsQuien& QuienEsQuien::operator= (const QuienEsQuien &quienEsQuien){
	//TODO :)
	if (this != &quienEsQuien){

		if (this != 0){

			this->limpiar();
		}
	}	

	return *this;
}
QuienEsQuien::~QuienEsQuien(){
	this->limpiar();
}

void QuienEsQuien::limpiar(){
	//TODO :)
	personajes.clear(); //vector de personajes vacío.
	atributos.clear(); //vector de atributos vacío.
	tablero.clear();
	arbol.clear(); //puede que haya que comprobar si no esta vacio.
	//if (!jugada_actual.null()){
	//jugada_actual.remove();
	//}
}

template <typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) {
  if ( !v.empty() ) {
    out << '[';
    std::copy (v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
    out << "\b\b]";
  }
  return out;
}

void QuienEsQuien::mostrar_estructuras_leidas(){
	cout << "personajes: "<< (this->personajes) << endl;
	cout << "atributos:  "<< (this->atributos)  << endl;
	cout << "tablero:    "<< endl;


	// Escribe la cabecera del tablero
	for(vector<string>::iterator it_atributos = this->atributos.begin();
		it_atributos != this->atributos.end();
		it_atributos++){
		cout << *it_atributos << "\t";
	}
	cout <<endl;

	int indice_personaje = 0;
	for(vector<vector<bool>>::iterator it_tablero_atributos = tablero.begin();
		it_tablero_atributos!= tablero.end();
		it_tablero_atributos++){

		string personaje = this->personajes[indice_personaje];
		int indice_atributo = 0;
		for(vector<bool>::iterator it_atributos_personaje = (*it_tablero_atributos).begin();
			it_atributos_personaje != (*it_tablero_atributos).end();
			it_atributos_personaje++){

			cout << *it_atributos_personaje<<"\t";

			indice_atributo++;
		}

		cout << personaje << endl;

		indice_personaje++;
	}

}

/**
  * @brief Devuelve una copia de la cadena original sin las subcadenas no deseadas.
  * 
  * @param cadena_original Cadena de la que se eliminan las subcadenas no deseadas.
  * @param cadena_a_eliminar Subcadena que se busca y se elimina.
  *
  * @return Copia de la cadena original sin las subcadenas no deseadas.
  */
string limpiar_string(string cadena_original,string cadena_a_eliminar){
	string linea(cadena_original);

	while(linea.find_first_of(cadena_a_eliminar) != std::string::npos){
		linea.erase(linea.find_first_of(cadena_a_eliminar),cadena_a_eliminar.length());
	}

	return linea;
}

istream& operator >> (istream& is, QuienEsQuien &quienEsQuien) {
	quienEsQuien.limpiar();
	
  	if(is.good()){
  		string linea;
    	getline(is, linea, '\n');

    	linea = limpiar_string(linea,"\r");
    	
    	while(linea.find('\t') != string::npos ){
    		string atributo = linea.substr(0,linea.find('\t'));
			quienEsQuien.atributos.push_back(atributo);
    		linea = linea.erase(0,linea.find('\t')+1);
    	}

		assert(linea ==  "Nombre personaje");
	}
	
    while( is.good() ) {
    	string linea;
    	getline(is, linea, '\n');
    	linea = limpiar_string(linea,"\r");

    	//Si la linea contiene algo extrae el personaje. Si no lo es, la ignora.
    	if(linea != ""){;
	    	vector<bool> atributos_personaje;
	    	
	    	int indice_atributo=0;
	    	while(linea.find('\t') != string::npos){
	    		string valor = linea.substr(0,linea.find('\t'));
	    		
	    		assert(valor == "0" || valor == "1");
	    		
	    		bool valor_atributo = valor == "1";
	    		
	    		atributos_personaje.push_back(valor_atributo);
				
	    		linea = linea.erase(0,linea.find('\t')+1);
	    		indice_atributo++;
			}
			
			string nombre_personaje = linea;
	    	
	    	quienEsQuien.personajes.push_back(nombre_personaje);
	    	quienEsQuien.tablero.push_back(atributos_personaje);
	    }
  	}
  	
	return is;
}

ostream& operator << (ostream& os, const QuienEsQuien &quienEsQuien){

	//Escribimos la cabecera, que contiene los atributos y al final una columna para el nombre
	for(vector<string>::const_iterator it_atributos = quienEsQuien.atributos.begin();
		it_atributos != quienEsQuien.atributos.end();
		it_atributos++){

		os  << *it_atributos << "\t";
	}
	os << "Nombre personaje" << endl;

	//Rellenamos con ceros y unos cada línea y al final ponemos el nombre del personaje.
	for(int indice_personaje=0;indice_personaje<quienEsQuien.personajes.size();indice_personaje++){
		for(int indice_atributo=0;indice_atributo<quienEsQuien.atributos.size();indice_atributo++){

			os  << quienEsQuien.tablero[indice_personaje][indice_atributo] << "\t";
		}
		os  << quienEsQuien.personajes[indice_personaje] << endl;
	}

	return os;
}

/**
  * @brief Convierte un número a un vector de bool que corresponde 
  *        con su representación en binario con un numero de digitos
  *        fijo.
  *
  * @param n Número a convertir en binario.
  * @param digitos Número de dígitos de la representación binaria.
  *
  * @return Vector de booleanos con la representación en binario de @e n 
  *      con el número de elementos especificado por @e digitos. 

  */
vector<bool> convertir_a_vector_bool(int n, int digitos) {
  vector<bool> ret;
  while(n) {
    if (n&1){
      ret.push_back(true);
    } else{
      ret.push_back(false);
    }
    n>>=1;  
  }

  while(ret.size()<digitos){
  	ret.push_back(false);
  }

  reverse(ret.begin(),ret.end());
  return ret;
}


bintree<Pregunta> QuienEsQuien::crear_arbol()
{

	bintree<Pregunta> arbol_creado;

	//construimos el vector donde se almacenarán las posiciones de los jugadores restantes de la jugada.

	vector<int> vector_posiciones(personajes.size());

	for (int i = 0; i < personajes.size();i++){

		vector_posiciones[i] = i;
	}

	//construimos el resto de preguntas
	//el valor de la columna actual es 0, ya que preguntaremos por la primera.
	arbol_creado = construir_pregunta(0, personajes.size(), vector_posiciones);

	return arbol_creado;
}

//columna actual es en realidad el atributo actual.

bintree<Pregunta> QuienEsQuien::construir_pregunta(int columna_actual, int numero_personajes, vector<int> vector_posiciones){

	//en el momento en que tengamos que elegir la pregunta más discriminatoria, tendremos que cambiar la columna_actual de forma que pase a ser la que haga la ptregunta más discriminatoria.

	bintree<Pregunta> arbol_ret;

	if (numero_personajes > 1){

		int si = 0;
		int no = 0;
		int numero_personaje;

		vector<int> vector_posiciones_si;
		vector<int> vector_posiciones_no;

		Pregunta pregunta (atributos[columna_actual],numero_personajes);

		bintree<Pregunta> arbol_aux(pregunta);

		//calculamos el número de personajes con los que llamaremos a la función recursiva y qué personajes han dicho que sí y cuáles que no.

		for (int i = 0; i < numero_personajes; i++){
		
			numero_personaje = vector_posiciones[i];
		
			if (tablero[numero_personaje][columna_actual] == 1){ //comprobamos la posición del tablero que queremos.
	
				vector_posiciones_si.push_back(numero_personaje); // guardamos la posicion del personaje que ha dicho que sí.
				si++; //incrementamos el numero de peronajes que ha dicho que sí.
			}

			else{

				vector_posiciones_no.push_back(numero_personaje); // guardamos la posición del personajes que ha dicho que no.
				no++; //incrementamos el número de personajes que han dicho que no.
			}
		}

		columna_actual = columna_actual + 1; //aquí se seleccionará la pregunta más discriminatoria.

		//se llama recursivamente a la función de forma que crea y enlaza un árbol de izquiera a derecha y de abajo a arriba.

		bintree<Pregunta> arbol_izda = construir_pregunta(columna_actual,si,vector_posiciones_si);

		bintree<Pregunta> arbol_dcha = construir_pregunta(columna_actual,no,vector_posiciones_no);
		
		//cout << "se va a insertar en el nodo " << (*arbol_aux.root()) << endl; 

		//Se insertan en su respectivo lugar recursivamente los árboles que hemos ido creando.

		arbol_aux.insert_left(arbol_aux.root(), arbol_izda);
		arbol_aux.insert_right(arbol_aux.root(), arbol_dcha);
		//}

		arbol_ret = arbol_aux; //se actualiza arbol final con cada arbol auxiliar que vamos construyendo.

	}

	else if(numero_personajes == 1){ //se pone fin a la recursividad.

		Pregunta pregunta_final(personajes[vector_posiciones[0]],numero_personajes); //construimos la pregunta con el nombre del personaje que queda y un 1, el número de personajes.

		bintree<Pregunta> arbol_aux(pregunta_final); //creamos un árbol auxiliar cuya raíz es el nodo que queremos insertar.		

		arbol_ret = arbol_aux;
	}

	return arbol_ret;
}
		


void QuienEsQuien::usar_arbol(bintree<Pregunta> arbol_nuevo){ //cuando en el main se cree un arbol, para asignarlo a su atributo de la clase usaremos este método.
	arbol = arbol_nuevo;
}

void QuienEsQuien::iniciar_juego(){
	//TODO :)

	//iniciamos la jugada actual en el nodo raíz.

	jugada_actual = arbol.root();

	//iniciamos el conjunto, el cual puede ser usado para obtener el nombre de los jugadores restantes de la partida.

	set<string> personajes_restantes;

	//iniciamos el iterador con el que recorreremos el conjunto creado.

	set<string>::iterator it;

	//inicializamos encontrado, que en casos extremos puede llegar a ser true.

	bool encontrado = false;

	if ((*jugada_actual).es_personaje()){
		encontrado = true;
	}

	string respuesta;

	//hasta que no se tenga una respuesta, la máquina pregunta al jugador.

	while (!encontrado){

		//Se muestra la pregunta.

		cout << endl << (*jugada_actual) << endl << "Introduzca respuesta (si, no, info(personajes que quedan) o infop(preguntas que se han hecho hasta ahora): " << endl;

		do{
			cin >> respuesta;
			
			if( (respuesta != "si") && (respuesta != "no") && (respuesta != "info") && (respuesta != "infop"))
				cout << endl << respuesta << " no es una respuesta valida." << endl;
			
		}while((respuesta != "si") && (respuesta != "no") && (respuesta != "info") && (respuesta != "infop"));

		if (respuesta == "si"){

			jugada_actual = jugada_actual.left();
		}

		else if (respuesta == "no"){

			jugada_actual = jugada_actual.right();
		}

		else if (respuesta == "info"){

			personajes_restantes = informacion_jugada(jugada_actual);
			
			cout << endl << "\tPersonajes restantes: " << endl;

			for (it = personajes_restantes.begin(); it != personajes_restantes.end(); ++it){

				cout << (*it) << endl;
			}
		}

		else if (respuesta == "infop"){

			preguntas_formuladas (jugada_actual);
		}

			

		if ((*jugada_actual).es_personaje()){
		encontrado = true;
		}
		

	}

	cout << endl << "He encontrado a tu personaje, cuyo nombre es: " << (*jugada_actual).obtener_personaje() << endl;

	//limpiar();


	
}

set<string> QuienEsQuien::informacion_jugada(bintree<Pregunta>::node jugada_actual){ //este método se utiliza en el método iniciar_juego();
	
	//TODO :)

	set<string> personajes_levantados;
	
	bintree<Pregunta>::node node_aux;

	node_aux = info_jugada_recursivo(jugada_actual, personajes_levantados);

	return personajes_levantados;
}

bintree<Pregunta>::node QuienEsQuien::info_jugada_recursivo(bintree<Pregunta>::node jugada_actual, set<string> & personajes_levantados){

	if (!(*jugada_actual).es_personaje()){

		//se llama recursivamente a la función de forma que va recorriendo los nodos restantes.

		bintree<Pregunta>::node nodo_izda = info_jugada_recursivo(jugada_actual.left(), personajes_levantados);

		bintree<Pregunta>::node nodo_dcha = info_jugada_recursivo(jugada_actual.right(), personajes_levantados);

	}

	else if((*jugada_actual).es_personaje()){

		personajes_levantados.insert((*jugada_actual).obtener_personaje());
	}

	return jugada_actual;

}

void escribir_esquema_arbol(ostream& ss,
					  const bintree<Pregunta>& a, 
		    		  bintree<Pregunta>::node n,
					  string& pre){
	if (n.null()){
	    ss << pre << "-- x" << endl;
	} else {
	    ss << pre << "-- " << (*n) << endl;
	    if ( !n.right().null() || !n.left().null()) {// Si no es una hoja
			pre += "   |";
	    	escribir_esquema_arbol(ss,a, n.right(), pre);
	     	pre.replace(pre.size()-4, 4, "    ");
	      	escribir_esquema_arbol (ss,a, n.left(), pre);
	      	pre.erase(pre.size()-4, 4);    
	    }
  	}
}

void QuienEsQuien::escribir_arbol_completo() const{
	string pre = "";
	escribir_esquema_arbol(cout,this->arbol,this->arbol.root(),pre);
}

float QuienEsQuien::profundidad_promedio_hojas(){
	//TODO :)

	int numero;

	int contador = 0;

	float profundidad;

	bintree<Pregunta>::preorder_iterator pre_it;

	for (pre_it = arbol.begin_preorder(); pre_it != arbol.end_preorder(); ++pre_it){

			contador = contador + (*pre_it).obtener_num_personajes();
		
	}	

	profundidad = (contador*1.0)/(*arbol.root()).obtener_num_personajes()*1.0;

	return profundidad;
}

bintree<Pregunta> QuienEsQuien::crear_arbol_entropia(){ //con este método creamos el árbol con las preguntas más discriminantes.

	bintree<Pregunta> arbol_creado;

	//construimos el vector donde se almacenarán las posiciones de los jugadores restantes de la jugada.

	vector<int> vector_posiciones(personajes.size());

	for (int i = 0; i < personajes.size();i++){

		vector_posiciones[i] = i;
	}

	//construimos el conjunto con el que llevaremos la cuenta de las preguntas que ya hemos realizado, de los atributos que ya hemos comprobado.

	set<int> preguntas_restantes;

	//rellenamos el conjunto con las preguntas restantes.

	for (int i = 0; i < atributos.size(); i++){

		preguntas_restantes.insert(i);
	}

	//calculamos la primera pregunta más discriminatoria.

	int pregunta_mas_discriminatoria;

	pregunta_mas_discriminatoria = entropia(preguntas_restantes, vector_posiciones, personajes.size());

	//añadimos la pregunta más discriminatoria al vector que hemos construido.

	preguntas_restantes.erase(pregunta_mas_discriminatoria);

	//construimos el resto de preguntas, de tal forma que se seleccionen las preguntas más discriminatorias.

	arbol_creado = construir_pregunta_entropia(pregunta_mas_discriminatoria, personajes.size(), vector_posiciones, preguntas_restantes);

	return arbol_creado;
}

bintree<Pregunta> QuienEsQuien::construir_pregunta_entropia(int pregunta_mas_discriminatoria, int numero_personajes, vector<int> vector_posiciones, set<int> preguntas_restantes){

	bintree<Pregunta> arbol_ret;

	if (numero_personajes > 1){

		int si = 0;
		int no = 0;
		int numero_personaje;

		vector<int> vector_posiciones_si;
		vector<int> vector_posiciones_no;

		set<int> preguntas_restantes_si = preguntas_restantes;
		set<int> preguntas_restantes_no = preguntas_restantes;

		int pregunta_mas_discriminatoria_si;
		int pregunta_mas_discriminatoria_no;

		Pregunta pregunta (atributos[pregunta_mas_discriminatoria],numero_personajes);

		bintree<Pregunta> arbol_aux(pregunta);

		//calculamos el número de personajes con los que llamaremos a la función recursiva y qué personajes han dicho que sí y cuáles que no.

		for (int i = 0; i < numero_personajes; i++){
		
			numero_personaje = vector_posiciones[i];
		
			if (tablero[numero_personaje][pregunta_mas_discriminatoria] == 1){ //comprobamos la posición del tablero que queremos.

				vector_posiciones_si.push_back(numero_personaje); // guardamos la posicion del personaje que ha dicho que sí.
				si++; //incrementamos el numero de peronajes que ha dicho que sí.
			}

			else{

				vector_posiciones_no.push_back(numero_personaje); // guardamos la posición del personajes que ha dicho que no.
				no++; //incrementamos el número de personajes que han dicho que no.
			}
		}

		pregunta_mas_discriminatoria_si = entropia(preguntas_restantes_si, vector_posiciones_si, si); //aquí se selecciona la pregunta más discriminatoria de los que han dicho que sí.

		//añadimos la pregunta a las que ya hemos hecho.

		preguntas_restantes_si.erase(pregunta_mas_discriminatoria_si);

		pregunta_mas_discriminatoria_no = entropia(preguntas_restantes_no, vector_posiciones_no, no); //aquí se selecciona la pregunta más discriminatoria de los que han dicho que no.

		//añadimos la pregunta a las que ya hemos hecho.

		preguntas_restantes_no.erase(pregunta_mas_discriminatoria_no);

		//se llama recursivamente a la función de forma que crea y enlaza un árbol de izquiera a derecha y de abajo a arriba.

		bintree<Pregunta> arbol_izda = construir_pregunta_entropia(pregunta_mas_discriminatoria_si,si,vector_posiciones_si, preguntas_restantes_si);

		bintree<Pregunta> arbol_dcha = construir_pregunta_entropia(pregunta_mas_discriminatoria_no,no,vector_posiciones_no, preguntas_restantes_no);
		
		//cout << "se va a insertar en el nodo " << (*arbol_aux.root()) << endl; 

		//Se insertan en su respectivo lugar recursivamente los árboles que hemos ido creando.

		arbol_aux.insert_left(arbol_aux.root(), arbol_izda);
		arbol_aux.insert_right(arbol_aux.root(), arbol_dcha);

		arbol_ret = arbol_aux; //se actualiza arbol final con cada arbol auxiliar que vamos construyendo.

	}

	else if(numero_personajes == 1){ //se pone fin a la recursividad.

		Pregunta pregunta_final(personajes[vector_posiciones[0]],numero_personajes); //construimos la pregunta con el nombre del personaje que queda y un 1, el número de personajes.

		bintree<Pregunta> arbol_aux(pregunta_final); //creamos un árbol auxiliar cuya raíz es el nodo que queremos insertar.		

		arbol_ret = arbol_aux;
	}

	return arbol_ret;
}

//Se usa el algoritmo ID3.

int QuienEsQuien::entropia(set<int> preguntas_restantes, vector<int> vector_posiciones, int numero_personajes){

	int columna;

	double logaritmo;

	int casos_positivos, casos_negativos;

	double maximo = 0.0;

	int pos_maximo = 0;

	bool se_puede_insertar;

	vector<int> vector_atributos_restantes;

	set<int>::iterator it;

	for (it=preguntas_restantes.begin(); it != preguntas_restantes.end(); ++it){

		vector_atributos_restantes.push_back(*it);
	}

	for (int i = 0; i < vector_atributos_restantes.size(); i++){

		columna = vector_atributos_restantes[i];

		casos_positivos = 0;

		casos_negativos = 0;

		for (int j = 0; j < numero_personajes; j++){

			if (tablero[vector_posiciones[j]][columna] == 1){

				casos_positivos++;
			}
			else{
				casos_negativos++;
			}
		}
	
		logaritmo = -(casos_positivos*1.0/numero_personajes*1.0) * log2((casos_positivos*1.0/numero_personajes*1.0)*1.0) - ((casos_negativos*1.0/numero_personajes*1.0)*1.0) * log2((casos_negativos*1.0/numero_personajes*1.0)*1.0);

		if (logaritmo > maximo){
			maximo = logaritmo;
			pos_maximo = columna;
		} 
		
	}

	return pos_maximo;
}

/**
 * @brief Genera numero enteros positivos aleatorios en el rango [min,max).
**/

int generaEntero(int min, int max){
    int tam= max -min;
    return ((rand()%tam)+min);
}

void QuienEsQuien::tablero_aleatorio(int numero_de_personajes){
	srand(0);

	this->limpiar();

	float log_2_numero_de_personajes = log(numero_de_personajes)/log(2);

	int numero_de_atributos = ceil(log_2_numero_de_personajes);

	cout << "Petición para generar "<< numero_de_personajes<<" personajes ";
	cout << "con "<<numero_de_atributos<< " atributos"<<endl;
	cout << "Paso 1: generar "<< pow(2,numero_de_atributos) << " personajes"<<endl;

	//Fase 1: completar el tablero con todos los personajes posibles
	//Completo el tablero y los nombres de personajes a la vez
	for(int indice_personaje=0;indice_personaje< pow(2,numero_de_atributos);indice_personaje++){
		vector<bool> atributos_personaje = convertir_a_vector_bool(indice_personaje,numero_de_atributos);
		string nombre_personaje = "Personaje_"+to_string(indice_personaje);

		this->personajes.push_back(nombre_personaje);
		this->tablero.push_back(atributos_personaje);
	}

	// Completo los nombres de los atributos.
	for(int indice_atributo=0;indice_atributo<numero_de_atributos;indice_atributo++){
		string nombre_atributo = "Atr_"+to_string(indice_atributo);
		this->atributos.push_back(nombre_atributo);
	}

	cout << "Paso 2: eliminar "<< (pow(2,numero_de_atributos)-numero_de_personajes) << " personajes"<<endl;
	//Fase 2. Borrar personajes aleatoriamente hasta que quedan solo los que hemos pedido.
	while(personajes.size()>numero_de_personajes){
		int personaje_a_eliminar = generaEntero(0,personajes.size());

		personajes.erase(personajes.begin()+personaje_a_eliminar);
		tablero.erase(tablero.begin()+personaje_a_eliminar);
	}
}

void QuienEsQuien::preguntas_formuladas (bintree<Pregunta>::node jugada){ //se utiliza en el metodo iniciar_juego()

	cout << "El personaje oculto tiene las siguientes características" << endl;

	while (jugada != arbol.root()){

		cout << (*jugada.parent()).obtener_pregunta() << "\t";
	
		if (jugada == jugada.parent().right())

			cout << "No" << endl;

		else

			cout << "Si" << endl;

		jugada = jugada.parent();

	}

	cout << "Pero aun no se cual es" << endl;

}

void QuienEsQuien::elimina_personaje (string nombre){

	int fila = 0;

	bool encontrado = false;

	while (!encontrado){

		if (personajes[fila] == nombre)
	
			encontrado = true;

		else

			fila++;

	}

	bintree<Pregunta>::node nodo_actual = arbol.root();

	int i = 0;
	bool personaje = false;

	//Iteramos hasta que encontremos al personaje a eliminar

	while (!personaje){
	if (!(nodo_actual.right().null())){	//Comprobamos que el hijo derecha no es nulo

	if ((*nodo_actual.right()).es_personaje()){	//Comprobamos si es un personaje

		if ((*nodo_actual.right()).obtener_personaje() == nombre){	//Y si es el que buscamos, podamos e insertamos donde corresponde
			personaje = true;
			bintree<Pregunta> aux;
			arbol.prune_left(nodo_actual, aux);
			if (tablero[fila][i-1] == 0)	//En caso de ser 0, debería ser insertado a la derecha
				arbol.insert_right(nodo_actual.parent(), aux);
			else
				arbol.insert_left(nodo_actual.parent(), aux); //En caso contrario, debería ser insertado a la izquierda

		}
		else if ((*nodo_actual.left()).es_personaje()){		//Miramos si el hijo de la izquierda es un personaje

			if((*nodo_actual.left()).obtener_personaje() == nombre){	//Si es el que buscamos, insertamos donde proceda
				personaje = true;
				bintree<Pregunta> aux;
				arbol.prune_right(nodo_actual, aux);
				if (tablero[fila][i-1] == 1)
					arbol.insert_left(nodo_actual.parent(), aux);

				else
					arbol.insert_right(nodo_actual.parent(), aux);

			}
			else{	//En caso de que no sea el personaje que buscamos, avanzamos en el árbol a izquierda o derecha según las caracteristicas del personaje

				if (tablero[fila][i] == 0){

				Pregunta pregunta((*nodo_actual).obtener_pregunta(), ((*nodo_actual).obtener_num_personajes()) - 1);
				(*nodo_actual) = pregunta;
				nodo_actual = nodo_actual.right();
				}
				else{

				Pregunta pregunta((*nodo_actual).obtener_pregunta(), ((*nodo_actual).obtener_num_personajes()) - 1);
				(*nodo_actual) = pregunta;
				nodo_actual = nodo_actual.left();
				}

			i++;

			}
		}else{		//Si ninguno de los dos es el personaje, avanzamos en el árbol

			if (tablero[fila][i] == 0){

				Pregunta pregunta((*nodo_actual).obtener_pregunta(), ((*nodo_actual).obtener_num_personajes()) - 1);
				(*nodo_actual) = pregunta;
				nodo_actual = nodo_actual.right();
			}
			else{

				Pregunta pregunta((*nodo_actual).obtener_pregunta(), ((*nodo_actual).obtener_num_personajes()) - 1);
				(*nodo_actual) = pregunta;
				nodo_actual = nodo_actual.left();
			}

				i++;
		}
	}

	else if(!(nodo_actual.left().null())){		//Comprobamos que el hijo izquierda no sea nulo
		if((*nodo_actual.left()).es_personaje()){

			if((*nodo_actual.left()).obtener_personaje() == nombre){
				personaje = true;
				bintree<Pregunta> aux;
				arbol.prune_right(nodo_actual, aux);
				if (tablero[fila][i-1] == 1)
					arbol.insert_left(nodo_actual.parent(), aux);

				else
					arbol.insert_right(nodo_actual.parent(), aux);

			}
			else{		//Si no es el que buscamos, avanzamos en el árbol
				if (tablero[fila][i] == 0){

					Pregunta pregunta((*nodo_actual).obtener_pregunta(), ((*nodo_actual).obtener_num_personajes()) - 1);
					(*nodo_actual) = pregunta;
					nodo_actual = nodo_actual.right();
				}
				else{

					Pregunta pregunta((*nodo_actual).obtener_pregunta(), ((*nodo_actual).obtener_num_personajes()) - 1);
					(*nodo_actual) = pregunta;
					nodo_actual = nodo_actual.left();
				}

				i++;

				}
		
			}
		else{	//Si no es un personaje, avanzamos en el árbol

			if (tablero[fila][i] == 0){

				Pregunta pregunta((*nodo_actual).obtener_pregunta(), ((*nodo_actual).obtener_num_personajes()) - 1);
				(*nodo_actual) = pregunta;
				nodo_actual = nodo_actual.right();
			}
			else{

				Pregunta pregunta((*nodo_actual).obtener_pregunta(), ((*nodo_actual).obtener_num_personajes()) - 1);
				(*nodo_actual) = pregunta;
				nodo_actual = nodo_actual.left();
			}

		i++;
		}
	}





	else{		//Si no es un personaje, avanzamos en el árbol

			if (tablero[fila][i] == 0){

				Pregunta pregunta((*nodo_actual).obtener_pregunta(), ((*nodo_actual).obtener_num_personajes()) - 1);
				(*nodo_actual) = pregunta;
				nodo_actual = nodo_actual.right();
			}
			else{

				Pregunta pregunta((*nodo_actual).obtener_pregunta(), ((*nodo_actual).obtener_num_personajes()) - 1);
				(*nodo_actual) = pregunta;
				nodo_actual = nodo_actual.left();
			}

				i++;
		}
	}

	else if(!(nodo_actual.left().null())){		//Comprobamos que el hijo izquierda no sea nulo
		if((*nodo_actual.left()).es_personaje()){

			if((*nodo_actual.left()).obtener_personaje() == nombre){
				personaje = true;
				bintree<Pregunta> aux;
				arbol.prune_right(nodo_actual, aux);
				if (tablero[fila][i-1] == 1)
					arbol.insert_left(nodo_actual.parent(), aux);

				else
					arbol.insert_right(nodo_actual.parent(), aux);

			}
			else{		//Si no es el que buscamos, avanzamos en el árbol
				if (tablero[fila][i] == 0){

					Pregunta pregunta((*nodo_actual).obtener_pregunta(), ((*nodo_actual).obtener_num_personajes()) - 1);
					(*nodo_actual) = pregunta;
					nodo_actual = nodo_actual.right();
				}
				else{

					Pregunta pregunta((*nodo_actual).obtener_pregunta(), ((*nodo_actual).obtener_num_personajes()) - 1);
					(*nodo_actual) = pregunta;
					nodo_actual = nodo_actual.left();
				}

				i++;

				}
		
			}
		else{	//Si no es un personaje, avanzamos en el árbol

			if (tablero[fila][i] == 0){

				Pregunta pregunta((*nodo_actual).obtener_pregunta(), ((*nodo_actual).obtener_num_personajes()) - 1);
				(*nodo_actual) = pregunta;
				nodo_actual = nodo_actual.right();
			}
			else{

				Pregunta pregunta((*nodo_actual).obtener_pregunta(), ((*nodo_actual).obtener_num_personajes()) - 1);
				(*nodo_actual) = pregunta;
				nodo_actual = nodo_actual.left();
			}

		i++;
		}
	}
	}


}


/*void QuienEsQuien::aniade_personaje (string nombre, vector<bool> caracteristicas){

	Pregunta personaje(nombre,1);



}*/
