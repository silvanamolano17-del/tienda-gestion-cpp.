# tienda-gestion-cpp.
Desarrollé un sistema de gestión de ventas e inventarios en C++ enfocado en el manejo eficiente de datos. El proyecto destaca por la implementación manual de estructuras dinámicas y punteros para la gestión de productos y clientes.

## 🚀 Lo que hace especial a este proyecto
A diferencia de otros proyectos básicos, este sistema implementa **Gestión Manual de Memoria Dinámica**. En lugar de usar librerías automáticas, el código maneja la creación, copia y liberación de memoria (`new[]` y `delete[]`), demostrando un control profundo sobre los recursos del sistema y el uso de punteros.

## 🛠️ Funcionalidades Core
- **Gestión de Inventario:** Carga masiva de productos desde archivos, creación de nuevos artículos y actualización de stock en tiempo real.
- **Flujo de Ventas Completo:** - Validación de stock antes de procesar pagos.
  - Registro automático de clientes nuevos durante la compra.
  - Cálculo de totales y generación de historial de órdenes.
- **Persistencia de Datos Híbrida:** - **Archivos de Texto:** Generación de reportes de inventario legibles.
  - **Archivos Binarios:** Serialización del estado completo de la tienda (`.dat`) para guardar y cargar la sesión de forma rápida.
- **Validación de Datos:** Control estricto de fechas de vencimiento, unicidad de códigos de producto y precios/stock positivos.

## 🧩 Arquitectura de Datos
El sistema utiliza una jerarquía de estructuras (`structs`) anidadas que modelan entidades de negocio reales:
- `Tienda`: Nodo central que agrupa productos, clientes y órdenes.
- `Cliente`: Contiene información personal y su historial de `Orden`.
- `Orden`: Relaciona productos específicos con un cliente y un total de compra.
- `Producto`: Detalles técnicos, categoría y `Fecha` de vencimiento.

## 💻 Conceptos Técnicos Aplicados
- **Punteros y Memoria Dinámica:** Redimensionamiento manual de arreglos para optimizar el uso de RAM.
- **Parsing de Archivos:** Uso de `stringstream` y `getline` para procesar archivos CSV.
- **File I/O Avanzado:** Manejo de flujos de salida en modo `binary` y `app` (append).
- **Lógica de Algoritmos:** Búsqueda secuencial y manipulación de buffers de caracteres (`char[]`).

## 📥 Instalación y Ejecución

1. **Requisitos:** Tener un compilador de C++ (GCC/MinGW).
2. **Compilación:**
   ```bash







   
   g++ -o tienda_pos main.cpp

   Ejecución: 
Asegúrese de tener un archivo llamado productos.txten la misma carpeta antes de iniciar.
Ejecución:
./tienda_pos
