# Proiect: Automatizarea unei camere inteligente

[Link către proiect pe Tinkercad](https://www.tinkercad.com/things/ib4Cs7Rp04m-copy-of-final-final-final)

## Descrierea proiectului

Acest proiect implementează un **sistem inteligent de automatizare a unei camere**, utilizând un modul Arduino Uno și diverși senzori. Scopul proiectului este de a crea un mediu automatizat, care să monitorizeze și să răspundă la diferiți factori de mediu și interacțiuni.

### Functionalități implementate:
1. **Senzor cu ultrasunete**:
   - Controlează deschiderea unei uși automate.
   - Dacă distanța față de senzor scade sub 50 cm, un servomotor deschide ușa la un unghi de 90°.
2. **Senzor PIR (de prezență)**:
   - Detectează mișcarea în cameră.
   - Aprinde un bec atunci când detectează mișcare.
3. **Senzor de temperatură (TMP36)**:
   - Monitorizează temperatura la fiecare 30 de secunde.
   - Dacă temperatura scade sub 25°C, ușa se închide automat (dacă este deschisă).
4. **Display LCD**:
   - Afișează informații despre starea senzorilor și temperatura în timp real.

### Cerințe tehnice:
- Codul este scris **la nivel de registru**, fără utilizarea funcțiilor Arduino sau a bibliotecilor externe.
- Include controlul senzorilor și afișarea datelor pe un ecran LCD.

## Cerințe inițiale

1. **Ultrasunete**: Control deschidere ușă.
2. **PIR**: Aprindere lumină la mișcare.
3. **TMP36**: Monitorizare temperatură.
4. **Servomotor**: Control ușă.
5. **LCD**: Afișare date senzori.

## Instrucțiuni pentru rulare

1. Clonează acest repository pe computerul tău.
2. Deschide fișierul `.ino` în Arduino IDE.
3. Asigură-te că ai conectat componentele conform schemei din proiectul Tinkercad.
4. Încarcă codul pe un Arduino Uno.
5. Monitorizează și testează funcționalitățile utilizând un display LCD și componentele conectate.

## Captură de ecran a proiectului

![Proiect Tinkercad](./proiect_tinkercad.png)

Proiect realizat ca parte a cerințelor academice pentru un sistem inteligent de automatizare. Toate componentele și codul respectă cerințele specificate.
