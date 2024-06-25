# Forest Frenzy OpenGL Project

## Inhaltsverzeichnis
- [Projektübersicht](#projektübersicht)
- [Features und Methoden](#features-und-methoden)
- [Installation und Steuerung](#installation-und-steuerung)
- [Abhängigkeiten](#abhängigkeiten)
- [Gruppenmitglieder](#gruppenmitglieder)
- [Quellen](#quellen)

## Projektübersicht
Im Rahmen eines Uni-Projekts wurde diese OpenGL-basierte Anwendung entwickelt, die eine dynamische und immersive Graslandschaft simuliert. Die Szene ist mit einer Vielzahl natürlicher Elemente ausgestattet, darunter Bäume, Terrain, diverse Pflanzen, einen Himmel mit Wolken und den Mond, die gemeinsam eine realistische Naturkulisse erzeugen.

### Objekte in der Szene
- **Terrain**: Texturiertes Gelände mit verschiedenen Texturen wie braunem Schlamm, Sand, Gras und Waldschlamm.
- **Skybox**: Skybox-Texturen für verschiedene Richtungen (Vorder-, Rück-, Links-, Rechts-, Oben- und Unten-Texturen).
- **Pflanzen**: Modelle und Texturen von Farnen und Brenneseln.
- **Mond**: Simulation der Beleuchtung bei Abend- und Nachtstimmung mit Mondmodell und Textur.
- **Weitere Objekte**: Modelle und Texturen wie Auto, Picknicktisch und Straßenratte zur Bereicherung der Szene.

## Features und Methoden
- **Skybox**: Die Skybox wird durch eine Cubemap realisiert, die aus einem Panoramafoto eine in sich geschlossene Umgebung erzeugt.
- **Texturierung**: Hochwertige Texturen für die Umgebung, den Mond und alle anderen Objekte.
- **Kamerabewegung**: Die Kamera-Klasse ermöglicht eine flexible Steuerung der Kamera zur Erkundung der Szene. Sie unterstützt Bewegungen in alle Richtungen (vorwärts, rückwärts, links, rechts, aufwärts, abwärts) und ermöglicht die Anpassung der Blickrichtung über Mausbewegungen. Zudem können Benutzer mithilfe des Mausrads zoomen. Die Klasse berechnet die notwendigen Euler-Winkel, Vektoren und Matrizen für das Rendering in OpenGL.

- **Transformationsfunktionen**: Bietet eine umfassende Sammlung von Funktionen zur Durchführung grundlegender 3D-Transformationen. Diese beinhalten:
 - **Translation**: Verschiebung von Objekten im 3D-Raum.
 - **Rotation**: Drehung von Objekten um die X-, Y- und Z-Achsen.
 - **Skalierung**: Anpassung der Größe von Objekten entlang der X-, Y- und Z-Achsen.
 - **View-Matrix**: Erstellung von Look-At-Matrizen, die die Position und Ausrichtung der Kamera definieren.
 - **Projektionsmatrix**: Erstellung von perspektivischen und orthogonalen Projektionsmatrizen, die bestimmen, wie 3D-Szenen auf einem 2D-Bildschirm dargestellt werden.
 - **Vektoroperationen**: Berechnung von Kreuzprodukten, Skalarprodukten und Normalisierung von Vektoren.
 - **Identitätsmatrix**: Setzt eine Matrix auf die Einheitsmatrix zurück.
 - **Entfernung von Translation**: Entfernt die Translation aus einer Matrix, um nur die Rotationskomponenten zu entfernen.

- **Animation**: Der Mond dreht sich in seiner eigenen Achse
- **Beleuchtung**: Verwendung von Shadern um die Beleuchtung der Szene gemäß Blinn-Phong-Beleuchtungsmodell zu Implementierten.
- **Materialeigenschaften**: Um ein Objekt realistisch darzustellen werden emissive, ambiente, diffuse, spekulare und glänzende Eigenschaften verwendet.
- **Light Maps**: Sie werden verwendet, um verschiedene Materialien mit unterschiedlichen Reflexionseigenschaften darzustellen.
- **Laden von komplexen .obj und .mtl Dateien**: Der OBJLoader ermöglicht das Laden von komplexen Datenstrukturen. Es können mehrere Objekte in einer .obj-Datei enthalten sein und jedem Objekt werden seine Materialien und Texturen zugeordnet.
- **Depth Testing**: Depth Testing ermöglicht die korrekte Überlagerung von Objekten basierend auf ihrer Tiefenposition im 3D-Raum.
- **Framebuffer**: Verwendung eines Framebuffers zur Nachbearbeitung um einen Vignettierungseffekt zu erzeugen und auf das gerenderte Bild anzuwenden.
- **Instanziierung**: Instancing ermöglicht die effiziente Darstellung vieler identischer Objekte durch einmalige Berechnung und wiederholte Verwendung der Geometrie und Materialien.
- **Anti Aliasing**: Anti-Aliasing reduziert sichtbare Treppeneffekte (Aliasing) in gerenderten Bildern, indem es glatte Kanten und Linien erzeugt.
- **Terrain**: Es wird eine Geometrie erzeugt, um das Terrain darzustellen.

## Ausführung und Steuerung

### Ausführungssschritte
1. Klone das Repository:
    ```bash
    git clone https://github.com/StefanRifel/Forest-Frenzy-OpenGL-Nature-Experience
    ```
2. Wechsle in das SMath-Verzeichnis:
    ```bash
    cd libs/SMath
    ```
3. Führe SMath Make aus:
    ```bash
    make
    ```
4. Wechsle in das Projektverzeichnis:
    ```bash
    cd ../..
    ```
5. Baue das Projekt mit dem Makefile im Projektverzeichnis:
    ```bash
    make
    ```
6. Wechsle in das Bin-Verzeichnis:
    ```bash
    cd bin
    ```
7. Starte die ausführbare Datei:
    ```bash
    ./Forest_Frenzy 
    ```
### Test Program
1. Um das Testprogramm zu erstellen, navigieren Sie zum Projektverzeichnis:
    ```bash
    make test
    ```
2. Wechsle in das Bin-Verzeichnis:
    ```bash
    cd bin
    ```
3. Starte die ausführbare Datei:
    ```bash
    ./Forest_Frenzy_Test
    ```

### Steuerung
- `W`: Vorwärts bewegen
- `S`: Rückwärts bewegen
- `A`: Nach links bewegen
- `D`: Nach rechts bewegen
- `Mausrad nach oben`: FOV verkleinern
- `Mausrad nach unten`: FOV vergrößern
- `Esc`: Anwendung beenden
- **360 Grad Bewegung mit der Maus**: Umschauen und Kamera drehen

## Abhängigkeiten
- **GLFW**: Fenster- und Eingabeverwaltung.
- **GLEW**: Laden von OpenGL-Funktionen.
- **stb_image**: Laden von Bilddateien für Texturen.
- **gtest**: Google Test für Unit Tests.
- **SMath**: Bibliothek für mathematische Funktionen.

## Gruppenmitglieder
-	Alexander Fitze
-	Katharina Nolte
-	Anna Viktoria Pape
-	Stefan Rifel
-	Parvaneh Sarjoughi

## Quellen
- **Texturen**: https://polyhaven.com/all
- **Modelle**: https://polyhaven.com/all
- **Bibliotheken und Tools**: OpenGL, GLFW, GLEW, stb_image, gtest, SMath.

----