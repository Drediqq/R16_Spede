# R16 Speden Speli

Arduinolla toteutettu muisti- ja reaktiopeli, joka perustuu Speden Spelit -ohjelman nopeustestiin.
<!-- GIF tai kuva pelistä -->

## Vuokaavio

[Avaa vuokaavio täysikokoisena](https://raw.githubusercontent.com/Drediqq/R16_Spede/images/Spedevuokaavio.svg)

![Vuokaavio](images/Spedevuokaavio.svg)

## Tarvittavat komponentit

| Osat | Määrä |
|---|---|
| Arduino Uno R3 | 1 |
| LED | 4 |
| 220 Ω vastus | 18 |
| 7-segmenttinäyttö | 2 |
| Painonappi | 4 |
| 74HC595-siirtorekisteri | 2 |

### Kotelointi (valinnainen)

| Osat | Määrä |
|---|---|
| Kaksipuolinen piirilevy | 1 |
| Piikkirima | > 1 |
| Holkkirima | > 1 |
| JST-XH-liitin | > 1 |
| Dupont-liitin | > 1 |
| M3-inserttimutteri | 12 |
| M3×8-ruuvi | 12 |

## Pelin toiminta
- Peli käynnistyy nappia 1 painamalla.
- Kun peli on käynnissä, ledejä syttyy satunnaisesti.
- Tehtäväsi on painaa kyseisen ledin nappia.
- Oikea painallus lisää näytölle yhden pisteen.
- Peli nopeutuu 10 syttyneen ledin välein 10% nopeammaksi.
- Peli loppuu, jos jäät 20 painallusta jälkeen tai painat väärää nappia.
- Kun peli päättyy, ledit näyttävät valoshown. 

## Kytkentä
<!-- Kuva kytkennästä -->

### Piirikaavio

![Piirikaavio](images/piirikaavio.png)

## Wokwi simulaatio
<!-- linkki simuun -->

## Tekijät

<table>
  <tr>
    <td align="center" width="25%">
      <a href="https://github.com/Drediqq">
        <img src="https://github.com/Drediqq.png" width="100" alt="Juuso Kiiala"/><br />
        <sub><b>Juuso Kiiala</b></sub>
      </a>
    </td>
    <td align="center" width="25%">
      <a href="https://github.com/xDeeZy666">
        <img src="https://github.com/xDeeZy666.png" width="100" alt="Eetu Stranden"/><br />
        <sub><b>Eetu Stranden</b></sub>
      </a>
    </td>
    <td align="center" width="25%">
      <a href="https://github.com/Moolokki">
        <img src="https://github.com/Moolokki.png" width="100" alt="Patrick Hietala"/><br />
        <sub><b>Patrick Hietala</b></sub>
      </a>
    </td>
    <td align="center" width="25%">
      <a href="https://github.com/xdanu">
        <img src="https://github.com/xdanu.png" width="100" alt="Daniel Kallio"/><br />
        <sub><b>Daniel Kallio</b></sub>
      </a>
    </td>
  </tr>
</table>