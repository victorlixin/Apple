#C+
# Copyright (C)  Microsoft Corporation.  All rights reserved.
# 
#
# THIS SOFTWARE IS PROVIDED ``AS IS'' BY MICROSOFT CORPORATION AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL MICROSOFT CORPORATION BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
#C-

#
# sys.mk:   BSD4.4 make's system default rules.
#           The POSIX.2/XPG4 default rules for make.
#
# This file is based on the macro definitions, etc. from X/Open's XCU4.2,
# make utility, p.489.
# It does not contain any of the extended SCCS rules and
# macros, however, these have been temporarily mapped to RCS constructs.
#

#
# RCSID = $Header: /E/interix/src/make.openbsd/mk.files/sys.mk,v 1.3 1996/08/23 21:35:24 mark Exp $
#

.SUFFIXES: .o .i .c .y .l .a .ksh .sh .f .c~ .y~ .l~ .sh~ .f~

MAKE=make
AR=ar
ARFLAGS=-rv
YACC=yacc
LEX=lex
LFLAGS=

LDFLAGS=

# C compiler
#
CC=c89
CFLAGS=-O

#
# SCCS rules (mapped to RCS for now)
#
GET=co
GFLAGS=
SCCSFLAGS=
SCCSGETFLAGS=-l

# Fortran not supported
#FC=fort77


.c:
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

.sh:
	cp $< $@
	chmod a+x $@

.ksh:
	cp $< $@
	chmod a+x $@


.c.o:
	$(CC) $(CFLAGS) -c $<

.c.i:
	$(CC) -P $(CFLAGS) $<

.y.o:
	$(YACC) $(YFLAGS) $<
	$(CC) $(CFLAGS) -c y.tab.c
	rm -f y.tab.c
	mv y.tab.o $@

.l.o:
	$(LEX) $(LFLAGS) $<
	$(CC) $(CFLAGS) -c lex.yy.c
	rm -f lex.yy.c
	mv lex.yy.o $@

.y.c:
	$(YACC) $(YFLAGS) $<
	mv y.tab.c $@

.l.c:
	$(LEX) $(LFLAGS) $<
	mv lex.yy.c $@


.o.a:
	$(AR) $(ARFLAGS) $@ $*.o
	rm -f $*.o

.c.a:
	$(CC) -c $(CFLAGS) $<
	$(AR) $(ARFLAGS) $@ $*.o
	rm -f $*.o
