# configFile-Snippet
Config file para ser utilizado en combinacion con deepstream

## Instalación de libconfig

* Descargar libconfig-1.7.x.tar.gz desde https://hyperrealm.github.io/libconfig/
* tar -xzvf libconfig-1.7.x.tar.gz
* cd libconfig-1.7.x
* sudo ./configure
* sudo make
* sudo make check
+ sudo make install

## Compilacion

### C
```
gcc main.c -o output -lconfig
```
### C++
```
g++ main.cpp -o output -lconfig++
```
