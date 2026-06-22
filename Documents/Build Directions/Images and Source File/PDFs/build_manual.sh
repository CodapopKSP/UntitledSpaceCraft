#!/bin/bash

# Combine all PDFs
qpdf --empty --pages *.pdf -- combined.pdf

# Add page numbers
python3 script.py


rm combined.pdf