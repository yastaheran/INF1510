# Kort beskrivelse av planlagt sluttprodukt.
  Sluttproduktet skal være en LCD-display stoppeklokke. Den skal ha en knapp for start/pause og en for tilbakestilling. 
  Klokken skal vise tiden siden start med minutter, sekunder og tidelssekunder. Når stoppeklokken slåes på skal skjermen vise:
    Press Start
    00:00:00.00
  Hvor tiden er representert i hh:mm:ss.dd. Dersom klokken startes forsvinner «Press Start», klokken begynner å tikke, og hvis 
  klokken stoppes og startes uten å nullstilles skal den fortsette fra der den stoppet. Når klokken nullstilles skal skjermen for 
  eksempel vise:
    Press Start
    Last: 00:10:45.8
   Hvor «Last» er tiden for forrige intervall. Man skal også kunne justere lyset til LCD-displayet. Dermed vil denne stoppeklokken ha 
   funksjonene start, pause, nullstill og mulighet for å vise forrige intervall.

# Beskrivelse av utstyret som brukes
    LCD-display: for å vise tiden siden start.
    Potensiometer: for å justere lysstyrken til LCD-displayet.
    To knapper; en for start/pause og en for nullstilling av tid.
    To 10k ohm; en for hver knapp.
    220 ohm; en for LCD-displayet.

# Beskrivelse av faktisk sluttprodukt
  Sluttproduktet ble nesten som planlagt. Det ble en LCD-display stoppeklokke med to knapper, og med mulighet til å justere lyset til 
  LCD-displayet. Den ene knappen starter og pauser tiden, og den andre nullstiller tiden. Når stoppeklokken slåes på viser skjermen:
    Press Start
    00:00:00.00
  Når stoppeklokken startes forsvinner  «Press Start», klokken begynner å tikke, og hvis klokken stoppes og startes uten å nullstilles 
  fortsetter den fra der den stoppet. Når klokken nullstilles skal skjermen for eksempel vise:
    Press Start
    Last: 00:10:45.8 
  Skjermen viser tiden i hh:mm:ss.dd som planlagt, men når nullstill-knappen trykkes blir blir rundet oppover. F.eks.: Hvis tiden ble 
  nullstilt 00:10:34.6, vil «Last» vise 00:10:34.7. Stoppeklokken oppfører seg heller ikke slik den skal dersom man trykker start, og 
  deretter nullstill. Når man trykker start, deretter nullstill, f.eks:
    00:00:01.4t
    Last: 00:00:01.4
  Derfor må stoppeklokken pauses før den nullstilles.
