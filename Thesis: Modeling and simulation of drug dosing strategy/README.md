# Modelarea și Simularea Strategiei de Dozare a Medicamentelor

## Descriere

Acest proiect se axează pe **modelarea și simularea strategiei de dozare a medicamentelor**, cu un focus special pe antibiotice. Folosind modele PK/PD (Farmacocinetică/Farmacodinamie), lucrarea stabilește doza terapeutică optimă de medicament administrată unui pacient.

### Funcționalități principale:
1. **Modele PK/PD**:
   - Model cu un compartiment.
   - Model cu două compartimente.
   - Model cu trei compartimente.
2. **Personalizare parametri pacient**:
   - Parametri fiziologici: sex, greutate, vârstă.
   - Parametri biologici: creatinină serică, rata de eliminare renală.
3. **Simulare dinamică**:
   - Simularea evoluției concentrației medicamentului și efectului asupra CFU (unități formatoare de colonii) pentru o perioadă de 14 zile.
   - Alegerea dozei optime pentru administrarea unui medicament.
4. **Interfață grafică (GUI)**:
   - Dezvoltată folosind **AppDesigner** din Matlab.
   - Permite introducerea și ajustarea parametrilor modelului și vizualizarea rezultatelor simulării într-un mod accesibil.

---

## Obiectiv

Proiectul își propune să faciliteze **administrarea optimă și sigură a antibioticelor** pentru pacienți, având în vedere parametrii biologici și fiziologici ai acestora. Utilizatorul poate selecta tipul de model PK/PD și vizualiza rezultatele simulării pentru mai mulți pacienți.

---

## Instrumente utilizate

- **SimBiology** din Matlab pentru crearea și rularea modelelor PK/PD.
- **AppDesigner** din Matlab pentru dezvoltarea unei interfețe grafice prietenoase.

---

## Cum funcționează?

1. **Introducerea parametrilor**: 
   - Utilizatorul introduce datele pacientului (fiziologice și biologice) în interfața grafică.
2. **Selectarea modelului PK/PD**:
   - Alege tipul de model farmacocinetic dorit.
3. **Rulare simulări**:
   - Sistemul simulează dinamica dozei pentru o perioadă de 14 zile.
4. **Analiza rezultatelor**:
   - Utilizatorul vizualizează grafice și recomandări privind doza optimă.

---

## Capturi de ecran

### Interfața grafică
![Interfață GUI](./interfata_gui.png)

### Exemplu simulare 1
![Exemplu Simulare 1](./exemplu_simulare_1.png)

### Exemplu simulare 2
![Exemplu Simulare 2](./exemplu_simulare_2.png)

---

## Documentație suplimentară

Pentru o descriere detaliată a proiectului, consultă fișierul PDF/PPTX disponibil în repository:  
[Prezentare Licență - Patrania Bogdan Andrei](./Prezentare_Licenta_PatraniaBogdanAndrei.pdf)

---

## Cum să rulezi proiectul?

1. Clonează repository-ul pe computer.
2. Deschide fișierul principal din Matlab.
3. Rulează aplicația pentru a deschide interfața grafică.
4. Introdu parametrii pacientului și selectează modelul PK/PD.
5. Analizează rezultatele simulării generate.

---

## Licență

Acest proiect este realizat ca parte a unei lucrări de licență și este destinat uzului educațional.

