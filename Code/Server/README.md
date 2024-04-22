# Raspberry Pi Docker Environment

Docker tillater utviklere å sette opp et felles utviklermiljø. 

Ved å bruke `compose` oppretter man et miljø som består av flere "konteinere" som kommuniserer sammen.

# Guide
1. Installer docker og docker-compose

[Installer Docker på raspberry pi (32-bit)](https://docs.docker.com/engine/install/raspberry-pi-os/)

2. Installer docker-compose plugin

```
 sudo apt-get update
 sudo apt-get install docker-compose-plugin
```

Sjekk at alt fungererer

```
docker compose version
```

3. Naviger til Server-mappen

```
cd Code/Server
```

Sørg for at du ikke har andre tjenester som kjører på portene `3036`, `1883` eller `1880`.

Dette kan gjøres ved å avinstallere mosquitto og mosquitto-clients. Følgende steg kan tas:

```
sudo apt remove mosquitto mosquitto-clients
```


```
sudo apt autoremove
```

Sjekk at portene er ledig med

```
sudo netstat -tulpn | grep -E '1880|1883|3036'
```

Om ingenting kommer opp skal alt være i orden.

4. Kjør kommandoen

```
docker-compose up -d
```

Fjern `-d` for debugging.

# Lokal bruk av MariaDB

Om nødvendig kan man undersøke databasen fra mysql-programvare på raspberry pi.

1. Installer mysql
```
sudo apt install default-mysql-client
```
2. Logg inn
```
mysql -h 127.0.0.1 -P 3306 -u root -p
```

# Gjenbygge database

Fjern alle filer fra `mariadb-data`-mappen.

Sørg for at rotmappen er Server-mappen før du kjører kommandoen under.

```
rm -rf docker/mariadb-data/*
```

# Python-MQTT-kommunikasjon

I mappen `Serial` er det et enkelt python script som håndterer kommunikasjon mellom UART og MQTT.

## Bruk av scriptet

1. Sett opp .venv

```
python -m venv .venv
```

2. Aktiver venv

```
source .venv/bin/activate
```

3. Installer avhengigheter i virtuelt miljø

```
pip install -r requirements.txt
```