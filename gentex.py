#!/usr/bin/env python
# -*- coding: UTF-8 -*-
doc_class = '\documentclass[landscape, 8pt,twocolumn,oneside, a4paper]{article}'

head = '''\\title {NCTU\\_Jaguar Codebook}
\\usepackage{parskip}
\\usepackage{xeCJK} 
\\setCJKmainfont{Noto Sans CJK TC}
\\setmonofont{Courier New}
\\usepackage {listings}
\\usepackage {color}
\\usepackage[x11names]{xcolor}
\\usepackage [left=1.0cm, right=1.0cm, top=2.0cm, bottom=0.5cm]{geometry}
\\definecolor {mygreen}{rgb}{0,0.6,0}
\\definecolor {mygray}{rgb}{0.5,0.5,0.5}
\\definecolor {mymauve}{rgb}{0.58,0,0.82}
\\usepackage{fancyheadings}
\\rhead{\\thepage}
\\chead{init? array size? \\texttt{x, y}? overflow\\texttt{int}? 1-based? OK, Submit!}
\\lhead{NCTU\\_Jaguar}
\\pagestyle{fancy}
\\cfoot{}
\\setlength{\\headsep}{5pt}
\\setlength{\\textheight}{540pt}
'''

lstset = '''\\lstset {
    language=C++,                 % the language of the code
    basicstyle=\\footnotesize\\ttfamily,          % the size of the fonts that are used for the code
    numberstyle=\\footnotesize,          % the size of the fonts that are used for the line-numbers
    stepnumber=1,                 % the step between two line-numbers. If it's 1, each line  will be numbered
    numbersep=5pt,                  % how far the line-numbers are from the code
    backgroundcolor=\\color{white},        % choose the background color. You must add \\usepackage{color}
    showspaces=false,               % show spaces adding particular underscores
    showstringspaces=false,           % underline spaces within strings
    showtabs=false,               % show tabs within strings adding particular underscores
    frame=false,                    % adds a frame around the code
    tabsize=2,                    % sets default tabsize to 2 spaces
    captionpos=b,                 % sets the caption-position to bottom
    breaklines=true,                % sets automatic line breaking
    breakatwhitespace=false,            % sets if automatic breaks should only happen at whitespace
    escapeinside={\\%*}{*)},           % if you want to add a comment within your code
    morekeywords={*},               % if you want to add more keywords to the set
    keywordstyle=\\bfseries\\color{Blue1},
    commentstyle=\\itshape\\color{Red4},
    stringstyle=\\itshape\\color{Green4},
}
'''

doc_head = '''\\begin {document}
\\thispagestyle{fancy}
{ \\Huge NCTU\\_Jaguar}
\\tableofcontents
'''

tail = '''
\\end{document}
'''

src_types = ['.c', '.cpp', '.java', '.py', '.sublime-build', '.sublime-settings', '.sh', '.txt', '.h']

lang_list = {
  '.c': 'c',
  '.cpp': 'c++',
  '.java': 'java',
  '.py': 'python',
  '.sublime-build': 'bash',
  '.sublime-settings': 'bash',
  '.sh': 'bash',
  '.txt': 'c++',
  '.h': 'c++'
}

import os
import sys

def escape(s):
  spe = '#$%&_{}'
  for c in spe:
    s = s.replace(c, '\\'+c)
  return s

def capitalize(line):
    return ' '.join(s[0].upper() + s[1:] for s in line.split(' '))

outname = 'codebook.tex'
sys.stdout = open(outname, 'w')
print(doc_class)
print(head)
print(lstset)
print(doc_head)
for root, dirs, files in os.walk('code'):
  if root.find('.svn') >= 0:
    continue
  secname = os.path.basename(root)
  if secname.startswith('.'):
    continue
  if escape(secname) == 'code':
    continue
  section_name = capitalize(secname.replace('_', ' '))
  print(f'\\section{{{section_name}}}')
  for name in files:
    base, ext = os.path.splitext(name)
    if name != 'vimrc' and ext not in src_types:
      continue
    subsection_name = capitalize(base.replace('_', ' '))
    print(f'\\subsection{{{subsection_name}}}')
    if ext not in src_types:
      lang = 'bash'
    else:
      lang = lang_list[ext]
    print(f'\\lstinputlisting [language={lang}] {{\"code/{escape(secname)}/{name}\"}}')
print(tail)
sys.stdout.flush()
# subprocess.call(['bg5pdflatex', outname])
