#include <iostream>

#include "funtions.h"

using namespace std;

int main(int argc, char const *argv[]) {

  inicializa();
  int option = -1;
  while (option != 9) {
    clear_screen();
    mostrarRegistros();
    option = ejecutaMenu();
    switch (option) {
      case 1:
        agregaRegistro();
        break;
      case 2:
        eliminaRegistro();
        break;
      case 3:
        modificaRegistro();
        break;
      case 4:
      guardaRegistros();

        break;
      case 5:
        mostrarRegistros();
        break;
      case 9:
        cout << "Saliendo...";
        guardaRegistros();
        break;

      default:
        cout << "No existe esa opcion...";
        break;

        break;
    }
  }
  guardaRegistros();
  return 0;
}
