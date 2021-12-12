# projetC
Lors de ce projet, nous avons utulisé une raspberry Pi, ainsi que ça caméra dédié et un capteur à ultrason pour en faire un petit projet.


La fichier ultrasonAmelioration.c permet de faire l'acquisition de la distance à l'aide du capteur SRF04. L'utilisateur entrera le nombre de mesure
qu'il souhaite effectuer. les valeurs acquises seront ensuite stocké dans un fichier texte et par la suite une photo sera prise à la fin de l'acquisition. Dans le fichier texte, les valeurs minimale et maximale seront indiqués clairement.

Nous avons utilisé un code en python pour pouvoir capturer une photo, toutefois nous avons réalisé une commande spéciale, "strcpy(cmd,"sudo python photo.py");"
qui permettra d'éxcécuter le code en python.

Pour pouvoir utiliser les broches du GPIO, nous avons utilisé la librairie wiringPi permettant de travailler avec.

Dans le cadre du capteur à ultrason, le TRIGGER est branché sur le broche WiringPi 8 soir la broche physique 3 et l'ECHO sur le broche WiringPi 9 soit la broche physique 5
https://fr.pinout.xyz/

Toutefois, nous avons pu réaliser des axes d'amélioration, par exemple nous avons pu envoyer les valeurs de distances dans une base de données ou un serveur. Nous avons commencer à coder pour envoyer sur le protocole TCP dans un serveur les informations mais nous avons pas eu le temps.

Concernant le capteur de température, nous avons configuré les fichiers du protocole 1-wire mais la sonde n'était pas détécté.
Nous pensons que nous avons un problème au niveau du cablage et du choix de notre resistance.

Groupe de projet
Paul FISHER
Olivier KAEWTA
