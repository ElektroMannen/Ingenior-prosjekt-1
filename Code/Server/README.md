# Raspberry Pi Docker Environment

Docker tillater utviklere å sette opp et felles utviklermiljø. 

Ved å bruke en plugin som heter `compose` oppretter man et miljø som består av flere "konteinere" alt fra samme fil.

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

4. Kjør kommandoen

```
docker-compose up -d
```