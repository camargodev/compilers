# João Vi4tor de Camargo (274722) e Marcellus Farias (281984)

CC     = gcc
PART   = etapa5
EXEC   = ./${PART}
FLAGS  = -g -c
LFLAGS = -g -o
BFLAGS = -d

TST  = tests
SRC  = src
LIB  = include
SCP  = scripts

SCN  = scanner
PSR  = parser
LXM  = lexeme
TBL  = table
TREE = tree
ERR  = error
CNV  = conversions
ILOC = iloc
CDS  = codes
MAIN = main
ITST = iloc_test
LEX  = lex.yy

SYNTEST  = ${TST}/syntest.txt

SCNFONT  = ${SCN}.l
SCNFLEX  = ${LEX}.c
PSRFONT  = ${PSR}.y
PSRBISON = ${PSR}.tab.c
LXMFONT  = ${SRC}/${LXM}.c
TBLFONT  = ${SRC}/${TBL}.c
TREEFONT = ${SRC}/${TREE}.c
ERRFONT  = ${SRC}/${ERR}.c
CNVFONT  = ${SRC}/${CNV}.c
ILOCFONT = ${SRC}/${ILOC}.c
CDSFONT  = ${SRC}/${CDS}.c
MAINFONT = ${SRC}/${MAIN}.c
ITSTFONT = ${TST}/${ITST}.c

SCNGEN  = ${LEX}.o
PSRGEN  = ${PSR}.tab.o
LXMGEN  = ${LXM}.o
TBLGEN  = ${TBL}.o
TREEGEN = ${TREE}.o
ERRGEN  = ${ERR}.o
CNVGEN  = ${CNV}.o
ILOCGEN = ${ILOC}.o
CDSGEN  = ${CDS}.o
MAINGEN = ${MAIN}.o
ITSTGEN = ${ITST}.o

PSRLIB  = ${PSR}.tab.h
LXMLIB  = ${LIB}/${LXM}.h
TBLLIB  = ${LIB}/${TBL}.h
TREELIB = ${LIB}/${TREE}.h
ERRLIB  = ${LIB}/${ERR}.h
CNVLIB  = ${LIB}/${CNV}.h
ILOCLIB = ${LIB}/${ILOC}.h
CDSLIB  = ${LIB}/${CDS}.h

SEMTST  = ${SCP}/sem_test.sh
LKTST   = ${SCP}/leak_test.sh
RESULTS = ${TST}/results.txt
TMPRES  = ${TST}/tempresults.txt

OUTPUT  = ${PSR}.output
LKTMP   = tmplk.txt

all: parser scanner main lexeme tree table error conversions
	${CC} ${LFLAGS} ${PART} ${PSRGEN} ${SCNGEN} ${MAINGEN} ${LXMGEN} ${TREEGEN} ${TBLGEN} ${ERRGEN} ${CNVGEN} -lfl

parser: ${PSRFONT}
	bison ${BFLAGS} ${PSRFONT}
	${CC} ${FLAGS} ${PSRBISON}

scanner: ${SCNFONT}
	flex ${SCNFONT}
	${CC} ${FLAGS} ${SCNFLEX}

main: ${MAINFONT}
	${CC} ${FLAGS} ${MAINFONT}

lexeme: ${LXMFONT} ${LXMLIB}
	${CC} ${FLAGS} ${LXMFONT}

tree: ${TREEFONT} ${TREELIB} ${LXMLIB}
	${CC} ${FLAGS} ${TREEFONT}

table: ${TBLFONT} ${TBLLIB} ${LXMLIB}
	${CC} ${FLAGS} ${TBLFONT}

error: ${ERRFONT} ${ERRLIB}
	${CC} ${FLAGS} ${ERRFONT}

conversions: ${CNVFONT} ${CNVLIB}
	${CC} ${FLAGS} ${CNVFONT}

semtest: ${EXEC} ${SEMTST} ${RESULTS}
	${SEMTST}
	diff ${RESULTS} ${TMPRES}

syntest: ${EXEC} ${SYNTEST}
	${EXEC} < ${SYNTEST} > r.txt
	${EXEC} < r.txt      > s.txt
	diff r.txt s.txt
	rm -f r.txt
	rm -f s.txt

lktst: ${EXEC} ${LKTST}
	${LKTST}

iloctst: ciloc codes mainiloc
	gcc ${LFLAGS} ${ILOC} ${ILOCGEN} ${CDSGEN} ${ITSTGEN}

ciloc: ${ILOCFONT} 
	${CC} ${FLAGS} ${ILOCFONT}

codes: ${CDSFONT}
	${CC} ${FLAGS} ${CDSFONT}

mainiloc: ${ITSTFONT}
	${CC} ${FLAGS} ${ITSTFONT}	

clean:
	rm -f ${EXEC}
	rm -f ${PSRBISON}
	rm -f ${PSRGEN}
	rm -f ${PSRLIB}
	rm -f ${SCNFLEX}
	rm -f ${SCNGEN}
	rm -f ${MAINGEN}
	rm -f ${LXMGEN}
	rm -f ${TBLGEN}
	rm -f ${TREEGEN}
	rm -f ${ERRGEN}
	rm -f ${CNVGEN}
	rm -f ${TMPRES}
	rm -f ${ILOC}
	rm -f ${ILOCGEN}
	rm -f ${CDSGEN}
	rm -f ${ITSTGEN}
	rm -f ${OUTPUT}
	rm -f ${LKTMP}