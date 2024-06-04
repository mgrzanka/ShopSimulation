# Symulacja działania sklepu

## Klasa Employee

Pracownicy sklepu są odpowiedzialni za różne czynności związane z jego funkcjonowaniem, takie jak otwieranie i zamykanie sklepu, utrzymywanie porządku, uzupełnianie towaru, obsługa klientów, wyliczanie należności, przyjmowanie zapłaty oraz wydawanie paragonów. Istnieją różne rodzaje pracowników, dziedziczące po klasie Employee: Cashier, Cleaner, Storekeeper, Manager.

### Atrybuty:
- **imię**: Losowo wybierane z bazy imion.
- **nazwisko**: Losowo wybierane z bazy nazwisk.
- **grafik pracy**: Określa godziny pracy pracownika w danym dniu tygodnia.
- **podstawowa stawka za godzinę**: Określa ile pracownik zarabia w ciągu godziny.
- **bonus do stawki**: Dodatek do podstawowej stawki za godzinę.
- **interfejs użytkownika**

### Metody:
- **posprzątaj (Cleaner)**: Pracownik losowo sprząta sklep.
- **obsłuż klienta (Cashier)**: Po zakupach klienta, pracownik wylicza należność do zapłaty.
- **wypłać wypłatę pracownikom (Manager)**: Wypłata wynagrodzenia pracownikom.
- **metody do wywoływania komunikatów, które pracownicy mówią np. do klientów**
- **obliczanie tygodniowego wynagrodzenia**

## Klasa Client

Klienci wchodzą i wychodzą ze sklepu, mają określony budżet na zakupy i spędzają w sklepie określoną ilość czasu. Mogą wybierać towary i za nie płacić. Klienci mogą być różnego rodzaju: przyjaciel menadżera, stały klient, turysta.

### Atrybuty:
- **imię**: Losowo wybierane z bazy imion.
- **nazwisko**: Losowo wybierane z bazy nazwisk.
- **budżet na zakupy**: Określa ile klient może wydać podczas pobytu w sklepie.
- **interface użytkownika**

### Metody:
- **wejdź do sklepu**
- **wyjdź ze sklepu**
- **kup przedmiot**: Klient może wybrać dowolny towar mieszczący się w jego budżecie.

## Klasa Product

Towary w sklepie są podzielone na kategorie, od których zależy wysokość podatku VAT. Klasy towarów z różnych grup podatkowych dziedziczą po klasie Product: pieczywo, napoje, nabiał, owoce i warzywa, kosmetyki, artykuły przemysłowe.

### Atrybuty:
- **nazwa**
- **cena**
- **opcjonalnie: dodatkowy atrybut**

### Metody:
- **oblicz cenę towaru uwzględniającą podatek**
- **podaj numer półki, na której znajduje się produkt**

## Klasa Receipt

Paragony zawierają informacje o rodzajach i ilości sprzedanych towarów.

### Atrybuty:
- **lista znajdujących się na nim towarów wraz z informacjami o nich**: Wektor obiektów klasy Product.
- **suma z podatkiem**
- **suma bez podatku**

### Metody:
- **wyświetl paragon**

## Klasa Store

Klasa przechowuje informacje o produktach, pracownikach i klientach w sklepie.

### Atrybuty:
- **pracownicy**: Wektor obiektów klasy Employee (osobny wektor dla pracowników, którzy są w sklepie, ale są wolni, tych, którzy są zajęci i tych, których obecnie nie ma w sklepie, ale w nim pracują).
- **klienci**: Wektor obiektów klasy Client (osobny wektor klientów, którzy są w sklepie i tych, którzy mogliby potencjalnie w nim być).
- **produkty**: Wektor obiektów klasy Product.
- **kwota, którą sklep w danym momencie dysponuje**

### Metody:
- **dodaj pieniądze do sklepu**
- **zabierz pieniądze ze sklepu**: np. kiedy sklep dostaje nowy towar i musi za niego zapłacić.
- **dodaj produkty**
- **dodaj klientów**
- **dodaj pracowników**
- **zmień grafik pracowników**

## Klasa Random Event

Podczas pracy sklepu mogą wystąpić zdarzenia losowe. Pojedynczy obiekt tej klasy reprezentuje pojedyncze zdarzenie, które może zajść w sklepie. Zdarzenia będą występować z określonym prawdopodobieństwem.

### Atrybuty:
- **sklep**: Z którego Random Event bierze informacje potrzebne do wykonania zdarzenia (np. jakie produkty są dostępne w sklepie, jacy pracownicy mają w danym momencie zmianę).
- **dodatkowe atrybuty w zależności od zdarzenia**

### Metody:
- **wyświetl zdarzenie**: Wyświetla opis w terminalu.
- **przeprowadź zdarzenie**: Wywołuje określone czynności obiektów zaangażowanych w tę metodę.

### Klasy pochodne:
- **ClientsBuysEvent**
- **CleanerCleansEvent**
- **ManagerGivesRiseEvent**
- **SupplierAddsProductsEvent**

## Klasa Event Generator

Generuje zdarzenia losowe podczas symulacji.

### Atrybuty:
- **sklep**
- **wektor prawdopodobieństw poszczególnych zdarzeń**
- **wektor indeksów dla zdarzeń**

### Metody:
- **wybierz nowe produkty, które będą dodane do sklepu**: Metoda wykorzystywana w zdarzeniu dostawy.
- **losuj zdarzenia**: Wylosowane zdarzenie jest wykonywane za pomocą odpowiedniej dla siebie metody.

## Klasa Simulation

Główna klasa programu pozwalająca na uruchomienie symulacji sklepu.

### Atrybuty:
- **ilość dni do zasymulowania**
- **sklep**
- **wektor prawdopodobieństw zdarzeń**
- **obiekt klasy FileHandler**: Do odczytania informacji o produktach, klientach i pracownikach z plików.

### Metody:
- **dodaj pierwszą dostawę**
- **run**: Przeprowadza całą symulację - w ramach tej metody losowane są zdarzenia losowe z wykorzystaniem generatora (EventGenerator). Każde zdarzenie ma określone prawdopodobieństwo wystąpienia.

Pętla programu trwa n iteracji, gdzie n to 15-minutowy okres działania sklepu. Wewnątrz pętli losowane jest, czy wystąpi jakieś zdarzenie (prawdopodobieństwo z atrybutów klasy). Wylosowane zdarzenie jest wykonywane (wprowadzane są odpowiednie zmiany w sklepie, wyświetlane są informacje o tych zmianach). Przeprowadzane są także zmiany pracowników w określonych w grafiku porach. Na koniec każdej iteracji program sprawdza, czy i który pracownik powinien zakończyć/zacząć pracę. Po zakończeniu pętli sklep jest zamykany i symulacja się kończy.

## Klasa UserInterface

Odpowiada za wyświetlanie wiadomości do użytkownika.

### Metody:
- **print**: Wyświetla wiadomości.

## Klasa FileHandler

Odpowiada za czytanie z pliku informacji o obiektach poszczególnych klas (pracownikach, klientach, produktach) i tworzenie wektorów wskaźników na obiekty klasy Product.

### Atrybuty:
- **ścieżka do pliku**

## Klasa PeopleParser

Odpowiada za tworzenie obiektów klas związanych z ludźmi (pracowników i klientów). Atrybutem jest ścieżka do pliku, bo przy wykorzystaniu klasy FileHandler, z pliku czytane są imiona i tworzone są odpowiednie dane (wektory wskaźników na obiekty klasy Employee lub Client).

### Atrybuty:
- **ścieżka do pliku**