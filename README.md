# ConexionMySql : ABP Grupo 2 : M3/M5
Nuestra implementación para los módulos M3 y M5 en el Proyecto.

## Contenido
- [Esquema](#esquema)
- [Funcionamiento](#funcionamiento)
- [Dependencias](#dependencias)

## Esquema
<p align="center">
  <img src="https://github.com/tomepro/ConexionMySql/blob/26ab490e8a2a786aca220c6f921118d3e78de403/img/esquema.png">
</p>

## Funcionamiento
Esta implementación está creada para el uso interno administrativo. Como muestra el esquema, el formulario Java envia datos al programa C++ y este mismo hace una query a la BDD y crea un certificado de inscripcion similar al siguiente:
<p align="center">
  <img src="https://github.com/tomepro/ConexionMySql/blob/6b39bdb8a3a8ecfb8fd9b5d512ba5002ddc9c2d3/img/Certificado.jpg" width=550>
</p>

## Dependencias
  - [MySQL C++ Connector](https://dev.mysql.com/downloads/connector/cpp/)
