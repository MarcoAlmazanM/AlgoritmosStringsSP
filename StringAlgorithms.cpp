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
    El vector es de longitud 25 porque es la maxima longitud que puede tener el patron.
    La posicion cero del vector siempre es cero.
    */
    vector<int>kmpArray(25);
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

void LongestCommonSubstring(string a, string b, int lenA, int lenB) {
    // Se crea la tabla para guardar los valores (Como lo veíamos en clase)
    int LongestCommonSuffix[lenA + 1][lenB + 1];

    // Longitud del substring más largo
    int lenLongestSubstring=0;
    // Fila de la tabla
    int tableRow;
    // Columna de la tabla
    int tableCol;

    // Con estos for se construye la tabla (Estoy ocupando programacion dinamica, vayan al algoritmo del profe)
    for (int i = 0; i <= lenA; i++){
        for (int j = 0; j <= lenB; j++){
            if ((i == 0 )|| (j == 0))
                LongestCommonSuffix[i][j] = 0;
            else if (a[i - 1] == b[j - 1]) {
                LongestCommonSuffix[i][j] = LongestCommonSuffix[i - 1][j - 1] + 1;
                // Aqui en este caso no necesitamos el maximo si no la longitud del Longest Common Substring
                if (lenLongestSubstring < LongestCommonSuffix[i][j]) {
                    // Se guardan los valores de la fila y la columna asi como la longitud
                    lenLongestSubstring = LongestCommonSuffix[i][j];
                    tableCol = j;
                    tableRow = i;
                }
            }
            else
                LongestCommonSuffix[i][j] = 0;
        }
    }

    // Aqui se imprimen las posiciones porfa chequen todos los casos que se les ocurran segun yo ya quedo.
    cout << tableRow -lenLongestSubstring <<"\n";
    cout << tableCol -1 << "\n";
    
}

int main() {

    bool foundPattern = false;
    bool fileFinish = true;
    string tFileContent, tFile1Content, tFile2Content, mcodeFileContent;
    vector<string> fileContent(3);
    vector<int>kmpArray;
    vector<int>positions;

    tFileContent = readWholeFile("transmission1.txt");
    tFile1Content = tFileContent;
    tFile2Content = readWholeFile("transmission2.txt");

    fileContent[0] = readWholeFile("mcodeFile1.txt");
    fileContent[1] = readWholeFile("mcodeFile2.txt");
    fileContent[2] = readWholeFile("mcodeFile3.txt");

    for (int i = 0; i < 3; i++) {
        kmpArray = preKMPAlgorithm(fileContent[i], fileContent[i].size());
        positions = kmpSearching(tFileContent, fileContent[i], kmpArray, foundPattern);
        if (foundPattern) {
            cout << "True" << " ";
            for (int i = 0; i < positions.size(); i++) {
                cout << positions[i] << " ";
            }
            cout << "\n";
            foundPattern = false;
        }
        else {
            cout << "False" << "\n";
        }
        if (i == 2 && fileFinish) {
            tFileContent = tFile2Content;
            i = -1;
            fileFinish = false;
        }
    }
    LongestCommonSubstring(tFile1Content, tFile2Content, tFile1Content.size(), tFile2Content.size());
    return 0;
}
