# LOUGHLIMI_LAB3

## LAB-3 _Accelerometer:
## Introduction:
Dans ce compte rendu, nous allons décrire les étapes nécessaires pour afficher les données de gyroscopie de notre carte DE10-Lite .


Nous allons commencer par décrire l'architecture système, puis nous allons décrire les étapes nécessaires pour mettre en place un système de base Nios. Ensuite, nous expliquerons comment interface l'accéléromètre à l'aide de l'interface I2C ou SPI en utilisant les IP Opencore disponibles dans QSYS. Nous allons également réécrire les fonctions I2C_READ et I2C_Write selon nos spécifications pour effectuer la lecture et l'écriture des données. Nous allons ensuite afficher les données d'accélération à travers JTAG_UART. Ensuite, nous allons calibrer le capteur en utilisant la gravité et I2C_Write. Enfin, nous ajouterons le (timer + PIO + BinTo7Seg) setup de ESN 11 dans notre design et implémenterons un bouton pour permuter entre les différents axes.


![Capture5](https://user-images.githubusercontent.com/17486030/213681900-163b2c11-9d80-4a3f-b688-849b2b6f97ea.PNG)




##  Partie matérielle :

Dans ce laboratoire, nous utilisons un système de blocs (qsys) qui comprend non seulement la base, mais aussi deux composants PIO (Peripheral Input/Output) et un composant timer. Le premier PIO permet de transmettre la valeur du compteur de la partie logicielle vers la partie matérielle, tandis que le second PIO permet à la partie logicielle de récupérer les états des 8 premiers switchs. Le timer, quant à lui, permet de déclencher une interruption régulièrement.

En ce qui concerne les blocs matériels que j'ai codés personnellement, ils sont au nombre de trois. Le premier, appelé DoubleDabble, reçoit la valeur du compteur du logiciel et retourne cette même valeur décomposée en centaine, dizaine et unités. Le deuxième, appelé bin_to_7seg, prend en entrée l’une des trois sorties du bloc précédent et se charge de l’afficher correctement sur un afficheur 7 segments. Le dernier, appelé Top-Level Entities, permet de câbler le bloc qsys avec les blocs précédents et les pins de la clock, du bouton poussoir pour le reset, des 3 afficheurs 7 segments et des 8 switchs.



![Capture6](https://user-images.githubusercontent.com/17486030/213681790-7436e4bf-d64d-4234-8bea-6d26d6462864.PNG)

## Partie Logicielle

Le logiciel fonctionne de la manière suivante :
   
    
    
    
    
- [x] Calibrer l'accéléromètre de notre carte (en utilisant la gravité)
- [x] Interroger les données d'accélération toutes les secondes
- [x] Lire les accélérations le long des axes X, Y et Z
- [x] Afficher ces valeurs sur l'afficheur 7 segments (l'accélération peut être négative)
- [x] Permuter entre les valeurs en utilisant un bouton poussoir




![Capture8](https://user-images.githubusercontent.com/17486030/213682016-afd5ca38-3947-4745-b170-ea3dead9769c.PNG)
