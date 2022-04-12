# directory progetto:
    hardware
    software
    Sopc 

# istruzioni
in sopc ci sono i file necessari per ricostruire il progetto nel proprio computer:
1) con il .qsys dal platform designer generare il .sopcinfo e il .qip con generate hdl, inserendo come directory \hardware
2) su quartus a partire dal top level.v e dal file .qip(generato prima) generare il .sof
3) caricare il .sof sulla scheda[altrimenti si può usare quello presente in Sopc, per non aspettare il tempo di compilazione]
4) creare il proprio progetto su Eclipse, usando come cartella di progetto \software, con il .sopcinfo ottenuto prima.
5) aggiornare la vista su eclipse con F5 e verificare che i file sorgente siano caricati correttamente
6) creare il file sorgenti solo in software/src e software/inc e caricare solo quelli si git
7) se si fanno modifiche al computer sostituire i file utili all'interno della cartella  Sopc, e avvisare gli altri così che possano ricreare il loro computer

tutto questo perchè eclipse è stupido, fa percorsi assoluti e se prendi i file generati da un altro il progetto si rompe!!!!
