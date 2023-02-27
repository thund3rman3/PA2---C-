# Výjimky

Na tomto cviku si vyzkoušíme práci s výjimkami (exceptions).

## Úkol 1

* Napište funkci `factorial()`, která vyhodí výjimku typu `unsigned` s hodnotou parametru, pokud bude parametr větší než 10.
* V `main()` tuto funkci zavolejte a zabezpečte řádné odchycení výjimky a výpis chybové hlášky. 

## Úkol 2

* Kód upravte, aby vyhodil výjimku typu `std::invalid_argument` ze STL. V `main()` funkci `factorial()` zavolejte a zabezpečte řádné odchycení výjimky a výpis chybové hlášky. 

## Úkol 3

* Napište funkci `passwd(string)`, která bude kontrolovat sílu hesla.
* Vytvořte hierarchii tříd pro výjimky při kontrole hesla.
* Základní třída bude `BaseExcept`, která bude mít jako parametr konstruktoru `std::string`. Dále bude mít veřejnou metodu `what()`, která vrátí onen `string` z konstruktoru.
* Odvoďte třídu `PasswordTooShortExcept`, která bude mít jako parametry konstruktoru `std::string` a `size_t` pro uložení délky krátkého hesla. Upravte `what()`, aby vracela v chybové hlášce i délku krátkého hesla.
* Odvoďte třídu `BadCharExcept` pro neplatný znak v hesle, ktará bude mít jako parametry konstruktoru `std::string` a `char` pro uložení neplatného znaku v hesle. Upravte `what()`, aby vracela i tento znak.
* Ve funkci `main()` tyto výjimky odchyťte a vypište chybové hlášky.

**Použijte vzorový `main.cpp`.**