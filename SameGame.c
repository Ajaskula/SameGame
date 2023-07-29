#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// definiuję parametry parametryzujące planszę
#ifndef WIERSZE
#define WIERSZE 10
#endif

#ifndef KOLUMNY
#define KOLUMNY 15
#endif

#ifndef RODZAJE
#define RODZAJE 4
#endif

// funkcja sprawdzi, czy w podanym przez gracza miejscu
// znajduje się pojedynczy element, określonego typu
// czy cały możliwy do usunięcia blok
bool not_single_element(char **plansza, int numer_wiersza, int numer_kolumny);

// funkcja umieszcza otrzymane dane
// w dwu wymiarowej tablicy typu char
void wczytaj_plansze(char **plansza);

// funkcja wypisuje finalny stan planszy
// po uporządkowaniu jej zgodnie z zaleceniami
void wypisz_plansze(char **plansza);

// funkcja usuwa cały blok danego typu, do któ©ego należy
// element o wskazanych przez koordytnaty: numer_wiersza, numer_kolumny
// współrzędnych
void usun_blok(char **plansza, int numer_wiersza, int numer_kolumny,
               char rodzaj_klocka, int *skrajne_lewe_usuniecie,
               int *skrajne_prawe_usuniecie);

// funkcja opuszcza kolumny od pierwszej wskazanej, do ostatniej wskazanej
// kolumny jeśli znajdują się w nich nie puste elementy
// poniżej, których znajdują się puste elementy
void opusc_kolumny_od_do(char **plansza, int numer_pierwszej_kolumny,
                         int numer_ostatniej_kolumny);

// funkcja porządkuje planszę w ten sposób, że przesuwa wszystkie
// kolumny dla których jest to możliwe maksymalnie do lewej strony
void przesun_wszystko_do_lewej(char **plansza,
                               int pierwsza_kolumna_do_przesuniecia);

// funkcja przesuwa kolumnę jak najdalej do lewej strony
// czyli na najbardziej na lewo od niej pustą kolumnę
void przesun_kolumne_najdalej_w_lewo(char **plansza, int numer_kolumny);

// funkcja opuszcza wszyskie elementy w obrębie danej kolumny
// na najniższe możliwe pozycje, czyli na najniższy
// pusty element znajdujący się pod nim
void opusc_kolumne(char **plansza, int numer_kolumny);

// funkcja przesuwa jedną kolumnę o jedeno miejsce w lewo
// pod warunkiem, że na lewo od tej kolumny znajudje
// się kolumna pusta
void przesun_w_lewo(char **plansza, int numer_kolumny);

// funkcja sprawdza, czy wszystkie elementy w tej
// kolumnie są elementami pustymi
bool kolumna_pusta(char **plansza, int numer_kolumny);

// funkcja opuszcza element wewnątrz kolumny, tak nisko jak to możliwe
void opusc_element(char **plansza, int numer_kolumny, int numer_wiersza);

// Otrzymuje planszę oraz współrzędne elementu do usunięcia.
// Przekazana plansza jest modyfikowana w następujący sposób:
// 1. Jeśli element należy do bloku który można usunąć (tj. ma conajmniej 2 elementy)
// usuwa cały ten blok, w.p.p. nie robi nic.
// 2. Po usunięciu bloku wszystkie elementy w kolumnach są spychane maksymalnie w dół.
// 3. Jeśli jakaś kolumna staje się pusta, to kolumny z jej prawej strony przesuwane
// są w lewo by zapełnić puste miejsce.
void dzialanie_programu(char **plansza, int numer_wiersza, int numer_kolumny);

int main(int argc, char *argv[]) {

  (void)argc;
  // współrzędne kolcka
  int numer_wiersza = atoi(argv[1]);
  int numer_kolumny = atoi(argv[2]);

  // deklarujemy tablicę na naszą planszę gry
  char **plansza = (char **)malloc((WIERSZE) * sizeof(char *));
  for (int i = 0; i < WIERSZE; i++) {

    plansza[i] = (char *)malloc(KOLUMNY * sizeof(char));
  }

  // funkcja odpowiadająca za działanie programu
  dzialanie_programu(plansza, numer_wiersza, numer_kolumny);

  // zwolnienie pamięci, wykorzystywanej jako
  // tablica do pamiętania stanu gry
  for (int i = 0; i < WIERSZE; i++) {
    free(plansza[i]);
  }
  free(plansza);

  return 0;
}

bool not_single_element(char **plansza, int numer_wiersza, int numer_kolumny) {

  // sprawdzamy, czy w sąsiedztwie klocka znajduje
  // się klocek tego samego typu
  if (numer_kolumny + 1 < KOLUMNY &&
      plansza[numer_wiersza][numer_kolumny] ==
          plansza[numer_wiersza][numer_kolumny + 1]) {

    return true;
  }
  if (numer_kolumny - 1 >= 0 && plansza[numer_wiersza][numer_kolumny] ==
                                    plansza[numer_wiersza][numer_kolumny - 1]) {

    return true;
  }
  if (numer_wiersza + 1 < WIERSZE &&
      plansza[numer_wiersza][numer_kolumny] ==
          plansza[numer_wiersza + 1][numer_kolumny]) {

    return true;
  }
  if (numer_wiersza - 1 >= 0 && plansza[numer_wiersza][numer_kolumny] ==
                                    plansza[numer_wiersza - 1][numer_kolumny]) {

    return true;
  }

  return false;
}

void wczytaj_plansze(char **plansza) {

  for (int i = 0; i < WIERSZE; i++) {

    for (int j = 0; j < KOLUMNY; j++) {

      scanf("%1c", &plansza[i][j]);
    }
    getchar();
  }
}

void wypisz_plansze(char **plansza) {

  for (int i = 0; i < WIERSZE; i++) {

    for (int j = 0; j < KOLUMNY; j++) {

      printf("%c", plansza[i][j]);
    }
    printf("\n");
  }
}

void usun_blok(char **plansza, int numer_wiersza, int numer_kolumny,
               char rodzaj_klocka, int *skrajne_lewe_usuniecie,
               int *skrajne_prawe_usuniecie) {

  // jeśli dochodzimy do końca planszy
  // kończymy wywoływanie funkcji
  if (numer_wiersza == WIERSZE || numer_wiersza < 0) {

    return;
  }
  if (numer_kolumny == KOLUMNY || numer_kolumny < 0) {

    return;
  }

  // jeśli trafiliśmy na klocek innego typu niż
  // oczekwiany również kończymy naszę rekurencję
  if (rodzaj_klocka != plansza[numer_wiersza][numer_kolumny]) {

    return;
  }
  // usuwamy element, czyli zamieniamy go na kropkę
  plansza[numer_wiersza][numer_kolumny] = '.';

  // znajdujemy numer kolumny skrajnego lewego
  // i skarjnego prawego usuniętego klocka
  if (numer_kolumny < (*skrajne_lewe_usuniecie)) {

    (*skrajne_lewe_usuniecie) = numer_kolumny;
  }
  if (numer_kolumny > (*skrajne_prawe_usuniecie)) {

    (*skrajne_prawe_usuniecie) = numer_kolumny;
  }
  // przechodzimy rekurencyjnie do sąsiednich elementów
  usun_blok(plansza, numer_wiersza + 1, numer_kolumny, rodzaj_klocka,
            skrajne_lewe_usuniecie, skrajne_prawe_usuniecie);
  usun_blok(plansza, numer_wiersza - 1, numer_kolumny, rodzaj_klocka,
            skrajne_lewe_usuniecie, skrajne_prawe_usuniecie);
  usun_blok(plansza, numer_wiersza, numer_kolumny - 1, rodzaj_klocka,
            skrajne_lewe_usuniecie, skrajne_prawe_usuniecie);
  usun_blok(plansza, numer_wiersza, numer_kolumny + 1, rodzaj_klocka,
            skrajne_lewe_usuniecie, skrajne_prawe_usuniecie);
}

void opusc_kolumny_od_do(char **plansza, int numer_pierwszej_kolumny,
                         int numer_ostatniej_kolumny) {

  for (int i = numer_pierwszej_kolumny; i <= numer_ostatniej_kolumny; i++) {

    opusc_kolumne(plansza, i);
  }
}

void przesun_wszystko_do_lewej(char **plansza,
                               int pierwsza_kolumna_do_przesuniecia) {

  for (int i = pierwsza_kolumna_do_przesuniecia; i < KOLUMNY; i++) {

    przesun_kolumne_najdalej_w_lewo(plansza, i);
  }
}

void przesun_kolumne_najdalej_w_lewo(char **plansza, int numer_kolumny) {

  // jeśli numer kolumny jest równy 0
  // lub kolumna po lewej stronie nie jest pusta
  // wtedy nie wykonujemy przesunięcia
  if (numer_kolumny == 0 || !(kolumna_pusta(plansza, numer_kolumny - 1))) {

    return;
  }
  // przesuwamy kolumę najdalej jak to możliwe
  // w lewą stronę
  przesun_w_lewo(plansza, numer_kolumny);

  // wywołujemy rekurencyjnie wywołanie od przesuniętej kolumny
  przesun_kolumne_najdalej_w_lewo(plansza, numer_kolumny - 1);
}

void opusc_kolumne(char **plansza, int numer_kolumny) {

  for (int i = WIERSZE - 1; i >= 0; i--) {

    opusc_element(plansza, numer_kolumny, i);
  }
}


void przesun_w_lewo(char **plansza, int numer_kolumny) {

  // przepisujemy element kolumny na element po lewej stronie
  // element pierwotnej kolumny zamieniamy na '.'
  for (int i = 0; i < WIERSZE; i++) {

    plansza[i][numer_kolumny - 1] = plansza[i][numer_kolumny];
    plansza[i][numer_kolumny] = '.';
  }
}

bool kolumna_pusta(char **plansza, int numer_kolumny) {

  int licznik = 0;

  if (numer_kolumny >= 0) {

    for (int i = 0; i < WIERSZE; i++) {

      if (plansza[i][numer_kolumny] == '.') {

        licznik++;
      }
    }
  }

  return (licznik == WIERSZE);
}

void opusc_element(char **plansza, int numer_kolumny, int numer_wiersza) {

  // chcemy znaleźć jak nisko możemy opuścić nasz element
  // w tym celu znajdujemy najniżej położony pusty element
  // pod elementem, który chcemy przesunąć
  int indeks_sprawdzany = numer_wiersza + 1;
  while (indeks_sprawdzany < WIERSZE &&
         plansza[indeks_sprawdzany][numer_kolumny] == '.') {

    indeks_sprawdzany++;
  }
  indeks_sprawdzany--;
  // umieszczamy element na najniższym pustym miejscu
  // w tej kolumnie
  if (plansza[indeks_sprawdzany][numer_kolumny] == '.') {

    plansza[indeks_sprawdzany][numer_kolumny] =
        plansza[numer_wiersza][numer_kolumny];
    plansza[numer_wiersza][numer_kolumny] = '.';
  }
}

void dzialanie_programu(char **plansza, int numer_wiersza, int numer_kolumny) {

  wczytaj_plansze(plansza);
  // sprawdzamy, czy pod zadanymi współrzędnymi jest tylko jeden element
  if (not_single_element(plansza, numer_wiersza, numer_kolumny)) {

    // zmienne, kótre przechowają zakres nzaszego usuwania
    int skrajne_lewe_usuniecie = KOLUMNY;
    int skrajne_prawe_usuniecie = -1;
    // funkcja usunie cały blok naszych
    usun_blok(plansza, numer_wiersza, numer_kolumny,
              plansza[numer_wiersza][numer_kolumny], &skrajne_lewe_usuniecie,
              &skrajne_prawe_usuniecie);
    // jak już usuneliśmy nasz blok, to teraz chcielibyśmy opóścić kolumny, w
    // których coś zostało usunięte
    opusc_kolumny_od_do(plansza, skrajne_lewe_usuniecie,
                        skrajne_prawe_usuniecie);
    // po opuszczeniu kolumn pozostaje nam poprzesuwać wszystko jak lecie
    przesun_wszystko_do_lewej(plansza, skrajne_lewe_usuniecie);
    // na tym teapie wszystko powinno być uporządkowane, więc wypisujemy planszę
    wypisz_plansze(plansza);

    // w przeciwnym wypadku nic nie usuwamy, więc po prostu wypiszemy planszę,
    // bo otrzymana plansza jest poprawna
  } else {

    wypisz_plansze(plansza);
  }
}
