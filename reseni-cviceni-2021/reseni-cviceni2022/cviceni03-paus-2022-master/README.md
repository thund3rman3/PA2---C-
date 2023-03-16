# Cvičení 03

Implementujte třídu `Stack` představující zásobník pomocí nafukovacího pole, která bude mít následující vlastnosti.

## Datový typ

Zásobník bude pro jednoduchost ukládat datový typ `int`.

## Metody

* `push_back()`: vloží prvek na vrchol zásobníku (na konec pole). Vrací `void`.
* `at( pozice )` : Vrátí prvek na pozici `pozice` v poli
* `at( pozice ) = int`: upraví hodnotu prvku na pozici `pozice`. Pokud je pozice mimo meze, ukončete program pomocí `assert()`. Výjimky zatím neumíme.
* `pop_back()`: Vrátí prvek na vrcholu zásobníku (na konci pole) a hodnotu odstraní. Pokud je zásobník prázdný, ukončete program pomocí `assert()`.
* 

## Další funkce

* Přetížený operátor `<<` pro výpis do streamu ve formátu `{ cislo0 cislo1 cislo2 ...}`.

