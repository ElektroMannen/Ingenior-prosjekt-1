# API

Referanse for diverse topics

## Kontroll

Brukerkontroll av bil

```
Struct oppgygging til bil data

struct data{
  int32_t drive, driverLevel, driverScore;
  bool warning;
};

MQTT topics

Kontroll:
car/control

Data som bilen får:
car/driverLevel
car/driverScore
car/warning

Mqtt topics som zumo sender til
"car/distance"
"car/score"
"car/speed"
```

### Eksempel på data sendt fra server

```js
// hold inn w og d
{"w":true,"d":true}

// kun w
{"w":true}

// ingen tast
{}
```
