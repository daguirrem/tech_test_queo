import re

def qr_dni_get(raw: str) -> str:
    
    delimiter_pre = "COL"
    delimiter_pre_idx = 2 # Segundo COL de la cadena de texto
    
    delimiter_post = "<"

    # Almacena todas las posiciones donde se encuentra 'COL'
    ocurrenses_pre = [match.start() for match in re.finditer(delimiter_pre, raw)]

    # Índices delimitadores    
    index_pre = ocurrenses_pre[delimiter_pre_idx - 1] + len(delimiter_pre)
    index_post = raw[index_pre::].find(delimiter_post) + index_pre

    return raw[index_pre:index_post]
