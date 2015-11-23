										/* numbers */
<xx>0x[0-9A-F]+				TX(Hex,NUM)	/* hexadecimal int */
<xx>0b[01]+					TX(Bin,NUM)	/* binary int */
<xx>{S}{N}\\.{N}[eE]{S}{N}	TX(Num,NUM)	/* exponential */
<xx>{S}{N}[eE]{S}{N}		TX(Num,NUM)	/* exponential */
<xx>{S}{N}\.{N}				TX(Num,NUM)	/* float */
<xx>{S}{N}					TX(Int,NUM)	/* integer */
