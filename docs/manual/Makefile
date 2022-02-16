all: manual

manual:
	pdflatex -f manual.tex
	bibtex manual.aux
	pdflatex -f  manual.tex

clean:
	rm -rf *.acn
	rm -rf *.aux
	rm -rf *.ist
	rm -rf *.log
	rm -rf *.lof
	rm -rf *.toc
	rm -rf *.out
	rm -rf *.lot

