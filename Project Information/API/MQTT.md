# API

Referanse for diverse topics

## Kontroll

Brukerkontroll av bil

```
**Struct oppgygging til bil data**

struct data{
  int32_t drive, driverLevel, driverScore;
  bool warning;
};

MQTT topics
Kontroll:
car/control
Data:
car/driverLevel
car/driverScore
car/warning
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
