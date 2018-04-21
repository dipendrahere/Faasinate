import sys
import re


def makeTop(output=sys.stdout):
    # print out the file header
    header = '''
\\documentclass{article}
\\usepackage[hmargin=1in,vmargin=1in]{geometry}
\\usepackage{listings}
\\usepackage{color}
\\IfFileExists{lmodern.sty}{\\usepackage{lmodern}}{}
\\usepackage[T1]{fontenc}
\\usepackage[utf8]{inputenc}
\\lstset{
    numbers=left,               
    numberstyle=\\small \\ttfamily \\color[rgb]{0.4,0.4,0.4},
                
    showspaces=false,               
    showstringspaces=false,         
    showtabs=false,                 
    frame=lines,                    
    tabsize=4,                      
    breaklines=true,                
    breakatwhitespace=false,        
    basicstyle=\\ttfamily,
    %identifierstyle=\\color[rgb]{0.3,0.133,0.133},   
    keywordstyle=\\color[rgb]{0.133,0.133,0.6},
    commentstyle=\\color[rgb]{0.133,0.545,0.133},
    stringstyle=\\color[rgb]{0.627,0.126,0.941},
    language=%s
}
\\begin{document}
'''
#    print header
    sys.stdout.write(header + "\n")

def main():
    stri = sys.stdin.read()
    y = stri[:1]
    if y == "1":
        lang = "C++"
    elif y == "2":
        lang = "Python"
    else:
        lang = "Java"
    makeTop();
    stri = stri[1:]
    code = '''
\\begin{lstlisting}[language='''+lang+''']
'''
    code = code + stri
    code = code + '''
\end{lstlisting}
'''
    sys.stdout.write(code + "\n")
    sys.stdout.write("\\end{document}" + "\n")

if __name__ == "__main__":
    main()
