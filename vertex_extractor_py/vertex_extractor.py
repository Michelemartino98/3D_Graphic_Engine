# -*- coding: utf-8 -*-
"""
Created on Fri May 13 18:09:43 2022

@author: zocco
"""

"""Specificare il path da cui prendere il file STL e quello in cui salvare il file txt contenente i vertici"""

file_STL_path   = "file_STL\Cubo.txt"
file_vertex_path= "file_vertex/Cubo_vertex.txt"

import numpy as np

MAX_coordinate = 0
extracted_text=[]
vertex=[]

"""SPECIFICARE IL PERCORSO DEL FILE STL CONVERTITO IN TXT"""
with open (file_STL_path, 'rt') as file_STL : 
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
i=0
j=0
vertex=np.array(vertex)
for i in range(len(vertex)):
    for j in range (3): 
        vertex[i][j]= vertex[i][j] / MAX_coordinate

"""trasposizione e aggiungo una riga di 1 che rappresenta la coordinata w dei vertici"""
i=0
w=np.array([])
for i in range(len(vertex)):
    w=np.append(w,1)
    
vertex=vertex.T
vertex=np.vstack([vertex,w])


"""salvo file di testo contenente solo i vertici """

"""SPECIFICARE IL PERCORSO IN CUI SALVARE IL FILE CON VERTICI"""
np.savetxt( file_vertex_path, vertex , fmt="%1.3f")

"""apro il file generato sopra per aggiungere il numero di vertici"""

N_VERTEX = str(int(float(vertex.size/4)))
with open ( file_vertex_path, 'at') as vertex_file : 
    vertex_file.write("N_VERTEX=")
    vertex_file.write( N_VERTEX )
    







