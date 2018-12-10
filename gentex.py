#!/usr/bin/env python
# -*- coding: UTF-8 -*-
head = '''
\\input{header.tex}
'''

tail = '''
\\input{note.tex}
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
print(head)
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
