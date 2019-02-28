---
header-includes:
	\usepackage{a4wide}
	\usepackage[czech]{babel}
---
# Hlídky
## Řešení
### Algoritmus
Problém řeším tak, že uložím si mapu měst, jako graf. Následně provádím hledání v grafu(hledání do šířky), s tím že 
používám vždy hrany s určitým maximálním počtem hlídek. Prvně 0, pak 1... Takže když se mi povede dostat do cíle vím, že 
to je s nejnižším maximálním počtem hlídek. Pokud ani s počtem hlídek na silnici, jež je roven maximálnímu zaznamenanému 
počtu hlídek při ukládání grafu nedojdu do cíle, vím že cesta neexistuje.

### Složitost
Složitost prohledávání grafu je `0(N)`, kdy N je součet hran a vrcholů, každou hranu i vrchol navštívím jednou. 
Složitost nalezení cesty je `O(N)`, kdy N je počet měst na cestě. Celková složitost je tedy:
```
O(N*N+N)
O(N^2)
```
Kdy N navíc je kolikrát jsem prováděl hledání než jsem nalezl cíl.
