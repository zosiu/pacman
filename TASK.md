# Első grafika házifeldat

Az első grafika házifeladat egy Packman klón megvalósítása.
A feladat részét képzi a pálya megtervezése, a szörnyecskék mozgásának implementálása és a "Packman" irányítása.

# Feladatok:
* A pálya megtervezése. Plusz pontért a pályát lehet véletlenszerűen generálni. (25 pont egy pálya, 35 pont véletlenszerűen generált pálya.)
* A szörnyek és a játékos sem tud a falakon áthaladni!
* A szörnyek mozgásának implementálása. Egyszerű random lépkedés (15 pont), valami kis logika (AI - 30 pont, pl a játékos irányába lépjenek a szörnyek).
* Játékos mozgatása (10 pont), a játékos karakterének van egy szája, ami mindig a mozgás irányába fordul.
* A pályán kis bogyók vannak elhelyezve, amit a játékosnak be kell gyűjtenie. Ha mindent begyűjti akkor a játékos győz. A begyűjtött kis bogyóknak el kell tűnnie. (15 pont)
* A szörnyecskék feladata, hogy elkapják a játékost. Ha sikerül a játék véget ér. Implementálni kell egy algoritmust ami kiszámolja, hogy mikor ütközött egy szörny a játékossal. (15 pont)
* A grafikai dizájn 20 pont.
* Az alap feladatra 100 pont kapható, és 25 plusz pont szerezhető.

# Kritériumok:
* A feladatot a modern OpenGL (>3.3 core) vertex-fragment shader pipeline működésével kell megoldani.
* A kód lényegi részeit dokumentációs kommentekkel kell ellátni.
