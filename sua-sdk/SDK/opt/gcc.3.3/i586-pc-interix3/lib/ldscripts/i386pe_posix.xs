/* Script for ld --shared: link shared library */
OUTPUT_FORMAT(pei-i386)
SEARCH_DIR("/opt/gcc.3.3/i586-pc-interix3/lib"); SEARCH_DIR("/opt/gcc.3.3/lib"); SEARCH_DIR("/usr/local/lib"); SEARCH_DIR("/usr/lib/"); SEARCH_DIR("/lib"); SEARCH_DIR("/usr/lib"); SEARCH_DIR("/usr/lib/x86");
ENTRY(___PosixProcessStartup)
/* if DYNAMIC_LINKING [ */
/* Not sure yet */
/* Do we need any of these for elf?
   __DYNAMIC = 0;    */
/* end DYNAMIC_LINKING ] */
SECTIONS
{
  .text  __section_alignment__  :
  {
     *(.init)
    *(.text)
    *(SORT(.text$*))
    *(.glue_7t)
    *(.glue_7)
    . = ALIGN(4);
    /* collect constructors only for final links */
        LONG (-1)
        KEEP (*(.ctor_head))
	KEEP (*(SORT(.ctors.*)))   /* Here we sort by section name! */
        KEEP (*(.ctors))
        KEEP (*(.ctor))
        LONG (0)
        LONG (-1)
        KEEP (*(.dtor_head))
	KEEP (*(SORT(.dtors.*)))
        KEEP (*(.dtors))
        KEEP (*(.dtor))
        LONG (0)
     *(.fini)
    /* ??? Why is .gcc_exc here?  */
     *(.gcc_exc)
     etext = .;
    *(.gcc_except_table)
  }
  /* The Cygwin32 library uses a section to avoid copying certain data
     on fork.  This used to be named ".data".  The linker used
     to include this between __data_start__ and __data_end__, but that
     breaks building the cygwin32 dll.  Instead, we name the section
     ".data_cygwin_nocopy" and explictly include it after __data_end__. */
  .data BLOCK(__section_alignment__) :
  {
    __data_start__ = . ;
    *(.data)
    *(.data2)
    *(SORT(.data$*))
    __data_end__ = . ;
    *(.data_cygwin_nocopy)
  }
  .rdata BLOCK(__section_alignment__) :
  {
    *(.rdata)
    *(SORT(.rdata$*))
    *(.eh_frame)
    /* DYNAMIC_LINKING [ */
    *(.hash)
    *(.interp)
    /* ] */
    ___RUNTIME_PSEUDO_RELOC_LIST__ = .;
    __RUNTIME_PSEUDO_RELOC_LIST__ = .;
    *(.rdata_runtime_pseudo_reloc)
    ___RUNTIME_PSEUDO_RELOC_LIST_END__ = .;
    __RUNTIME_PSEUDO_RELOC_LIST_END__ = .;
  }
  .pdata BLOCK(__section_alignment__) :
  {
    *(.pdata)
  }
/* if DYNAMIC_LINKING [ */
  .got    BLOCK(__section_alignment__)  :
  {
     *(.got.plt)
     *(.got)
  }
/* end DYNAMIC_LINKING ] */
/* .idata must precede bss so file and code offsets remain the same for .sos */
/* (At least for now... using Ldr* routines may fix.) */
  .idata BLOCK(__section_alignment__) :
  {
    /* This cannot currently be handled with grouped sections.
	See pe.em:sort_sections.  */
    SORT(*)(.idata$2)  /* here we sort by filename! */
    SORT(*)(.idata$3)
    /* These zeroes mark the end of the import list.  */
    LONG (0); LONG (0); LONG (0); LONG (0); LONG (0);
    SORT(*)(.idata$4)
    SORT(*)(.idata$5)
    SORT(*)(.idata$6)
    SORT(*)(.idata$7)
  }
  .bss BLOCK(__section_alignment__) :
  {
    __bss_start__ = . ;
/* DYNAMIC_LINKING */
    *(.dynbss)
/* end DYNAMIC_LINKING */
    *(.bss)
    *(COMMON)
    __bss_end__ = . ;
  }
  .edata BLOCK(__section_alignment__) :
  {
    *(.edata)
  }
  /DISCARD/ :
  {
    *(.debug$S)
    *(.debug$T)
    *(.debug$F)
    *(.drectve)
  }
  .CRT BLOCK(__section_alignment__) :
  {
    *(SORT(.CRT$*))
  }
  .endjunk BLOCK(__section_alignment__) :
  {
    /* end is deprecated, don't use it */
     end = .;
     _end = .;
     __end__ = .;
  }
/* DYNAMIC_LINKING [  // XXX below, rela??? */
  /* // ??? .dynamic    : { */
  .dynamic     BLOCK(__section_alignment__) : {
    *(.dynamic)
  }
  .dynsym     BLOCK(__section_alignment__)  : {
    *(.dynsym)
  }
  .dynstr     BLOCK(__section_alignment__)  : {
    *(.dynstr)
  }
  .gnu.version     BLOCK(__section_alignment__)  : {
    *(.gnu.version)
  }
  .gnu.version_d     BLOCK(__section_alignment__)  : {
    *(.gnu.version_d)
  }
  .gnu.version_r     BLOCK(__section_alignment__)  : {
    *(.gnu.version_r)
  }
  .rel.dyn     BLOCK(__section_alignment__)  :
  {
    *(.rel.internal)
    *(.rel.got)
    *(.rel.plt)
  }
  .rela.dyn     BLOCK(__section_alignment__)  :
  {
    *(.rela.*)
  }
  .init     BLOCK(__section_alignment__)  : {
    *(.init)
  } =0
/* end DYNAMIC_LINKING ] */
  .rsrc BLOCK(__section_alignment__) :
  {
    *(.rsrc)
    *(SORT(.rsrc$*))
  }
  .reloc BLOCK(__section_alignment__) :
  {
    *(.reloc)
  }
  .stab BLOCK(__section_alignment__) (NOLOAD) :
  {
    [ .stab ]
  }
  .stabstr BLOCK(__section_alignment__) (NOLOAD) :
  {
    [ .stabstr ]
  }
}
