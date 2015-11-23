										/* operators */
<xx>\\=				TC(EQ)				/* some = value */
<xx>\\[				TC(LQ)				/* [list begin */
<xx>\\]				TC(RQ)				/* list end] */
<xx>\\(				TC(LP)
<xx>\\)				TC(RP)
#<xx>\\<				TC(LL)
#<xx>\\>				TC(GG)
#<xx>\\:				TC(COLON)			/* some:pair */
#<xx>\\+				TC(ADD)
#<xx>\\-				TC(SUB)
#<xx>\\*				TC(MUL)
#<xx>\\/				TC(DIV)
#<xx>\\^				TC(POW)
