#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>    

using namespace std;

struct Fecha {
  int dia;
  int mes;
  int anio;
};
struct Producto {
  char nombre[50];
  char categoria[20];
  Fecha fechaVencimiento;
  int codigo;
  int stock;
  float precio;
};
struct Orden {
  int idOrden;
  char idCliente[15];
  Producto *productos;
  int totalProductos;
  float total;
};

struct Cliente {
  char nombre[50];
  char direccion[100];
  char telefono[15];
  char id[15];
  Orden *ordenes;
  int totalOrdenes;
};

struct Tienda {
  char nombre[50];
  Producto *productos;
  int totalProductos;
  Cliente *clientes;
  int totalClientes;
  Orden *ordenes;
  int totalOrdenes;
};

Producto *leerArchivo(const char *nombreArchivo, int *total) {
  ifstream archivo(nombreArchivo);
  if (!archivo) {
    cout << "No se pudo abrir el archivo" << endl;
    exit(1);
  }

  Producto *productos = nullptr;
  Producto leido;
  string linea;

  while (getline(archivo, linea)) {
    stringstream ss(linea);
    string dia, mes, anio;

    ss.getline(leido.nombre, 50, ',');
    ss.getline(leido.categoria, 20, ',');
    getline(ss, dia, '/');
    getline(ss, mes, '/');
    getline(ss, anio, ',');
    leido.fechaVencimiento.dia = stoi(dia);
    leido.fechaVencimiento.mes = stoi(mes);
    leido.fechaVencimiento.anio = stoi(anio);
    ss >> leido.codigo;
    ss.ignore();
    ss >> leido.stock;
    ss.ignore();
    ss >> leido.precio;

    Producto *aux = productos;
    (*total)++;
    productos = new Producto[*total];

    if (aux) {
      for (int i = 0; i < (*total) - 1; i++) {
        productos[i] = aux[i];
      }
      delete[] aux;
    }

    productos[*total - 1] = leido;
  }

  archivo.close();
  return productos;
}
void guardarProductoEnArchivo(const Producto& producto, const char* nombreArchivo) {
    ofstream archivo(nombreArchivo, ios::app);
    if (!archivo) {
        cout << "No se pudo abrir el archivo para escritura." << endl;
        return;
    }
    archivo << producto.nombre << "," << producto.categoria << ","
            << producto.fechaVencimiento.dia << "/" << producto.fechaVencimiento.mes << "/" << producto.fechaVencimiento.anio << ","
            << producto.codigo << "," << producto.stock << "," << producto.precio << endl;
    archivo.close();
}

void agregarProducto(Orden* orden, const char* nombreArchivo) {
    Producto nuevoProducto;
    cout << "Ingrese nombre del producto: ";
     cin.ignore();
    cin.getline(nuevoProducto.nombre, 50);


    for (int i = 0; i < orden->totalProductos; i++) {
        if (strcmp(orden->productos[i].nombre, nuevoProducto.nombre) == 0) {
            cout << "Error: El producto ya existe." << endl;
            return;
        }
    }

    cout << "Ingrese categoria: ";
    cin.getline(nuevoProducto.categoria, 20);


    cout << "Ingrese fecha de ingreso (DD MM AAAA): ";
    cin >> nuevoProducto.fechaVencimiento.dia >> nuevoProducto.fechaVencimiento.mes >> nuevoProducto.fechaVencimiento.anio;
    if (nuevoProducto.fechaVencimiento.dia < 1 || nuevoProducto.fechaVencimiento.dia > 31 ||
        nuevoProducto.fechaVencimiento.mes < 1 || nuevoProducto.fechaVencimiento.mes > 12 ||
        nuevoProducto.fechaVencimiento.anio < 2000) {
        cout << "Error: Fecha inválida." << endl;
        return;
    }

    cout << "Ingrese codigo del producto: ";
    cin >> nuevoProducto.codigo;
    for (int i = 0; i < orden->totalProductos; i++) {
        if (orden->productos[i].codigo == nuevoProducto.codigo) {
            cout << "Error: El código ya existe." << endl;
            return;
        }
    }

    cout << "Ingrese stock: ";
    cin >> nuevoProducto.stock;
    if (nuevoProducto.stock < 0) {
        cout << "Error: El stock debe ser positivo." << endl;
        return;
    }

    cout << "Ingrese precio: ";
    cin >> nuevoProducto.precio;
    if (nuevoProducto.precio < 0) {
        cout << "Error: El precio debe ser positivo." << endl;
        return;
    }

    Producto* aux = orden->productos;
    orden->totalProductos++;
    orden->productos = new Producto[orden->totalProductos];

    for (int i = 0; i < orden->totalProductos - 1; i++) {
        orden->productos[i] = aux[i];
    }

    orden->productos[orden->totalProductos - 1] = nuevoProducto;
    delete[] aux;

    guardarProductoEnArchivo(nuevoProducto, nombreArchivo);
    cout << "Producto agregado exitosamente!" << endl;
}

 void agregarStock(Tienda* tienda) {
          int codigoProducto, cantidad;

          cout << "Ingrese el código del producto: ";
          cin >> codigoProducto;

          for (int i = 0; i < tienda->totalProductos; i++) {
              if (tienda->productos[i].codigo == codigoProducto) {
                  cout << "Ingrese la cantidad a agregar: ";
                  cin >> cantidad;

                  if (cantidad > 0) {
                      tienda->productos[i].stock += cantidad;
                      cout << "Stock actualizado. Nuevo stock de " << tienda->productos[i].nombre 
                           << ": " << tienda->productos[i].stock << endl;
                  } else {
                      cout << "Error: La cantidad debe ser mayor que cero." << endl;
                  }
                  return;
              }
          }

          cout << "Error: El producto con código " << codigoProducto << " no está registrado." << endl;
      }


void buscarProducto(Tienda &tienda) {
      char nom[50];
      int cont = 0;
      cout << "Ingrese el nombre del producto que desea buscar: ";
      cin >> nom;
      for (int i = 0; i < tienda.totalProductos; i++){
        if (strcmp(tienda.productos[i].nombre, nom) == 0){
          cont++;
        }
      }
      if (cont == 0){
        cout << "Producto no encontrado." << endl;
      return;
      }
      Producto* encontrados= new Producto[cont];
      int j = 0;
      for (int i = 0; i < tienda.totalProductos; i++){
        if (strcmp(tienda.productos[i].nombre, nom) == 0){
          encontrados[j] = tienda.productos[i];
        j++;
        }
      }
      cout << "Productos encontrados: " << endl;
      for (int i = 0; i < cont; i++){
        cout << "Nombre: " << encontrados[i].nombre << endl;
        cout << "Categoría: " << encontrados[i].categoria << endl;
        cout << "Fecha de vencimiento: " << encontrados[i].fechaVencimiento.dia << "/" << encontrados[i].fechaVencimiento.mes << "/" << encontrados[i].fechaVencimiento.anio << endl;
        cout << "Código: " << encontrados[i].codigo << endl;
        cout << "Stock: " << encontrados[i].stock << endl;   
        cout << "Precio por unidad: " << encontrados[i].precio << endl;
        cout << "---------------------" << endl;
      }
      }

void realizarCompra(Tienda &tienda) {
  Orden nuevaOrden;
  cout << "Ingrese ID de la orden: ";
  cin >> nuevaOrden.idOrden;
  cout << "Ingrese ID del cliente: ";
  cin >> nuevaOrden.idCliente;
  Cliente *cliente = nullptr;
  for (int i = 0; i < tienda.totalClientes; i++) {
    if (strcmp(tienda.clientes[i].id, nuevaOrden.idCliente) == 0) {
      cliente = &tienda.clientes[i];
      break;
    }
  }
  if (!cliente) {
    cout << "Cliente no encontrado, se registrará un nuevo cliente." << endl;
    Cliente *tempClientes = new Cliente[tienda.totalClientes + 1];
    for (int i = 0; i < tienda.totalClientes; i++) {
      tempClientes[i] = tienda.clientes[i];
    }
    strcpy(tempClientes[tienda.totalClientes].id, nuevaOrden.idCliente);
    cout << "Ingrese nombre: ";
    cin >> tempClientes[tienda.totalClientes].nombre;
    cout << "Ingrese dirección: ";
    cin >> tempClientes[tienda.totalClientes].direccion;
    cout << "Ingrese teléfono: ";
    cin >> tempClientes[tienda.totalClientes].telefono;
    tempClientes[tienda.totalClientes].totalOrdenes = 0;
    tempClientes[tienda.totalClientes].ordenes = nullptr;
    delete[] tienda.clientes;
    tienda.clientes = tempClientes;
    cliente = &tienda.clientes[tienda.totalClientes];
    tienda.totalClientes++;
  }
  cout << "Ingrese cantidad de productos a comprar: ";
  cin >> nuevaOrden.totalProductos;
  nuevaOrden.productos = new Producto[nuevaOrden.totalProductos];
  nuevaOrden.total = 0;
  for (int i = 0; i < nuevaOrden.totalProductos; i++) {
    int codigo, cantidad;
    cout << "Ingrese código del producto: ";
    cin >> codigo;
    cout << "Ingrese cantidad: ";
    cin >> cantidad;
    bool encontrado = false;
    for (int j = 0; j < tienda.totalProductos; j++) {
      if (tienda.productos[j].codigo == codigo &&
          tienda.productos[j].stock >= cantidad) {
        tienda.productos[j].stock -= cantidad;
        nuevaOrden.productos[i] = tienda.productos[j];
        nuevaOrden.productos[i].stock = cantidad;
        nuevaOrden.total += tienda.productos[j].precio * cantidad;
        encontrado = true;
        break;
      }
    }
    if (!encontrado) {
      cout << "Error: Producto no encontrado o sin stock suficiente." << endl;
      delete[] nuevaOrden.productos;
      return;
    }
  }
  Orden *auxOrdenes = new Orden[cliente->totalOrdenes + 1];
  for (int i = 0; i < cliente->totalOrdenes; i++) {
    auxOrdenes[i] = cliente->ordenes[i];
  }
  auxOrdenes[cliente->totalOrdenes] = nuevaOrden;
  delete[] cliente->ordenes;
  cliente->ordenes = auxOrdenes;
  cliente->totalOrdenes++;

  cout << "Compra realizada con éxito. Total a pagar: $" << nuevaOrden.total
       << endl;
}

void mostrarReporteProductos(Tienda &tienda, const char *nombreArchivo) {
  ofstream archivo(nombreArchivo);
  if (!archivo) {
    cout << "Error al abrir el archivo." << endl;
    return;
  }
  archivo << "-----Productos Disponibles-----\n";
  for (int i = 0; i < tienda.totalProductos; i++) {
    archivo << "Nombre: " << tienda.productos[i].nombre << endl;
    archivo << "Categoría: " << tienda.productos[i].categoria << endl;
    archivo << "Código: " << tienda.productos[i].codigo << endl;
    archivo << "Stock: " << tienda.productos[i].stock << endl;
    archivo << "Precio: $" << tienda.productos[i].precio << endl;
    archivo << "Fecha de Vencimiento: "
            << tienda.productos[i].fechaVencimiento.dia << "/"
            << tienda.productos[i].fechaVencimiento.mes << "/"
            << tienda.productos[i].fechaVencimiento.anio << endl;
    archivo << "--------------------------------\n";
  }
  archivo.close();
  cout << "Reporte generado en '" << nombreArchivo << "' correctamente."
       << endl;
}

void guardarEnBinario(Tienda& tienda, Producto* productos, Cliente* clientes, Orden* ordenes) {
    ofstream archivo("tienda.dat", ios::binary);
    if (!archivo) {
        cerr << "Error al abrir el archivo binario para escritura." << endl;
        exit(1);
    }
    
    archivo.write((char*)&tienda, sizeof(Tienda));
    
    for (int i = 0; i < tienda.totalProductos; i++) {
        archivo.write((char*)&productos[i], sizeof(Producto));
    }
    
    for (int i = 0; i < tienda.totalClientes; i++) {
        archivo.write((char*)&clientes[i], sizeof(Cliente));
    }
    
    for (int i = 0; i < tienda.totalOrdenes; i++) {
        archivo.write((char*)&ordenes[i], sizeof(Orden));
    }
    
    archivo.close();
    cout << "Datos de la tienda guardados en el archivo binario." << endl;
}

void cargarDesdeBinario(Tienda& tienda, Producto*& productos, Cliente*& clientes, Orden*& ordenes) {
    ifstream archivo("tienda.dat", ios::binary);
    if (!archivo) {
        cerr << "Error al abrir el archivo binario para lectura." << endl;
        exit(1);
    }
    
    archivo.read((char*)&tienda, sizeof(Tienda));
    
    productos = new Producto[tienda.totalProductos];
    archivo.read((char*)productos, sizeof(Producto) * tienda.totalProductos);
    
    clientes = new Cliente[tienda.totalClientes];
    archivo.read((char*)clientes, sizeof(Cliente) * tienda.totalClientes);
    
    ordenes = new Orden[tienda.totalOrdenes];
    archivo.read((char*)ordenes, sizeof(Orden) * tienda.totalOrdenes);
    
    archivo.close();
    cout << "Datos de la tienda cargados desde el archivo binario." << endl;
}


void cargarDatosTienda(Tienda &tienda, const char *nombreArchivo) {
  ifstream archivo(nombreArchivo, ios::binary);
  if (!archivo) {
    cout << "Error: No se pudo abrir el archivo." << endl;
    return;
  }
  archivo.read((char *)&tienda.totalProductos, sizeof(int));
  tienda.productos = new Producto[tienda.totalProductos];
  for (int i = 0; i < tienda.totalProductos; i++) {
    archivo.read((char *)&tienda.productos[i], sizeof(Producto));
  }
  archivo.read((char *)&tienda.totalClientes, sizeof(int));
  tienda.clientes = new Cliente[tienda.totalClientes];
  for (int i = 0; i < tienda.totalClientes; i++) {
    archivo.read((char *)&tienda.clientes[i], sizeof(Cliente));
    archivo.read((char *)&tienda.clientes[i].totalOrdenes, sizeof(int));
    tienda.clientes[i].ordenes = new Orden[tienda.clientes[i].totalOrdenes];
    for (int j = 0; j < tienda.clientes[i].totalOrdenes; j++) {
      archivo.read((char *)&tienda.clientes[i].ordenes[j], sizeof(Orden));
    }
  }
  archivo.read((char *)&tienda.totalOrdenes, sizeof(int));
  tienda.ordenes = new Orden[tienda.totalOrdenes];
  for (int i = 0; i < tienda.totalOrdenes; i++) {
    archivo.read((char *)&tienda.ordenes[i], sizeof(Orden));
  }
  archivo.close();
  cout << "Datos de la tienda cargados correctamente desde '" << nombreArchivo
       << "'." << endl;
}


      void mostrarMenu() {
          cout << "\n----- Menú -----" << endl;
          cout << "1. Cargar productos desde archivo" << endl;
          cout << "2. Crear producto" << endl;
          cout << "3. Agregar stock" << endl;
          cout << "4. Buscar producto" << endl;
          cout << "5. Realizar compra" << endl;
          cout << "6. Mostrar reporte de productos" << endl;
          cout << "7. Guardar datos de la tienda" << endl;
          cout << "8. Cargar datos de la tienda" << endl;
          cout << "9. Salir" << endl;
          cout << "-----------------" << endl;
      }

      int main() {
       Orden orden;
    orden.totalProductos = 0;
    orden.productos = nullptr;

    Tienda tienda;
    tienda.totalProductos = 0;
    tienda.productos = nullptr;

    int totalProductos = 0;
    tienda.productos = leerArchivo("productos.txt", &totalProductos);
    tienda.totalProductos = totalProductos;

    orden.productos = tienda.productos;
    orden.totalProductos = tienda.totalProductos;
        Producto* productos = nullptr;
    Cliente* clientes = nullptr;
    Orden* ordenes = nullptr;
    
 string nombreArchivoTXT = "tienda.txt";
    string nombreArchivoBin = "tienda.dat";
          int opcion;
          do {
              mostrarMenu();
              cout << "Ingrese una opción: ";
              cin >> opcion;

              switch (opcion) {
                  case 1: {
                      int totalProductos = 0;
                      tienda.productos = leerArchivo("productos.txt", &totalProductos);
                      tienda.totalProductos = totalProductos;

                      if (tienda.totalProductos > 0) {
                          cout << "\nProductos cargados desde archivo:\n";
                          for (int i = 0; i < tienda.totalProductos; i++) {
                              cout << "Producto: " << tienda.productos[i].nombre
                                   << " | Categoria: " << tienda.productos[i].categoria
                                   << " | Fecha: " << tienda.productos[i].fechaVencimiento.dia << "/"
                                   << tienda.productos[i].fechaVencimiento.mes << "/" << tienda.productos[i].fechaVencimiento.anio
                                   << " | Codigo: " << tienda.productos[i].codigo
                                   << " | Stock: " << tienda.productos[i].stock
                                   << " | Precio: " << tienda.productos[i].precio << endl;
                          }
                      } else {
                          cout << "No se encontraron productos en el archivo.\n";
                      }
                      break;
                  }

                  case 2:
                     agregarProducto(&orden, "productos.txt");
                      break;

                  case 3:
                      if (tienda.totalProductos > 0) {
                          agregarStock(&tienda);
                      } else {
                          cout << "Error: No hay productos cargados en la tienda.\n";
                      }
                      break;

                  case 4:
                      if (tienda.totalProductos > 0) {
                          buscarProducto(tienda);
                      } else {
                          cout << "Error: No hay productos en la tienda.\n";
                      }
                      break;

                  case 5:
                      if (tienda.totalProductos > 0) {
                          realizarCompra(tienda);
                      } else {
                          cout << "Error: No hay productos disponibles para comprar.\n";
                      }
                      break;

                  case 6:
                      if (tienda.totalProductos > 0) {
                          mostrarReporteProductos(tienda, "reporte.txt");
                      } else {
                          cout << "Error: No hay productos para generar un reporte.\n";
                      }
                      break;

                  case 7:
                     
    cout << "Tienda cargada y guardada en binario: " << tienda.nombre << endl;
                      break;

                  case 8:
                      cargarDatosTienda(tienda, "datos_tienda.bin");
                      cout << "Datos de la tienda cargados correctamente.\n";
                      break;

                  case 9:
                      cout << "Saliendo del programa...\n";
                      break;

                  default:
                      cout << "Opción inválida. Intente nuevamente.\n";
              }
          } while (opcion != 9);

          if (tienda.productos) {
              delete[] tienda.productos;
          }

          return 0;
    }
