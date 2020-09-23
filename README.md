<p align="center">
  <a href="" rel="noopener">
 <img width=200px height=200px src="https://i.imgur.com/6wj0hh6.jpg" alt="Project logo"></a>
</p>

<h3 align="center">Qt5-Client-MQTT</h3>

<div align="center">

[![Status](https://img.shields.io/badge/status-active-success.svg)]()
<!-- [![GitHub Issues](https://img.shields.io/github/issues/kylelobo/The-Documentation-Compendium.svg)](https://github.com/kylelobo/The-Documentation-Compendium/issues) -->
[![GitHub Pull Requests](https://img.shields.io/github/issues-pr/kylelobo/The-Documentation-Compendium.svg)](https://github.com/kylelobo/The-Documentation-Compendium/pulls)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](/LICENSE)

</div>

---


## 📝 Table of Contents

- [About](#about)
- [Getting Started](#getting_started)
- [Authors](#authors)
- [Screenshots](#screenshots)

## 🧐 About <a name = "about"></a>

 Ce projet est un  **Data	Logger** dans lequel nous visualisons et enregistrons des données.

 Nous avons utilisé une carte **Raspberry Pi** et un capteur **bme280** pour lire les données	d’environnement (la température, l'humidité et la pression) et des données de la carte (température et fréquence du cpu). 

 Ce dépôt présente uniquement l'application de visualisation développée en **Qt5**, elle utilise le protocole **MQTT** pour la communication entre l’ordinateur et la Raspberry.
 Vous pouvez trouver [ici](https://github.com/2brams/Qt5ClientSocket)  une autre version avec les **Sockets**. 

## 🏁 Getting Started <a name = "getting_started"></a>

Ces instructions vous permettront d'obtenir une copie du projet opérationnel sur votre machine locale à des fins de développement et de test. 


### Prerequisites

Nous devons installer MQTT pour qtCreator.

```
mkdir -p ${HOME}/qt

cd ${HOME}/qt

git clone https://code.qt.io/qt/qtmqtt.git -b 5.13

cd qtmqtt

mkdir build && cd build

QT_INSTALL_DIR=/path/Qt5.1.0/5.1.0

QT_QMAKE_DIR=$QT_INSTALL_DIR/gcc_64/bin/

$QT_QMAKE_DIR/qmake -r ..

make 

sudo make install
```

## 🔧 Running <a name = "tests"></a>

Nous devons ajouter MQTT au fichier MqttTest2.pro

```
QT += network mqtt
```

## ✍️ Authors <a name = "authors"></a>

- [@2brams](https://github.com/2brams)



## Screenshots <a name = "screenshots"></a>

![connexion](https://imgur.com/y0Fz8UQ.png)

![visualisation_data](https://imgur.com/bMLs68I.png)

