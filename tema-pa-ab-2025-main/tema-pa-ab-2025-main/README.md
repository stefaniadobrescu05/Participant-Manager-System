## Autor
- Nume: Dobrescu Stefania-Maria
- Grupa: 313 AB (subgrupa a)
- Universitatea Politehnica Bucuresti, ACS
- Materie: Proiectarea Algoritmilor

---

# Vanatoarea Regala - Tema Proiectarea Algoritmilor

## Status
Tema este complet implementata, modularizata si testata conform cerintelor.

---

## Descriere generala
Aceasta proiect simuleaza organizarea unui eveniment numit **Vanatoarea Regala**, conform cerintei din cadrul temei. Scopul este gestionarea completa a participantilor (lorzi, cavaleri si aventurieri), validarea datelor, organizarea in structuri de date eficiente, atribuirea traseelor de vanatoare si premierea celor mai performanti.

---

## Note Tehnice
- **Limbaj utilizat**: C
- **Structuri de date**: Cozi (liste inlantuite), arbori binari de cautare (BST), graf orientat (liste de adiacenta), coada cu prioritati (heap maxim)
- **Tehnici algoritmice**: DFS, sortare lexicografica, traversare inorder, heapify

---

## Implementare si sursa originala
Proiectul a fost initial descarcat si configurat pornind de la repository-ul disponibil public:
https://gitlab.com/bogdangheorghe98/tema-pa-ab-2025 

## Structura proiectului
Proiectul este organizat modular, fiecare pas fiind implementat in fisiere dedicate:

| Fisier        | Descriere |
|---------------|----------|
| `main.c`      | Coordoneaza executia temei pas cu pas. |
| `bPas1.c/h`   | Procesarea numelui, conversia statutului si citirea candidatilor in coada. |
| `bPas2_3.c/h` | Implementarea si gestionarea arborilor binari de cautare (BST) pentru participanti. |
| `bPas4.c/h`   | Extrage participantii cu cea mai mare experienta si incarca traseele. |
| `bPas5.c/h`   | Actualizeaz experiena participanilor in functie de traseu. |
| `bPas6.c/h`   | Extrage primii 3 participanti cu cea mai mare experienta. |
| `bPas7.c/h`   | Genereaza trasee valide folosind un graf orientat (DAG). |
| `heap.c/h`    | Implementarea cozii cu prioritati (max-heap). |
| `queue.c/h`   | Implementarea cozii pentru inscrierea participantilor. |
| `list.c/h`    | Noduri pentru lista de participanti (folosita in coada). |

Bibliotecile heap, queue si list contin functii specializate pentru prelucrarea structurilor de date aferente. Aceste biblioteci sunt incluse si utilizate in bibliotecile aferente fiecarui pas, acolo unde este necesar. Functiile sunt adaptate pentru cerintele fiecarei etape, asigurand modularitate si reutilizare eficienta a codului.

O excepti este biblioteca bPas2_3, care nu poarta explicit denumirea "BST", dar contine exclusiv functii pentru prelucarea arborilor binari de cautare. Acest lucru se datoreaza faptului ca, in pasii 2 si 3, cerintele au presupus operatii specifice pe arbori binari de cautare, fara a necesita functii suplimentare.

---

## Descrierea pasilor
### Pasul 1 - inregistrare candidati
- Citirea datelor din `candidati.csv`.
- Normalizarea numelor (cratime, capitalizare).
- Conversia statutului social in `enum`.
- Salvarea participantilor intr-o **coada implementata cu liste**.
- Scrierea in `test_1.csv`.

#### Challengeuri si solutii
Am invatat sa lucrez cu tipuri de date de tip enum si am descoperit functiile atoi() si atof(). Acest pas a fost esential pentru a-mi reaminti cum se realizeaza prelucrarea datelor din fisiere in C.


### Pasul 2 - Organizare in arbori BST
- Lorzii sunt introdusi intr-un `BST_Lorzi`, ceilalti intr-un `BST_Aventurieri_Cavaleri`.
- Salvare in `test_2_lorzi.csv` si `test_2_cavaleri_aventurieri.csv`, in ordine descrescatoare a experientei.

### Pasul 3 - Validare si eliminare
- Se citesc contestatiile din `contestatii.csv`.
- Lorzii cu informatii false sunt eliminati din `BST_Lorzi`.
- Rezultatul este salvat in `test_3_lorzi.csv`.

### Pasul 4 - Atribuirea traseelor si crearea heapului
- Se selecteaza alternativ 4 lorzi si 4 cavaleri/aventurieri cu experienta maxima.
- Se incarca traseele din `trasee.csv` si se asociaza.
- Se introduce fiecare participant in **max-heap**.
- Rezultatul se salveaza in `test_4.csv`.

### Pasul 5 - Actualizarea experienei
- Fiecarui participant i se actualizeaza experienta:
- Se mentine max-heap-ul valid la fiecare modificare.
- Scrierea in `test_5.csv`.

### Pasul 6 - Premierea
- Se extrag din heap primii 3 participanti cu experienta cea mai mare.
- Se salveaza in `test_6.csv`.

#### Challengeuri si solutii (5-6)
Atat heapify_up cat si heapify_down (din biblioteac heap.c) sunt implementate iterativ (cu while), nu recursiv.
Avantajele sunt ca evita apelurile recursive care pot consuma mai multa memorie (stack overhead) si este mai sigur pentru procesarea de date (fara risc de stack overflow).


### Challengeuri si solutii
Au aparut problemele de scurgeri de memorie din cauza neeliberarii complete a tuturor campurilor asociate structurii Participant, la momentul potrivit, in special in cazul eliberarii copiilor profunde; (probleme intre pasii 2 si 6). De asemenea, la eliberarea structurii max-heap, am identificat cazuri in care anumite campuri sau vectori de trasee erau eliberati de mai multe ori pentru aceeasi variabila, ceea ce ducea la comportament incorect.


### Pasul 7 - Generarea traseelor din graf
- Se citeste un graf orientat din `drumuri.csv`.
- Se construieste cu liste de adiacenta.
- Se genereazs toate traseele de la noduri cu grad de intrare 0 la cele cu grad de iesire 0, prin metoda DFS (la fiecare pas mergem cat mai departe de nodul de unde am inceput).
- Traseele sunt sortate lexicografic si salvate in `test_7.csv`.

#### Challengeuri si solutii
Am invatat ce inseamna o ordonare lexicografica si am analizat putin mai mult pana am identificat o metoda de implementare. Astfel, am ajuns la ideea de a crea o structura dedicata, Path, pentru a gestiona traseele. Initial nu am realizat ca trebuie sa folosesc algoritmul DFS, deoarece nu am facut imediat legatura cu conceptele discutate la curs-mai exact, faptul ca pot alege nodul de pornire si decide, in functie de nodul de destinatie, ce drumuri pastrez in cadrul traseelor generate.

---
