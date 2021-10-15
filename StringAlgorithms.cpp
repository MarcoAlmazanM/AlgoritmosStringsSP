/*
Angel Nolasco Serrano A01365726
Jose Luis Hernandez Hurtado A01365190
Marco Antonio Almazan Martinez A01769046
Este codigo fue creado el dia 8 de Octubre de 2021
El codigo tiene como finalidad la creacion y prueba de 3 algoritmos de strings, los cuales son:
KMP (el cual sirve para buscar un patron en un string).
Manacher (el cual nos ayuda a encontrar el paindromo mas grande contenido en un string).
Longest Common Substring(el cual sirve para encontrar el substring más largo entre dos strings).
La complejidad de este codigo se resume a la suma de las complejidades de cada uno de los anteriores algoritmos,
siendo el de mayor complejidad en el peor caso el del Longest Common Substring, es por esto que la complejidad de este codigo
en el peor de los caso es de O(n*m), siendo n la longitud del primer string y m la longitud del segundo string.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include<string>
#include<vector>

using namespace std;

/*
 La funcion readWholeFile se encarga de hacer las lecturas a los archivos para devolver una cadena de
 caracteres que las demas funciones puedan ocupar.
 Esta funcion recibe 1 parametro de tipo string (El nombre del archivo).
 Complejidad O(n) donde n es la longitud de la cadena de caracteres en el archivo de texto.
*/
string readWholeFile(string fileName) {
    // Se declaran las variables a utilizar.
    stringstream fileContent;
    ifstream file;

    // Se abre el archivo en modo lectura.
    file.open(fileName, ios::in);

    // Si no se puede abrir el archivo muestra un error.
    if (file.fail()) {
        cout << "No se pudo abrir el archivo - '"
            << fileName << "'\n";
    }
    else {
        // Se lee el archivo y se guardan los contenidos a una variable.
        fileContent << file.rdbuf();
    }

    // Se regresa la cadena de caracteres que contiene la lectura del archivo.
    return fileContent.str();
}

/*
 La funcion preKMPAlgorithm se encarga del preprocesamiento del patron para poder generar un arreglo de valores,
 que nos ayudara a poder realizar la busqueda del patron de manera mas sencilla dentro del string principal.
 Esta función recibe 2 parámetros de tipo (string y entero ).
 El string es el patron que es el contenido de los archivos de codigo malicioso.
 El entero es la longitud de dicho patron.
 Complejidad O(m) donde m es la longitud del patron.
*/
vector<int> preKMPAlgorithm(string pattern, int lenPattern) {

    /*
    Se inicializan las variables y el vector que se utilizara para almacenar los valores del preprocesamiento.
    El vector es de longitud igual a la longitud del patron.
    La posicion cero del vector siempre es cero.
    */
    vector<int>kmpArray(lenPattern);
    kmpArray[0] = 0;
    int i = 1;
    int j = 0;

    //El ciclo calcula los valores del desde i=1 hasta lenPattern -1
    while (i < lenPattern) {
        if (pattern[i] == pattern[j]) { //Los caracteres son iguales.
            j++;
            kmpArray[i] = j;
            i++;
        }
        else { // Los caracteres son diferentes.
            if (j != 0) {
                j = kmpArray[j - 1];
            }
            else {
                kmpArray[i] = 0;
                i++;
            }
        }
    }
    return kmpArray;
}

/*
 La funcion kmpSearching se encarga de buscar el patron dentro del string principal con ayuda del vector que obtuvimos en el preprocesamiento.
 Esta función recibe 3 parámetros de tipo (string , string y vector ).
 El primer string es la transmision (string principal) que ingreso el usuario.
 El segundo string es el patron que ingreso el usuario.
 El vector es el que se obtuvo al realizar el preprocesamiento del patron.
 Complejidad O(n) donde n es la longitud de la transmision (string principal).
*/
vector<int> kmpSearching(string st, string pattern, vector<int> kmpArray, bool &foundPattern) {

    // Se inicializan los valores de las variables que se ocuparan para la busqueda del patron dentro del string principal.
    int lenString = st.size();
    int lenPattern = pattern.size();
    int indexSt = 0;
    int indexPattern = 0;
    int position = 0;
    vector<int> positions;

    // Mientras que el indice del string principal sea menor que la longitud del string principal.
    while (indexSt < lenString) {
        // Si el caracter es igual, se deben incrementar ambos indices.
        if (st[indexSt] == pattern[indexPattern]) {
            indexPattern++;
            indexSt++;
            // Si el indice del patron es igual a longitud del patron, entonces el patron fue encontrado.
            if (indexPattern == lenPattern) {
                position = indexSt - indexPattern;
                positions.push_back(position);
                foundPattern = true;
                indexPattern = kmpArray[indexPattern - 1];
            }
        }

        else { // Si los caracteres no son iguales.
            if (indexPattern == 0) {
                indexSt++;
            }
            else {
                indexPattern = kmpArray[indexPattern - 1];
            }
        }
    }
    return positions;
}

/*
 La funcion longestCommonSubstring se encarga de encontrar las posiciones de inicio y fin donde se encuentra 
 el substring más largo en común entre los dos archivos de transmision.
 Esta función recibe 4 parámetros de tipo (string , string , int, int ).
 El primer string se trata del contenido del primer archivo de transmision.
 El primer string se trata del contenido del primer archivo de transmision.
 El primer entero contiene la longitud del primer archivo de transmision.
 El segundo entero contiene la longitud del segundo archivo de transmision.

 La complejidad de este algoritmo es de O(n*m), siendo n la longitud del primer string y m la longitud del segundo string.
*/
pair<int,int> longestCommonSubstring(string transmissionFile1, string transmissionFile2, int lenTransmission1, int lenTransmission2) {
    
    pair<int,int> result;
    
    // Se crea la matriz de valores que permitirá guardar los valores del Longest Substring.
    vector < vector <int> > table(lenTransmission1+1);
    vector <int> cols(lenTransmission2+1);

    // Longitud del substring más largo
    int lenLongestSubstring=0;
    // Indice Final del substring
    int endIndex = 0;
    
    // Ciclo donde se contruye la tabla de valores que tendra el Longest Common Substring.
    for (int i = 0; i <= lenTransmission1; i++){
        for (int j = 0; j <= lenTransmission2; j++){
            if ((i == 0 )|| (j == 0)) {
                table[i] = cols;
                table[i][j] = 0;
            }
            else if (transmissionFile1[i - 1] == transmissionFile2[j - 1]) {
                table[i][j] = table[i - 1][j - 1] + 1;
                /*Si la longitud del substring más grande encontrado hasta ahorita es menor que el valor actual en la tabla
                guardar tanto la longitud como el indice final de substring*/
                if (lenLongestSubstring < table[i][j]) {
                    lenLongestSubstring = table[i][j];
                    endIndex = i;
                }
            }
            else{
                table[i][j] = 0;
            }
        }
    }

    result.first = endIndex -lenLongestSubstring + 1;
    result.second = endIndex;

    return result;
}

/*
La funcion "aumenta" funciona como complemento a la funcion de manacher, se encarga de colocar un caracter adicional
entre cada caracter de la cadena, con esto se alarga el string de tal forma que el tamaño resultante siempre resulta
en un numero impar.
*/
string aumenta(string S){
    string s = "";

    for (char c:S){
        s = s+"|"+c;
    }
    return s+"|";
}

/*
La funcion manacher(string S) se encarga de implementar el algoritmo de manacher, el cual consiste, a grandes rasgos en 
encontrar la subcadena mas larga(que sea un palindromo) de una cadena.

La funcion es de tipo pair y recibe 1 parametro de tipo string, el cual representa la cadena sobre la que se ejecuta el algoritmo.
La complejidad presentada en este algoritmo es de O(n), siendo n la longitud de la cadena.
*/
pair<int,int> manacher(string S){

    // Se declara la variable res representado al resultado(inicio y fin de la subcadena encontrada)
    pair<int,int> res(0,0);

    //S es nulo
    if (S.length() == 0){
        return res;
    }

    // Convierte el tamaño del string actual a un tamaño impar
    string T = aumenta(S);
    int N = T.length();

    // longitud y centro del máximo palíndromo encontrado
    // Hasta ahora posición 1
    int C=1, Li = 0, Ri = 0, maxLong=1, maxCentro=1;
    vector <int> L(N);

    // true si requiera expansión
    bool expansion = false;

    L[0]=0; L[1]=1;

    /*
    En esta parte empieza el recorrido a partir de la longitud de la cadena modificada por la funcion "aumenta".
    Una vez finalizado el ciclo, se obtienen ambas partes del pair, representando la posicion inicial y
    final respectiva del palindromo encontrado
    */
    for (Ri=2; Ri<N; Ri++){
        expansion = false;
        Li = C - (Ri-C);

        if ((C+L[C])-Ri >= 0){
            // Caso 1
            if(L[Li] < (C+L[C])-Ri){
                L[Ri] = L[Li];
            }

            // Caso 2
            else if(L[Li] == (C+L[C])-Ri && (C+L[C]) == N-1){
                L[Ri] = L[Li];
            }

            // Caso 3
            else if(L[Li] == (C+L[C])-Ri && (C+L[C]) < N-1){
                L[Ri] = L[Li];

                // requiere expansión
                expansion = true;
            }

            // Caso 4
            else if(L[Li] > (C+L[C])-Ri){
                L[Ri] = (C+L[C])-Ri;

                // requiere expansión
                expansion = true;
            }
        }
        else{
            L[Ri] = 0;

            // requiere expansión
            expansion = true;
        }

        // hacer la expansión hasta donde se pueda
        if (expansion){
          while (((Ri + L[Ri]) < N) && ((Ri - L[Ri]) > 0) && T[Ri+L[Ri]+1] == T[Ri-L[Ri]-1]){
              L[Ri]++;
          }
        }

        if (Ri + L[Ri] > (C + L[C])){

            // si el nuevo palíndromo se expande más allá de C
            C = Ri;
        }

        if(L[Ri] > maxLong) {
          // Guardar longitud y centro del palíndromo más grande,
          // hasta ahora
            maxLong = L[Ri];
            maxCentro = Ri;
        }
    }
    // obtener inicio y longitud del máximo palíndromo encontrado

    // inicio en S
    res.first = (maxCentro - maxLong)/2;
    // fin de S
    res.second = res.first + maxLong;
    return res;
}

/*
En el main se declaran e inicializan las variables que se van a utilizar 
para el funcionamiento y control del programa.
*/
int main() {
    /*
    Se establecen 2 booleanos cuyo proposito es de variable de control del
    flujo del programa para las condiciones que se encuentran dentro del ciclo.
    */
    bool foundPattern = false;
    bool fileFinish = true;
    /*
    Se establecen elementos de tipo pair para procesar y almacenar las posiciones iniciales y finales
    respecto al punto de los palindromos.
    */
    pair <int, int> palindrome1;
    pair <int, int> palindrome2;

    /*
    Se establecen elementos de tipo pair para procesar y almacenar las posiciones iniciales y finales
    respecto al Longest Common Substring.
    */
    pair <int, int> positionsLCS;

    /*
    Se indican las variables donde se almacena y ordena el contenido de los archivos
    */
    string tFileContent, tFile1Content, tFile2Content, mcodeFileContent;
    vector<string> fileContent(3);
    vector<int>kmpArray;
    vector<int>positions;
    /*
    En esta seccion se carga el contenido de los archivos en las variables declaradas
    anteriormente, del mismo modo, se ordenan para facilitar su uso dentro del ciclo
    del programa.
    */
    tFileContent = readWholeFile("transmission1.txt");
    tFile1Content = tFileContent;
    tFile2Content = readWholeFile("transmission2.txt");

    fileContent[0] = readWholeFile("mcode1.txt");
    fileContent[1] = readWholeFile("mcode2.txt");
    fileContent[2] = readWholeFile("mcode3.txt");

    /*
    Esta seccion es el proceso de ejecucion del programa, en esta primera parte se hace un ciclo
    que itera un numero de veces proporcional al vector fileContent, cada iteracion ejecuta prepKMPAlgorithm
    y kmpSearching para la resolucion de la primera parte de la actividad
    */
    cout<<"Parte 1" << "\n";
    for (int i = 0; i < 3; i++) {
        kmpArray = preKMPAlgorithm(fileContent[i], fileContent[i].size());
        positions = kmpSearching(tFileContent, fileContent[i], kmpArray, foundPattern);
        int vectorLength = positions.size();
        if (foundPattern) {
            cout << "true" << " ";
            for (int i = 0; i < vectorLength; i++) {
                cout << positions[i] << " ";
            }
            cout << "\n";
            foundPattern = false;
        }
        else {
            cout << "false" << "\n";
        }
        if (i == 2 && fileFinish) {
            tFileContent = tFile2Content;
            i = -1;
            fileFinish = false;
        }
    }
    /*
    Este segmento corresponde a la parte 2 de la actividad, donde se utiliza una implementacion
    del algoritmo de manacher para la búsqueda del palíndromo, así como de su posición inicial
    y final.
    */
    palindrome1 = manacher(tFile1Content);
    palindrome2 = manacher(tFile2Content);
    
    cout<<"\n"<<"Parte 2" << "\n";

    cout << palindrome1.first + 1 << ' ' << palindrome1.second<< "\n";

    cout << palindrome2.first + 1 << ' ' << palindrome2.second << "\n";

    /*
    Este segmento corresponde a la parte 3 de la actividad, donde se obtiene la posición inicial
    y final del substring común más largo en la transmisión de archivos, se requiere de los contenidos
    del archivo, así como su respectivo tamaño
    */
    positionsLCS = longestCommonSubstring(tFile1Content, tFile2Content, tFile1Content.size(), tFile2Content.size());

    // Se imprime la posicion donde inicia el Longest Common Substring asi como donde finaliza.
    cout<<"\n"<<"Parte 3" << "\n";
    cout << positionsLCS.first << ' ' << positionsLCS.second << "\n";

    return 0;
}
