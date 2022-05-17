# -*- coding: utf-8 -*-
"""
Created on Fri May 13 18:09:43 2022

@author: zocco
"""

"""Specificare il path da cui prendere il file STL e quello in cui salvare il file txt contenente i vertici"""

file_STL_path   = "file_STL\Sphericon.txt"
file_vertex_path= "file_vertex/Sphericon_vertex.txt"

import numpy as np
import re

MAX_coordinate = 0
extracted_text=[]
vertex=[]
triangles =[]

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

# salvo i parametri N_VERTEX e N_FACES come stringhe
N_VERTEX = int(float((vertex.size/4)))
N_FACES = int(float((float(N_VERTEX)/3)))

# calcolo l'array per i triangoli
triangles.append( "uint16_t faces[N_FACES][3] = {\n")
temp =  0;
for i in range(N_FACES):
    triangles.append("{"+(str(temp))+", "+(str(temp+1))+", "+(str(temp+2))+"},\n")
    temp+=3
triangles.append("};\n")

"""salvo file di testo contenente solo i vertici """

"""SPECIFICARE IL PERCORSO IN CUI SALVARE IL FILE CON VERTICI"""
np.savetxt( file_vertex_path, vertex , fmt="%1.3f")

"""apro il file generato sopra per aggiungere il numero di vertici"""

with open ( file_vertex_path, 'r') as vertex_file :
    buffer = vertex_file.readlines()

line_counter = 0
buffer
with open( file_vertex_path, 'w') as vertex_file:
    for line in buffer:
        if(line_counter == 0):
            vertex_file.write( '{' + '\n' + re.sub("\s", ", ", line, count = N_VERTEX ) + '\n' )
        elif( line_counter == 3 ) :
            vertex_file.write( re.sub("\s", ", ", line, count = N_VERTEX-1 ) + '}' + ';' )
        else :
            vertex_file.write( re.sub("\s", ", ", line, count = N_VERTEX ) + '\n')
        line_counter += 1
        
    vertex_file.write("\n")
    vertex_file.write("\n")
    vertex_file.write("N_VERTEX=")
    vertex_file.write(str(N_VERTEX))
    vertex_file.write("\n")
    vertex_file.write("N_FACES= ")
    vertex_file.write(str(N_FACES))
    vertex_file.write("\n")
    vertex_file.write("\n")

    c = 0

    for i in range(N_FACES+2):
        vertex_file.write(triangles[c])
        c = c + 1







