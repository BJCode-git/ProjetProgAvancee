Le projet nécesessite une version une version de la SDL2 supérieure à 2.0.5 ainsi que 
la bibliothèque SDL2_ttf pour l'afficahe des textes.
Il nécessite également 
CMake 3.2 and newer
C++14 capable compiler
Doxygen for docs (Graphviz for more graphs in docs, PlantUML for more UML diagrams, PlantUML needs java)


Pour compiler le projet :
```
cmake .
make BrickBreaker
./bin/BrickBreaker
```



Le dossier intègre quelques test qui permettent d'éprouver les différentes fonctionnalités du projet. Pour les lancer, il suffit de lancer la commande `make test` dans le dossier build