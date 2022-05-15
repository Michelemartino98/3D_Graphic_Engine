# -*- coding: utf-8 -*-
"""
Created on Fri May 13 18:09:43 2022

@author: zocco
"""

import numpy as np

MAX_coordinate = 0
extracted_text=[]
vertex=[]

"""SPECIFICARE IL PERCORSO DEL FILE STL CONVERTITO IN TXT"""
with open ('file_STL\Cubo.txt', 'rt') as file_STL : 
    for line in file_STL:    #prendo una riga alla volta del file .stl
        extracted_text.append( line )

"""verifico corretta estrazione del testo"""
i=0
for line in extracted_text:
    print(extracted_text[i])
    i=i+1
    
"""estraggo i vertici"""
for line in extracted_text :
    index = line.find("vertex")
    if( index!= -1 ):
        vertex.append(line.lstrip("  vertex")) #con lstrip elimino la parola "vertex" dalla riga
        
"""verifico corretta estrazione vertici"""
i=0
for line in vertex:
    print(vertex[i])
    i=i+1
        
"""splitto le righe in modo che da stringhe diventino liste"""
i=0
for line in vertex :
    vertex[i]=vertex[i].split()
    i=i+1
    
"""coverto numeri ascii in floating point"""
i=0
j=0
for i in range(len(vertex)):
    for j in range (3): 
        vertex[i][j]= float( vertex[i][j] )
        
"""valuto massimo valore coordinata"""
i=0
j=0
for i in range(len(vertex)):
    for j in range (3): 
        if ( vertex[i][j] > MAX_coordinate ):
            MAX_coordinate = vertex[i][j]

"""normalizzo"""
 #/////////////////////POTREBBE CAMBIARE//////////////////////////////
i=0
j=0
for i in range(len(vertex)):
    for j in range (3): 
        vertex[i][j]= vertex[i][j] / MAX_coordinate
        
"""trasposizione"""
vertex=np.array(vertex)
vertex=vertex.T


"""salvo file di testo contenente solo i vertici """

"""SPECIFICARE IL PERCORSO IN CUI SALVARE IL FILE CON VERTICI"""
np.savetxt("file_vertex/Cubo_vertex.txt", vertex , fmt="%1.3f")

"""apro il file generato sopra per aggiungere il numero di vertici"""

N_VERTEX = str((vertex.size/3))
with open ("file_vertex/Cubo_vertex.txt", 'at') as vertex_file : 
    vertex_file.write("N_VERTEX=")
    vertex_file.write(N_VERTEX )
    







