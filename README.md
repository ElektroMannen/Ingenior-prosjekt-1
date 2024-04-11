# Ingeniør prosjekt 1

----------------

## Problemstilling (utkast)

Vi har fått et oppdrag av bystyret til å lage en IOT løsning for å hjelpe med å gjøre byen grønnere. Bystyret ønsker å ha insentiver til å skape grønne vaner hos byen's innbyggere.
De ønsker også å redusert last på strømnettet, løsningen på dette er opp til oss. 

-------------------

## Frister
- **Ideskapning** 5.April
- **Ferdigstille prosjekter** 20.Mai
- **Ferdigstille innlevering** 31.Mai
- **Innlevering senest** 6.Juni

-----------------

## Ressurser

- **Refleksjons notat:** [Refleksjons notat.tex](https://www.overleaf.com/3524624722xnnfcykfcyht#74726a)
- **Design:**
- **Ideer** [Diskusjons forum i github](https://github.com/ElektroMannen/Ingenior-prosjekt-1/discussions)
- **Oppgave text:** [ Oppgave_text.md](https://github.com/ElektroMannen/Ingenior-prosjekt-1/blob/main/Prosjekt%20informasjon/Oppgave_text.md)

------------------

## Ansvarsfordeling
|**Person**|**Ansvar**|**Modul/Del**|
|------------|--------|---------:|
|He You Ma|Kommunikasjons dev|          |
|Eirin Iversen|       |          | 
|Olav André Telneset|Database dev|          |
|Zuzanna Kalawska|Design ansvarlig|          |
|Ottar Rolfsrud|Bil dev|          |

-----------------------------------

## Bruk av github
- Issues er vår kanban/Fremgangs oppfølgings metode. Hvor vi legger moduler som vi jobber på og status på hvor i løypen den ligger.
- Koden vi lager blir bassert på forskjellige esp32er og dermed vil trenge egene filer.
- Ideer blir lagt i discussions, slik at vi kan diskutere og stemme opp idene som er verdt å utvikle

MMMMMMMMMMMMMMMMMMMMMMMMWWWWWMWWNKkoc:;,;;:lx0XWMMMMMMWMMMMWMMMMMMMMMWWWWWWWMWWWMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMWWWMWN0dlc;,,,,,,,,,,;;:clxk0NMMWMMWWMWN0kdolccccclodkKWWMMMMMMWMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMMWKd:,,;:ccllcc:ccccccc:;,',:okXWNKkoc;,,,;:cccc::;,,;cxKWMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMW0l,,:ccccccccccccccccccccccc:,,;c:;,,:cccccccccccccccc;,,dXMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMWMMMMKl,,:cccccccccccccccccccccccccccc:,,:clcc:cccccccccccccccc;':0WWWMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMWMNx,,:cccccccccccc:::::::::::::cccccc::;:cccccccccccccccccccccc';0WMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMWKl':lccccccccc:::;::::::::::::;;;;::cc:;:ccccccccccccccccccccccc'lNWMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMW0:,:ccccc:cc:;;:::cccccccccccccccc:::;::;;;;;;;;;;;;;;;;;;;;;;;;:.'d0NWMMMMMMMMMMM
MMMMMMMMMMMMMMMMWO;':cc:cccccc::ccccccccccccccccccccccccc:;,,;::::c:::ccc::::::::;:;,,;:ld0NMMMMMMMM
MMMMMMMMMMMMMMMWO;'cccccccccccccccccccccccccc::::::::::::::;;;;:cccccccccccccccccccccccc:,,:xXWMMMMM
MMMMMMMMMMMMMMM0;'ccccccccccccccccccccccc:;;::;;;;;;;;;;;::::;;;;:cccc:::;;;;;::;;;:::;;;::,.;kXWMMM
MMMMMMMMMMWWXOd;':ccccccccccccccccccc::;;:::;;;:::::::::::::::::;;,;::;;;,;;;;:::;:::;;;;;;;;,,;dXWM
MMMMWWMWWXxc:;'';lc:cccccccccccc::::;;;;;;::::cccllcccccccccc:::::;;;:::;;:::cccclc:::::::;::::'.oXW
MMMMMWWNx;,:cc;;:ccccccccccccc::;::::;;::::cccccccccc::::cccccllooc::cccccc:::ccclc::::codxool:;'';O
MWMMWWKl';cccc;;ccccccccccc:;;;::;:::ccccccccc:cclllcccccodk0XXXNXXkc;clodxkOOOko,.'....,ckXNXKOkl.o
MMMMWK:':ccccc;:ccccccccccc:;;;:::::cc:cclodxkOko;;co:.   .'l0WWWWWKxkKXWWWWMWO,  ;l.     .c0WWWWXl:
MWWMK:':cccccc:ccccccccccccc:::;::;;lkOKXNWWWWK:.  .:;. .,'  .dNWWN00WWWWWWWMK;   ..  ;d;   cXWWNOcl
MMMK:':ccccccccccccccccccccccccccccc:cdOXNWWWNl     ..  ;Oo.  .dKOooOXXNWWWWMk.  .;'  ,l,   .dOxl,oX
MMXc.:cccccccccccccccccccccccccccc::;;::coxk00:     ',  .......;c:;,:lodddxxxl....'.....''',;;,,;xWW
WXc':ccccccccccccccccccccccccccccccc:;;;:;;;::;;,,,,,,,;;;;::::;;;;:cccccccccc:c:cc::ccccccc,,o0NWWM
Nd.;cccccccccccccccccccccccccccccccccccc::;::;;:;;;;:;;::;;;;::;::cccccccccccccclccccccc::,,c0WWWMMM
0;'cccc:ccccccccccccccccccccccccccccccccccccccccccccccc:::;;:ccccccccc:::ccccccccccccc;,,;o0WWMWMMMM
d.;lcccccccccccccccccccccccccccccccccccccccccccccc:::;;;;:::ccccccccc::;;;;;;:::;::::;..lKWMMMMMMMMM
l.:cccccccccccccccccccccccccccccccccccccccccc:::;;;;;::cccccccccccccccccc:;;;:::::ccccc;'cOWWWMWMMMM
;'ccccccccccccccccccccccccccccccccccccccccccccc::cccccccccccccccccccccccccccccccc:ccccccc,,dXWWWWMMM
,'lccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc:'lXMWMMMM
',lcccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc;'oNMMMMM
.,cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccl,,0MMMMM
',cccccccccccccccccccccccccccc:;;;;;;;;;;::::::ccccccccccccccccccccccccccccccccccccccccccc::,.cKWMMM
',cccccccccccccccccccccccccc:;;;:::::::::;;;;;;;;;;;:::::::cccccccccccccccccccccccccc::::;;;;;.:KMMM
,'lccccccccccccccccccccccc:;;:::::::::::::::::::::::::;;;;;;;;;;;::::::::;;;;;;;;;;;;;;;;:c:::.:XMMM
:'c:cc:ccccccccccccccccccc;,;:::::;;;;;;;;;;;;;;;:::::ccc::::::::;;;;;;;;;;;;;;;;::::::::::;',oKWMMM
l.:ccccccccccccccccccccccc;;;::::::ccccc:::;;;;;;;;;;;;;;;;;;;;;;::::::::::::::::;;;;;;;;,.'dKWMMMMM
d';cccccccccccccccccccc::cc:;;;;;;;;;;;;;;;::::::::cc::::;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;::',OMWWMMMM
0,'cc:ccccccccccccccccc;;:ccccc::::::::::::;;;;;;;;;;;:::::::::::::ccccccccccccc:::ccc:::,'lXMWWMMMM
WO;':lcccccccccccccccccc::;;::cccccccccccccccccc:::::::::;;;;;;;;;;;;;::;;;;;;;;;;,,'',,;lONMMMMMMMM
WW0l;,;:cccccccc:ccccccccc::::cccccccccccccccccccccccccccccccccccccccccc::::::::,',lxkOKNWMMMMMMMMMM
WWMWKxl:,'';:ccc:ccccccccccccccccccccccccccccccccccccccccccccccccccccc:ccccc:;,,cxXWWWWMMMMMMMMMMMMM
WWMMWWWNKkoc:,'',,:ccccccccccccccccccccccccccccccccccccccccccccccccccccc:;',:lxKWWMMMMWWMMMMMMMMMMMM
WMMWWMWWMMMMWKOxolc:;,,,,,;::ccccccccccccccccccccccccccccccccccccc:;,,,;:ldOXWWWWWMMWMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMWNX0Oxolc:::;,,,'',,,,,''',,,'',,,,'''',,,,'''',:coxOKNMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMMMWWNXKOkxddolccc:::;;;,,,,''',,;;:clllodOXWMWWWMMMMMMMMMMMMMMMMMMMMMMMMMMMM
