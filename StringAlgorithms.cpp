#include <iostream>
#include <fstream>
#include <sstream>
#include<string>
#include<vector>

using namespace std;

string readWholeFile(string fileName) {
    stringstream fileContent;
    ifstream file;
    file.open(fileName, ios::in);
    if (file.fail()) {
        cout << "No se pudo abrir el archivo - '"
            << fileName << "'\n";
    }
    else {
        fileContent << file.rdbuf();
    }

    return fileContent.str();
}

/*
 La funcion preKMPAlgorithm se encarga del preprocesamiento del patron para poder generar un arreglo de valores,
 que nos ayudara a poder realizar la busqueda del patron de manera mas sencilla dentro del string principal.
 Esta función recibe 2 parámetros de tipo (string y entero ).
 El string es el patron que ingreso el usuario.
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
 El primer string es el genoma (string principal) que ingreso el usuario.
 El segundo string es el patron que ingreso el usuario.
 El vector es el que se obtuvo al realizar el preprocesamiento del patron.
 Complejidad O(n) donde n es la longitud del genoma (string principal).
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

    result.first = endIndex -lenLongestSubstring;
    result.second = endIndex -1;

    return result;
}

void findLongestPalindromicString(string text){
	int N = text.size();
	if(N == 0)
		return;
	N = 2*N + 1; //Position count
	int L[N]; //LPS Length Array
	L[0] = 0;
	L[1] = 1;
	int C = 1; //centerPosition
	int R = 2; //centerRightPosition
	int i = 0; //currentRightPosition
	int iMirror; //currentLeftPosition
	int expand = -1;
	int diff = -1;
	int maxLPSLength = 0;
	int maxLPSCenterPosition = 0;
	int start = -1;
	int end = -1;
	
	//Uncomment it to print LPS Length array
	//printf("%d %d ", L[0], L[1]);
	for (i = 2; i < N; i++){
		//get currentLeftPosition iMirror for currentRightPosition i
		iMirror = 2*C-i;
		//Reset expand - means no expansion required
		expand = 0;
		diff = R - i;
		//If currentRightPosition i is within centerRightPosition R
		if(diff >= 0){
			if(L[iMirror] < diff) // Case 1
				L[i] = L[iMirror];
			else if(L[iMirror] == diff && R == N-1) // Case 2
				L[i] = L[iMirror];
			else if(L[iMirror] == diff && R < N-1) // Case 3
			{
					L[i] = L[iMirror];
					expand = 1; // expansion required
			}
			else if(L[iMirror] > diff) // Case 4
			{
				L[i] = diff;
				expand = 1; // expansion required
			}
		}
		else
		{
			L[i] = 0;
			expand = 1; // expansion required
		}
		
		if (expand == 1)
		{
			//Attempt to expand palindrome centered at currentRightPosition i
			//Here for odd positions, we compare characters and
			//if match then increment LPS Length by ONE
			//If even position, we just increment LPS by ONE without
			//any character comparison
			while (((i + L[i]) < N && (i - L[i]) > 0) &&
				( ((i + L[i] + 1) % 2 == 0) ||
				(text[(i + L[i] + 1)/2] == text[(i-L[i]-1)/2] )))
			{
				L[i]++;
			}
		}

		if(L[i] > maxLPSLength) // Track maxLPSLength
		{
			maxLPSLength = L[i];
			maxLPSCenterPosition = i;
		}

		// If palindrome centered at currentRightPosition i
		// expand beyond centerRightPosition R,
		// adjust centerPosition C based on expanded palindrome.
		if (i + L[i] > R)
		{
			C = i;
			R = i + L[i];
		}
	}
	start = (maxLPSCenterPosition - maxLPSLength)/2;
	end = start + maxLPSLength - 1;
	cout << start << " " << end << "\n";
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

    fileContent[0] = readWholeFile("mcodeFile1.txt");
    fileContent[1] = readWholeFile("mcodeFile2.txt");
    fileContent[2] = readWholeFile("mcodeFile3.txt");

    /*
    Esta seccion es el proceso de ejecucion del programa, en esta primera parte se hace un ciclo
    que itera un numero de veces proporcional al vector fileContent, cada iteracion ejecuta prepKMPAlgorithm
    y kmpSearching para la resolucion de la primera parte de la actividad
    */
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
    findLongestPalindromicString(tFile1Content);
    findLongestPalindromicString(tFile2Content);
    
    // cout << palindrome1.first << ' ' << palindrome1.second<< "\n";

    // cout << palindrome2.first << ' ' << palindrome2.second << "\n";

    /*
    Este segmento corresponde a la parte 3 de la actividad, donde se obtiene la posición inicial
    y final del substring común más largo en la transmisión de archivos, se requiere de los contenidos
    del archivo, así como su respectivo tamaño
    */
    positionsLCS = longestCommonSubstring(tFile1Content, tFile2Content, tFile1Content.size(), tFile2Content.size());

    // Se imprime la posicion donde inicia el Longest Common Substring asi como donde finaliza.
    cout << positionsLCS.first << ' ' << positionsLCS.second << "\n";

    return 0;
}
