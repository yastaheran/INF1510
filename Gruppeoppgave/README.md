# Tema og målgruppe
Kobra ønsker å se nærmere på teknologiske løsninger for personer med utviklingshemming som bor i samlokalisert bolig. En stor del av
beboers vedtak er hjelp til tilrettelegging og bistand til daglige gjøremål på en slik måte at beboeren er mest mulig selvhjulpen og 
selvstendig. Struktur i hverdagen er en stor del av brukergruppens utfordring, og motivasjon er en viktig faktor for å oppnå positive 
resultater. Derfor har vi valgt å utforske temaet: Beboers hverdag og hvordan hverdagslige gjøremål kan oppleves mer oversiktlig og 
strukturert gjennom motivasjon.
 
# Problemstilling
Vår opprinnelige problemstilling gikk ut på å gjøre beboeren mer selvstendig og selvhjulpen, og samtidig gjøre arbeidsdagen til de 
ansatte enklere og mer strukturert. Etter første iterasjon definerte vi unødvendig mas og påminning fra personalet som nytt problemområde. 
Videre ville vi utforske om påminnelser kunne erstattes med motivasjon, med problemstillingen: 
 «Kan en endret opplevelse av dagsplanlegging gi økt motivasjon til aktiviteter i dagliglivet (ADL)?»
 
# Datainnsamlingsmetoder
Underveis i designprosessen har vi benyttet oss av kvalitative metoder for datainnsamling med triangulering for å oppnå en god 
dybdeinnsikt for identifisering av problemområde og svar på problemstilling. For alle intervjuer har vi utarbeidet en intervjuplan 
og -guide.
 
# Innledende datainnsamling (Feltstudie og intervju)
For å bli kjent med brukergruppen og videre danne et generelt grunnlag for videre undersøkelser, startet vi designprosessen med 
observasjon av to beboere og ett personal i naturlige omgivelser. Vi var passive observatører gjennom en vanlig morgen og ettermiddag 
hos to beboere. Vi valgte å ha en passiv rolle for å få et bilde av samhandling mellom beboerne og personalet i hverdagssituasjon.
 
Etter observasjonen satt vi igjen med flere spørsmål vi ønsket svar på, og gjennomførte derfor semistrukturerte intervjuer med seks 
ansatte. Gjennom observasjonen fikk vi et generelt inntrykk av beboernes situasjon, og vi ville nå ha svar på spørsmålene som omhandlet 
hvordan, hva og hvorfor ting vi observerte var som de var.
 
## 1. iterasjon (Fokusgruppe)
Vi utforsket ulike konsepter med nødvendige funksjoner, og eksperimenterte med ulike idéer og skisser for å danne et godt grunnlag 
for evalueringen. Skissene skulle være et springbrett for mer kreative tilbakemeldinger der personalet kunne ta utgangspunkt i konseptene. 
Vi benyttet fokusgruppe for å få innspill om idéer og konsepter der flere personer sammen kunne diskutere og beslutte ut ifra konklusjonen 
de kom fram til. Hovedmålet med evalueringen var å se om vi hadde ivaretatt brukernes ønsker og behov.
 
## 2. iterasjon (Fokusgruppe)
For evaluering av nye lavoppløselige prototyper av papp valgte vi å ha fokusgruppeintervju med personalet. Vi holdt fokusgruppe for å se 
om personalet hadde forslag til forbedringer eller om det var noen feil eller mangler ved prototypen. Hovedmålet med evalueringen var å 
se om vi hadde tolket behovene og ønskene deres riktig, samtidig som vi ville få tilbakemeldinger som kunne bidra til et mer appellerende 
design for beboerne. Vi stilte spørsmål angående form, design og funksjonalitet.
 
## 3. Iterasjon (Brukbarhetstesting med intervju)
Vi ønsket raske tilbakemeldinger da vi selv ikke anså prototypen som særlig funksjonell, og ville dermed komme igang med ny idémyldring 
for videre prototyping. Vi gjennomførte brukbarhetstesting etterfulgt av semistrukturerte intervjuer med to ansatte. Her ønsket vi å få 
bekreftelse fra personalet om at prototypen kunne testes med beboer. Vi fokuserte på brukbarhet og brukervennlighet, interaksjon og 
feedback, samtidig som vi så etter kritiske feil eller endringer som måtte gjøres.
 

# Endelig evaluering (Observasjon og semistrukturert intervju)
Under evaluering av endelig prototype observerte vi én beboer teste prototypen. Observasjonen ble gjort i naturlige omgivelser sammen 
med personalet. De evaluerte brukbarhet og brukervennlighet, samtidig som vi ønsket å se om beboeren klarte å interagere med prototypen. 
Etter testingen utførte vi semistrukturerte intervjuer for å stille spørsmål vi satt igjen med etter observasjonen. Vi ønsket også å se 
om Motus kunne være med på å svare på problemstillingen vår.
 
# Motus
Motus er en høyoppløselig prototype som skal hjelpe beboere med å bli mer motiverte til å gjøre deres daglige gjøremål. Motus skal 
brukes hjemme hos beboerne, og kan designes for hver enkelt beboer ved å bytte farge på forsiden og gjøremålskortene. Beboeren finner, 
sammen med en ansatt, ut hvilke oppgaver han skal utføre og skanner disse inn i Motus. 4 lys vil blinke når en aktivitet blir registrert. 
Når alle aktivitetene er registrert kan beboeren skanne de ut etter å ha fullført sine aktiviteter. 4 lys vil da slås på for å vise 
beboeren sin progresjon. Når alle aktiviteter er gjort, vil det være mulig å trykke på den gule knappen for å motta belønning i form av 
musikk. Dette kan virke motiverende for beboeren. Vi ønsker at Motus skal motivere beboerne slik at de føler glede av å gjøre nødvendige 
aktiviteter, samtidig som vi ønsker å belønne dem for utførte gjøremål.
 
## Teknisk løsning
Motus drives av to Arduino UNOer som kommuniserer sammen ved hjelp av Wire-biblioteket. Hovedkomponenten er en RFID-leser som leser 
og lagrer RFID-kort som representerer ulike daglige aktiviteter. Knappene, Mp3-shieldet og lyslenken gir feedback til beboerne ved hjelp 
av lys og musikk. Alle komponentene er koblet til en treramme med forside av pleksiglass. 
 
## Hvordan har Motus forsøkt å møte behovene?
Brukergruppen har uttrykt behov for mer motivasjon i hverdagen. Å utføre aktiviteter oppfattes som kjedelig og beboerne opplever mas 
rundt det å bli påminnet av personalet hver dag. Motus kan hjelpe beboerne med struktur i hverdagen, der alle aktiviteter blir hengt opp 
og skannet inn. Beboerne ser i tillegg egen progresjon ved hjelp av lyslenken. Motus er verken kontrollerende eller masete, og beboerne 
velger selv hva de vil registrere inn. Å utføre aktiviteter kan nå bli sett på som morsomt, der belønningen musikk ved slutten av 
interaksjonen kan bidra til glede hos beboerne. Prototypen kan også være med på å eliminere mas og bidra til mer motivasjon gjennom en 
endret opplevelse av dagsplanlegging og gjennomførelse av ADL.
 
## Hvordan har Motus forsøkt å møte kravene?
Under designprosessen har vi forsøkt å lage en prototype som er oversiktlig for beboerne, der de selv kan planlegge dagen sin og dermed 
vise selvstendighet og selvbestemmelse. Motus er enkel å forstå, estetisk pen og lite plasskrevende, og gir feedback på interaksjonene. 
Dermed kan beboerne bli motiverte til å utføre aktiviteter. Feedback viser samtidig oversikt over progresjon i form av lyd og lys, og 
kan bidra til struktur i hverdagen til beboerne. Motus maser ikke, og lar beboerne heller planlegge dagen sin selv med positive 
feedbacks. Ved å bruke Motus kan beboerne få en endret opplevelse av teknologiske hjelpemidler, der de kan føle glede og motivasjon 
istedenfor mas og kontrollering. 
