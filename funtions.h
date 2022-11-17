#include <fstream>
#include <iostream>
#include <string>

#define MAX_CHAR_ARRAY 500
#define MAX_ALUMNOS 500
#define DELIMITADOR_CAMPO '|'
#define DELIMITADOR_REGISTRO '\n'
#define NOMBRE_ARCHIVO "alumnos.dat"
using namespace std;

struct Alumno {
  char nombre[MAX_CHAR_ARRAY+1];
  char carrera[MAX_CHAR_ARRAY+1];
  int edad;
  float promedio;
};

Alumno* alumnos[MAX_ALUMNOS];
int numeroRegistros = 0;

int ejecutaMenu();
void inicializa();
Alumno* capturaRegistro();
void modificaRegistro();
void mostrarRegistro(Alumno* );
void mostrarRegistros();
void eliminaRegistro();
void agregaRegistro();
void clear_screen();
Alumno* leeRegistro(ifstream&);
void guardaRegistros();

void guardaRegistros(){
  ofstream archivo(NOMBRE_ARCHIVO, ios:: trunc | ios:: binary);
  int size;
  for (int i = 0; i < numeroRegistros; i++){

   size = sizeof(alumnos[i]->nombre);
   archivo.write((char*)&size,sizeof(int));
   archivo.write((char*)alumnos[i]->nombre,size);

   size = sizeof(alumnos[i]->carrera);
   archivo.write((char*)&size,sizeof(int));
   archivo.write((char*)alumnos[i]->carrera,size);

   archivo.write((char*)&alumnos[i]->edad,sizeof(int));
   archivo.write((char*)&alumnos[i]->promedio,sizeof(float));
  }
  archivo.close();
}

Alumno* leeRegistro(ifstream&ar){
  if(ar.eof() or ar.bad())
    return NULL;

  int size = -1;
  ar.read((char*)&size, sizeof(int));
  if (size == -1 || ar.eof())
    return NULL;
  Alumno* alum = new Alumno;
  ar.read((char*)alum->nombre,size);

//tal vez tenga que poner el caracter nulo de cadena, nose
  ar.read((char*)&size,sizeof(int));
  ar.read((char*)alum->carrera,size);
  
  ar.read((char*)&alum->edad,sizeof(int));
  ar.read((char*)&alum->promedio,sizeof(float));

  return alum;
}

void clear_screen() {
#ifdef _WIN32
  std::system("cls");
#else
  // Assume POSIX
  std::system("clear");
#endif
}

int ejecutaMenu() {
  cout << "MENU\n\n";
  cout << "1-Agrega\n";
  cout << "2-Elimina\n";
  cout << "3-Modifica\n";
  cout << "4-Guarda archivo de texto\n";
  cout << "5-Mostrar Registros\n";
  cout << "9-Salir (salir guardando)\n";
  cout << "\nIntrodusca su opción: ";
  int n;
  cin >> n;
  cin.get();
  return n;
}

void inicializa() {
  for (int i = 0; i < MAX_ALUMNOS; i++) {
    alumnos[i] = nullptr;
  }
  ifstream archivo(NOMBRE_ARCHIVO, ios::binary);
  if(archivo.is_open()){
      Alumno* alum = leeRegistro(archivo);
      while (alum){
        alumnos[numeroRegistros++] = alum;
        alum = leeRegistro(archivo);
      }
      
  }else{
    fstream arch(NOMBRE_ARCHIVO, ios::binary | ios::trunc);
    arch.close();
  }
  archivo.close();
  
}

Alumno* capturaRegistro() {
  Alumno* alumno = new Alumno;
  cout << "Nombre: ";
  cin.getline(alumno->nombre,MAX_CHAR_ARRAY);
  cout << "Carrera: ";
  cin.getline(alumno->carrera,MAX_CHAR_ARRAY);
  cout << "Edad: ";
  cin >> alumno->edad;
  cin.get();
  cout << "Estatura: ";
  cin >> alumno->promedio;
  cin.get();
  return alumno;
}

void modificaRegistro() {
  cout << "Ingresa el numero del registro a modificar: ";
  int n;
  cin >> n;
  cin.get();
  delete alumnos[n - 1];
  alumnos[n - 1] = capturaRegistro();
}

void mostrarRegistro(Alumno* a) {
  cout << "Nombre: " << a->nombre << endl;
  cout << "Carrera: " << a->carrera << endl;
  cout << "Edad: " << a->edad << endl;
  cout << "Promedio: " << a->promedio << endl;
}
void mostrarRegistros() {
  for (int i = 0; i < numeroRegistros; i++) {
    cout << "REGISTRO #" << i + 1 << endl;
    mostrarRegistro(alumnos[i]);
    cout<<"\n\n";
  }
}
void eliminaRegistro() {
  cout << "ELIMINANDO REGISTRO\n\n";
  cout << "Ingresa el numero del registro a eliminar: ";
  int n;
  cin >> n;
  cin.get();
  delete alumnos[n - 1];
  alumnos[n - 1] = alumnos[numeroRegistros - 1];
  alumnos[numeroRegistros - 1] = nullptr;
  numeroRegistros--;
}

void agregaRegistro() {
  cout << "AGREGANDO REGISTRO\n\n";
  alumnos[numeroRegistros++] = capturaRegistro();
}