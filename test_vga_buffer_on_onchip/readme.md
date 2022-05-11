il front buffer è nella onchip memory, il back e tutto il programma risiedono nella SDRAM
invece di fare la swap buffer, a fine schermo viene invocata la move buffer, che copia il contenuto del back buffer nel front buffer,
    in questo modo il front buffer sarà sempre nella onchip e il DMA non ha problemi ad accederci.
Infatti anche senza includere le inline assembly nop non ci sono glitch video.
Il problema principale  è che avendo tutto il codice nella sdram si ha un notevole rallentamento dell'elaborazione, rimanendo sui 40fps per renderizzare il cubo wireframe.
Non è stato provato, ma pare plausibile ritenere che aumentare il numero di vertici penalizzi fortemente questa soluzione.
L'unico vantaggio è che in compenso viene perso relativamente poco tempo nella parte di disegno effettivo e ciò permetterebbe di aumentare la risoluzione a 640\*480 senza troppe penalizzazioni,
    ma avendo un buffer nella onchip questo risulta impossibile in quanto non è abbastanza grande da contenere il buffer ad alta risoluzione.
